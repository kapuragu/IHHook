
#include "spdlog/spdlog.h"
#include "windowsapi.h"
#include <filesystem>
#include <mutex>
#include <string>

extern HMODULE g_thisModule; 

HMODULE g_origDll = nullptr;

static std::once_flag g_loadOnce, g_resolveEverythingOnce;

static bool g_isDInput8 = false;
static bool g_isXInput1_3 = false;
static bool g_isXInput1_4 = false;
static bool g_isMFReadWrite = false;

static void ResolveAllExports();

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

            const std::filesystem::path& path = std::filesystem::path(systemDir) / std::filesystem::path(ourPath).filename();

            spdlog::trace(L"Loading original: {}", path.wstring());

            g_origDll = LoadLibraryW(path.c_str());
            if (!g_origDll)
            {
                spdlog::error("LoadLibraryW failed: {}", GetLastError());
                return;
            }

            // detect our proxy
            std::wstring name = std::filesystem::path(ourPath).filename().wstring();
            for (auto& c : name)
                {
                    c = towlower(c);
                }
            g_isDInput8 = (name == L"dinput8.dll");
            g_isMFReadWrite = (name == L"mfreadwrite.dll");
            g_isXInput1_3 = (name == L"xinput1_3.dll");
            g_isXInput1_4 = (name == L"xinput1_4.dll");

            spdlog::info("Proxy mode: {}", g_isDInput8 ? "dinput8" : g_isXInput1_3 ? "xinput1_3" : g_isXInput1_4 ? "xinput1_4" : g_isMFReadWrite ? "mfreadwrite" : "unknown");
        });
}

// dinput8 exports
#pragma comment(linker, "/export:DirectInput8Create=_DirectInput8Create")
#pragma comment(linker, "/export:DllCanUnloadNow=_DllCanUnloadNow,PRIVATE")
#pragma comment(linker, "/export:DllGetClassObject=_DllGetClassObject,PRIVATE")
#pragma comment(linker, "/export:DllRegisterServer=_DllRegisterServer,PRIVATE")
#pragma comment(linker, "/export:DllUnregisterServer=_DllUnregisterServer,PRIVATE")
#pragma comment(linker, "/export:GetdfDIJoystick=_GetdfDIJoystick")

typedef HRESULT(WINAPI* DirectInput8Create_t)(HINSTANCE hinst, DWORD dwVersion, REFIID riidltf, LPVOID* ppvOut, void* punkOuter);

static DirectInput8Create_t DirectInput8Create_Orig = nullptr;
static FARPROC DllCanUnloadNow_Orig = nullptr;
static FARPROC DllGetClassObject_Orig = nullptr;
static FARPROC DllRegisterServer_Orig = nullptr;
static FARPROC DllUnregisterServer_Orig = nullptr;
static FARPROC GetdfDIJoystick_Orig = nullptr;


extern "C" __declspec(dllexport) HRESULT WINAPI _DirectInput8Create(HINSTANCE hinst, DWORD dwVersion, REFIID riidltf, LPVOID* ppvOut, void* punkOuter)
{
    if (!DirectInput8Create_Orig)
    {
        LoadOriginalDll();
        ResolveAllExports();
    }
    return DirectInput8Create_Orig(hinst, dwVersion, riidltf, ppvOut, punkOuter);
}

extern "C" __declspec(dllexport) HRESULT WINAPI _DllCanUnloadNow()
{
    if (!DllCanUnloadNow_Orig)
    {
        LoadOriginalDll();
        ResolveAllExports();
    }
    return ((HRESULT(WINAPI*)())DllCanUnloadNow_Orig)();
}

extern "C" __declspec(dllexport) HRESULT WINAPI _DllGetClassObject(REFCLSID rclsid, REFIID riid, LPVOID* ppv)
{
    if (!DllGetClassObject_Orig)
    {
        LoadOriginalDll();
        ResolveAllExports();
    }
    return ((HRESULT(WINAPI*)(REFCLSID, REFIID, LPVOID*))DllGetClassObject_Orig)(rclsid, riid, ppv);
}

