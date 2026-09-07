// D3D11Hook.cpp - from RE2Framework
// Hooks by creating a dummy device and swapchain to get the addresses of present and resizebuffers from the swapchains dummy swapchain's virtual method table
#include <algorithm>
#include <spdlog/spdlog.h>

#include "D3D11Hook.hpp"
#include "Hooking.Patterns/Hooking.Patterns.h"

using namespace std;

static D3D11Hook* g_d3d11_hook = nullptr;

D3D11Hook::~D3D11Hook() { unhook(); }

bool D3D11Hook::hook()
{
    spdlog::info("Hooking D3D11");

    g_d3d11_hook = this;

    ID3D11Device* pDevice = hook::get_address<ID3D11Device*>(hook::get_pattern<uint8_t>("85 C0 0F 88 CB 00 00 00 48 8B", 0xA)); // static ptr to the games D3D11 device

    uint8_t* present_fn = hook::get_address<uint8_t*>(hook::get_pattern<uint8_t>("E8 ? ? ? ? 85 C0 75 12 38 43 69", 1)); // games own wrapper around IDXGISwapChain::Present

    uint8_t* resize_buffers_fn = hook::get_address<uint8_t*>(hook::get_pattern<uint8_t>("BA 03 00 00 00 48 8B 4F 20",0xA)); // games own wrapper around IDXGISwapChain::ResizeBuffers

    m_device = pDevice;

    m_present_hook = std::make_unique<FunctionHook>(present_fn, (uintptr_t)&D3D11Hook::present);
    m_resize_buffers_hook = std::make_unique<FunctionHook>(resize_buffers_fn, (uintptr_t)&D3D11Hook::resize_buffers);


    m_hooked = m_present_hook->create() && m_resize_buffers_hook->create();

    return m_hooked;
}

bool D3D11Hook::unhook()
{
    if (!m_hooked)
    {
        return true;
    }

    spdlog::info("Unhooking D3D11");

    if (m_present_hook->remove() && m_resize_buffers_hook->remove())
    {
        m_hooked = false;
        return true;
    }

    return false;
}

HRESULT WINAPI D3D11Hook::present(__int64 a1, __int64 SyncInterval)
{
    auto d3d11 = g_d3d11_hook;

    // a1 is some struct or class that contains a pointer to the swapchain at offset 0x18, so we can get the swapchain from it

    IDXGISwapChain* swap_chain = reinterpret_cast<IDXGISwapChain*>(*reinterpret_cast<uintptr_t*>(a1 + 0x18));

    d3d11->m_swap_chain = swap_chain;

    swap_chain->GetDevice(__uuidof(d3d11->m_device), (void**)&d3d11->m_device);

    if (d3d11->m_on_present)
    {
        d3d11->m_on_present(*d3d11);
    }

    auto present_fn = d3d11->m_present_hook->get_original<decltype(D3D11Hook::present)>();

    return present_fn(a1, SyncInterval);
}

HRESULT WINAPI D3D11Hook::resize_buffers(__int64 a1, unsigned int buffer_count, unsigned int width, unsigned int height, int new_format, int swap_chain_flags)
{
    auto d3d11 = g_d3d11_hook;

    if (d3d11->m_on_resize_buffers)
    {
        d3d11->m_on_resize_buffers(*d3d11);
    }

    auto resize_buffers_fn = d3d11->m_resize_buffers_hook->get_original<decltype(D3D11Hook::resize_buffers)>();

    return resize_buffers_fn(a1, buffer_count, width, height, new_format, swap_chain_flags);
}