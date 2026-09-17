
#include "spdlog/spdlog.h"
#include "windowsapi.h" 

#include <filesystem>
#include <mutex>
#include <string>

extern HMODULE g_thisModule; 

HMODULE g_origDll = nullptr;

static std::once_flag g_loadOnce, g_resolveXInputOnce, g_resolveDInputOnce;

static bool g_isDInput8 = false;
static bool g_isXInput = false;

static void LoadOriginalDll()
{
    std::call_once(g_loadOnce,[]()
        {
            WCHAR systemDir[MAX_PATH]{};
            if (!GetSystemDirectoryW(systemDir, _countof(systemDir)))
            {
                spdlog::error("GetSystemDirectoryW failed");
                return;
            }

            WCHAR ourPath[MAX_PATH]{};
            if (!GetModuleFileNameW(g_thisModule, ourPath, _countof(ourPath)))
            {
                spdlog::error("GetModuleFileNameW failed");
                return;
            }

            std::filesystem::path path = std::filesystem::path(systemDir) / std::filesystem::path(ourPath).filename();
            spdlog::debug("Loading original: {}", path.string());

            g_origDll = LoadLibraryW(path.c_str());
            if (!g_origDll)
            {
                spdlog::error("LoadLibrary failed: {}", GetLastError());
                return;
            }

            // detect our proxy
            std::wstring name = std::filesystem::path(ourPath).filename().wstring();
            for (auto& c : name)
                {
                    c = towlower(c);
                }
            g_isDInput8 = (name == L"dinput8.dll");
            g_isXInput = (name == L"xinput1_3.dll");

            spdlog::info("Proxy mode: {} {}", g_isDInput8 ? "dinput8" : "", g_isXInput ? "xinput" : "");
        });
}

// dinput8 exports

#pragma comment(linker, "/export:DirectInput8Create=DirectInput8Create")
#pragma comment(linker, "/export:DllCanUnloadNow=DllCanUnloadNow,PRIVATE")
#pragma comment(linker, "/export:DllGetClassObject=DllGetClassObject,PRIVATE")
#pragma comment(linker, "/export:DllRegisterServer=DllRegisterServer,PRIVATE")
#pragma comment(linker, "/export:DllUnregisterServer=DllUnregisterServer,PRIVATE")
#pragma comment(linker, "/export:GetdfDIJoystick=GetdfDIJoystick")

typedef HRESULT(WINAPI* DirectInput8Create_t)(HINSTANCE hinst, DWORD dwVersion, REFIID riidltf, LPVOID* ppvOut, void* punkOuter);

static DirectInput8Create_t DirectInput8Create_Orig = nullptr;
static FARPROC DllCanUnloadNow_Orig = nullptr;
static FARPROC DllGetClassObject_Orig = nullptr;
static FARPROC DllRegisterServer_Orig = nullptr;
static FARPROC DllUnregisterServer_Orig = nullptr;
static FARPROC GetdfDIJoystick_Orig = nullptr;

static void ResolveDInput8()
{
    std::call_once(g_resolveXInputOnce,[]()
        {
            if (!g_origDll)
                return;

            DirectInput8Create_Orig = (DirectInput8Create_t)GetProcAddress(g_origDll, "DirectInput8Create");
            DllCanUnloadNow_Orig = GetProcAddress(g_origDll, "DllCanUnloadNow");
            DllGetClassObject_Orig = GetProcAddress(g_origDll, "DllGetClassObject");
            DllRegisterServer_Orig = GetProcAddress(g_origDll, "DllRegisterServer");
            DllUnregisterServer_Orig = GetProcAddress(g_origDll, "DllUnregisterServer");
            GetdfDIJoystick_Orig = GetProcAddress(g_origDll, "GetdfDIJoystick");
        });
}

extern "C" __declspec(dllexport) HRESULT WINAPI DirectInput8Create(HINSTANCE hinst, DWORD dwVersion, REFIID riidltf, LPVOID* ppvOut, void* punkOuter)
{
    if (!DirectInput8Create_Orig)
    {
        LoadOriginalDll();
        ResolveDInput8();
    }
    return DirectInput8Create_Orig(hinst, dwVersion, riidltf, ppvOut, punkOuter);
}

extern "C" __declspec(dllexport) HRESULT WINAPI DllCanUnloadNow()
{
    if (!DllCanUnloadNow_Orig)
    {
        LoadOriginalDll();
        ResolveDInput8();
    }
    return ((HRESULT(WINAPI*)())DllCanUnloadNow_Orig)();
}

extern "C" __declspec(dllexport) HRESULT WINAPI DllGetClassObject(REFCLSID rclsid, REFIID riid, LPVOID* ppv)
{
    if (!DllGetClassObject_Orig)
    {
        LoadOriginalDll();
        ResolveDInput8();
    }
    return  ((HRESULT(WINAPI*)(REFCLSID, REFIID, LPVOID*))DllGetClassObject_Orig)(rclsid, riid, ppv);
}

