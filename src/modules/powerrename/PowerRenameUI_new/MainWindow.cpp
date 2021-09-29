#include "pch.h"
#include "MainWindow.h"
#if __has_include("MainWindow.g.cpp")
#include "MainWindow.g.cpp"
#endif
#include <winuser.h>

using namespace winrt;
using namespace Windows::UI::Xaml;

namespace winrt::PowerRenameUI_new::implementation
{
    MainWindow::MainWindow() :
        m_allSelected{ true }
    {
        m_searchMRU = winrt::single_threaded_observable_vector<hstring>();
        m_replaceMRU = winrt::single_threaded_observable_vector<hstring>();

        m_explorerItems = winrt::single_threaded_observable_vector<PowerRenameUI_new::ExplorerItem>();

        m_searchRegExShortcuts = winrt::single_threaded_observable_vector<PowerRenameUI_new::PatternSnippet>();
        m_searchRegExShortcuts.Append(winrt::make<PowerRenameUI_new::implementation::PatternSnippet>(L"\\.", L"Matches any character"));
        m_searchRegExShortcuts.Append(winrt::make<PowerRenameUI_new::implementation::PatternSnippet>(L"\\d", L"Any digit, short for [0-9]"));
        m_searchRegExShortcuts.Append(winrt::make<PowerRenameUI_new::implementation::PatternSnippet>(L"\\D", L"A non-digit, short for [^0-9]"));
        m_searchRegExShortcuts.Append(winrt::make<PowerRenameUI_new::implementation::PatternSnippet>(L"\\w", L"A non-whitespace character, short for [^\\s]"));
        m_searchRegExShortcuts.Append(winrt::make<PowerRenameUI_new::implementation::PatternSnippet>(L"\\S", L"A word character, short for [a-zA-Z_0-9]"));
        m_searchRegExShortcuts.Append(winrt::make<PowerRenameUI_new::implementation::PatternSnippet>(L"\\S+", L"Several non-whitespace characters"));
        m_searchRegExShortcuts.Append(winrt::make<PowerRenameUI_new::implementation::PatternSnippet>(L"\\b", L"Matches a word boundary where a word character is [a-zA-Z0-9_]."));

        m_dateTimeShortcuts = winrt::single_threaded_observable_vector<PowerRenameUI_new::PatternSnippet>();
        m_dateTimeShortcuts.Append(winrt::make<PowerRenameUI_new::implementation::PatternSnippet>(L"$YYYY", L"Year represented by a full four or five digits, depending on the calendar used"));
        m_dateTimeShortcuts.Append(winrt::make<PowerRenameUI_new::implementation::PatternSnippet>(L"$YY", L"Year represented only by the last two digits. A leading zero is added for single-digit years"));
        m_dateTimeShortcuts.Append(winrt::make<PowerRenameUI_new::implementation::PatternSnippet>(L"$Y", L"Year represented only by the last digit."));
        m_dateTimeShortcuts.Append(winrt::make<PowerRenameUI_new::implementation::PatternSnippet>(L"$MMMM", L"Name of the month"));
        m_dateTimeShortcuts.Append(winrt::make<PowerRenameUI_new::implementation::PatternSnippet>(L"$MMM", L"Abbreviated name of the month"));
        m_dateTimeShortcuts.Append(winrt::make<PowerRenameUI_new::implementation::PatternSnippet>(L"$MM", L"Month as digits with leading zeros for single-digit months"));
        m_dateTimeShortcuts.Append(winrt::make<PowerRenameUI_new::implementation::PatternSnippet>(L"$M", L"Month as digits without leading zeros for single-digit months"));
        m_dateTimeShortcuts.Append(winrt::make<PowerRenameUI_new::implementation::PatternSnippet>(L"$DDDD", L"Name of the day of the week"));
        m_dateTimeShortcuts.Append(winrt::make<PowerRenameUI_new::implementation::PatternSnippet>(L"$DDD", L"Abbreviated name of the day of the week"));
        m_dateTimeShortcuts.Append(winrt::make<PowerRenameUI_new::implementation::PatternSnippet>(L"$DD", L"Day of the month as digits with leading zeros for single-digit days"));
        m_dateTimeShortcuts.Append(winrt::make<PowerRenameUI_new::implementation::PatternSnippet>(L"$D", L"Day of the month as digits without leading zeros for single-digit days"));
        m_dateTimeShortcuts.Append(winrt::make<PowerRenameUI_new::implementation::PatternSnippet>(L"$hh", L"Hours with leading zeros for single-digit hours"));
        m_dateTimeShortcuts.Append(winrt::make<PowerRenameUI_new::implementation::PatternSnippet>(L"$h", L"Hours without leading zeros for single-digit hours"));
        m_dateTimeShortcuts.Append(winrt::make<PowerRenameUI_new::implementation::PatternSnippet>(L"$mm", L"Minutes with leading zeros for single-digit minutes"));
        m_dateTimeShortcuts.Append(winrt::make<PowerRenameUI_new::implementation::PatternSnippet>(L"$m", L"Minutes without leading zeros for single-digit minutes"));
        m_dateTimeShortcuts.Append(winrt::make<PowerRenameUI_new::implementation::PatternSnippet>(L"$ss", L"Seconds with leading zeros for single-digit seconds"));
        m_dateTimeShortcuts.Append(winrt::make<PowerRenameUI_new::implementation::PatternSnippet>(L"$s", L"Seconds without leading zeros for single-digit seconds"));
        m_dateTimeShortcuts.Append(winrt::make<PowerRenameUI_new::implementation::PatternSnippet>(L"$fff", L"Milliseconds represented by full three digits"));
        m_dateTimeShortcuts.Append(winrt::make<PowerRenameUI_new::implementation::PatternSnippet>(L"$ff", L"Milliseconds represented only by the first two digit"));
        m_dateTimeShortcuts.Append(winrt::make<PowerRenameUI_new::implementation::PatternSnippet>(L"$f", L"Milliseconds represented only by the first digit"));

        InitializeComponent();
    }

