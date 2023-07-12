#include "pch.h"
#include "Mercatec.Helpers.WindowsShell.hpp"

//!
//! CSIDL
//! https://learn.microsoft.com/en-us/windows/win32/shell/csidl
//!
//! SHGetSpecialFolderPathW
//! https://learn.microsoft.com/en-us/windows/win32/api/shlobj_core/nf-shlobj_core-shgetspecialfolderpathw
//!
//! SHGetKnownFolderPath
//! https://learn.microsoft.com/en-us/windows/win32/api/shlobj_core/nf-shlobj_core-shgetknownfolderpath
//!
//! Known Folders Sample
//! https://learn.microsoft.com/en-us/windows/win32/shell/samples-knownfolders
//!
//! Known Folders
//! https://learn.microsoft.com/en-us/windows/win32/shell/known-folders
//!
//! PathCombineW function (shlwapi.h)
//! https://learn.microsoft.com/en-us/windows/win32/api/shlwapi/nf-shlwapi-pathcombinew
//!
//! PathAddExtensionW function (shlwapi.h)
//! https://learn.microsoft.com/en-us/windows/win32/api/shlwapi/nf-shlwapi-pathaddextensionw
//!
//! PathAppendW function (shlwapi.h)
//! https://learn.microsoft.com/en-us/windows/win32/api/shlwapi/nf-shlwapi-pathappendw
//!

#pragma push_macro("PathAppend")
#pragma push_macro("PathCombine")
#pragma push_macro("PathAddExtension")

#undef PathAppend
#undef PathCombine
#undef PathAddExtension

namespace Mercatec::Helpers
{
    std::optional<winrt::hstring> GetKnownFolderPath(REFKNOWNFOLDERID FolderId, const DWORD Flags, HANDLE Token) noexcept
    {
        PWSTR   szPath  = NULL;
        HRESULT HResult = ::SHGetKnownFolderPath(FolderId, Flags, Token, &szPath);

        if ( SUCCEEDED(HResult) )
        {
            winrt::hstring FolderPath = szPath;
            CoTaskMemFree(szPath);
            return FolderPath;
        }

        return std::nullopt;
    }

    std::optional<winrt::hstring> GetSpecialFolderPath(const int32_t CSIDL, const bool Create) noexcept
    {
        if ( TCHAR szPath[MAX_PATH] = { L'\0' }; SUCCEEDED(::SHGetSpecialFolderPathW(NULL, szPath, CSIDL, Create)) )
        {
            return szPath;
        }

        return std::nullopt;
    }

    std::optional<winrt::hstring> PathAdd(const winrt::param::async_iterable<winrt::hstring>& Paths)
    {
        std::filesystem::path PathResult;

        for ( const auto& Path : static_cast<const winrt::Windows::Foundation::Collections::IIterable<winrt::hstring>&>(Paths) )
        {
            PathResult /= Path.c_str();
        }

        return PathResult.c_str();
    }

    std::optional<winrt::hstring> PathAppend(const winrt::param::async_iterable<winrt::hstring>& Paths) noexcept
    {
        wchar_t PathResult[MAX_PATH] = { L'\0' };

        for ( const auto& Path : static_cast<const winrt::Windows::Foundation::Collections::IIterable<winrt::hstring>&>(Paths) )
        {
            if ( ::PathAppendW(PathResult, Path.c_str()) != TRUE )
            {
                return std::nullopt;
            }
        }

        return PathResult;
    }

    std::optional<winrt::hstring> PathCombine(const winrt::param::async_iterable<winrt::hstring>& Paths) noexcept
    {
        wchar_t PathResult[MAX_PATH] = { L'\0' };

        for ( const auto& Path : static_cast<const winrt::Windows::Foundation::Collections::IIterable<winrt::hstring>&>(Paths) )
        {
            if ( ::PathCombineW(PathResult, Path.c_str(), PathResult) == nullptr )
            {
                return std::nullopt;
            }
        }

        return PathResult;
    }

    std::optional<winrt::hstring> PathAddExtension(const winrt::param::async_iterable<winrt::hstring>& Paths, const winrt::hstring& Extension) noexcept
    {
        wchar_t PathResult[MAX_PATH] = { L'\0' };

        if ( auto Path = PathAppend(Paths); Path.has_value() )
        {
            std::char_traits<wchar_t>::copy(PathResult, Path->c_str(), Path->size());

            if ( ::PathAddExtensionW(PathResult, Extension.c_str()) == TRUE )
            {
                return PathResult;
            }
        }

        return std::nullopt;
    }
} // namespace Mercatec::Helpers

#pragma pop_macro("PathAppend")
#pragma pop_macro("PathCombine")
#pragma pop_macro("PathAddExtension")