extern "C" __declspec(dllexport) HRESULT WINAPI _DllRegisterServer()
{
    if (!DllRegisterServer_Orig)
    {
        LoadOriginalDll();
        ResolveAllExports();
    }
    return ((HRESULT(WINAPI*)())DllRegisterServer_Orig)();
}

extern "C" __declspec(dllexport) HRESULT WINAPI _DllUnregisterServer()
{
    
    if (!DllUnregisterServer_Orig)
    {
        LoadOriginalDll();
        ResolveAllExports();
    }
    return ((HRESULT(WINAPI*)())DllUnregisterServer_Orig)();
}

extern "C" __declspec(dllexport) void WINAPI _GetdfDIJoystick()
{
    if (!GetdfDIJoystick_Orig)
    {
        LoadOriginalDll();
        ResolveAllExports();
    }
    return ((void(WINAPI*)())GetdfDIJoystick_Orig)();
}


// xinput exports
#pragma comment(linker, "/export:DllMain=_DllMain,@1")
#pragma comment(linker, "/export:XInputGetState=_XInputGetState,@2")
#pragma comment(linker, "/export:XInputSetState=_XInputSetState,@3")
#pragma comment(linker, "/export:XInputGetCapabilities=_XInputGetCapabilities,@4")
#pragma comment(linker, "/export:XInputEnable=_XInputEnable,@5")
#pragma comment(linker, "/export:XInputGetDSoundAudioDeviceGuids=_XInputGetDSoundAudioDeviceGuids,@6")
#pragma comment(linker, "/export:XInputGetBatteryInformation=_XInputGetBatteryInformation,@7")
#pragma comment(linker, "/export:XInputGetKeystroke=_XInputGetKeystroke,@8")
#pragma comment(linker, "/export:XInputGetAudioDeviceIds=_XInputGetAudioDeviceIds,@10")

// Undocumented
#pragma comment(linker, "/export:ordinal100=_ordinal100,@100,NONAME")
#pragma comment(linker, "/export:ordinal101=_ordinal101,@101,NONAME")
#pragma comment(linker, "/export:ordinal102=_ordinal102,@102,NONAME")
#pragma comment(linker, "/export:ordinal103=_ordinal103,@103,NONAME")
// xinput1_4 undocumented
#pragma comment(linker, "/export:ordinal104=_ordinal104,@104,NONAME")
#pragma comment(linker, "/export:ordinal108=_ordinal108,@108,NONAME")

// structs
struct XINPUT_STATE;
struct XINPUT_VIBRATION;
struct XINPUT_CAPABILITIES;
struct XINPUT_BATTERY_INFORMATION;
struct XINPUT_KEYSTROKE;

typedef BOOL(WINAPI* DllMain_t)(HMODULE, DWORD, LPVOID);
typedef DWORD(WINAPI* XInputGetState_t)(DWORD, XINPUT_STATE*);
typedef DWORD(WINAPI* XInputSetState_t)(DWORD, XINPUT_VIBRATION*);
typedef DWORD(WINAPI* XInputGetCapabilities_t)(DWORD, DWORD, XINPUT_CAPABILITIES*);
typedef void(WINAPI* XInputEnable_t)(BOOL);
typedef DWORD(WINAPI* XInputGetDSoundAudioDeviceGuids_t)(DWORD, GUID*, GUID*);
typedef DWORD(WINAPI* XInputGetBatteryInformation_t)(DWORD, BYTE, XINPUT_BATTERY_INFORMATION*);
typedef DWORD(WINAPI* XInputGetKeystroke_t)(DWORD, DWORD, XINPUT_KEYSTROKE*);

//xinput1_4
typedef DWORD(WINAPI* XInputGetAudioDeviceIds_t)(DWORD dwUserIndex, LPWSTR pRenderDeviceId, UINT* pRenderCount, LPWSTR pCaptureDeviceId, UINT* pCaptureCount);

//undocumented ordinals 
typedef DWORD(WINAPI* XInputGetStateEx_t)(DWORD dwUserIndex, XINPUT_STATE* pState); // ordinal 100
typedef DWORD(WINAPI* XInputWaitForGuideButton_t)(DWORD dwUserIndex, DWORD dwFlag, LPVOID pVoid); // ordinal 101
typedef DWORD(WINAPI* XInputCancelGuideButtonWait_t)(DWORD dwUserIndex); // ordinal 102
typedef DWORD(WINAPI* XInputPowerOffController_t)(DWORD dwUserIndex);   // ordinal 103

