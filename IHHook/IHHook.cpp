#include <ctime>
#include "spdlog/spdlog.h"
#include "spdlog/sinks/basic_file_sink.h"
#include "IHHook.h"
#include "OS.h"
#include "PipeServer.h"
#include "MinHook/MinHook.h" // MH_Initialize
#include <signal.h>

#include "Hooks_CityHash.h"
#include "Hooks_FnvHash.h"
#include "Hooks_Lua.h"
#include "Hooks_TPP.h"
#include "Hooks_FOV.h"
#include "Hooks_LoadFile.h"
#include "Hooks_Character.h"
#include "Hooks_Buddy.h" //ZIP: For buddies
#include "Hooks_Vehicle.h" //ZIP: For vehicles
//#include "Hooks_FoxString.h" //ZIP: FoxString hook
//#include "Hooks_CallMenu.h" //ZIP: For Call Menu

#include "RawInput.h"

#include <imgui/imgui.h>
#include "imguiimpl/imgui_impl_win32.h"
#include "imguiimpl/imgui_impl_dx11.h"

#include <string>
#include <filesystem>
// version_info parse
#include <fstream>
#include <sstream>


#include "IHMenu.h"
#include "StyleEditor.h"

#include "Util.h"//config 

#include "hooks/mgsvtpp_adresses_1_0_15_3_en.h"
#include "hooks/mgsvtpp_adresses_1_0_15_3_jp.h"
#include "hooks/mgsvtpp_adresses_1_0_15_4_en.h"
#include "hooks/mgsvtpp_adresses_1_0_15_4_jp.h"
#include "hooks/mgsvtpp_patterns.h"


extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);//tex see note in imgui_impl_win32.h

std::unique_ptr<IHHook::IHH> g_ihhook{};

namespace IHHook {
	//mgsvtpp_funcptr_set.cpp
	extern void SetFuncPtrs();
	extern void CreateHooks();

	struct Config config;
	bool ParseConfig(std::string fileName);

	std::atomic<bool> doShutDown = false;

	std::vector<std::string> errorMessages{};

	bool isTargetExe = false;
	std::unordered_map<std::string, uint64_t> addressSet{};
	std::unordered_map<std::string, char*> patterns{};

	terminate_function terminate_Original;

	void AbortHandler(int signal_number) {
		auto log = spdlog::get("ihhook");
		if (log != NULL) {
			log->error("abort was called, signal_number: {}", signal_number);
			log->flush();
		}
	}//AbortHandler

	void TerminateHandler() {
		auto log = spdlog::get("ihhook");
		if (log != NULL) {
			log->error("terminate was called");
			log->flush();
		}
		terminate_Original();
	}//TerminateHandler

	bool g_showCrashDialog = true;
	LONG WINAPI UnhandledExceptionHandler(EXCEPTION_POINTERS* /*ExceptionInfo*/) {
		auto log = spdlog::get("ihhook");
		if (log != NULL) {
			log->error("Unhandled exception");
			log->flush();
		}

		return g_showCrashDialog ? EXCEPTION_CONTINUE_SEARCH : EXCEPTION_EXECUTE_HANDLER;
	}//UnhandledExceptionHandler

	LONG WINAPI UnhandledExceptionFilter_Hook(EXCEPTION_POINTERS* /*ExceptionInfo*/) {
		// When the CRT calls SetUnhandledExceptionFilter with NULL parameter
		// our handler will not get removed.
		auto log = spdlog::get("ihhook");
		if (log != NULL) {
			log->error("Unhandled exception H");
			log->flush();
		}

		return 0;
	}//UnhandledExceptionFilter_Hook

	typedef LPTOP_LEVEL_EXCEPTION_FILTER(WINAPI* SetUnhandledExceptionFilter_Type)(LPTOP_LEVEL_EXCEPTION_FILTER lpTopLevelExceptionFilter);
	SetUnhandledExceptionFilter_Type SetUnhandledExceptionFilter_Orig = NULL;

