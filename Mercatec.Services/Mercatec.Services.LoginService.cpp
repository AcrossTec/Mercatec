#include "pch.h"
#include "Mercatec.Services.LoginService.h"
#if __has_include("LoginService.g.cpp")
# include "LoginService.g.cpp"
#endif

using ::Mercatec::Helpers::AppSettings;
using ::Mercatec::Services::AuthService;
using ::Mercatec::Services::MicrosoftPassportHelper;

namespace winrt::Mercatec::Services::implementation
{
    LoginService::LoginService( //!
      const Helpers::Services::IMessageService& MessageService,
      const Helpers::Services::IDialogService&  DialogService
    )
      : m_MessageService{ MessageService }
      , m_DialogService{ DialogService }
      , m_IsAuthenticated{ false }
    {
    }

    winrt::com_ptr<::Mercatec::Services::MessageService> LoginService::MsgService() const noexcept
    {
        // com_ptr::copy_from ensures that AddRef is called.
        winrt::com_ptr<::Mercatec::Services::MessageService> Impl;
        Impl.copy_from(winrt::get_self<::Mercatec::Services::MessageService>(MessageService()));
        return Impl;
    }

    Helpers::Services::IMessageService LoginService::MessageService() const noexcept
    {
        return m_MessageService;
    }

    Helpers::Services::IDialogService LoginService::DialogService() const noexcept
    {
        return m_DialogService;
    }

    bool LoginService::IsAuthenticated() const noexcept
    {
        return m_IsAuthenticated;
    }

    void LoginService::IsAuthenticated(const bool Value) noexcept
    {
        m_IsAuthenticated = Value;
    }

    void LoginService::Logoff()
    {
        UpdateAuthenticationStatus(false);
    }

    bool LoginService::IsWindowsHelloEnabled([[maybe_unused]] const std::wstring_view UserName)
    {
        if ( not UserName.empty() )
        {
            if ( UserName == AppSettings::Current().UserName )
            {
                return not AppSettings::Current().WindowsHelloPublicKeyHint.empty();
            }
        }

        return false;
    }

    Windows::Foundation::IAsyncAction LoginService::TrySetupWindowsHelloAsync([[maybe_unused]] const std::wstring_view UserName)
    {
        winrt::apartment_context ui_thread; // Capture calling context.

        if ( co_await MicrosoftPassportHelper::MicrosoftPassportAvailableCheckAsync() )
        {
            co_await ui_thread; // Switch back to calling context.
            if ( co_await DialogService().ShowAsync(L"Windows Hello", L"Su dispositivo es compatible con Windows Hello y puede usarlo para autenticarse con la aplicación.\r\n¿Desea habilitar Windows Hello para su próximo inicio de sesión con este usuario?", L"Ok", L"Quizas más tarde") )
            {
                co_await SetupWindowsHelloAsync(UserName);
            }
            else
            {
                co_await TryDeleteCredentialAccountAsync(UserName);
            }
        }
    }

    Windows::Foundation::IAsyncAction LoginService::SetupWindowsHelloAsync(const std::wstring_view UserName)
    {
        auto PublicKey = co_await CreatePassportKeyCredentialAsync(UserName);

        if ( PublicKey != nullptr )
        {
            if ( co_await RegisterPassportCredentialWithServerAsync(PublicKey) )
            {
                // When communicating with the server in the future, we pass a hash of the
                // public key in order to identify which key the server should use to verify the challenge.
                auto HashProvider  = Windows::Security::Cryptography::Core::HashAlgorithmProvider::OpenAlgorithm(Windows::Security::Cryptography::Core::HashAlgorithmNames::Sha256());
                auto PublicKeyHash = HashProvider.HashData(PublicKey);

                AppSettings::Current().WindowsHelloPublicKeyHint = Windows::Security::Cryptography::CryptographicBuffer::EncodeToBase64String(PublicKeyHash);
            }
        }
        else
        {
            co_await TryDeleteCredentialAccountAsync(UserName);
        }
    }

    Windows::Foundation::IAsyncOperation<bool> LoginService::SignInWithPasswordAsync([[maybe_unused]] const std::wstring_view UserName, [[maybe_unused]] const std::wstring_view Password)
    {
        // Perform authentication here.
        // This sample accepts any user name and password.
        UpdateAuthenticationStatus(true);
        co_return true;
    }

