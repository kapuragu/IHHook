#include "IHHook.h"
#include "windowsapi.h"
#include "plugin_loader.hpp"
#include <filesystem>

#include "Hooks_FOV.h" //DEBUGNOW

HMODULE g_thisModule;
extern HMODULE g_origDll; // dinputproxy

static void initialize()
{

    // games anti dx-11 hook patch
    // we nop fox::gr::dg::CheckModuleHook call and the checks come with it inside fox::gr::dg::DgDx11::Initialize
    constexpr const uint8_t bytes[]{ 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90 };
    auto addr = hook::get_pattern<uint8_t>("4C 8D 44 24 30 48 8D 55 E8", 0x2C);
    if (*addr == 0xE8)
    {
         hook::patch(addr, bytes);
    }
    g_ihhook = std::make_unique<IHHook::IHH>();
    g_ihhook->Initialize();
}

DWORD WINAPI InitThread(LPVOID)
{
    PluginLoader::LoadPlugins();

    return 0;
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved)
{
    if (ul_reason_for_call == DLL_PROCESS_ATTACH)
    {
        //DisableThreadLibraryCalls(hModule);

        g_thisModule = hModule;

        initialize();

        CloseHandle(CreateThread(nullptr, 0,(LPTHREAD_START_ROUTINE)InitThread, nullptr, 0, nullptr));

    }
    else if (ul_reason_for_call == DLL_PROCESS_DETACH)
    {
        IHHook::Shutdown();
        PluginLoader::UnloadPlugins();
        // DInputProxy
        if (g_origDll)
        {
            FreeLibrary(g_origDll);
        }
    }

    return TRUE;
} // DllMain