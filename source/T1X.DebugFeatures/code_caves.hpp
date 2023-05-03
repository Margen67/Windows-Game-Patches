#include "helper.hpp"

#define MEM_TYPE 0x25 // TODO: Check this heap type

#define FUNCTION_PTR(return_type, func_name, func_addr, ...) \
    typedef return_type (*func_name##_t)(__VA_ARGS__); \
    func_name##_t func_name = (func_name##_t)(func_addr);

#define STRING_SIZEOF(str) sizeof(str) / sizeof(const char*)

extern uint64_t Memory_PushAllocatorReturnAddr;
extern uint64_t Memory_NewHandlerReturnAddr;
extern uint64_t GivePlayerWeapon_MainReturn;
extern uint64_t GivePlayerWeapon_SubReturn;
extern uint64_t GivePlayerWeapon_EntryReturn;
extern uint64_t Game_SnprintfAddr;
extern uint64_t ScriptLookupAddr;
extern uint64_t PlayerPtrAddr;

void __attribute__((naked)) Memory_PushAllocator_CC();
void __attribute__((naked)) Memory_NewHandler_CC();
void __attribute__((naked)) GivePlayerWeapon_MainCC();
void __attribute__((naked)) GivePlayerWeapon_SubCC();
void __attribute__((naked)) GivePlayerWeapon_EntryCC();
void __attribute__((naked)) GetPlayerPtrAddr_CC();
const char* ScriptPrintWarn_CC(const char* ret, const char* fmt, ...);
void MakeMeleeMenu(uintptr_t menu_structure);
