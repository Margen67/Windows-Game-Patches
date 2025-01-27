#include "stdafx.h"
#include "helper.hpp"
#include "memory.hpp"

bool bLoggingEnabled;
FILE* fp_log;
std::time_t current_time;
struct tm timeinfo;

void log_time(void)
{
    wchar_t wtime[256];
    if (localtime_s(&timeinfo, &current_time) == 0 && std::wcsftime(wtime, _countof(wtime), L"%A %c", &timeinfo))
        fwprintf_s(fp_log, L"%-32s ", wtime);
}

void file_log(const wchar_t* fmt, ...)
{
    if (!bLoggingEnabled || !fp_log)
        return;
    log_time();
    va_list args;
    va_start(args, fmt);
    vfwprintf_s(fp_log, fmt, args);
    va_end(args);
}

void file_log2(const wchar_t* fmt, ...)
{
    if (!bLoggingEnabled || !fp_log)
        return;
    va_list args;
    va_start(args, fmt);
    vfwprintf_s(fp_log, fmt, args);
    va_end(args);
}

const wchar_t* GetBoolStr(bool input_bool)
{
    return input_bool ? L"true" : L"false";
}

void LoggingInit(const wchar_t* Project_Name, const wchar_t* Project_Log_Name)
{
    errno_t file_stat = _wfopen_s(&fp_log, Project_Log_Name, L"w+, ccs=UTF-8");
    if (file_stat == 0)
    {
        bLoggingEnabled = true;
        std::locale::global(std::locale("en_US.utf8"));
        current_time = std::time(nullptr);
        LOG(L"Log file opened at %s\n", Project_Log_Name);
    }
    else
    {
        bLoggingEnabled = false;
        wchar_t errorText[256] = { 0 };
        wchar_t errorMsg[512] = { 0 };
        _wcserror_s(errorText, _countof(errorText), file_stat);
        _snwprintf_s(errorMsg, _countof(errorMsg), _TRUNCATE, L"Failed to open log file. (%s)\nError code: %i (0x%x) %s", Project_Log_Name, file_stat, file_stat, errorText);
        MessageBox(0, errorMsg, Project_Name, MB_ICONWARNING);
    }
}

void ShowPatchInfo(size_t Patch_Size, uint64_t Patch_Addr, const wchar_t* Patch_Name, uint64_t Patch_Function_Target)
{
    LOG(L"Patch Name: %s\n", Patch_Name);
    LOG(L"Patch length: %llu bytes\n", Patch_Size);
    LOG(L"Patch address: 0x%016llx\n", Patch_Addr);
    if (Patch_Function_Target)
        LOG(L"Patch Function Target: 0x%016llx\n", Patch_Function_Target);
}

void LogPatchFailed(const wchar_t* Patch_Name, const wchar_t* Patch_Pattern)
{
    LOG(L"%s Pattern Scan Failed. Please adjust your scan patterns and try again\n", Patch_Name);
    LOG(L"Pattern %s\n", Patch_Pattern);
}

uintptr_t WritePatchPattern(const wchar_t* Patch_Pattern, const unsigned char* Patch_Bytes, size_t Patch_Size, const wchar_t* Patch_Name, uint64_t Patch_Offset)
{
    uint8_t* Address_Result = Memory::PatternScanW(baseModule, Patch_Pattern);
    uintptr_t Patch_Address = 0;
    if (Address_Result)
    {
        Patch_Address = (uintptr_t)Address_Result + Patch_Offset;
        Memory::PatchBytes(Patch_Address, Patch_Bytes, Patch_Size);
        ShowPatchInfo(Patch_Size, Patch_Address, Patch_Name, 0);
        return Patch_Address;
    }
    else
    {
        LogPatchFailed(Patch_Name, Patch_Pattern);
        return 0;
    }
    return 0;
}

void WritePatchPattern_Hook(const wchar_t* Patch_Pattern, size_t Patch_Size, const wchar_t* Patch_Name, uint64_t Patch_Offset, void* Function_Target, uint64_t* Return_Address)
{
    uint8_t* Address_Result = nullptr;
    Address_Result = Memory::PatternScanW(baseModule, Patch_Pattern);
    uint64_t Patch_Address = 0;
    if (Address_Result)
    {
        Patch_Address = (uintptr_t)Address_Result + Patch_Offset;
        if (Return_Address)
        {
            *Return_Address = Patch_Address + Patch_Size;
            LOG(L"%s Hook Info:\n", Patch_Name);
            LOG(L"Start address: 0x%016llx\n", Address_Result);
            LOG(L"Return address: 0x%016llx\n", *Return_Address);
            LOG(L"Function target address: 0x%016llx\n", uintptr_t(Function_Target));
        }
        else
        {
            LOG(L"%s Hook does not contain a returning address\n", Patch_Name);
            LOG(L"Start address: 0x%016llx\n", Address_Result);
            LOG(L"Function target address: 0x%016llx\n", uintptr_t(Function_Target));
            LOG(L"Please make sure it is intentional\n");
        }
        Memory::DetourFunction64((void*)(Patch_Address), Function_Target, Patch_Size);
    }
    else
    {
        LogPatchFailed(Patch_Name, Patch_Pattern);
    }
}

