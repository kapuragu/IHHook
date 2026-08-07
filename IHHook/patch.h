#pragma once
#include <cstdint>

#include "D3D11Hook.hpp"

class patch
{
public:
    
};
void* GetTarget(uintptr_t pointer);
bool ComparePointerBytes(uintptr_t pointer, std::uint8_t* bytes, SIZE_T dwSize);
bool TogglePatch(bool isEnable, uintptr_t pointer, SIZE_T dwSize, std::uint8_t* originalBytes, std::uint8_t* enabledBytes);