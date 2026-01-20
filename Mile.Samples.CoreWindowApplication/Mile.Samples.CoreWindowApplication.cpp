/*
 * PROJECT:    Mile.Samples.CoreWindowApplication
 * FILE:       Mile.Samples.CoreWindowApplication.cpp
 * PURPOSE:    Implementation for Mile.Samples.CoreWindowApplication
 *
 * LICENSE:    The MIT License
 *
 * MAINTAINER: MouriNaruto (Kenji.Mouri@outlook.com)
 */

#include <Mile.Helpers.h>

#include <CoreWindow.h>

#include <winrt/Windows.Foundation.h>
#include <winrt/Windows.Foundation.Collections.h>
#include <winrt/Windows.ApplicationModel.Core.h>
#include <winrt/Windows.UI.Core.h>
#include <winrt/Windows.UI.Composition.h>
#include <winrt/Windows.UI.Input.h>

namespace winrt
{
    using Windows::ApplicationModel::Activation::IActivatedEventArgs;
    using Windows::ApplicationModel::Core::CoreApplication;
    using Windows::ApplicationModel::Core::CoreApplicationView;
    using Windows::ApplicationModel::Core::ICoreApplicationView;
    using Windows::ApplicationModel::Core::IFrameworkView;
    using Windows::ApplicationModel::Core::IFrameworkViewSource;
    using Windows::Foundation::IInspectable;
    using Windows::Foundation::Numerics::float2;
    using Windows::Foundation::Numerics::float3;
    using Windows::Foundation::TypedEventHandler;
    using Windows::UI::Color;
    using Windows::UI::Core::PointerEventArgs;
    using Windows::UI::Composition::Compositor;
    using Windows::UI::Composition::ContainerVisual;
    using Windows::UI::Composition::CompositionTarget;
    using Windows::UI::Composition::SpriteVisual;
    using Windows::UI::Composition::Visual;
    using Windows::UI::Composition::VisualCollection;
    using Windows::UI::ColorHelper;
    using Windows::UI::Core::CoreDispatcher;
    using Windows::UI::Core::CoreProcessEventsOption;
    using Windows::UI::Core::CoreWindow;
}

struct App : winrt::implements<
    App,
    winrt::IFrameworkViewSource,
    winrt::IFrameworkView>
{
    winrt::CompositionTarget m_target{ nullptr };
    winrt::VisualCollection m_visuals{ nullptr };
    winrt::Visual m_selected{ nullptr };
    winrt::float2 m_offset{};

    winrt::IFrameworkView CreateView()
    {
        return *this;
    }

    void Initialize(
        winrt::CoreApplicationView const&)
    {
    }

    void Load(
        winrt::hstring const&)
    {
    }

    void Uninitialize()
    {
    }

    void Run()
    {
        winrt::CoreWindow window = winrt::CoreWindow::GetForCurrentThread();
        window.Activate();

        winrt::CoreDispatcher dispatcher = window.Dispatcher();
        dispatcher.ProcessEvents(winrt::CoreProcessEventsOption::ProcessUntilQuit);
    }

    void SetWindow(
        winrt::CoreWindow const& window)
    {
        winrt::Compositor compositor;
        winrt::ContainerVisual root = compositor.CreateContainerVisual();
        m_target = compositor.CreateTargetForCurrentView();
        m_target.Root(root);
        m_visuals = root.Children();

        window.PointerPressed({ this, &App::OnPointerPressed });
        window.PointerMoved({ this, &App::OnPointerMoved });

        window.PointerReleased([&](auto && ...)
        {
            m_selected = nullptr;
        });
    }

    void OnPointerPressed(
        winrt::IInspectable const&,
        winrt::PointerEventArgs const& args)
    {
        winrt::float2 const point = args.CurrentPoint().Position();

        for (winrt::Visual visual : m_visuals)
        {
            winrt::float3 const offset = visual.Offset();
            winrt::float2 const size = visual.Size();

            if (point.x >= offset.x &&
                point.x < offset.x + size.x &&
                point.y >= offset.y &&
                point.y < offset.y + size.y)
            {
                m_selected = visual;
                m_offset.x = offset.x - point.x;
                m_offset.y = offset.y - point.y;
            }
        }

        if (m_selected)
        {
            m_visuals.Remove(m_selected);
            m_visuals.InsertAtTop(m_selected);
        }
        else
        {
            AddVisual(point);
        }
    }

    void OnPointerMoved(
        winrt::IInspectable const&,
        winrt::PointerEventArgs const& args)
    {
        if (m_selected)
        {
            winrt::float2 const point = args.CurrentPoint().Position();

            m_selected.Offset(
                {
                    point.x + m_offset.x,
                    point.y + m_offset.y,
                    0.0f
                });
        }
    }

    void AddVisual(
        winrt::float2 const point)
    {
        winrt::Compositor compositor = m_visuals.Compositor();
        winrt::SpriteVisual visual = compositor.CreateSpriteVisual();

        static winrt::Color colors[] =
        {
            { 0xDC, 0x5B, 0x9B, 0xD5 },
            { 0xDC, 0xED, 0x7D, 0x31 },
            { 0xDC, 0x70, 0xAD, 0x47 },
            { 0xDC, 0xFF, 0xC0, 0x00 }
        };

        static unsigned last = 0;
        unsigned const next = ++last % _countof(colors);
        visual.Brush(compositor.CreateColorBrush(colors[next]));

        float const BlockSize = 100.0f;

        visual.Size(
            {
                BlockSize,
                BlockSize
            });

        visual.Offset(
            {
                point.x - BlockSize / 2.0f,
                point.y - BlockSize / 2.0f,
                0.0f,
            });

        m_visuals.InsertAtTop(visual);

        m_selected = visual;
        m_offset.x = -BlockSize / 2.0f;
        m_offset.y = -BlockSize / 2.0f;
    }
};