// xinput1_4 undocumented
typedef DWORD(WINAPI* XInputGetBaseBusInformation_t)(DWORD dwUserIndex, LPVOID pVoid); // ordinal 104
typedef DWORD(WINAPI* XInputGetCapabilitiesEx_t)(DWORD unk1, DWORD dwUserIndex, DWORD dwFlags, LPVOID pCapabilitiesEx); // ordinal 108


static DllMain_t DllMain_Orig = nullptr;
static XInputGetState_t XInputGetState_Orig = nullptr;
static XInputSetState_t XInputSetState_Orig = nullptr;
static XInputGetCapabilities_t XInputGetCapabilities_Orig = nullptr;
static XInputEnable_t XInputEnable_Orig = nullptr;
static XInputGetDSoundAudioDeviceGuids_t XInputGetDSoundAudioDeviceGuids_Orig = nullptr;
static XInputGetBatteryInformation_t XInputGetBatteryInformation_Orig = nullptr;
static XInputGetKeystroke_t XInputGetKeystroke_Orig = nullptr;
static XInputGetAudioDeviceIds_t XInputGetAudioDeviceIds_Orig = nullptr; // xinput1_4
//undocumented
static XInputGetStateEx_t XInputGetStateEx_Orig = nullptr;
static XInputWaitForGuideButton_t XInputWaitForGuideButton_Orig = nullptr;
static XInputCancelGuideButtonWait_t XInputCancelGuideButtonWait_Orig = nullptr;
static XInputPowerOffController_t XInputPowerOffController_Orig = nullptr;

static XInputGetBaseBusInformation_t XInputGetBaseBusInformation_Orig = nullptr; // xinput1_4   undocumented 
static XInputGetCapabilitiesEx_t XInputGetCapabilitiesEx_Orig = nullptr;         // xinput1_4 undocumented


extern "C" __declspec(dllexport) BOOL WINAPI _DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved)
{
    if (!DllMain_Orig)
    {
        LoadOriginalDll();
        ResolveAllExports();
    }
    return DllMain_Orig ? DllMain_Orig(hModule, ul_reason_for_call, lpReserved) : TRUE;
}

extern "C" __declspec(dllexport) DWORD WINAPI _XInputGetState(DWORD dwUserIndex, XINPUT_STATE* pState)
{
    if (!XInputGetState_Orig)
    {
        LoadOriginalDll();
        ResolveAllExports();
    }
    return XInputGetState_Orig(dwUserIndex, pState);
}

extern "C" __declspec(dllexport) DWORD WINAPI _XInputSetState(DWORD dwUserIndex, XINPUT_VIBRATION* pVibration)
{
    
    if (!XInputSetState_Orig)
    {
        LoadOriginalDll();
        ResolveAllExports();
    }
    return XInputSetState_Orig(dwUserIndex, pVibration);
}

extern "C" __declspec(dllexport) DWORD WINAPI _XInputGetCapabilities(DWORD dwUserIndex, DWORD dwFlags, XINPUT_CAPABILITIES* pCapabilities)
{
    
    if (!XInputGetCapabilities_Orig)
    {
        LoadOriginalDll();
        ResolveAllExports();
    }
    return XInputGetCapabilities_Orig(dwUserIndex, dwFlags, pCapabilities);
}

extern "C" __declspec(dllexport) void WINAPI _XInputEnable(BOOL enable)
{
    
    if (!XInputEnable_Orig)
    {
        LoadOriginalDll();
        ResolveAllExports();
    }
    return XInputEnable_Orig(enable);
}

extern "C" __declspec(dllexport) DWORD WINAPI _XInputGetDSoundAudioDeviceGuids(DWORD dwUserIndex, GUID* pDSoundRenderGuid, GUID* pDSoundCaptureGuid)
{
    
    if (!XInputGetDSoundAudioDeviceGuids_Orig)
    {
        LoadOriginalDll();
        ResolveAllExports();
    }
    return XInputGetDSoundAudioDeviceGuids_Orig(dwUserIndex, pDSoundRenderGuid, pDSoundCaptureGuid);
}

