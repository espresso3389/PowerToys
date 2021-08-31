#pragma once
#include "RegExShortcut.g.h"

namespace winrt::PowerRenameUI_new::implementation
{
    struct RegExShortcut : RegExShortcutT<RegExShortcut>
    {
        RegExShortcut() = delete;

        RegExShortcut(hstring const& code, hstring const& description);
        hstring Code();
        void Code(hstring const& value);
        hstring Description();
        void Description(hstring const& value);
        winrt::event_token PropertyChanged(winrt::Windows::UI::Xaml::Data::PropertyChangedEventHandler const& handler);
        void PropertyChanged(winrt::event_token const& token) noexcept;

    private:
        winrt::hstring m_code;
        winrt::hstring m_description;
        winrt::event<Windows::UI::Xaml::Data::PropertyChangedEventHandler> m_propertyChanged;
    };
}
namespace winrt::PowerRenameUI_new::factory_implementation
{
    struct RegExShortcut : RegExShortcutT<RegExShortcut, implementation::RegExShortcut>
    {
    };
}