    Windows::Foundation::Collections::IObservableVector<hstring> MainWindow::SearchMRU()
    {
        return m_searchMRU;
    }

    Windows::Foundation::Collections::IObservableVector<hstring> MainWindow::ReplaceMRU()
    {
        return m_replaceMRU;
    }
    
    winrt::Windows::Foundation::Collections::IObservableVector<winrt::PowerRenameUI_new::ExplorerItem> MainWindow::ExplorerItems()
    {
        return m_explorerItems;
    }

    winrt::Windows::Foundation::Collections::IObservableVector<winrt::PowerRenameUI_new::PatternSnippet> MainWindow::SearchRegExShortcuts()
    {
        return m_searchRegExShortcuts;
    }

    winrt::Windows::Foundation::Collections::IObservableVector<winrt::PowerRenameUI_new::PatternSnippet> MainWindow::DateTimeShortcuts()
    {
        return m_dateTimeShortcuts;
    }

    Windows::UI::Xaml::Controls::AutoSuggestBox MainWindow::AutoSuggestBoxSearch()
    {
        return textBox_search();
    }

    Windows::UI::Xaml::Controls::AutoSuggestBox MainWindow::AutoSuggestBoxReplace()
    {
        return textBox_replace();
    }

    Windows::UI::Xaml::Controls::CheckBox MainWindow::ChckBoxRegex()
    {
        return chckBox_regex();
    }

    Windows::UI::Xaml::Controls::CheckBox MainWindow::ChckBoxCaseSensitive()
    {
        return chckBox_case();
    }

    Windows::UI::Xaml::Controls::CheckBox MainWindow::ChckBoxMatchAll()
    {
        return chckBox_matchAll();
    }

    Windows::UI::Xaml::Controls::ComboBox MainWindow::ComboBoxRenameParts()
    {
        return comboBox_renameParts();
    }

    Windows::UI::Xaml::Controls::Primitives::ToggleButton MainWindow::TglBtnIncludeFiles()
    {
        return tglBtn_includeFiles();
    }

    Windows::UI::Xaml::Controls::Primitives::ToggleButton MainWindow::TglBtnIncludeFolders()
    {
        return tglBtn_includeFolders();
    }

    Windows::UI::Xaml::Controls::Primitives::ToggleButton MainWindow::TglBtnIncludeSubfolders()
    {
        return tglBtn_includeSubfolders();
    }

    Windows::UI::Xaml::Controls::Primitives::ToggleButton MainWindow::TglBtnEnumerateItems()
    {
        return tglBtn_enumItems();
    }

    Windows::UI::Xaml::Controls::Primitives::ToggleButton MainWindow::TglBtnUpperCase()
    {
        return tglBtn_upperCase();
    }
    
    Windows::UI::Xaml::Controls::Primitives::ToggleButton MainWindow::TglBtnLowerCase()
    {
        return tglBtn_lowerCase();
    }
    
    Windows::UI::Xaml::Controls::Primitives::ToggleButton MainWindow::TglBtnTitleCase()
    {
        return tglBtn_titleCase();
    }

    Windows::UI::Xaml::Controls::Primitives::ToggleButton MainWindow::TglBtnCapitalize()
    {
        return tglBtn_capitalize();
    }

    Windows::UI::Xaml::Controls::Button MainWindow::BtnRename()
    {
        return btn_rename();
    }

    Windows::UI::Xaml::Controls::Button MainWindow::BtnSettings()
    {
        return btn_settings();
    }

    Windows::UI::Xaml::Controls::CheckBox MainWindow::ChckBoxSelectAll()
    {
        return chckBox_selectAll();
    }

    PowerRenameUI_new::UIUpdates MainWindow::UIUpdatesItem()
    {
        return m_uiUpdatesItem;
    }

