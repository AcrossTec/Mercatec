#include "pch.h"
#include "Mercatec.WinUIEx.Internal.WindowManager.hpp"

namespace Mercatec::WinUIEx
{
    void WindowsSystemDispatcherQueueHelper::EnsureWindowsSystemDispatcherQueueController()
    {
        if ( winrt::Windows::System::DispatcherQueue::GetForCurrentThread() != nullptr )
        {
            return;
        }

        if ( DispatcherQueueController == nullptr )
        {
            DispatcherQueueOptions Options{ sizeof(DispatcherQueueOptions), DQTYPE_THREAD_CURRENT, DQTAT_COM_STA };

            ABI::Windows::System::IDispatcherQueueController* Pointer{};
            winrt::check_hresult(CreateDispatcherQueueController(Options, &Pointer));
            DispatcherQueueController = winrt::Windows::System::DispatcherQueueController{ Pointer, winrt::take_ownership_from_abi };
        }
    }

    std::map<HWND, std::weak_ptr<WindowManager>>      WindowManager::WindowManagerImpl::Managers;
    std::shared_ptr<std::map<std::wstring, std::any>> WindowManager::WindowManagerImpl::PersistenceStorage = nullptr;
} // namespace Mercatec::WinUIEx