extern "C" __declspec(dllexport) DWORD WINAPI _XInputGetBatteryInformation(DWORD dwUserIndex, BYTE devType, XINPUT_BATTERY_INFORMATION* pBatteryInformation)
{
    
    if (!XInputGetBatteryInformation_Orig)
    {
        LoadOriginalDll();
        ResolveAllExports();
    }
    return XInputGetBatteryInformation_Orig(dwUserIndex, devType, pBatteryInformation);
}

extern "C" __declspec(dllexport) DWORD WINAPI _XInputGetKeystroke(DWORD dwUserIndex, DWORD dwReserved, XINPUT_KEYSTROKE* pKeystroke)
{
    if (!XInputGetKeystroke_Orig)
    {
        LoadOriginalDll();
        ResolveAllExports();
    }
    return XInputGetKeystroke_Orig(dwUserIndex, dwReserved, pKeystroke);
}

extern "C" __declspec(dllexport) DWORD WINAPI _XInputGetAudioDeviceIds(DWORD dwUserIndex, LPWSTR pRenderDeviceId, UINT* pRenderCount, LPWSTR pCaptureDeviceId, UINT* pCaptureCount)
{
    if (!XInputGetAudioDeviceIds_Orig)
    {
        LoadOriginalDll();
        ResolveAllExports();
    }
    return XInputGetAudioDeviceIds_Orig(dwUserIndex, pRenderDeviceId, pRenderCount, pCaptureDeviceId, pCaptureCount);
}

// Undocumented
extern "C" __declspec(dllexport) DWORD WINAPI _ordinal100(DWORD dwUserIndex, XINPUT_STATE* pState)
{
    if (!XInputGetStateEx_Orig)
    {
        LoadOriginalDll();
        ResolveAllExports();
    }
    return XInputGetStateEx_Orig(dwUserIndex, pState);
}

extern "C" __declspec(dllexport) DWORD WINAPI _ordinal101(DWORD dwUserIndex, DWORD dwFlag, LPVOID pVoid)
{ 
    if (!XInputWaitForGuideButton_Orig)
    {
        LoadOriginalDll();
        ResolveAllExports();
    }
    return XInputWaitForGuideButton_Orig(dwUserIndex, dwFlag, pVoid);
}

extern "C" __declspec(dllexport) DWORD WINAPI _ordinal102(DWORD dwUserIndex)
{ 
    if (!XInputCancelGuideButtonWait_Orig)
    {
        LoadOriginalDll();
        ResolveAllExports();
    }
    return XInputCancelGuideButtonWait_Orig(dwUserIndex);
}

extern "C" __declspec(dllexport) DWORD WINAPI _ordinal103(DWORD dwUserIndex)
{ 
    if (!XInputPowerOffController_Orig)
    {
        LoadOriginalDll();
        ResolveAllExports();
    }
    return XInputPowerOffController_Orig(dwUserIndex);
}

extern "C" __declspec(dllexport) DWORD WINAPI _ordinal104(DWORD dwUserIndex, LPVOID pVoid)
{
    if (!XInputGetBaseBusInformation_Orig)
    {
        LoadOriginalDll();
        ResolveAllExports();
    }
    return XInputGetBaseBusInformation_Orig(dwUserIndex, pVoid);
}

extern "C" __declspec(dllexport) DWORD WINAPI _ordinal108(DWORD unk1, DWORD dwUserIndex, DWORD dwFlags, LPVOID pCapabilitiesEx)
{
    if (!XInputGetCapabilitiesEx_Orig)
    {
        LoadOriginalDll();
        ResolveAllExports();
    }
    return XInputGetCapabilitiesEx_Orig(unk1, dwUserIndex, dwFlags, pCapabilitiesEx);
}

//MFReadWrite.dll
#pragma comment(linker, "/export:MFCreateSinkWriterFromMediaSink=__MFCreateSinkWriterFromMediaSink")
#pragma comment(linker, "/export:MFCreateSinkWriterFromURL=__MFCreateSinkWriterFromURL")
#pragma comment(linker, "/export:MFCreateSourceReaderFromByteStream=__MFCreateSourceReaderFromByteStream")
#pragma comment(linker, "/export:MFCreateSourceReaderFromMediaSource=__MFCreateSourceReaderFromMediaSource")
#pragma comment(linker, "/export:MFCreateSourceReaderFromURL=__MFCreateSourceReaderFromURL")

