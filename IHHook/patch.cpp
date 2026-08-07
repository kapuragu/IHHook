#include "patch.h"

#include <spdlog/spdlog.h>

void* GetTarget(uintptr_t pointer)
{
    uintptr_t exeBase = reinterpret_cast<uintptr_t>(GetModuleHandleW(nullptr));
    constexpr uintptr_t EXE_PREFERRED_BASE = 0x140000000ull;
    void* target = reinterpret_cast<void*>(exeBase+(pointer-EXE_PREFERRED_BASE));
    if (pointer==NULL)
    {
        spdlog::error("[Patch] GetTarget({:p}): ResolveGameAddress address is NULL", pointer);
        return NULL;
    }
    
    if (pointer==0)
    {
        spdlog::error("[Patch] GetTarget({:p}): ResolveGameAddress address is 0", pointer);
        return NULL;
    }
    return target;
}

bool ComparePointerBytes(uintptr_t pointer, std::uint8_t* bytes, SIZE_T dwSize)
{
    void* target = GetTarget(pointer);
    
    const auto* cur = static_cast<const std::uint8_t*>(target);
    
    bool ret = std::memcmp(cur,bytes, dwSize)==0;
    
    return ret;
}

bool TogglePatch(bool isEnable, uintptr_t pointer, SIZE_T dwSize, std::uint8_t* originalBytes, std::uint8_t* enabledBytes)
{
    
    void* target = GetTarget(pointer);
    if (!target)
    {
        spdlog::error("[Patch] TogglePatch(%s): ResolveGameAddress @{:p} null", isEnable ? "true" : "false", pointer);
        return false;
    }
    
    if (!std::memcmp(originalBytes,enabledBytes, dwSize)==0)   //not trying to patch og with og
    {
        if (!ComparePointerBytes(pointer,originalBytes,dwSize)) //source doesn't match original
        {
            spdlog::error("[Patch] unexpected bytes at {:p} - not patching", target);
            return false;
        }
    }

    DWORD oldProtect = 0;
    if (!VirtualProtect(target, dwSize, PAGE_EXECUTE_READWRITE, &oldProtect))
    {
        spdlog::error("[Patch] TogglePatch(%s): VirtualProtect failed @{:p} (err={:p})", isEnable ? "true" : "false", pointer, GetLastError());
        return false;
    }
    
    std::uint8_t* src = isEnable ? enabledBytes : originalBytes;
    std::memcpy(target, src, dwSize);

    DWORD restored = 0;
    VirtualProtect(target, dwSize, oldProtect, &restored);
    FlushInstructionCache(GetCurrentProcess(), target, dwSize);
    return true;
}