extern "C" __declspec(dllexport) HRESULT WINAPI DllRegisterServer()
{
    if (!DllRegisterServer_Orig)
    {
        LoadOriginalDll();
        ResolveDInput8();
    }
    return ((HRESULT(WINAPI*)())DllRegisterServer_Orig)();
}

extern "C" __declspec(dllexport) HRESULT WINAPI DllUnregisterServer()
{
    
    if (!DllUnregisterServer_Orig)
    {
        LoadOriginalDll();
        ResolveDInput8();
    }
    return ((HRESULT(WINAPI*)())DllUnregisterServer_Orig)();
}

extern "C" __declspec(dllexport) void WINAPI GetdfDIJoystick()
{
    if (!GetdfDIJoystick_Orig)
    {
        LoadOriginalDll();
        ResolveDInput8();
    }
    ((void(WINAPI*)())GetdfDIJoystick_Orig)();
}


// xinput exports

#pragma comment(linker, "/export:XInputGetState=XInputGetState,@2")
#pragma comment(linker, "/export:XInputSetState=XInputSetState,@3")
#pragma comment(linker, "/export:XInputGetCapabilities=XInputGetCapabilities,@4")
#pragma comment(linker, "/export:XInputEnable=XInputEnable,@5")
#pragma comment(linker, "/export:XInputGetDSoundAudioDeviceGuids=XInputGetDSoundAudioDeviceGuids,@6")
#pragma comment(linker, "/export:XInputGetBatteryInformation=XInputGetBatteryInformation,@7")
#pragma comment(linker, "/export:XInputGetKeystroke=XInputGetKeystroke,@8")

// Undocumented
#pragma comment(linker, "/export:ordinal100=ordinal100,@100,NONAME")
#pragma comment(linker, "/export:ordinal101=ordinal101,@101,NONAME")
#pragma comment(linker, "/export:ordinal102=ordinal102,@102,NONAME")
#pragma comment(linker, "/export:ordinal103=ordinal103,@103,NONAME")

// structs
struct XINPUT_STATE;
struct XINPUT_VIBRATION;
struct XINPUT_CAPABILITIES;
struct XINPUT_BATTERY_INFORMATION;
struct XINPUT_KEYSTROKE;

typedef DWORD(WINAPI* XInputGetState_t)(DWORD, XINPUT_STATE*);
typedef DWORD(WINAPI* XInputSetState_t)(DWORD, XINPUT_VIBRATION*);
typedef DWORD(WINAPI* XInputGetCapabilities_t)(DWORD, DWORD, XINPUT_CAPABILITIES*);
typedef void(WINAPI* XInputEnable_t)(BOOL);
typedef DWORD(WINAPI* XInputGetDSoundAudioDeviceGuids_t)(DWORD, GUID*, GUID*);
typedef DWORD(WINAPI* XInputGetBatteryInformation_t)(DWORD, BYTE, XINPUT_BATTERY_INFORMATION*);
typedef DWORD(WINAPI* XInputGetKeystroke_t)(DWORD, DWORD, XINPUT_KEYSTROKE*);
typedef DWORD(WINAPI* XInputGetStateEx_t)(DWORD, void*); // ordinal 100

static XInputGetState_t XInputGetState_Orig = nullptr;
static XInputSetState_t XInputSetState_Orig = nullptr;
static XInputGetCapabilities_t XInputGetCapabilities_Orig = nullptr;
static XInputEnable_t XInputEnable_Orig = nullptr;
static XInputGetDSoundAudioDeviceGuids_t XInputGetDSoundAudioDeviceGuids_Orig = nullptr;
static XInputGetBatteryInformation_t XInputGetBatteryInformation_Orig = nullptr;
static XInputGetKeystroke_t XInputGetKeystroke_Orig = nullptr;
static XInputGetStateEx_t XInputGetStateEx_Orig = nullptr;
static FARPROC ordinal101_Orig = nullptr;
static FARPROC ordinal102_Orig = nullptr;
static FARPROC ordinal103_Orig = nullptr;

