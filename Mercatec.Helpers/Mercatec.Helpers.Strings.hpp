#pragma once

#include "Mercatec.Helpers.Exports.Api.hpp"

#include <windows.foundation.h>
#include <winrt/Windows.Foundation.Collections.h>

#include <string>
#include <string_view>
#include <sstream>
#include <span>
#include <spanstream>
#include <format>
#include <array>
#include <cstring>
#include <cuchar>
#include <cwchar>
#include <vector>
#include <ranges>

namespace Mercatec::Helpers::inline Strings
{
    using namespace std::string_literals;
    using namespace std::string_view_literals;

    template <typename ValueType>
    inline constexpr const ValueType Empty = std::declval<ValueType>();

    // clang-format off
    template<> inline constexpr const     char* Empty<char>     = "";
    template<> inline constexpr const  wchar_t* Empty<wchar_t>  = L"";
    template<> inline constexpr const  char8_t* Empty<char8_t>  = u8"";
    template<> inline constexpr const char16_t* Empty<char16_t> = u"";
    template<> inline constexpr const char32_t* Empty<char32_t> = U"";

    // clang-format on

    MERCATEC_HELPERS_API std::vector<std::wstring> SplitStrings(const std::wstring_view text) noexcept;

    MERCATEC_HELPERS_API std::vector<winrt::hstring> SplitHStrings(const std::wstring_view text) noexcept;

    namespace Traits
    {
        template <typename T, typename = void>
        struct StringTraits;

        template <std::ranges::contiguous_range T>
        requires(not requires { typename std::remove_cvref_t<T>::traits_type; }) // clang-format off
        struct StringTraits<T, std::void_t<std::ranges::range_value_t<std::remove_reference_t<T>>>> // clang-format on
        {
            using Type       = std::ranges::range_value_t<std::remove_reference_t<T>>;
            using TraitsType = std::char_traits<Type>;

            inline static constexpr bool IsInternalTrait = false;
        };

        template <std::ranges::contiguous_range T>
        struct StringTraits<T, std::void_t<std::ranges::range_value_t<std::remove_reference_t<T>>, typename std::remove_cvref_t<T>::traits_type>>
        {
            using Type       = std::ranges::range_value_t<std::remove_reference_t<T>>;
            using TraitsType = typename std::remove_cvref_t<T>::traits_type;

            inline static constexpr bool IsInternalTrait = true;
        };

        template <typename T>
        requires std::is_pointer_v<std::remove_cvref_t<T>>
        struct StringTraits<T, std::void_t<typename std::iterator_traits<std::remove_cvref_t<T>>::value_type>>
        {
            using Type       = typename std::iterator_traits<std::remove_cvref_t<T>>::value_type;
            using TraitsType = std::char_traits<Type>;

            inline static constexpr bool IsInternalTrait = false;
        };

        template <typename T>
        using CharacterTypeOf = typename Traits::StringTraits<T>::Type;

        template <typename T>
        using CharacterTraitsOf = typename Traits::StringTraits<T>::TraitsType;
    } // namespace Traits

    namespace Concepts
    {
        namespace Details
        {
            template <class Type>
            concept BooleanTestableImpl = std::convertible_to<Type, bool>;
        }

        /**
         * @brief Concepto que verifica que un Tipo se puede convertir en Boolean.
         *
         *  Referencia: https://en.cppreference.com/w/cpp/concepts/boolean-testable
         *
         * @tparam Type Parámetro de tipo que se va ha evaluar.
         */
        template <class Type> // clang-format off
        concept BooleanTestable = Details::BooleanTestableImpl<Type> and requires(Type&& value)
        {
          { !std::forward<Type>(value) } -> Details::BooleanTestableImpl;
        };
        // clang-format on

        template <typename StringType>
        concept StringViewCompatible =                                   //
          requires { typename Traits::CharacterTypeOf<StringType>; } and //
          std::constructible_from<std::basic_string_view<Traits::CharacterTypeOf<StringType>, Traits::CharacterTraitsOf<StringType>>, StringType>;
    } // namespace Concepts

    /**
     * @brief Specifies whether applicable Overload:Cxx::Algorithms::Split method overloads include or omit empty substrings from the return value.
     */
    enum class StringSplitOptions
    {
        /**
         * @brief The return value includes array elements that contain an empty string.
         */
        None = 0x0,

