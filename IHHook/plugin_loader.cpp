
#include "plugin_loader.hpp"

namespace fs = std::filesystem;

namespace PluginLoader
{
    static std::vector<HMODULE> loaded_plugins {};

    // Returns true only for a valid 64-bit DLL PE image.
    static bool IsValidDll(const fs::path& path)
    {
        std::ifstream file(path, std::ios::binary | std::ios::ate);
        if (!file)
            return false;

        const auto file_size = file.tellg();
        if (file_size < static_cast<std::streamsize>(sizeof(IMAGE_DOS_HEADER)))
            return false;

        file.seekg(0);

        IMAGE_DOS_HEADER dos{};
        if (!file.read(reinterpret_cast<char*>(&dos), sizeof(dos)))
            return false;

        // "MZ"
        if (dos.e_magic != IMAGE_DOS_SIGNATURE)
            return false;

        // e_lfanew must be non-negative and leave room for at least
        // the PE signature + IMAGE_FILE_HEADER.
        if (dos.e_lfanew < 0)
            return false;

        const auto lfanew = static_cast<std::streamsize>(dos.e_lfanew);
        const auto min_required = lfanew + static_cast<std::streamsize>(sizeof(DWORD) + sizeof(IMAGE_FILE_HEADER));

        if (lfanew >= file_size || min_required > file_size)
            return false;

        file.seekg(lfanew);

        DWORD signature = 0;
        if (!file.read(reinterpret_cast<char*>(&signature), sizeof(signature)))
            return false;

        // "PE\0\0"
        if (signature != IMAGE_NT_SIGNATURE)
            return false;

        IMAGE_FILE_HEADER fh{};
        if (!file.read(reinterpret_cast<char*>(&fh), sizeof(fh)))
            return false;

        // Game is 64-bit → only accept AMD64 and File must be a DLL
        if ((fh.Machine != IMAGE_FILE_MACHINE_AMD64) || ((fh.Characteristics & IMAGE_FILE_DLL) == 0))
            return false;

        return true;
    }

    void LoadPlugins()
    {
        wchar_t module_path[MAX_PATH]{};
        HMODULE self = nullptr;

        if (!GetModuleHandleExW(GET_MODULE_HANDLE_EX_FLAG_FROM_ADDRESS | GET_MODULE_HANDLE_EX_FLAG_UNCHANGED_REFCOUNT, reinterpret_cast<LPCWSTR>(&LoadPlugins), &self) || self == nullptr)
        {
            spdlog::error("Failed to get IHHook module handle.");
            return;
        }

        if (GetModuleFileNameW(self, module_path, MAX_PATH) == 0)
        {
            spdlog::error("Failed to get IHHook module path.");
            return;
        }

        const fs::path plugin_dir = fs::path(module_path).parent_path() / L"plugins";

        spdlog::info("Searching for plugins in {}", plugin_dir.string());

        if (!fs::exists(plugin_dir) || !fs::is_directory(plugin_dir))
        {
            spdlog::info("Plugin directory does not exist or Plugin path is not a directory skipping plugin loading...");
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
            spdlog::info(L"Found plugin: {}", plugin_name);

            //not sure if this is required
            if (!IsValidDll(plugin_path))
            {
                spdlog::error(L"Rejected plugin '{}': invalid PE/DLL (or not 64-bit).", plugin_name);
                continue;
            }

            spdlog::info(L"Loading plugin '{}'.", plugin_name);

            HMODULE plugin = LoadLibraryW(plugin_path.c_str());
            if (plugin == nullptr)
            {
                spdlog::error(L"Failed to load plugin '{}'. GetLastError() code: {}", plugin_name, GetLastError());
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