	typedef BOOL(WINAPI* SetCursorPosFunc)(int, int);
	SetCursorPosFunc SetCursorPos_Orig = NULL;

	BOOL WINAPI SetCursorPos_Hook(int X, int Y) {
		if (g_ihhook->IsUnlockCursor())
			return FALSE;

		return SetCursorPos_Orig(X, Y);
	}//SetCursorPos_Hook

	void InitCursorHook() {
		auto log = spdlog::get("ihhook");
		if (MH_CreateHook(&SetCursorPos, &SetCursorPos_Hook, reinterpret_cast<LPVOID*>(&SetCursorPos_Orig)) != MH_OK) {
			log->info("Couldn't create hook for SetCursorPos.");
			return;
		}

		if (MH_EnableHook(&SetCursorPos) != MH_OK) {
			log->info("Couldn't enable SetCursorPos hook.");
		}
	}//InitCursorHook

	void Shutdown() {
		spdlog::debug("IHHook DLL_PROCESS_DETACH");
		doShutDown = true;
		RawInput::UninitializeInput();
		PipeServer::ShutDownPipeServer();
	}//Shutdown

	//GOTCHA: only set up stuff that can be done in this point of fox engine execution (when it's loading this dinput8.dll proxy)
	//see Initialize for stuff after

	IHH::IHH()
		: thisModule{ *reinterpret_cast<HMODULE*>(__readgsqword(0x60) + 0x10) } {

		signal(SIGABRT, &AbortHandler);//tex signal handler for SIGABRT which is thrown by abort()
		terminate_Original = set_terminate(TerminateHandler);
		_set_abort_behavior(1, _WRITE_ABORT_MSG);

		SetUnhandledExceptionFilter(UnhandledExceptionHandler);

		//https://www.codeproject.com/Articles/154686/SetUnhandledExceptionFilter-and-the-C-C-Runtime-Li
		//if (MH_CreateHook(&SetUnhandledExceptionFilter, &UnhandledExceptionFilter_Hook, reinterpret_cast<LPVOID*>(&SetUnhandledExceptionFilter_Orig)) != MH_OK) {
		//	//DEBUGNOW message error
		//	return 1;
		//}
		//MH_EnableHook(SetUnhandledExceptionFilter);


		if (config.openConsole) {
			AllocConsole();
			SetConsoleTitle(L"IHHook");
			freopen("CONOUT$", "w", stdout);
			freopen("CONOUT$", "w", stderr);
			freopen("CONIN$", "r", stdin);
			printf("Console test\n");
		}

		//tex DEBUG, logged below 
		TCHAR Buffer[MAX_PATH];
		GetCurrentDirectory(MAX_PATH, Buffer);
		std::wstring currentDir(Buffer);

		std::wstring gameDir = OS::GetGameDir();
		SetCurrentDirectory(gameDir.c_str());//tex so this dll and lua can use reletive paths

		config.debugMode = true;//DEBUGNOW -v
		ParseConfig(hookConfigName);//TODO: set log level via config.debugMode
		SetupLog();

		//tex DEBUGNOW mgo is a seperate exe in the same dir, so bail out on exe name
		WCHAR fullPath[MAX_PATH]{ 0 };
		GetModuleFileNameW(thisModule, fullPath, MAX_PATH);
		std::filesystem::path path(fullPath);
		std::wstring exeName = path.filename().c_str();
		if (exeName.find(L"mgo")!= std::wstring::npos) {
			log->warn("IHHook is not for mgo");
			return;
		}
		//

		log->debug(L"Original CurrentDir: {}", currentDir.c_str());
		log->debug(L"gameDir: {}", gameDir);

#ifdef _DEBUG
		std::vector<std::string> modFileNames = OS::GetFileNames("./mod");
		std::vector<std::string> folderNames = OS::GetFolderNames("./mod");
#endif // _DEBUG

		if (!std::filesystem::exists("./mod/modules")) {//tex GOTCHA: since this continues ih_log will be created thus ./mod will actually exist. so check modules instead
			errorMessages.push_back("ERROR: IH mod folder not found.");

			for (const auto& message : errorMessages) {
				log->error(message);
			}
		}

       auto* base = reinterpret_cast<uint8_t*>(thisModule);
       const auto* dos = reinterpret_cast<const IMAGE_DOS_HEADER*>(base);
       const auto* nt = reinterpret_cast<const IMAGE_NT_HEADERS*>(base + dos->e_lfanew);


       const auto sz = nt->OptionalHeader.SizeOfImage;

	   switch (sz)
       {
       case 0xA01D000u:
           addressSet = mgsvtpp_adresses_1_0_15_4_en;
           isTargetExe = true;
           log->info("detected mgsvtpp.exe version 1.0.15.4 (EN)");
           break;
       case 0xA01E000u:
           addressSet = mgsvtpp_adresses_1_0_15_4_en;
           isTargetExe = true;
           log->info("detected mgsvtpp.exe version 1.0.15.4 (EN) pirated");
           errorMessages.push_back("Warning: pirated version detected");
           errorMessages.push_back("Infinite Heaven is not supported on pirated versions");
           errorMessages.push_back("it may not work correctly or it might crash the game");
           break;
       case 0xA080000u:
           addressSet = mgsvtpp_adresses_1_0_15_4_jp;
           isTargetExe = true;
           log->info("detected mgsvtpp.exe version 1.0.15.4 (JP)");
           break;
       case 0xDB7B000u:
           addressSet = mgsvtpp_adresses_1_0_15_3_en;
           isTargetExe = true;
           log->info("detected mgsvtpp.exe version 1.0.15.3 (EN)");
           break;
       case 0xE15C000u:
           addressSet = mgsvtpp_adresses_1_0_15_3_jp;
           isTargetExe = true;
           log->info("detected mgsvtpp.exe version 1.0.15.3 (JP)");
           break;
       default:
           isTargetExe = false;
           errorMessages.push_back("ERROR: executable version mismatch");
           errorMessages.push_back("Infinite Heaven will continue to load");
           errorMessages.push_back("but it may not work correctly or it might crash the game");
           errorMessages.push_back("including this menu not working in-game.");
           for (const auto& message : errorMessages)
           {
               log->error(message);
           }
           SetCursor(true);
           break;
       }

		bool doHooks = isTargetExe;

		if (config.forceUsePatterns) {
			isTargetExe = false;//tex use sig scanning instead
			doHooks = true;
		}

		if (doHooks) {//tex hook em up boys
			Hooks_Lua::SetupLog();

			MH_Initialize();

			g_isMinHookInitialized = true;

			auto tstart = std::chrono::high_resolution_clock::now();

			bool foundAllAddresses = RebaseAddresses();

			if (!foundAllAddresses) {
				log->warn("Could not find all addresses");
			}
			else {
				SetFuncPtrs();
				//DEBUGNOW CreateHooks();
			}

			CreateAllHooks();

			auto tend = std::chrono::high_resolution_clock::now();
			auto durationShort = std::chrono::duration_cast<std::chrono::microseconds>(tend - tstart).count();
			log->debug("IHHook::CreateHooks total time(microseconds): {}μs", durationShort);
		}//if doHooks

		PipeServer::StartPipeServer();

		log->debug("IHH ctor complete");
		log->flush();
	}//IHH