int WINAPI wWinMain(
    _In_ HINSTANCE hInstance,
    _In_opt_ HINSTANCE hPrevInstance,
    _In_ LPWSTR lpCmdLine,
    _In_ int nShowCmd)
{
    UNREFERENCED_PARAMETER(hInstance);
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    winrt::init_apartment(winrt::apartment_type::single_threaded);

    winrt::CoreWindow CoreWindow = nullptr;
    {
        void* RawCoreWindow = nullptr;
        winrt::check_hresult(::MileCreateCoreWindow(
            MILE_COREWINDOW_IMMERSIVE_HOSTED,
            L"Hosted CoreWindow Demo",
            0,
            0,
            0,
            0,
            0,
            ::GetDesktopWindow(),
            winrt::guid_of<winrt::CoreWindow>(),
            &RawCoreWindow));
        CoreWindow = winrt::CoreWindow(
            RawCoreWindow,
            winrt::take_ownership_from_abi);
    }

    HWND CoreWindowHandle = nullptr;

    winrt::com_ptr<ICoreWindowInterop> CoreWindowInterop =
        CoreWindow.as<ICoreWindowInterop>();
    winrt::check_hresult(
        CoreWindowInterop->get_WindowHandle(&CoreWindowHandle));

    ::SetWindowLongW(
        CoreWindowHandle,
        GWL_EXSTYLE,
        WS_EX_STATICEDGE | WS_EX_DLGMODALFRAME);
    ::SetWindowLongW(
        CoreWindowHandle,
        GWL_STYLE,
        WS_OVERLAPPEDWINDOW);

    UINT DpiValue = ::GetDpiForWindow(CoreWindowHandle);

    ::SetWindowPos(
        CoreWindowHandle,
        nullptr,
        ::MulDiv(100, DpiValue, USER_DEFAULT_SCREEN_DPI),
        ::MulDiv(100, DpiValue, USER_DEFAULT_SCREEN_DPI),
        ::MulDiv(800, DpiValue, USER_DEFAULT_SCREEN_DPI),
        ::MulDiv(600, DpiValue, USER_DEFAULT_SCREEN_DPI),
        SWP_NONE);

    ::ShowWindow(CoreWindowHandle, nShowCmd);
    ::UpdateWindow(CoreWindowHandle);

    winrt::IFrameworkView InstanceView = winrt::make<App>().CreateView();
    InstanceView.SetWindow(CoreWindow);
    InstanceView.Run();

    return 0;
}