    Windows::Foundation::IAsyncOperation<Helpers::Result> LoginService::SignInWithWindowsHelloAsync()
    {
        std::wstring UserName = AppSettings::Current().UserName;

        if ( IsWindowsHelloEnabled(UserName) )
        {
            auto RetrieveResult = co_await Windows::Security::Credentials::KeyCredentialManager::OpenAsync(UserName);

            if ( RetrieveResult.Status() == Windows::Security::Credentials::KeyCredentialStatus::Success )
            {
                auto Credential      = RetrieveResult.Credential();
                auto ChallengeBuffer = Windows::Security::Cryptography::CryptographicBuffer::DecodeFromBase64String(L"Challenge");
                auto Result          = co_await Credential.RequestSignAsync(ChallengeBuffer);

                if ( Result.Status() == Windows::Security::Credentials::KeyCredentialStatus::Success )
                {
                    UpdateAuthenticationStatus(true);
                    co_return Helpers::Result::Ok();
                }

                // TODO: Crear el Mapping para los Enum correspondientes a String

                co_return Helpers::Result::Error(L"Windows Hello", std::format(L"Cannot sign in with Windows Hello: {}", static_cast<int32_t>(Result.Status())));
            }

            co_return Helpers::Result::Error(L"Windows Hello", std::format(L"Cannot sign in with Windows Hello: {}", static_cast<int32_t>(RetrieveResult.Status())));
        }

        co_return Helpers::Result::Error(L"Windows Hello", L"Windows Hello is not enabled for current user.");
    }

    void LoginService::UpdateAuthenticationStatus(const bool IsAuthenticated)
    {
        this->IsAuthenticated(IsAuthenticated);
        MsgService()->Send(*this, L"AuthenticationChanged", IsAuthenticated);
    }

    Windows::Foundation::IAsyncOperation<bool> LoginService::TryDeleteCredentialAccountAsync(const std::wstring_view UserName)
    {
        try
        {
            AppSettings::Current().WindowsHelloPublicKeyHint = Empty<Char>;
            co_await Windows::Security::Credentials::KeyCredentialManager::DeleteAsync(UserName);
            co_return true;
        }
        catch ( const hresult_error& Ex )
        {
            switch ( Ex.code() )
            {
                case NTE_NO_KEY:
                {
                    // Key is already deleted. Ignore this error.
                    break;
                }
                case NTE_PERM:
                {
                    // Access is denied. Ignore this error. We tried our best.
                    break;
                }
                default:
                {
                    OutputDebug(L"Error Code: {}, Message: {}", static_cast<int32_t>(Ex.code()), Ex.message());
                    break;
                }
            }
        }

        co_return false;
    }

    Windows::Foundation::IAsyncOperation<LoginService::IBuffer> LoginService::CreatePassportKeyCredentialAsync(const std::wstring_view UserName)
    {
        winrt::apartment_context ui_thread; // Capture calling context.

        // Create a new KeyCredential for the user on the device
        auto KeyCreationResult = co_await Windows::Security::Credentials::KeyCredentialManager::RequestCreateAsync(UserName, Windows::Security::Credentials::KeyCredentialCreationOption::ReplaceExisting);

        if ( KeyCreationResult.Status() == Windows::Security::Credentials::KeyCredentialStatus::Success )
        {
            // User has autheniticated with Windows Hello and the key credential is created
            auto Credential = KeyCreationResult.Credential();
            co_return Credential.RetrievePublicKey();
        }
        else if ( KeyCreationResult.Status() == Windows::Security::Credentials::KeyCredentialStatus::NotFound )
        {
            co_await ui_thread; // Switch back to calling context.
            co_await DialogService().ShowAsync(L"Windows Hello", L"To proceed, Windows Hello needs to be configured in Windows Settings (Accounts -> Sign-in options)");
        }
        else if ( KeyCreationResult.Status() == Windows::Security::Credentials::KeyCredentialStatus::UnknownError )
        {
            co_await ui_thread; // Switch back to calling context.
            co_await DialogService().ShowAsync(L"Windows Hello Error", L"The key credential could not be created. Please try again.");
        }

        co_return nullptr;
    }

    Windows::Foundation::IAsyncOperation<bool> LoginService::RegisterPassportCredentialWithServerAsync([[maybe_unused]] const IBuffer& PublicKey)
    {
        // TODO:
        // Register the public key and attestation of the key credential with the server
        // In a real-world scenario, this would likely also include:
        //      - Certificate chain for attestation endorsement if available
        //      - Status code of the Key Attestation result : Included / retrieved later / retry type

        co_return true;
    }
} // namespace winrt::Mercatec::Services::implementation