// typedefs
typedef HRESULT(WINAPI* MFCreateSinkWriterFromMediaSink_t)(void* pMediaSink, void* pAttributes, void** ppSinkWriter);
typedef HRESULT(WINAPI* MFCreateSinkWriterFromURL_t)(LPCWSTR pwszOutputURL, void* pByteStream, void* pAttributes, void** ppSinkWriter);
typedef HRESULT(WINAPI* MFCreateSourceReaderFromByteStream_t)(void* pByteStream, void* pAttributes, void** ppSourceReader);
typedef HRESULT(WINAPI* MFCreateSourceReaderFromMediaSource_t)(void* pMediaSource, void* pAttributes, void** ppSourceReader);
typedef HRESULT(WINAPI* MFCreateSourceReaderFromURL_t)(LPCWSTR pwszURL, void* pAttributes, void** ppSourceReader);

//ptrs
static MFCreateSinkWriterFromMediaSink_t MFCreateSinkWriterFromMediaSink_Orig = nullptr;
static MFCreateSinkWriterFromURL_t MFCreateSinkWriterFromURL_Orig = nullptr;
static MFCreateSourceReaderFromByteStream_t MFCreateSourceReaderFromByteStream_Orig = nullptr;
static MFCreateSourceReaderFromMediaSource_t MFCreateSourceReaderFromMediaSource_Orig = nullptr;
static MFCreateSourceReaderFromURL_t MFCreateSourceReaderFromURL_Orig = nullptr;

extern "C" __declspec(dllexport) HRESULT WINAPI __MFCreateSinkWriterFromMediaSink(void* pMediaSink, void* pAttributes, void** ppSinkWriter)
{
    if (!MFCreateSinkWriterFromMediaSink_Orig)
    {
        LoadOriginalDll();
        ResolveAllExports();
    }
    return MFCreateSinkWriterFromMediaSink_Orig(pMediaSink, pAttributes, ppSinkWriter);
}

extern "C" __declspec(dllexport) HRESULT WINAPI __MFCreateSinkWriterFromURL(LPCWSTR pwszOutputURL, void* pByteStream, void* pAttributes, void** ppSinkWriter)
{
    if (!MFCreateSinkWriterFromURL_Orig)
    {
        LoadOriginalDll();
        ResolveAllExports();
    }
    return MFCreateSinkWriterFromURL_Orig(pwszOutputURL, pByteStream, pAttributes, ppSinkWriter);
}

extern "C" __declspec(dllexport) HRESULT WINAPI __MFCreateSourceReaderFromByteStream(void* pByteStream, void* pAttributes, void** ppSourceReader)
{
    if (!MFCreateSourceReaderFromByteStream_Orig)
    {
        LoadOriginalDll();
        ResolveAllExports();
    }
    return MFCreateSourceReaderFromByteStream_Orig(pByteStream, pAttributes, ppSourceReader);
}

extern "C" __declspec(dllexport) HRESULT WINAPI __MFCreateSourceReaderFromMediaSource(void* pMediaSource, void* pAttributes, void** ppSourceReader)
{
    if (!MFCreateSourceReaderFromMediaSource_Orig)
    {
        LoadOriginalDll();
        ResolveAllExports();
    }
    return MFCreateSourceReaderFromMediaSource_Orig(pMediaSource, pAttributes, ppSourceReader);
}

extern "C" __declspec(dllexport) HRESULT WINAPI __MFCreateSourceReaderFromURL(LPCWSTR pwszURL, void* pAttributes, void** ppSourceReader)
{
    if (!MFCreateSourceReaderFromURL_Orig)
    {
        LoadOriginalDll();
        ResolveAllExports();
    }
    return MFCreateSourceReaderFromURL_Orig(pwszURL, pAttributes, ppSourceReader);
}