static void ResolveXInput()
{
    std::call_once(g_resolveXInputOnce, []()
        {
        if (!g_origDll)
            return;

        XInputGetState_Orig = (XInputGetState_t)GetProcAddress(g_origDll, "XInputGetState");
        XInputSetState_Orig = (XInputSetState_t)GetProcAddress(g_origDll, "XInputSetState");
        XInputGetCapabilities_Orig = (XInputGetCapabilities_t)GetProcAddress(g_origDll, "XInputGetCapabilities");
        XInputEnable_Orig = (XInputEnable_t)GetProcAddress(g_origDll, "XInputEnable");
        XInputGetDSoundAudioDeviceGuids_Orig = (XInputGetDSoundAudioDeviceGuids_t)GetProcAddress(g_origDll, "XInputGetDSoundAudioDeviceGuids");
        XInputGetBatteryInformation_Orig = (XInputGetBatteryInformation_t)GetProcAddress(g_origDll, "XInputGetBatteryInformation");
        XInputGetKeystroke_Orig = (XInputGetKeystroke_t)GetProcAddress(g_origDll, "XInputGetKeystroke");

        XInputGetStateEx_Orig = (XInputGetStateEx_t)GetProcAddress(g_origDll, (LPCSTR)100);
        ordinal101_Orig = GetProcAddress(g_origDll, (LPCSTR)101);
        ordinal102_Orig = GetProcAddress(g_origDll, (LPCSTR)102);
        ordinal103_Orig = GetProcAddress(g_origDll, (LPCSTR)103);
        });
}

extern "C" __declspec(dllexport) DWORD WINAPI XInputGetState(DWORD dwUserIndex, XINPUT_STATE* pState)
{
    if (!XInputGetState_Orig)
    {
        LoadOriginalDll();
        ResolveXInput();
    }
    return XInputGetState_Orig(dwUserIndex, pState);
}

extern "C" __declspec(dllexport) DWORD WINAPI XInputSetState(DWORD dwUserIndex, XINPUT_VIBRATION* pVibration)
{
    
    if (!XInputSetState_Orig)
    {
        LoadOriginalDll();
        ResolveXInput();
    }
    return XInputSetState_Orig(dwUserIndex, pVibration);
}

extern "C" __declspec(dllexport) DWORD WINAPI XInputGetCapabilities(DWORD dwUserIndex, DWORD dwFlags, XINPUT_CAPABILITIES* pCapabilities)
{
    
    if (!XInputGetCapabilities_Orig)
    {
        LoadOriginalDll();
        ResolveXInput();
    }
    return XInputGetCapabilities_Orig(dwUserIndex, dwFlags, pCapabilities);
}

extern "C" __declspec(dllexport) void WINAPI XInputEnable(BOOL enable)
{
    
    if (!XInputEnable_Orig)
    {
        LoadOriginalDll();
        ResolveXInput();
    }
    XInputEnable_Orig(enable);
}

extern "C" __declspec(dllexport) DWORD WINAPI XInputGetDSoundAudioDeviceGuids(DWORD dwUserIndex, GUID* pDSoundRenderGuid, GUID* pDSoundCaptureGuid)
{
    
    if (!XInputGetDSoundAudioDeviceGuids_Orig)
    {
        LoadOriginalDll();
        ResolveXInput();
    }
    return XInputGetDSoundAudioDeviceGuids_Orig(dwUserIndex, pDSoundRenderGuid, pDSoundCaptureGuid);
}

extern "C" __declspec(dllexport) DWORD WINAPI XInputGetBatteryInformation(DWORD dwUserIndex, BYTE devType, XINPUT_BATTERY_INFORMATION* pBatteryInformation)
{
    
    if (!XInputGetBatteryInformation_Orig)
    {
        LoadOriginalDll();
        ResolveXInput();
    }
    return XInputGetBatteryInformation_Orig(dwUserIndex, devType, pBatteryInformation);
}

extern "C" __declspec(dllexport) DWORD WINAPI XInputGetKeystroke(DWORD dwUserIndex, DWORD dwReserved, XINPUT_KEYSTROKE* pKeystroke)
{
    
    if (!XInputGetKeystroke_Orig)
    {
        LoadOriginalDll();
        ResolveXInput();
    }
    return XInputGetKeystroke_Orig(dwUserIndex, dwReserved, pKeystroke);
}

// Undocumented
extern "C" __declspec(dllexport) DWORD WINAPI ordinal100(DWORD dwUserIndex, void* pState)
{
    if (!XInputGetStateEx_Orig)
    {
        LoadOriginalDll();
        ResolveXInput();
    }
    return XInputGetStateEx_Orig(dwUserIndex, pState);
}

extern "C" __declspec(dllexport) void __stdcall ordinal101()
{
    
    if (!ordinal101_Orig)
    {
        LoadOriginalDll();
        ResolveXInput();
    }
    ordinal101_Orig();
}

extern "C" __declspec(dllexport) void __stdcall ordinal102()
{
    
    if (!ordinal102_Orig)
    {
        LoadOriginalDll();
        ResolveXInput();
    }
    ordinal102_Orig();
}

extern "C" __declspec(dllexport) void __stdcall ordinal103()
{
    
    if (!ordinal103_Orig)
    {
        LoadOriginalDll();
        ResolveXInput();
    }
    ordinal103_Orig();
}