        /**
         * @brief The return value does not include array elements that contain an empty string.
         */
        RemoveEmptyEntries = 0x1
    };

    namespace Views
    {
        /**
         * @brief View que permite ignorar los valores vacíos de un Rango.
         */
        struct IgnoreEmptyValuesAdaptorClosure : std::ranges::range_adaptor_closure<IgnoreEmptyValuesAdaptorClosure>
        {
            template <std::ranges::viewable_range Range>
            requires std::ranges::viewable_range<std::ranges::range_value_t<Range>> and // clang-format off
                   requires(std::ranges::range_value_t<Range>&& value)
                   {
                     { value.empty() } -> Concepts::BooleanTestable;
                   } // clang-format on
            [[nodiscard]] constexpr auto operator()(Range&& range) const noexcept
            {
                return std::forward<Range>(range) | std::views::filter([](auto&& value) { return not value.empty(); });
            }
        };

        inline constexpr IgnoreEmptyValuesAdaptorClosure IgnoreEmptyValues{};

        struct ValuesToStringViewAdaptorClosure : std::ranges::range_adaptor_closure<ValuesToStringViewAdaptorClosure>
        {
            template <std::ranges::viewable_range Range>
            requires std::ranges::viewable_range<std::ranges::range_value_t<Range>> and Concepts::StringViewCompatible<std::ranges::range_value_t<Range>>
            [[nodiscard]] constexpr auto operator()(Range&& range) const noexcept
            {
                using subrange_t    = std::ranges::range_value_t<Range>;
                using value_type_t  = std::ranges::range_value_t<subrange_t>;
                using string_view_t = std::basic_string_view<value_type_t>;

                return std::forward<Range>(range) | std::views::transform([](auto&& value) { return string_view_t(value.begin(), value.end()); });
            }
        };

        inline constexpr ValuesToStringViewAdaptorClosure ValuesToStringView{};
    } // namespace Views

    /**
     * @brief Separa una Cadena en una lista de Tokens según el Patrón indicado.
     *
     * @tparam Options Opción para indicar si se debe regresar un rango con valores vacíos o sin ellos.
     *
     * @param[in] Text    Cadena que será separada en Tokens.
     * @param[in] Pattern Cadena usada como Patrón para separar la Cadena Text en Tokens.
     *
     * @return Regresa una lista de std::basic_string_view<CharType, TraitType> con todos los Tokens.
     */
    template <StringSplitOptions Options = StringSplitOptions::RemoveEmptyEntries>
    [[nodiscard]] inline constexpr auto Split(Concepts::StringViewCompatible auto&& Text, Concepts::StringViewCompatible auto&& Pattern) noexcept
    requires std::same_as<Traits::CharacterTypeOf<decltype(Text)>, Traits::CharacterTypeOf<decltype(Pattern)>>
    {
        using enum StringSplitOptions;
        using StringView = std::basic_string_view<Traits::CharacterTypeOf<decltype(Text)>, Traits::CharacterTraitsOf<decltype(Text)>>;

        auto&& tokens = StringView{ Text } | std::views::split(StringView{ Pattern }) | Views::ValuesToStringView;

        if constexpr ( Options == RemoveEmptyEntries )
        {
            return tokens | Views::IgnoreEmptyValues;
        }
        else
        {
            return tokens;
        }
    }

    inline constexpr std::string_view StringViewOrDefault(const std::string_view text, const std::string_view _default = "")
    {
        if ( text.empty() )
        {
            return _default;
        }

        return text;
    }

    inline constexpr std::string_view StringViewOrDefault(const char* text, const std::string_view _default = "")
    {
        if ( text == nullptr || *text == '\0' )
        {
            return _default;
        }

        return text;
    }

    inline constexpr std::wstring_view StringViewOrDefault(const std::wstring_view text, const std::wstring_view _default = L"")
    {
        if ( text.empty() )
        {
            return _default;
        }

        return text;
    }

    inline constexpr std::wstring_view StringViewOrDefault(const wchar_t* text, const std::wstring_view _default = L"")
    {
        if ( text == nullptr || *text == L'\0' )
        {
            return _default;
        }

        return text;
    }
} // namespace Mercatec::Helpers::inline Strings
