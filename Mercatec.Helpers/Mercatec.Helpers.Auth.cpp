#include "pch.h"
#include "Mercatec.Helpers.Auth.hpp"

#include <winrt/Windows.System.Profile.h>
#include <winrt/Windows.Security.Credentials.h>
#include <winrt/Windows.Security.Cryptography.h>

#include <winrt/Windows.Security.ExchangeActiveSyncProvisioning.h>

#include <winrt/Windows.Storage.h>
#include <winrt/Windows.Storage.Streams.h>

namespace WSP    = winrt::Windows::System::Profile;
namespace WSCRY  = winrt::Windows::Security::Cryptography;
namespace WSEASP = winrt::Windows::Security::ExchangeActiveSyncProvisioning;

#define _WIN32_DCOM

#include <WbemIdl.h>
#include <atlbase.h>
#include <comutil.h>
#include <strsafe.h>
#include <tchar.h>

#pragma comment(lib, "comsuppw.lib")
#pragma comment(lib, "wbemuuid.lib")

std::wstring Win32BIOSSerialNumber()
{
    //!
    //! https://learn.microsoft.com/en-us/windows/win32/wmisdk/wmi-start-page
    //! https://learn.microsoft.com/en-us/windows/win32/wmisdk/using-wmi
    //! https://learn.microsoft.com/en-us/windows/win32/wmisdk/wmi-c---application-examples
    //! https://learn.microsoft.com/es-mx/windows/win32/wmisdk/initializing-com-for-a-wmi-application
    //!
    //! https://www.codeproject.com/articles/10539/making-wmi-queries-in-c
    //! https://stackoverflow.com/questions/1999765/how-can-i-execute-this-wmi-query-in-vc
    //! https://github.com/Thomas-Sparber/wmi
    //! https://github.com/bozali/wmi
    //!
    //! https://learn.microsoft.com/en-us/windows/win32/cimwin32prov/win32-bios
    //! https://learn.microsoft.com/en-us/windows/win32/cimwin32prov/win32-processor
    //! https://learn.microsoft.com/en-us/windows/win32/cimwin32prov/computer-system-hardware-classes
    //! https://learn.microsoft.com/en-us/windows/win32/cimwin32prov/operating-system-classes
    //!

    CComPtr<IWbemLocator>         pWbemLocator;
    CComPtr<IWbemServices>        pWbemServices;
    CComPtr<IEnumWbemClassObject> pEnumerator;
    CComPtr<IWbemClassObject>     pWmiObject;
    CComVariant                   cvtValue;
    HRESULT                       hresult;

    ULONG    uObjectCount = 0;
    CComBSTR cbsQuery     = L"Select SerialNumber From Win32_BIOS";

    hresult = CoInitializeEx(NULL, COINIT_MULTITHREADED);
    hresult = pWbemLocator.CoCreateInstance(CLSID_WbemLocator);
    hresult = pWbemLocator->ConnectServer(CComBSTR(L"ROOT\\CIMV2"), NULL, NULL, NULL, NULL, NULL, NULL, &pWbemServices);
    hresult = CoSetProxyBlanket(pWbemServices, RPC_C_AUTHN_WINNT, RPC_C_AUTHZ_NONE, NULL, RPC_C_AUTHN_LEVEL_CALL, RPC_C_IMP_LEVEL_IMPERSONATE, NULL, EOAC_NONE);
    hresult = pWbemServices->ExecQuery(CComBSTR("WQL"), cbsQuery, WBEM_FLAG_FORWARD_ONLY | WBEM_FLAG_RETURN_IMMEDIATELY, NULL, &pEnumerator);
    hresult = pEnumerator->Next(WBEM_INFINITE, 1, &pWmiObject, &uObjectCount);
    hresult = pWmiObject->Get(L"SerialNumber", NULL, &cvtValue, NULL, NULL);

    CoUninitialize();

    const std::wstring szQueryResult = cvtValue.bstrVal;
    return szQueryResult;
}

winrt::hstring GetProductId()
{
    HKEY    RegistryKey  = NULL;
    WCHAR   Value[1'024] = { 0 };
    DWORD   BufferSize   = 1'024;
    LSTATUS Status       = 0;

    RegOpenKeyExW(HKEY_LOCAL_MACHINE, L"SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion", NULL, KEY_QUERY_VALUE | KEY_WOW64_64KEY, &RegistryKey);
    Status = RegQueryValueExW(RegistryKey, L"ProductId", NULL, NULL, (LPBYTE)Value, &BufferSize);
    RegCloseKey(RegistryKey);

    return Value;
}

namespace Mercatec::Helpers::Auth
{
    winrt::hstring GetDeviceId()
    {
        // Get the Device ID to pass to the server
        // WSEASP::EasClientDeviceInformation device_information;
        // assert(device_information != nullptr);
        // [[maybe_unused]] const std::wstring_view operating_system = device_information.OperatingSystem();
        // [[maybe_unused]] const std::wstring_view product_name     = device_information.SystemProductName();
        // [[maybe_unused]] const std::wstring_view friendly_name    = device_information.FriendlyName();
        // [[maybe_unused]] const std::wstring_view system_sku       = device_information.SystemSku();

        return GetProductId();
    }
} // namespace Mercatec::Helpers::Auth
