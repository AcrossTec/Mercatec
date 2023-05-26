#include "pch.h"
#include "Mercatec.WinUIEx.WindowExtensions.hpp"

//!
//! Display WinRT UI objects that depend on CoreWindow
//! https://learn.microsoft.com/en-us/windows/apps/develop/ui-input/display-ui-objects
//! https://learn.microsoft.com/en-us/windows/apps/develop/ui-input/display-ui-objects#winui-3-with-c
//!

using winrt::Microsoft::UI::Xaml::Window;
using winrt::Windows::Storage::Pickers::FileOpenPicker;
using winrt::Windows::Storage::Pickers::FileSavePicker;
using winrt::Windows::UI::Popups::MessageDialog;

namespace Mercatec::WinUIEx
{
    /// <summary>
    /// Initializes a new instance of the MessageDialog class with the provided window as a parent to display a titled message
    /// dialog that can be used to ask your user simple questions.
    /// </summary>
    /// <param name="window">Parent window</param>
    /// <param name="content">The message displayed to the user.</param>
    /// <param name="title">The title you want displayed on the dialog.</param>
    /// <returns>Message dialog</returns>
    MessageDialog WindowExtensions::CreateMessageDialog(const Window& Window, const std::wstring_view Content, const std::wstring_view Title) noexcept
    {
        MessageDialog Dialog(Content, Title);

        // Initialize the message dialog with the window handle (HWND).
        auto InitializeWithWindow{ Dialog.as<::IInitializeWithWindow>() };
        InitializeWithWindow->Initialize(GetWindowHandle(Window));

        return Dialog;
    }

    /// <summary>
    /// Creates a new instance of a FileOpenPicker with the provided window as a parent.
    /// </summary>
    /// <param name="window">Parent window</param>
    /// <returns>FileOpenPicker</returns>
    FileOpenPicker WindowExtensions::CreateOpenFilePicker(const Window& Window) noexcept
    {
        FileOpenPicker OpenPicker;

        // Initialize the folder picker with the window handle (HWND).
        auto InitializeWithWindow{ OpenPicker.as<::IInitializeWithWindow>() };
        InitializeWithWindow->Initialize(GetWindowHandle(Window));

        return OpenPicker;
    }

    /// <summary>
    /// Creates a new instance of a FileSavePicker with the provided window as a parent.
    /// </summary>
    /// <param name="window">Parent window</param>
    /// <returns>SaveFilePicker</returns>
    FileSavePicker WindowExtensions::CreateSaveFilePicker(const Window& Window) noexcept
    {
        FileSavePicker SavePicker;

        // Initialize the folder picker with the window handle (HWND).
        auto InitializeWithWindow{ SavePicker.as<::IInitializeWithWindow>() };
        InitializeWithWindow->Initialize(GetWindowHandle(Window));

        return SavePicker;
    }
} // namespace Mercatec::WinUIEx
