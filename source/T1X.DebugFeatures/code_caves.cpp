#include "code_caves.hpp"
#include "memory.hpp"

uint64_t Memory_PushAllocatorReturnAddr = 0;
void __attribute__((naked)) Memory_PushAllocator_CC() {
    __asm {
        // code by infogram
        cmp eax, 0x10 // Debug DMENU
        je retail_memory_type
            // extra check
        cmp eax, 0xa  // Debug CPU Memory
        jnz ret_loc
        retail_memory_type :
        mov eax, MEM_TYPE
        mov dword ptr [rcx], eax
            // original code
        ret_loc :
        lea rcx, [rsp + 0x30]
        mov dword ptr[rsp + 0x30], eax
        mov r15, r9
        mov r14d, r8d
        jmp[Memory_PushAllocatorReturnAddr]
    }
}

const char* weapon_list_main[] = {"invisible-cube",
                                  "pistol-shotgun-military",
                                  "bloater-pustule",
                                  "pistol-colt-1911-dark",
                                  "bow-joel",
                                  "shiv-d",
                                  "invisible-cube",
                                  "bandage-autofeed",
                                  "rifle-vepr",
                                  "pistol-uber-hunter",
                                  "invisible-cube",
                                  "rifle-m14-sniper",
                                  "bow-ellie",
                                  "invisible-cube",
                                  "invisible-cube",
                                  "bow-ellie",
                                  "pistol-revolver-taurus",
                                  "rifle-m14-sniper",
                                  "bow-scar",
                                  "rifle-mpx5",
                                  "two-hand-axe",
                                  "molotov",
                                  "digital-recorder-carry-t1x",
                                  "club-2h-scar",
                                  "rifle-remington-81",
                                  "hammer-modern",
                                  "pipe-bomb",
                                  "pistol-9mm-firefly",
                                  "gas-mask-lev",
                                  "mp-spotting-scope",
                                  "pistol-revolver-taurus",
                                  "rifle-m14-sniper",
                                  "shotgun-pump-stock",
                                  "pipe-wrench",
                                  "shotgun-remington-pump",
                                  "t1x-shotgun-remington-pump",
                                  "hammer-scar",
                                  "rifle-mini-14-manny",
                                  "flamethrower",
                                  "invisible-cube",
                                  "club-1h-police",
                                  "baseball-bat",
                                  "invisible-cube",
                                  "shiv-b",
                                  "invisible-cube",
                                  "shotgun-pump-firefly",
                                  "pistol-browning",
                                  "rifle-mini-14",
                                  "shotgun-pump-stock",
                                  "baseball-bat-metal",
                                  "bow-lev",
                                  "pistol-shotgun-firefly",
                                  "pistol-uber-firefly",
                                  "m4-rifle-military",
                                  "pickaxe-scar-player",
                                  "ski-aquarium-dog-toy",
                                  "knife-bill-game",
                                  "hatchet-tomahawk",
                                  "short-pipe",
                                  "pistol-revolver-taurus-owen",
                                  "pistol-revolver-scar",
                                  "stun-bomb",
                                  "pistol-ruger",
                                  "rifle-galil",
                                  "rifle-m14-sniper",
                                  "invisible-cube",
                                  "m4-rifle-firefly",
                                  "torch-game",
                                  "invisible-cube",
                                  "bow-ellie",
                                  "molotov",
                                  "machete-wood-joel",
                                  "pistol-xcaliber",
                                  "invisible-cube",
                                  "shiv-f",
                                  "t1x-leather-toolkit",
                                  "pistol-colt-defender",
                                  "shotgun-remington-pump-sawedoff",
                                  "two-hand-axe-scar",
                                  "shotgun-dbl-barrel-scar",
                                  "rifle-vepr",
                                  "rifle-m14-dark",
                                  "rifle-mini-14-wood",
                                  "club-1h-scar",
                                  "bandage-autofeed",
                                  "bow-scar",
                                  "rifle-bolt-firefly",
                                  "pistol-cz75",
                                  "shiv-a",
                                  "pistol-revolver-taurus-owen",
                                  "pistol-9mm-military",
                                  "pistol-beretta",
                                  "invisible-cube",
                                  "invisible-cube",
                                  "invisible-cube",
                                  "fob-basketball",
                                  "rifle-bolt-m24",
                                  "pistol-ruger",
                                  "throw-brick",
                                  "NO_ART_GROUP",
                                  "machete-black",
                                  "bloater-pustule",
                                  "rifle-ruger-scar",
                                  "smoke-bomb",
                                  "machete-scar",
                                  "rifle-winchester-lever",
                                  "shotgun-remington-pump-sawedoff",
                                  "lead-pipe",
                                  "pistol-ruger",
                                  "t1x-shiv-mod-a",
                                  "pistol-shotgun-hunter",
                                  "amp-gift-shop-toy-orca",
                                  "pistol-revolver-firefly",
                                  "molotov",
                                  "smoke-bomb-basic",
                                  "beer-bottle",
                                  "machete-black",
                                  "shotgun-pump-stock-black",
                                  "pipe-bomb",
                                  "crossbow",
                                  "bloater-pustule",
                                  "shotgun-baserri-over-under",
                                  "bloater-pustule",
                                  "pistol-colt-1911-silver",
                                  "pickaxe-scar",
                                  "shotgun-remington-pump",
                                  "rifle-m14-sniper",
                                  "bow-toy",
                                  "shiv-e",
                                  "rifle-sniper-hunter",
                                  "pistol-revolver-357",
                                  "syringe",
                                  "rifle-remington-81",
                                  "scythe-scar",
                                  "hatchet-black",
                                  "crowbar-one-hand",
                                  "hatchet-modern",
                                  "shotgun-remington-pump-black",
                                  "dagger-scar-lev",
                                  "trap-mine",
                                  "invisible-cube",
                                  "rifle-remington-81",
                                  "two-by-four",
                                  "shotgun-dbl-barrel-abby",
                                  "rifle-bolt-m24-dark",
                                  "firecracker",
                                  "oil-can-silencer",
                                  "shotgun-remington-pump",
                                  "rifle-mpx5-tilt",
                                  "short-pipe",
                                  "t1x-turret-sniper",
                                  "t1x-shiv",
                                  "molotov",
                                  "whistle",
                                  "rifle-mpx5",
                                  "dagger-scar",
                                  "NO_ART_GROUP",
                                  "NO_ART_GROUP",
                                  "pistol-glock",
                                  "hatchet-tomahawk",
                                  "machete-wood",
                                  "pistol-cz75-black",
                                  "rifle-bolt-m24",
                                  "pat-snowball",
                                  "pistol-browning-scar",
                                  "sledgehammer",
                                  "fireman-axe",
                                  "shiv-c",
                                  "pistol-revolver-militia",
                                  "pistol-revolver-military",
                                  "t1x-shiv-mod-b",
                                  "pistol-9mm-hunter",
                                  "rifle-semi-auto-firefly",
                                  "rifle-bolt-scar",
                                  "hatchet-scar",
                                  "rifle-remington-bolt",
                                  "tennis-ball-throw",
                                  "t1x-leather-toolkit"};