static void ResolveAllExports()
{
     std::call_once(g_resolveEverythingOnce,[]()
        {
            if (!g_origDll)
                return;

            if (g_isDInput8)
            {
                DirectInput8Create_Orig = (DirectInput8Create_t)GetProcAddress(g_origDll, "DirectInput8Create");
                DllRegisterServer_Orig = GetProcAddress(g_origDll, "DllRegisterServer");
                DllUnregisterServer_Orig = GetProcAddress(g_origDll, "DllUnregisterServer");
                GetdfDIJoystick_Orig = GetProcAddress(g_origDll, "GetdfDIJoystick");
            }

            
            if (g_isMFReadWrite)
            {
                MFCreateSinkWriterFromMediaSink_Orig = (MFCreateSinkWriterFromMediaSink_t)GetProcAddress(g_origDll, "MFCreateSinkWriterFromMediaSink");
                MFCreateSinkWriterFromURL_Orig = (MFCreateSinkWriterFromURL_t)GetProcAddress(g_origDll, "MFCreateSinkWriterFromURL");
                MFCreateSourceReaderFromByteStream_Orig = (MFCreateSourceReaderFromByteStream_t)GetProcAddress(g_origDll, "MFCreateSourceReaderFromByteStream");
                MFCreateSourceReaderFromMediaSource_Orig =(MFCreateSourceReaderFromMediaSource_t)GetProcAddress(g_origDll, "MFCreateSourceReaderFromMediaSource");
                MFCreateSourceReaderFromURL_Orig = (MFCreateSourceReaderFromURL_t)GetProcAddress(g_origDll, "MFCreateSourceReaderFromURL");
            }

            if (g_isDInput8 || g_isMFReadWrite)
            {
                DllCanUnloadNow_Orig = GetProcAddress(g_origDll, "DllCanUnloadNow");
                DllGetClassObject_Orig = GetProcAddress(g_origDll, "DllGetClassObject");
            }

            if (g_isXInput1_3 || g_isXInput1_4)
            {
                DllMain_Orig = (DllMain_t)GetProcAddress(g_origDll, "DllMain");
                XInputGetState_Orig = (XInputGetState_t)GetProcAddress(g_origDll, "XInputGetState");
                XInputSetState_Orig = (XInputSetState_t)GetProcAddress(g_origDll, "XInputSetState");
                XInputGetCapabilities_Orig = (XInputGetCapabilities_t)GetProcAddress(g_origDll, "XInputGetCapabilities");
                XInputEnable_Orig = (XInputEnable_t)GetProcAddress(g_origDll, "XInputEnable");
                XInputGetDSoundAudioDeviceGuids_Orig = (XInputGetDSoundAudioDeviceGuids_t)GetProcAddress(g_origDll, "XInputGetDSoundAudioDeviceGuids");
                XInputGetBatteryInformation_Orig = (XInputGetBatteryInformation_t)GetProcAddress(g_origDll, "XInputGetBatteryInformation");
                XInputGetKeystroke_Orig = (XInputGetKeystroke_t)GetProcAddress(g_origDll, "XInputGetKeystroke");

                // undocumented orrdinals
                XInputGetStateEx_Orig = (XInputGetStateEx_t)GetProcAddress(g_origDll, (LPCSTR)100);
                XInputWaitForGuideButton_Orig = (XInputWaitForGuideButton_t)GetProcAddress(g_origDll, (LPCSTR)101);
                XInputCancelGuideButtonWait_Orig = (XInputCancelGuideButtonWait_t)GetProcAddress(g_origDll, (LPCSTR)102);
                XInputPowerOffController_Orig = (XInputPowerOffController_t)GetProcAddress(g_origDll, (LPCSTR)103);
            }

            if (g_isXInput1_4)
            {
                XInputGetAudioDeviceIds_Orig = (XInputGetAudioDeviceIds_t)GetProcAddress(g_origDll, "XInputGetAudioDeviceIds");
                XInputGetBaseBusInformation_Orig = (XInputGetBaseBusInformation_t)GetProcAddress(g_origDll, (LPCSTR)104);
                XInputGetCapabilitiesEx_Orig = (XInputGetCapabilitiesEx_t)GetProcAddress(g_origDll, (LPCSTR)108);
            }

            spdlog::trace("Resolved exports from original DLL");

        });
}