void WritePatchPattern_Int(uint32_t mode, const wchar_t* Patch_Pattern, void* Patch_Value, const wchar_t* Patch_Name, uint64_t Patch_Offset)
{
    switch (mode)
    {
        case 1:
        {
            unsigned char bytes_array[1] = { 0 };
            memcpy((void*)bytes_array, &Patch_Value, sizeof(bytes_array));
            WritePatchPattern(Patch_Pattern, bytes_array, sizeof(bytes_array), Patch_Name, Patch_Offset);
            memset(bytes_array, 0, sizeof(bytes_array));
            break;
        }
        case 2:
        {
            unsigned char bytes_array[2] = { 0 };
            memcpy((void*)bytes_array, &Patch_Value, sizeof(bytes_array));
            WritePatchPattern(Patch_Pattern, bytes_array, sizeof(bytes_array), Patch_Name, Patch_Offset);
            memset(bytes_array, 0, sizeof(bytes_array));
            break;
        }
        case 4:
        {
            unsigned char bytes_array[4] = { 0 };
            memcpy((void*)bytes_array, &Patch_Value, sizeof(bytes_array));
            WritePatchPattern(Patch_Pattern, bytes_array, sizeof(bytes_array), Patch_Name, Patch_Offset);
            memset(bytes_array, 0, sizeof(bytes_array));
            break;
        }
        case 8:
        {
            unsigned char bytes_array[8] = { 0 };
            memcpy((void*)bytes_array, &Patch_Value, sizeof(bytes_array));
            WritePatchPattern(Patch_Pattern, bytes_array, sizeof(bytes_array), Patch_Name, Patch_Offset);
            memset(bytes_array, 0, sizeof(bytes_array));
            break;
        }
    }
}

void WritePatchAddress(uint64_t Patch_Address, const unsigned char* Patch_Bytes, size_t Patch_Size, const wchar_t* Patch_Name, uint64_t Patch_Offset)
{
    uint64_t Patch_Address_Offset = Patch_Address + Patch_Offset;
    Memory::PatchBytes(Patch_Address_Offset, Patch_Bytes, Patch_Size);
    ShowPatchInfo(Patch_Size, Patch_Address_Offset, Patch_Name, 0);
}

wchar_t* GetRunningPath(wchar_t* output)
{
    GetModuleFileNameW(nullptr, output, MAX_PATH);
    PathRemoveFileSpecW(output);
    return output;
}

wchar_t* ConvertToWideChar(const char* input)
{
    int length = MultiByteToWideChar(CP_UTF8, 0, input, -1, nullptr, 0);
    if (length == 0)
    {
        return nullptr;
    }
    wchar_t* output = new wchar_t[length];
    MultiByteToWideChar(CP_UTF8, 0, input, -1, output, length);
    return output;
}

uintptr_t FindAndPrintPatternW(const wchar_t* Patch_Pattern, const wchar_t* Pattern_Name, size_t offset)
{
    size_t Address_Result = (size_t)Memory::PatternScanW(baseModule, Patch_Pattern);
    size_t Patch_Address = 0;
    if (Address_Result)
    {
        if (offset)
        {
            Patch_Address = offset + Address_Result;
            LOG(L"%s: 0x%016llx - 0x%llx = 0x%016llx\n", Pattern_Name, Address_Result, offset, Patch_Address);
        }
        else
        {
            Patch_Address = Address_Result;
            LOG(L"%s: 0x%016llx\n", Pattern_Name, Patch_Address);
        }
        return Patch_Address;
    }
    else
    {
        LogPatchFailed(Pattern_Name, Patch_Pattern);
    }
    return 0;
}

void Make32to64Hook(void* source_target, void* second_jmp, void* target_jmp, uint32_t source_size, const wchar_t* source_name, const wchar_t* second_jmp_name, const wchar_t* target_jmp_name)
{
    Memory::DetourFunction32((void*)source_target, (void*)second_jmp, source_size);
    LOG(L"Created jump %s (0x%016llx) to %s (0x%016llx)\n", source_name, (uintptr_t)source_target, second_jmp_name, (uintptr_t)second_jmp);
    Memory::DetourFunction64((void*)second_jmp, (void*)target_jmp, 14);
    LOG(L"Created jump %s (0x%016llx) to %s (0x%016llx)\n", second_jmp_name, (uintptr_t)second_jmp, target_jmp_name, (uintptr_t)target_jmp);
}
