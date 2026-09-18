#pragma once
#include "windowsapi.h"
#include <filesystem>
#include <fstream>
#include <string>
#include <vector>
#include "spdlog/spdlog.h"

namespace PluginLoader
{
    void LoadPlugins();
    void UnloadPlugins();
}

