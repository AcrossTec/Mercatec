#include "pch.h"
#include "Mercatec.Services.LogService.h"
#if __has_include("LogService.g.cpp")
# include "LogService.g.cpp"
#endif

namespace winrt::Mercatec::Services::implementation
{
    LogService::LogService([[maybe_unused]] const Helpers::Services::IMessageService& message_service)
    {
    }

    Helpers::Services::IMessageService LogService::MessageService() const noexcept
    {
        return nullptr;
    }

    Windows::Foundation::IAsyncAction LogService::WriteAsync( //!
      [[maybe_unused]] const Helpers::LogType  type,
      [[maybe_unused]] const std::wstring_view source,
      [[maybe_unused]] const std::wstring_view action,
      [[maybe_unused]] const std::wstring_view dessage,
      [[maybe_unused]] const std::wstring_view description
    )
    {
        co_return;
    }

    Windows::Foundation::IAsyncAction LogService::WriteAsync( //!
      [[maybe_unused]] const Helpers::LogType  type,
      [[maybe_unused]] const std::wstring_view source,
      [[maybe_unused]] const std::wstring_view action,
      [[maybe_unused]] const hresult           code,
      [[maybe_unused]] const std::wstring_view message
    )
    {
        co_return;
    }

    Windows::Foundation::IAsyncOperation<Helpers::Models::AppLogModel> LogService::GetLogAsync([[maybe_unused]] const guid& app_log_id)
    {
        co_return nullptr;
    }

    Windows::Foundation::IAsyncOperation<Windows::Foundation::Collections::IVector<Helpers::Models::AppLogModel>> LogService::GetLogsAsync([[maybe_unused]] const Helpers::DataRequest& request)
    {
        co_return single_threaded_vector<Helpers::Models::AppLogModel>();
    }

    Windows::Foundation::IAsyncOperation<Windows::Foundation::Collections::IVector<Helpers::Models::AppLogModel>> LogService::GetLogsAsync( //!
      [[maybe_unused]] const int32_t               skip,
      [[maybe_unused]] const int32_t               take,
      [[maybe_unused]] const Helpers::DataRequest& request
    )
    {
        co_return single_threaded_vector<Helpers::Models::AppLogModel>();
    }

    Windows::Foundation::IAsyncOperation<int32_t> LogService::GetLogsCountAsync([[maybe_unused]] const Helpers::DataRequest& request)
    {
        co_return 0;
    }

    Windows::Foundation::IAsyncOperation<int32_t> LogService::DeleteLogAsync([[maybe_unused]] const Helpers::Models::AppLogModel& model)
    {
        co_return 0;
    }

    Windows::Foundation::IAsyncOperation<int32_t> LogService::DeleteLogRangeAsync( //!
      [[maybe_unused]] const int32_t               index,
      [[maybe_unused]] const int32_t               length,
      [[maybe_unused]] const Helpers::DataRequest& request
    )
    {
        co_return 0;
    }

    Windows::Foundation::IAsyncAction LogService::MarkAllAsReadAsync()
    {
        co_return;
    }
} // namespace winrt::Mercatec::Services::implementation
