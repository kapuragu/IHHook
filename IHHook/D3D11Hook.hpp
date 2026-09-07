// D3D11Hook.hpp - from RE2Framework
#pragma once

#include <functional>

#include <d3d11.h>
#include <dxgi.h>
#include <memory>

#include "utility/FunctionHook.hpp"

class D3D11Hook
{
  public:
    typedef std::function<void(D3D11Hook&)> OnPresentFn;
    typedef std::function<void(D3D11Hook&)> OnResizeBuffersFn;

    D3D11Hook() = default;
    virtual ~D3D11Hook();

    bool hook();
    bool unhook();

    void on_present(OnPresentFn fn) { m_on_present = fn; }
    void on_resize_buffers(OnResizeBuffersFn fn) { m_on_resize_buffers = fn; }

    ID3D11Device* get_device() { return m_device; }
    IDXGISwapChain* get_swap_chain() { return m_swap_chain; }

  protected:
    ID3D11Device* m_device{nullptr};
    IDXGISwapChain* m_swap_chain{nullptr};
    bool m_hooked{false};

    std::unique_ptr<FunctionHook> m_present_hook{};
    std::unique_ptr<FunctionHook> m_resize_buffers_hook{};
    OnPresentFn m_on_present{nullptr};
    OnResizeBuffersFn m_on_resize_buffers{nullptr};

    static HRESULT WINAPI present(__int64 a1, __int64 SyncInterval);
    static HRESULT WINAPI resize_buffers(__int64 a1, unsigned int buffer_count, unsigned int width, unsigned int height, int new_format, int swap_chain_flags);
};
