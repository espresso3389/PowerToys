#include "pch.h"
#include "RegExShortcut.h"
#include "RegExShortcut.g.cpp"

namespace winrt::PowerRenameUI_new::implementation
{
    RegExShortcut::RegExShortcut(hstring const& code, hstring const& description) :
        m_code{ code }, m_description{ description }
    {
    }

    hstring RegExShortcut::Code()
    {
        return m_code;
    }

    void RegExShortcut::Code(hstring const& value)
    {
        if (m_code != value)
        {
            m_code = value;
            m_propertyChanged(*this, Windows::UI::Xaml::Data::PropertyChangedEventArgs{ L"Code" });
        }
    }

    hstring RegExShortcut::Description()
    {
        return m_description;
    }

    void RegExShortcut::Description(hstring const& value)
    {
        if (m_description != value)
        {
            m_description = value;
            m_propertyChanged(*this, Windows::UI::Xaml::Data::PropertyChangedEventArgs{ L"Description" });
        }
    }

    winrt::event_token RegExShortcut::PropertyChanged(winrt::Windows::UI::Xaml::Data::PropertyChangedEventHandler const& handler)
    {
        return m_propertyChanged.add(handler);
    }

    void RegExShortcut::PropertyChanged(winrt::event_token const& token) noexcept
    {
        m_propertyChanged.remove(token);
    }
}
