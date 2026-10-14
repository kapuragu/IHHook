#include "Hooks_FOV.h" //DEBUGNOW
#include "IHHook.h"
#include "ntdll.h"
#include "windowsapi.h"

#include <filesystem>

HMODULE g_thisModule;
extern HMODULE g_origDll; // dinputproxy

static void initialize()
{
    auto anti_anti_dbg = []() -> void
    {
        DWORD64 dwAddr = (DWORD64)GetProcAddress(GetModuleHandleW(L"KERNELBASE.dll"), "IsDebuggerPresent");
        DWORD buf;

        bool result = VirtualProtect((BYTE*)dwAddr, 0x20, PAGE_EXECUTE_READWRITE, &buf);
        if (result == NULL)
        {
            spdlog::error("Failed to patch anti-dbg checks");
        }
        else
        {
            *(BYTE*)(dwAddr) = 0xB8;
            std::memset((BYTE*)(dwAddr + 0x01), 0x00, 0x04);
            *(BYTE*)(dwAddr + 0x5) = 0xC3;
            VirtualProtect((BYTE*)dwAddr, 0x20, buf, &buf);
            FlushInstructionCache(GetCurrentProcess(), (BYTE*)dwAddr, 0x20);
        }

        PPEB peb = (PPEB)__readgsqword(0x60);
        peb->BeingDebugged = false;
        peb->NtGlobalFlag &= ~0x70;


        // crashes inside fox::ui::`anonymous namespace'::ResourceCreatorUseCallbackAndWindowInfo::SetupGraph

        /*
        constexpr const uint8_t patch1[]{ 0xB9, 0xF3, 0x01, 0x00, 0x00 };
        constexpr const uint8_t patch2[]{ 0xB9, 0xF4, 0x01, 0x00, 0x00 };
        constexpr const uint8_t patch3[]{ 0x66, 0x3D, 0xF4, 0x01, 0x90, 0x90, 0x90, 0x90, 0x0F, 0xB7, 0xC0 };

        auto qaddr = hook::get_pattern("B9 BF 00 00 00 0F 1F 00");
        hook::patch(qaddr, patch1);

        auto qaddr2 = hook::get_pattern("B9 C0 00 00 00 48 89 ? EC");
        hook::patch(qaddr2, patch2);

        auto qaddr3 = hook::get_pattern("3C C0 0F 83 E4 04 00 00");
        hook::patch(qaddr3, patch3);

        auto qaddr4 = hook::get_pattern("B9 C0 00 00 00 33 DB 90");
        hook::patch(qaddr4, patch2);

        constexpr const uint8_t patchA[]{ 0x80, 0xF9, 0x7F };
        constexpr const uint8_t patchB[]{ 0x8D, 0x4E, 0x7E };
        constexpr const uint8_t patchC[]{ 0xB8, 0x7F, 0x00, 0x00, 0x00 };

        auto zz = hook::get_pattern("B8 40 00 00 00 0F 1F 40 00");
        hook::patch(zz, patchC);

        auto zy = hook::get_pattern("8D 4E 3F 48 BD 98 9F 16 BF A0 B8 00 00");
        hook::patch(zy, patchB);

        auto zx = hook::get_pattern("80 F9 40 0F 83 99 00 00 00");
        hook::patch(zx, patchA);
        */
        

        // dx11 anti-anti-hook
        constexpr const uint8_t bytes[]{ 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90 };
        auto addr = hook::get_pattern<uint8_t>("4C 8D 44 24 30 48 8D 55 E8", 0x2C);
        if (*addr == 0xE8)
        {
            hook::patch(addr, bytes);
        }
    };

    anti_anti_dbg();
    g_ihhook = std::make_unique<IHHook::IHH>();
    g_ihhook->Initialize();
}


DWORD WINAPI InitThread(LPVOID)
{
    g_ihhook->Load_Dlls();

    return 0;
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved)
{
    if (ul_reason_for_call == DLL_PROCESS_ATTACH)
    {
        DisableThreadLibraryCalls(hModule);

        g_thisModule = hModule;

        initialize();
     
        CloseHandle(CreateThread(nullptr, 0,(LPTHREAD_START_ROUTINE)InitThread, nullptr, 0, nullptr));
    }
    else if (ul_reason_for_call == DLL_PROCESS_DETACH)
    {
        IHHook::Shutdown();
        
        // DInputProxy
        if (g_origDll)
        {
            FreeLibrary(g_origDll);
        }
    }

    return TRUE;
} // DllMain