    void MainWindow::AddExplorerItem(int32_t id, hstring const& original, hstring const& renamed, int32_t type, int32_t parentId, bool checked)
    {
        auto newItem = winrt::make<PowerRenameUI_new::implementation::ExplorerItem>(id, original, renamed, type, checked);
        if (parentId == 0)
        {
            m_explorerItems.Append(newItem);
        }
        else
        {
            auto parent = FindById(parentId);
            parent.Children().Append(newItem);
        }
    }

    void MainWindow::UpdateExplorerItem(int32_t id, hstring const& newName)
    {        
        auto itemToUpdate = FindById(id);
        if (itemToUpdate != NULL)
        {
            itemToUpdate.Renamed(newName);
        }
    }

    void MainWindow::AppendSearchMRU(hstring const& value)
    {
        m_searchMRU.Append(value);
    }

    void MainWindow::AppendReplaceMRU(hstring const& value)
    {
        m_replaceMRU.Append(value);
    }

    PowerRenameUI_new::ExplorerItem MainWindow::FindById(int32_t id)
    {
        auto fakeRoot = winrt::make<PowerRenameUI_new::implementation::ExplorerItem>(0, L"Fake", L"", 0, false);
        fakeRoot.Children(m_explorerItems);
        return FindById(fakeRoot, id);
    }

    PowerRenameUI_new::ExplorerItem MainWindow::FindById(PowerRenameUI_new::ExplorerItem& root, int32_t id)
    {
        if (root.Id() == id)
            return root;

        if (root.Type() == static_cast<UINT>(ExplorerItem::ExplorerItemType::Folder))
        {
            for (auto c : root.Children())
            {
                auto result = FindById(c, id);
                if (result != NULL)
                    return result;
            }
        }

        return NULL;
    }

    void MainWindow::ToggleAll(PowerRenameUI_new::ExplorerItem node, bool checked)
    {
        if (node == NULL)
            return;

        node.Checked(checked);

        if (node.Type() == static_cast<UINT>(ExplorerItem::ExplorerItemType::Folder))
        {
            for (auto c : node.Children())
            {
                ToggleAll(c, checked);
            }
        }
    }

    void MainWindow::Checked_ids(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const&)
    {
        auto checkbox = sender.as<Windows::UI::Xaml::Controls::CheckBox>();
        auto id = std::stoi(std::wstring{ checkbox.Name() });
        auto item = FindById(id);
        if (checkbox.IsChecked().GetBoolean() != item.Checked())
        {
            m_uiUpdatesItem.Checked(checkbox.IsChecked().GetBoolean());
            m_uiUpdatesItem.ChangedExplorerItemId(id);
        }
    }

    void MainWindow::SelectAll(winrt::Windows::Foundation::IInspectable const&, winrt::Windows::UI::Xaml::RoutedEventArgs const&)
    {
        if (chckBox_selectAll().IsChecked().GetBoolean() != m_allSelected)
        {
            auto fakeRoot = winrt::make<PowerRenameUI_new::implementation::ExplorerItem>(0, L"Fake", L"", 0, false);
            fakeRoot.Children(m_explorerItems);
            ToggleAll(fakeRoot, chckBox_selectAll().IsChecked().GetBoolean());
            m_uiUpdatesItem.ToggleAll();
            m_allSelected = !m_allSelected;
        }
    }

    void MainWindow::ShowAll(winrt::Windows::Foundation::IInspectable const&, winrt::Windows::UI::Xaml::RoutedEventArgs const&)
    {
        btn_showAll().IsChecked(true);
        btn_showRenamed().IsChecked(false);
        if (!m_uiUpdatesItem.ShowAll())
        {
            m_explorerItems.Clear();
            m_uiUpdatesItem.ShowAll(true);
        }
    }

    void MainWindow::ShowRenamed(winrt::Windows::Foundation::IInspectable const&, winrt::Windows::UI::Xaml::RoutedEventArgs const&)
    {
        btn_showRenamed().IsChecked(true);
        btn_showAll().IsChecked(false);
        if (m_uiUpdatesItem.ShowAll())
        {
            m_explorerItems.Clear();
            m_uiUpdatesItem.ShowAll(false);
        }
    }

    void MainWindow::RegExItemClick(winrt::Windows::Foundation::IInspectable const&, winrt::Windows::UI::Xaml::Controls::ItemClickEventArgs const& e)
    {
        auto s = e.ClickedItem().try_as<PatternSnippet>();
        RegExFlyout().Hide();
        textBox_search().Text(textBox_search().Text() + s->Code());
    }

    void MainWindow::DateTimeItemClick(winrt::Windows::Foundation::IInspectable const&, winrt::Windows::UI::Xaml::Controls::ItemClickEventArgs const& e)
    {
        auto s = e.ClickedItem().try_as<PatternSnippet>();
        DateTimeFlyout().Hide();
        textBox_replace().Text(textBox_replace().Text() + s->Code());
    }
}