	IHH::~IHH() {
        if (p_imguiContext != nullptr)
        {
            ImGui::SetCurrentContext(p_imguiContext);
            ImGui_ImplDX11_Shutdown();
            ImGui_ImplWin32_Shutdown();
            ImGui::DestroyContext(p_imguiContext);
            p_imguiContext = nullptr;
        }
		MH_DisableHook(MH_ALL_HOOKS);
		MH_RemoveHook(MH_ALL_HOOKS);
		MH_Uninitialize();
		log->info("mod uninitialized IHHook unloaded");
		spdlog::shutdown();
	}//~IHH

	void IHH::Initialize() {
		CreateD3DHook();
	}

	//OUT/SIDE: log file, log file prev
	//OUT/SIDE: log
	void IHH::SetupLog() {
		DeleteFile(IHHook::hookLogNamePrev.c_str());
		CopyFile(IHHook::hookLogName.c_str(), IHHook::hookLogNamePrev.c_str(), false);
		DeleteFile(IHHook::hookLogName.c_str());

		log = spdlog::basic_logger_mt("ihhook", IHHook::hookLogName);//DEBUGNOW st vs mt

		if (config.logTime) {
			log->set_pattern("|%H:%M:%S:%e|%l: %v");
		}
		else {
			log->set_pattern("%l: %v");
		}
		log->info("IHHook r{}", IHHook::Version);
		log->flush();

		spdlog::set_default_logger(log);
		if (config.debugMode) {
			spdlog::set_level(spdlog::level::trace);
			spdlog::flush_on(spdlog::level::trace);
		}
		else {
			spdlog::set_level(spdlog::level::info);		
			spdlog::flush_on(spdlog::level::err);
		}

    SYSTEMTIME st = {};
    GetLocalTime(&st);

    log->info("Started: {:04}/{:02}/{:02} {:02}:{:02}:{:02}", st.wYear, st.wMonth, st.wDay, st.wHour, st.wMinute, st.wSecond);
    log->debug("Note: ihhook_log is multithreaded to accept logging from multiple threads so order of entries may not be sequential.");
    log->flush();
	}//SetupLog

