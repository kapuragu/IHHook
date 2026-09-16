//DInputProxy.cpp - from CityHook
//Proxy dinput8.dll
#include "windowsapi.h"
#include <stdlib.h>
#include <stdio.h>
#include <filesystem>

#include "spdlog/spdlog.h"

//DEBUGNOW put this into a header or a DEF
#pragma comment(linker, "/export:DirectInput8Create=DirectInput8Create")
#pragma comment(linker, "/export:DllCanUnloadNow=DllCanUnloadNow,PRIVATE")
#pragma comment(linker, "/export:DllGetClassObject=DllGetClassObject,PRIVATE")
#pragma comment(linker, "/export:DllRegisterServer=DllRegisterServer,PRIVATE")
#pragma comment(linker, "/export:DllUnregisterServer=DllUnregisterServer,PRIVATE")
#pragma comment(linker, "/export:GetdfDIJoystick=GetdfDIJoystick")

typedef HRESULT(WINAPI*DirectInput8Create_ptr)(HINSTANCE hinst, DWORD dwVersion, REFIID riidltf, LPVOID * ppvOut, void* punkOuter);

DirectInput8Create_ptr DirectInput8Create_Orig = NULL;
FARPROC DllCanUnloadNow_Orig;
FARPROC DllGetClassObject_Orig;
FARPROC DllRegisterServer_Orig;
FARPROC DllUnregisterServer_Orig;
FARPROC GetdfDIJoystick_Orig;



extern HMODULE g_thisModule;
bool origLoaded = false;
HMODULE origDll = NULL;
static std::once_flag s_xinputLoadFlag{};

void LoadProxiedDll()
{
    std::call_once(
        s_xinputLoadFlag,
        []() -> void
        {
            // System directory
            WCHAR systemDirBuf[MAX_PATH]{};
            if (!GetSystemDirectoryW(systemDirBuf, _countof(systemDirBuf)))
            {
                spdlog::error("GetSystemDirectoryW failed");
                return;
            }
            const std::filesystem::path systemDir = systemDirBuf;

            // Full path of this (proxy) DLL
            WCHAR ourModulePathBuf[MAX_PATH]{};
            if (!GetModuleFileNameW(g_thisModule, ourModulePathBuf, _countof(ourModulePathBuf)))
            {
                spdlog::error("GetModuleFileNameW failed");
                return;
            }
            const std::filesystem::path ourModulePath = ourModulePathBuf;

            // Same filename as the original system DLL
            const std::filesystem::path modulePath = systemDir / ourModulePath.filename();

            spdlog::debug("Loading original module from: {}", modulePath.string());

            origDll = LoadLibraryW(modulePath.c_str());
            if (!origDll)
            {
                spdlog::error("Could not load original module (error {})", GetLastError());
                return;
            }

	        DirectInput8Create_Orig = (DirectInput8Create_ptr)GetProcAddress(origDll, "DirectInput8Create");
	        DllCanUnloadNow_Orig = GetProcAddress(origDll, "DllCanUnloadNow");
	        DllGetClassObject_Orig = GetProcAddress(origDll, "DllGetClassObject");
	        DllRegisterServer_Orig = GetProcAddress(origDll, "DllRegisterServer");
	        DllUnregisterServer_Orig = GetProcAddress(origDll, "DllUnregisterServer");
        });
}



extern "C" __declspec(dllexport) HRESULT DirectInput8Create(HINSTANCE hinst, DWORD dwVersion, REFIID riidltf, LPVOID * ppvOut, void* punkOuter)
{
	spdlog::debug("IHHook: DirectInput8Create");

	if (!DirectInput8Create_Orig)
		LoadProxiedDll();

	return DirectInput8Create_Orig(hinst, dwVersion, riidltf, ppvOut, punkOuter);
}

extern "C" __declspec(dllexport) void __stdcall DllCanUnloadNow() { DllCanUnloadNow_Orig(); }
extern "C" __declspec(dllexport) void __stdcall DllGetClassObject() { DllGetClassObject_Orig(); }
extern "C" __declspec(dllexport) void __stdcall DllRegisterServer() { DllRegisterServer_Orig(); }
extern "C" __declspec(dllexport) void __stdcall DllUnregisterServer() { DllUnregisterServer_Orig(); }
extern "C" __declspec(dllexport) void __stdcall GetdfDIJoystick() { GetdfDIJoystick_Orig(); }
