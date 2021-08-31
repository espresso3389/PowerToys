#include "pch.h"
#include "ExplorerItem.h"
#include "ExplorerItem.g.cpp"

namespace winrt::PowerRenameUI_new::implementation
{
    ExplorerItem::ExplorerItem(hstring const& original, int32_t type) :
        m_original{ original }, m_type{ type }
    {
    }
    
    hstring ExplorerItem::Original()
    {
        return m_original;
    }
    
    void ExplorerItem::Original(hstring const& value)
    {
        if (m_original != value)
        {
            m_original = value;
            m_propertyChanged(*this, Windows::UI::Xaml::Data::PropertyChangedEventArgs{ L"Original" });
        }
    }
    
    hstring ExplorerItem::Renamed()
    {
        return m_renamed;
    }
    
    void ExplorerItem::Renamed(hstring const& value)
    {
        if (m_renamed != value)
        {
            m_renamed = value;
            m_propertyChanged(*this, Windows::UI::Xaml::Data::PropertyChangedEventArgs{ L"Renamed" });
        }
    }

    int32_t ExplorerItem::Type()
    {
        return m_type;
    }

    void ExplorerItem::Type(int32_t value)
    {
        m_type = value;
    }
    
    winrt::Windows::Foundation::Collections::IObservableVector<winrt::PowerRenameUI_new::ExplorerItem> ExplorerItem::Children()
    {
        return m_children;
    }
    
    winrt::event_token ExplorerItem::PropertyChanged(winrt::Windows::UI::Xaml::Data::PropertyChangedEventHandler const& handler)
    {
        return m_propertyChanged.add(handler);
    }
    
    void ExplorerItem::PropertyChanged(winrt::event_token const& token) noexcept
    {
        m_propertyChanged.remove(token);
    }
}