const char* weapon_list_subsection[] = {"invisible-cube",
                                        "",
                                        "bandage-autofeed",
                                        "bandage-autofeed",
                                        "throw-brick",
                                        "beer-bottle",
                                        "nail-bomb-basic",
                                        "molotov-basic",
                                        "smoke-bomb-basic",
                                        "t1x-mal-gas-can",
                                        "pistol-t1x-beretta-jaguar-pistol",
                                        "t1x-bow-ellie",
                                        "t1x-rifle-bolt-m24",
                                        "rifle-shotgun-pump-hunter",
                                        "pistol-revolver-hunter",
                                        "rifle-bolt-hunter",
                                        "t1x-super-soaker",
                                        "t1x-pistol-9mm",
                                        "t1x-taurus-66b4-revolver",
                                        "t1x-pistol-uber-t1",
                                        "t1x-pistol-shotgun",
                                        "t1x-rifle-bolt",
                                        "t1x-m4-rifle-t1",
                                        "t1x-shotgun-pump-stock",
                                        "t1x-bow-dark",
                                        "t1x-flamethrower",
                                        "t1x-super-soaker",
                                        "t1x-machete-blade",
                                        "t1x-hatchet",
                                        "t1x-baseball-bat",
                                        "t1x-two-by-four",
                                        "t1x-lead-pipe",
                                        "invisible-cube",
                                        "t1x-switchblade"};

