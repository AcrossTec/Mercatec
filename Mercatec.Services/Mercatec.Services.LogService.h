#pragma once

#include "LogService.g.h"

#include <winrt/Mercatec.Helpers.h>
#include <winrt/Mercatec.Helpers.Models.h>
#include <winrt/Mercatec.Helpers.Services.h>

namespace winrt::Mercatec::Services::implementation
{
    struct LogService : LogServiceT<LogService>
    {
        LogService(const Helpers::Services::IMessageService& message_service);

        Helpers::Services::IMessageService MessageService() const noexcept;

        Windows::Foundation::IAsyncAction WriteAsync(const Helpers::LogType type, const std::wstring_view source, const std::wstring_view action, const std::wstring_view dessage, const std::wstring_view description);
        Windows::Foundation::IAsyncAction WriteAsync(const Helpers::LogType type, const std::wstring_view source, const std::wstring_view action, const hresult code, const std::wstring_view message);

        Windows::Foundation::IAsyncOperation<Helpers::Models::AppLogModel>                                            GetLogAsync(const guid& app_log_id);
        Windows::Foundation::IAsyncOperation<Windows::Foundation::Collections::IVector<Helpers::Models::AppLogModel>> GetLogsAsync(const Helpers::DataRequest& request);
        Windows::Foundation::IAsyncOperation<Windows::Foundation::Collections::IVector<Helpers::Models::AppLogModel>> GetLogsAsync(const int32_t skip, const int32_t take, const Helpers::DataRequest& request);
        Windows::Foundation::IAsyncOperation<int32_t>                                                                 GetLogsCountAsync(const Helpers::DataRequest& request);

        Windows::Foundation::IAsyncOperation<int32_t> DeleteLogAsync(const Helpers::Models::AppLogModel& model);
        Windows::Foundation::IAsyncOperation<int32_t> DeleteLogRangeAsync(const int32_t index, const int32_t length, const Helpers::DataRequest& request);

        Windows::Foundation::IAsyncAction MarkAllAsReadAsync();
    };
} // namespace winrt::Mercatec::Services::implementation

namespace winrt::Mercatec::Services::factory_implementation
{
    struct LogService : LogServiceT<LogService, implementation::LogService>
    {
    };
} // namespace winrt::Mercatec::Services::factory_implementation
