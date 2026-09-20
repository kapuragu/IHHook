
#include "plugin_loader.hpp"
#include <Windows.h>
#include <filesystem>
#include "IHHook.h"

namespace IHHook
{
    namespace Plugin_Loader
    {
        static std::vector<HMODULE> loaded_plugins{};
        namespace fs = std::filesystem;

        void LoadPlugins()
        {
            wchar_t module_path[MAX_PATH]{};
            HMODULE self = nullptr;

            if (!GetModuleHandleExW(
                    GET_MODULE_HANDLE_EX_FLAG_FROM_ADDRESS | GET_MODULE_HANDLE_EX_FLAG_UNCHANGED_REFCOUNT, reinterpret_cast<LPCWSTR>(&LoadPlugins), &self)
                || self == nullptr)
            {
                spdlog::error(L"Failed to get IHHook module handle.");
                return;
            }

            if (GetModuleFileNameW(self, module_path, MAX_PATH) == 0)
            {
                spdlog::error(L"Failed to get IHHook module path.");
                return;
            }

            const fs::path plugin_dir = fs::path(module_path).parent_path() / L"plugins";

            spdlog::info(L"Searching for plugins in {}", plugin_dir.wstring());

            if (!fs::exists(plugin_dir) || !fs::is_directory(plugin_dir))
            {
                spdlog::info(L"Plugin directory does not exist or Plugin path is not a directory skipping plugin loading...");
                return;
            }

            for (const auto& entry : fs::directory_iterator(plugin_dir))
            {
                if (!entry.is_regular_file())
                {
                    continue;
                }

                const fs::path& plugin_path = entry.path();
                std::wstring ext = plugin_path.extension();
                if (ext != L".dll" && ext != L".asi")
                {
                    continue;
                }

                const std::wstring plugin_name = plugin_path.filename().wstring();
                spdlog::info(L"Found plugin and loading: {}", plugin_name);

                HMODULE plugin = LoadLibraryW(plugin_path.c_str());
                if (plugin == nullptr)
                {
                    spdlog::error(L"Failed to load plugin '{}'. Error code: {}", plugin_name, GetLastError());
                    continue;
                }

                loaded_plugins.push_back(plugin);
                spdlog::info(L"Successfully loaded plugin '{}'.", plugin_name);
            }

            if (loaded_plugins.size() > 0)
            {
                spdlog::info(L"Plugin loading complete. {} plugin(s) loaded.", loaded_plugins.size());
            }
            else
            {
                spdlog::info(L"No plugins found.");
            }
        }

        void UnloadPlugins()
        {
            // Unload in reverse order of loading
            for (auto it = loaded_plugins.rbegin(); it != loaded_plugins.rend(); ++it)
            {
                FreeLibrary(*it);
            }
            loaded_plugins.clear();
        }

    }
}