	void IHH::CreateD3DHook() {
		d3d11Hook.reset();
		d3d11Hook = std::make_unique<D3D11Hook>();
		d3d11Hook->on_present([this](D3D11Hook& hook) { OnFrame(); });
		d3d11Hook->on_resize_buffers([this](D3D11Hook& hook) { OnReset(); });

		d3dHooked = d3d11Hook->hook();
		if (d3dHooked) {
			log->info("Hooked D3D11");
		}
		else {
			if (std::filesystem::exists("d3d11.dll")) {
				std::wstring title = L"MGSTPP - Infinite Heaven IHHook";
				std::wstring message =
					L"ERROR: Could not hook D3D11\n"
					L"Unknown d3d11.dll in MGS_TPP folder\n"
					//DEBUGNOW L"If this is from the FOV Modifier dll you can remove it\n"
					//L"as IHHook now has it intergrated\n"
					;
				MessageBox(NULL, message.c_str(), title.c_str(), NULL);
			}
			else {
				std::wstring title = L"MGSTPP - Infinite Heaven IHHook";
				std::wstring message =
					L"ERROR: Could not hook D3D11\n"
					L"See ihhook_log.txt in MGS_TPP folder for details.\n"
					;
				MessageBox(NULL, message.c_str(), title.c_str(), NULL);
			}//exists d3d11.dll

		}//d3dHooked
	}//CreateD3DHook

	//D3D11Hook->present
	//GOTCHA: this is blocking to actual d3d Present, so keep performance in mind
	void IHH::OnFrame() {

		//GOTCHA: frameInitialized is reset in OnReset, so if you want something to run only once a session use firstFrame in FramInisialize instead
		if (!frameInitialized) {
			if (!FrameInitialize()) {
				log->error("Failed to frame initialize IHHook");
				return;
			}

			log->info("IHHook frame initialized");
			frameInitialized = true;
			return;//tex give it an extra frame to settle I guess?
		}


		ImGuiContext* previousContext = ImGui::GetCurrentContext();
        ImGui::SetCurrentContext(p_imguiContext);

		ImGui_ImplDX11_NewFrame();
		ImGui_ImplWin32_NewFrame();
		ImGui::NewFrame();

		DrawUI();

		ImGui::EndFrame();
		ImGui::Render();
		ID3D11DeviceContext* context = nullptr;
		d3d11Hook->get_device()->GetImmediateContext(&context);

		context->OMSetRenderTargets(1, &mainRenderTargetView, NULL);

		ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());