const char* weapon_subentry_names[] = {"Misc", "Consumables", "Throwables", "Ellie", "Joel", "Melee"};

const constexpr uint32_t GivePlayerWeapon_ListMax = sizeof(weapon_list_main) / sizeof(weapon_list_main[0]);
const constexpr uint32_t GivePlayerWeapon_SubListMax = sizeof(weapon_list_subsection) / sizeof(weapon_list_subsection[0]);
const constexpr uint32_t GivePlayerWeapon_EntryListMax = sizeof(weapon_subentry_names) / sizeof(weapon_subentry_names[0]);

// Main list
uint32_t GivePlayerWeapon_index_count = 0;
uint64_t GivePlayerWeapon_MainReturn = 0;
// Sub entry
uint32_t GivePlayerWeaponSub_index_count = 0;
uint64_t GivePlayerWeapon_SubReturn = 0;
// Entry
uint32_t GivePlayerWeaponEntry_index_count = 0;
uint64_t GivePlayerWeapon_EntryReturn = 0;

// Game funcs
uint64_t ScriptLookupAddr = 0;

char temp_str[128];

const char* GivePlayerWeaponMain(const StringId64 Sid, const int32_t mode)
{
    const char* string_index = nullptr;
    switch (mode) {
    case 1: {
        if (GivePlayerWeapon_index_count == GivePlayerWeapon_ListMax)
            GivePlayerWeapon_index_count = 0;
        string_index = weapon_list_main[GivePlayerWeapon_index_count];
        GivePlayerWeapon_index_count++;
        break;
    }
    case 2: {
        if (GivePlayerWeaponSub_index_count == GivePlayerWeapon_SubListMax)
            GivePlayerWeaponSub_index_count = 0;
        string_index = weapon_list_subsection[GivePlayerWeaponSub_index_count];
        GivePlayerWeaponSub_index_count++;
        break;
    }
    case 3: {
        if (GivePlayerWeaponEntry_index_count == GivePlayerWeapon_EntryListMax)
            GivePlayerWeaponEntry_index_count = 0;
        string_index = weapon_subentry_names[GivePlayerWeaponEntry_index_count];
        GivePlayerWeaponEntry_index_count++;
        break;
    }
    default: {
        memset(temp_str, 0, sizeof(temp_str));
        return temp_str;
    }
    }
    if (string_index[0] == '\0')
        string_index = "(null)";
    _snprintf_s(temp_str, sizeof(temp_str), "%s (#%.16llx)", string_index, Sid);
    return temp_str;
}

void __attribute__((naked)) GivePlayerWeapon_MainCC() {
    __asm {
        mov rcx, [r15 + 0x8]
        mov rcx, [rsi + rcx * 1]
        mov edx, 1
        call [GivePlayerWeaponMain]
        jmp [GivePlayerWeapon_MainReturn]
    }
}

void __attribute__((naked)) GivePlayerWeapon_SubCC() {
    __asm {
        mov rcx, [r13 + 0x8]
        mov rcx, [r12 + rcx * 1]
        mov edx, 2
        call [GivePlayerWeaponMain]
        jmp [GivePlayerWeapon_SubReturn]
    }
}

void __attribute__((naked)) GivePlayerWeapon_EntryCC() {
    __asm {
        mov rcx, [r14 + 0x8]
        mov rcx, [r15 + rcx * 1]
        mov edx, 3
        call [GivePlayerWeaponMain]
        jmp [GivePlayerWeapon_EntryReturn]
    }
}

char temp_buffer[256];
const char* ScriptPrintWarn_CC(void* unused, char* fmt, ...)
{
    memset(temp_buffer, 0, sizeof(temp_buffer));
    va_list args;
    va_start(args, fmt);
    vsprintf_s(temp_buffer, sizeof(temp_buffer), fmt, args);
    va_end(args);
    printf_s(temp_buffer);
    return temp_buffer;
}