		ImGui::SetCurrentContext(previousContext);
	}//OnFrame

	//D3D11Hook
	void IHH::OnReset() {
		log->info("OnReset");
		//DEBUGNOW
		auto log = spdlog::get("ihhook");
		if (log != NULL) {
			log->flush();
		}

		// RE2FW: Crashes if we don't release it at this point.
		CleanupRenderTarget();
		frameInitialized = false;

		//DEBUGNOW
		log->info("OnReset done");
		if (log != NULL) {
			log->flush();
		}

	}//OnReset

	//WindowsMessageHook
	bool IHH::OnMessage(HWND wnd, UINT message, WPARAM w_param, LPARAM l_param) {
		//spdlog::trace("OnMessage");

		if (!frameInitialized) {
			return true;
		}				

		bool handledMessage = !RawInput::OnMessage(wnd, message, w_param, l_param);

		if (drawUI) {

			ImGuiContext* previousContext = ImGui::GetCurrentContext();
            ImGui::SetCurrentContext(p_imguiContext);

			if(ImGui_ImplWin32_WndProcHandler(wnd, message, w_param, l_param) != 0) {
			auto& io = ImGui::GetIO();

			if (io.WantCaptureMouse || io.WantCaptureKeyboard || io.WantTextInput) {
				handledMessage = true;
				}
			}

			ImGui::SetCurrentContext(previousContext);
		}

		if (handledMessage) {
			//tex DEBUGNOW WORKAROUND: having menu eat all game can cause a problem if user was holding a key at the time as the keyup even will be eaten
			if (w_param == WM_KEYUP) {
				return true;
			}

			return false;//tex eat the message
		}
		return true;
	}//OnMessage

	//tex called on initialize and on device reset
	bool IHH::FrameInitialize() {
		if (frameInitialized) {
			return true;
		}

		log->info("Attempting to frame initialize");

		auto device = d3d11Hook->get_device();
		auto swapChain = d3d11Hook->get_swap_chain();

		// Wait.
		if (device == nullptr || swapChain == nullptr) {
			log->info("Device or SwapChain null. DirectX 12 may be in use. A crash may occur.");
			return false;
		}

		ID3D11DeviceContext* context = nullptr;
		device->GetImmediateContext(&context);

		DXGI_SWAP_CHAIN_DESC swapDesc{};
		swapChain->GetDesc(&swapDesc);

		hwnd = swapDesc.OutputWindow;

		//RE2FW: Explicitly call destructor first
		windowsMessageHook.reset();
		windowsMessageHook = std::make_unique<WindowsMessageHook>(hwnd);
		windowsMessageHook->on_message = [this](auto wnd, auto msg, auto wParam, auto lParam) {
			return OnMessage(wnd, msg, wParam, lParam);
		};

		log->info("Creating render target");

		CreateRenderTarget();

		log->info("Window Handle: {0:x}", (uintptr_t)hwnd);

		if (!ImGuiInitialized)
		{
			log->info("Initializing ImGui");

			IMGUI_CHECKVERSION();
			p_imguiContext = ImGui::CreateContext();
            ImGui::SetCurrentContext(p_imguiContext);
			
			ImGuiIO& io = ImGui::GetIO(); (void)io;
			//io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
			//io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

			log->info("Initializing ImGui Win32");

			if (!ImGui_ImplWin32_Init(hwnd)) {
				log->error("Failed to initialize ImGui.");
				return false;
			}

			log->info("Initializing ImGui D3D11");

			if (!ImGui_ImplDX11_Init(device, context)) {
				log->error("Failed to initialize ImGui.");
				return false;
			}
			ImGuiInitialized = true;
		}

		ImGui::StyleColorsDark();
		
		//SaveGuiStyle("styledefaultdump.lua");//DEBUGNOW

		if (firstFrame) {
			firstFrame = false;

			RawInput::InitializeInput();

			//HWND hWnd = OS::GetMainWindow();
			//DEBUGNOW RawInput::HookWndProc(hWnd);

			IHMenu::AddMenuCommands();

			InitCursorHook();

			InitStyleEditor();//StyleEditor

			IHMenu::SetInitialText();
		}//if firstFrame

		spdlog::info("frame initialized");
		return true;
	}//FrameInitialize

	void IHH::CreateRenderTarget() {
		CleanupRenderTarget();

		ID3D11Texture2D* backBuffer{ nullptr };
		if (d3d11Hook->get_swap_chain()->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&backBuffer) == S_OK) {
			d3d11Hook->get_device()->CreateRenderTargetView(backBuffer, NULL, &mainRenderTargetView);
			backBuffer->Release();
		}
	}//CreateRenderTarget

	void IHH::CleanupRenderTarget() {
		log->trace("CleanupRenderTarget");
		//DEBUGNOW
		auto log = spdlog::get("ihhook");
		if (log != NULL) {
			log->flush();
		}

		if (mainRenderTargetView != nullptr) {
			mainRenderTargetView->Release();
			mainRenderTargetView = nullptr;
		}
	}//CleanupRenderTarget

	void IHH::DrawUI() {
		//std::lock_guard _{ inputMutex };//DEBUGNOW

		IHMenu::ProcessMessages();

		auto& io = ImGui::GetIO();
		if (!drawUI) {
			RawInput::UnBlockMouseClick();
			RawInput::UnBlockKeyboard();
			unlockCursor = false;
			io.MouseDrawCursor = false;
			return;
		}

		//tex disable mouse input to game
		if (unlockCursor) {
			ImGui::SetNextFrameWantCaptureMouse(true);
		}

		if (io.WantCaptureMouse) {
			RawInput::BlockMouseClick();
		}
		else {
			RawInput::UnBlockMouseClick();
		}


		if (io.WantCaptureKeyboard) {
			RawInput::BlockKeyboard();
		}
		else {
			RawInput::UnBlockKeyboard();
		}

		io.MouseDrawCursor = unlockCursor;

		if (showStyleEditor) {
			ShowStyleEditor(&showStyleEditor, showStyleEditorPrev, NULL);
			showStyleEditorPrev = showStyleEditor;
		}

		if (showImguiDemo) {
			ImGui::ShowDemoWindow(&showImguiDemo);
		}

		if (menuOpen) {
			IHMenu::DrawMenu(&menuOpen, menuOpenPrev);
		}
		if (!menuOpen && menuOpenPrev) {
			IHMenu::QueueMessageIn("menuoff");
		}
		menuOpenPrev = menuOpen;

		//ImGui::End();
	}//DrawUI

	//TODO: move to own file
	//tex: even though it's saved as valid lua, we'll just parse it as text on IHHook side rather than dealing with back and forth through lua, and so IHHook can use it before lua is stood up
	bool ParseConfig(std::string fileName) {
		spdlog::debug("ParseConfig {}", fileName);
		std::ifstream infile(fileName);
		if (infile.fail()) {
			spdlog::warn("ParseConfig ifstream.fail for {}", fileName);
			return false;
		}

		config.debugMode = true;//TODO debug level instead
		config.openConsole = false;
		config.enableCityHook = false;
		config.enableFnvHook = false;
		config.logFileLoad = false;
		config.forceUsePatterns = false;
		config.logFoxStringCreateInPlace = false; //ZIP: Fox hooks

		std::string line;
		while (std::getline(infile, line)) {
			std::istringstream iss(line);
			//tex trim leading/trailing whitespace
			line = trim(line);
			if (line.size() == 0) {
				continue;
			}

			//tex deal with comments
			std::size_t found = line.find("--");
			//tex line is only comment
			if (found == 0) {
				continue;
			}
			//tex line has comment, trim to before comment
			if (found != std::string::npos) {
				line = line.substr(0, found - 1);
			}

			if (line.size() == 0) {
				continue;
			}

			//tex just skip the specific cases outright
			found = line.find("local this");
			if (found != std::string::npos) {
				continue;
			}
			found = line.find("return this");
			if (found != std::string::npos) {
				continue;
			}
			if (line == "}") {
				continue;
			}

			//tex trim trailing comma
			if (line[line.size() - 1] == ',') {
				line = line.substr(0, line.size() - 1);
			}

			found = line.find("=");
			if (found == std::string::npos) {
				continue;
			}

			std::string varName = line.substr(0, found);
			std::string valueStr = line.substr(found + 1);
			varName = trim(varName);
			valueStr = trim(valueStr);

			spdlog::info("config varName={},valueStr={}", varName, valueStr);

			//tex ugh
			if (varName == "debugMode") {
				config.debugMode = valueStr == "true";
			}
			else if (varName == "openConsole") {
				config.openConsole = valueStr == "true";
			}
			else if (varName == "enableCityHook") {
				config.enableCityHook = valueStr == "true";
			}
			else if (varName == "enableFnvHook") {
				config.enableFnvHook = valueStr == "true";
			}
			else if (varName == "logFileLoad") {
				config.logFileLoad = valueStr == "true";
			}
			else if (varName == "forceUsePatterns") {
				config.forceUsePatterns = valueStr == "true";
			}
			else if (varName == "logFoxStringCreateInPlace") { //ZIP: Fox hooks
				config.logFoxStringCreateInPlace = valueStr == "true";
			}
			else if (varName == "logTime") {
				config.logTime = valueStr == "true";
			}
		}//while line

		return true;
	}//

	//IN: BaseAddr, RealBaseAddr
	//IN: mgsvtpp_patterns
	//SIDE: addressSet
	//rebases the static addresses or sig scans for them
	bool IHH::RebaseAddresses()	{
		bool foundAllAddresses = true;
		for (auto const& entry : addressSet) {
			std::string name = entry.first;
			if (isTargetExe) {
				log->info("isTargetExe, rebasing addr {}", name);
				uint64_t addr = entry.second;
				uint64_t rebasedAddr = (addr - BaseAddr) + (int64_t)thisModule;
				addressSet[name] = rebasedAddr;
			}
			else {
				//tex fall back to sig scan
				log->info("!isTargetExe, sig scanning");
				addressSet[name] = 0;
				auto it = mgsvtpp_patterns.find(name);
				if (it != mgsvtpp_patterns.end()) {
					//found
					//const char* sig = it->second;
					//const char* mask = mgsvtpp_masks[name];//ASSUMPTION: if sig exists then mask does
					//uintptr_t addr = MemoryUtils::sigscan(name.c_str(), sig, mask);//tex returns null if not found

					const char* pattern = it->second.c_str();
					auto tstart = std::chrono::high_resolution_clock::now();
					uintptr_t addr = (uintptr_t)MemoryUtils::PatternScan(pattern);//tex returns null if not found
					auto tend = std::chrono::high_resolution_clock::now();
					auto duration = std::chrono::duration_cast<std::chrono::microseconds>(tend - tstart).count();
					if (addr == NULL) {
						log->debug("sigscan not found {} in(microseconds): {}", name, duration);
						foundAllAddresses = false;
					}
					else {
						log->debug("sigscan found {} at 0x{:x} in(microseconds): {}", name, addr, duration);//DEBUGNOW dump addr
					}

					addressSet[name] = addr;
				}
				else {
					log->warn("Could not find sig for {}", name);
				}
			}//if isTargetExe
		}//for addressSet
		return foundAllAddresses;
	}//RebaseAddresses

	typedef DWORD(WINAPI* CREATEHOOKS)();
	void IHH::CreateAllHooks() {
		Hooks_CityHash::CreateHooks();
		Hooks_FNVHash::CreateHooks();
		Hooks_Lua::CreateHooks();
		Hooks_TPP::CreateHooks();
		Hooks_FOV::CreateHooks();
		Hooks_LoadFile::CreateHooks();//DEBUGNOW exploring
		Hooks_Character::CreateHooks();
		Hooks_Buddy::CreateHooks(); //ZIP: For buddies
		Hooks_Vehicle::CreateHooks(); //ZIP: For vehicles
		//Hooks_FoxString::CreateHooks(); //ZIP: FoxString hook
		//Hooks_CallMenu::CreateHooks(); //ZIP: Call Menu
	}//CreateAllHooks
}//namespace IHHook