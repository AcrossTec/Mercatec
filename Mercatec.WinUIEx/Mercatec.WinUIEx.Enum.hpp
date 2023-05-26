#pragma once

#include <array>
#include <concepts>
#include <string_view>

#include "Mercatec.WinUIEx.ForeachMacro.hpp"

namespace Mercatec::WinUIEx
{
    template <typename TEnum>
    requires std::is_enum_v<TEnum>
    struct EnumTraits
    {
        using enum_t            = TEnum;
        using underlying_type_t = std::underlying_type_t<TEnum>;

        inline static constexpr size_t            Size      = 0;
        inline static constexpr std::wstring_view Name      = L"Unknown";
        inline static constexpr std::wstring_view Namespace = L"::";
        inline static constexpr std::wstring_view FullName  = L"::Unknown";

        inline static constexpr std::wstring_view GetName(const TEnum) noexcept
        {
            return L"Unknown";
        }

        inline static constexpr TEnum GetValue(const std::underlying_type_t<TEnum> Value) noexcept
        {
            return TEnum{ Value };
        }

        inline static constexpr std::underlying_type_t<TEnum> GetValue(const TEnum Value) noexcept
        {
            return std::underlying_type_t<TEnum>{ Value };
        }

        inline static constexpr std::array<std::wstring_view, Size> GetNames() noexcept
        {
            return {};
        }

        inline static constexpr std::array<TEnum, Size> GetValues() noexcept
        {
            return {};
        }

        inline static constexpr std::array<std::underlying_type_t<TEnum>, Size> GetUnderlyingValues() noexcept
        {
            return {};
        }
    };

    template <typename TEnum>
    requires std::is_enum_v<TEnum>
    struct Enum
    {
        using enum_t            = typename EnumTraits<TEnum>::enum_t;
        using underlying_type_t = typename EnumTraits<TEnum>::underlying_type_t;

        inline static constexpr auto Name             = EnumTraits<TEnum>::Name;
        inline static constexpr auto Namespace        = EnumTraits<TEnum>::Namespace;
        inline static constexpr auto FullName         = EnumTraits<TEnum>::FullName;
        inline static constexpr auto Names            = EnumTraits<TEnum>::GetNames();
        inline static constexpr auto Values           = EnumTraits<TEnum>::GetValues();
        inline static constexpr auto UnderlyingValues = EnumTraits<TEnum>::GetUnderlyingValues();

        inline static constexpr underlying_type_t GetValue(const TEnum Value) noexcept
        {
            return EnumTraits<TEnum>::GetValue(Value);
        }

        inline static constexpr TEnum GetValue(const underlying_type_t Value) noexcept
        {
            return EnumTraits<TEnum>::GetValue(Value);
        }

        template <typename TValue>
        requires std::is_enum_v<TValue> or std::is_integral_v<TValue>
        inline static constexpr std::wstring_view GetName(const TValue Value) noexcept
        {
            return EnumTraits<TEnum>::GetName(static_cast<TEnum>(Value));
        }
    };
} // namespace Mercatec::WinUIEx

// clang-format off
#define ENUM_VALUES(EnumNamespace, EnumType, ...)                 \
    __VA_OPT__(MERCATEC_EXPAND(ENUM_VALUES_HELPER(EnumNamespace, EnumType, __VA_ARGS__)))
#define ENUM_VALUES_HELPER(EnumNamespace, EnumType, Value, ...)   \
    EnumNamespace::EnumType::Value                                \
    __VA_OPT__(,) __VA_OPT__(ENUM_VALUES_AGAIN MERCATEC_PARENS (EnumNamespace, EnumType, __VA_ARGS__))
#define ENUM_VALUES_AGAIN() ENUM_VALUES_HELPER

#define ENUM_VALUES_STRING(EnumNamespace, EnumType, ...)                 \
    __VA_OPT__(MERCATEC_EXPAND(ENUM_VALUES_STRING_HELPER(EnumNamespace, EnumType, __VA_ARGS__)))
#define ENUM_VALUES_STRING_HELPER(EnumNamespace, EnumType, Value, ...)   \
    L## #EnumNamespace L"::" L## #EnumType L"::" L## #Value              \
    __VA_OPT__(,) __VA_OPT__(ENUM_VALUES_STRING_AGAIN MERCATEC_PARENS (EnumNamespace, EnumType, __VA_ARGS__))
#define ENUM_VALUES_STRING_AGAIN() ENUM_VALUES_STRING_HELPER

#define ENUM_VALUES_UNDERLYING(EnumNamespace, EnumType, ...)                                             \
    __VA_OPT__(MERCATEC_EXPAND(ENUM_VALUES_UNDERLYING_HELPER(EnumNamespace, EnumType, __VA_ARGS__)))
#define ENUM_VALUES_UNDERLYING_HELPER(EnumNamespace, EnumType, Value, ...)                               \
    static_cast<std::underlying_type_t<EnumNamespace::EnumType>>(EnumNamespace::EnumType::Value)         \
    __VA_OPT__(,) __VA_OPT__(ENUM_VALUES_UNDERLYING_AGAIN MERCATEC_PARENS (EnumNamespace, EnumType, __VA_ARGS__))
#define ENUM_VALUES_UNDERLYING_AGAIN() ENUM_VALUES_UNDERLYING_HELPER
// clang-format on

#define ENUM_TRAITS_GET_VALUES(EnumNamespace, EnumType)                \
 inline static constexpr std::array<enum_t, Size> GetValues() noexcept \
 {                                                                     \
  return { ENUM_VALUES(EnumNamespace, EnumType, X) };                  \
 }

#define ENUM_TRAITS_GET_UNDERLYING_VALUES(EnumNamespace, EnumType)                          \
 inline static constexpr std::array<underlying_type_t, Size> GetUnderlyingValues() noexcept \
 {                                                                                          \
  return { ENUM_VALUES_UNDERLYING(EnumNamespace, EnumType, X) };                            \
 }

#define ENUM_TRAITS_GET_NAMES(EnumNamespace, EnumType)                           \
 inline static constexpr std::array<std::wstring_view, Size> GetNames() noexcept \
 {                                                                               \
  return { ENUM_VALUES_STRING(EnumNamespace, EnumType, X) };                     \
 }

#define ENUM_TRAITS_GET_NAME(EnumNamespace, EnumType)                           \
 inline static constexpr std::wstring_view GetName(const enum_t Value) noexcept \
 {                                                                              \
  constexpr auto Values = GetValues();                                          \
  constexpr auto Names  = GetNames();                                           \
  for ( int32_t Index = 0; Index < Size; ++Index )                              \
  {                                                                             \
   if ( Value == Values[Index] )                                                \
   {                                                                            \
    return Names[Index];                                                        \
   }                                                                            \
  }                                                                             \
  return L"Unknown";                                                            \
 }

#define ENUM_TRAITS_GET_VALUE(EnumNamespace, EnumType)                           \
 inline static constexpr underlying_type_t GetValue(const enum_t Value) noexcept \
 {                                                                               \
  return static_cast<underlying_type_t>(Value);                                  \
 }                                                                               \
 inline static constexpr enum_t GetValue(const underlying_type_t Value) noexcept \
 {                                                                               \
  return static_cast<enum_t>(Value);                                             \
 }

#define MAKE_ENUM_TRAITS(EnumNamespace, EnumType)                                              \
 template <>                                                                                   \
 struct Mercatec::WinUIEx::EnumTraits<EnumNamespace::EnumType>                                 \
 {                                                                                             \
  private:                                                                                     \
  template <auto... Values>                                                                    \
  inline static consteval size_t GetSize() noexcept                                            \
  {                                                                                            \
   return sizeof...(Values);                                                                   \
  }                                                                                            \
                                                                                               \
  public:                                                                                      \
  using enum_t = EnumNamespace::EnumType;                                                      \
                                                                                               \
  using underlying_type_t = std::underlying_type_t<enum_t>;                                    \
                                                                                               \
  inline static constexpr size_t Size = GetSize<ENUM_VALUES(EnumNamespace, EnumType, X)>();    \
                                                                                               \
  inline static constexpr std::wstring_view Name = L## #EnumType;                              \
                                                                                               \
  inline static constexpr std::wstring_view Namespace = L## #EnumNamespace;                    \
                                                                                               \
  inline static constexpr std::wstring_view FullName = L## #EnumNamespace L"::" L## #EnumType; \
                                                                                               \
  ENUM_TRAITS_GET_NAMES(EnumNamespace, EnumType)                                               \
                                                                                               \
  ENUM_TRAITS_GET_VALUES(EnumNamespace, EnumType)                                              \
                                                                                               \
  ENUM_TRAITS_GET_UNDERLYING_VALUES(EnumNamespace, EnumType)                                   \
                                                                                               \
  ENUM_TRAITS_GET_NAME(EnumNamespace, EnumType)                                                \
                                                                                               \
  ENUM_TRAITS_GET_VALUE(EnumNamespace, EnumType)                                               \
 };

#define ENUM_BITMASK_OPS(BITMASK)                                                                   \
 [[nodiscard]] inline constexpr BITMASK operator&(const BITMASK Left, const BITMASK Right) noexcept \
 {                                                                                                  \
  using IntType = std::underlying_type_t<BITMASK>;                                                  \
  return static_cast<BITMASK>(static_cast<IntType>(Left) & static_cast<IntType>(Right));            \
 }                                                                                                  \
                                                                                                    \
 [[nodiscard]] inline constexpr BITMASK operator|(const BITMASK Left, const BITMASK Right) noexcept \
 {                                                                                                  \
  using IntType = std::underlying_type_t<BITMASK>;                                                  \
  return static_cast<BITMASK>(static_cast<IntType>(Left) | static_cast<IntType>(Right));            \
 }                                                                                                  \
                                                                                                    \
 [[nodiscard]] inline constexpr BITMASK operator^(const BITMASK Left, const BITMASK Right) noexcept \
 {                                                                                                  \
  using IntType = std::underlying_type_t<BITMASK>;                                                  \
  return static_cast<BITMASK>(static_cast<IntType>(Left) ^ static_cast<IntType>(Right));            \
 }                                                                                                  \
                                                                                                    \
 inline constexpr BITMASK& operator&=(BITMASK& Left, const BITMASK Right) noexcept                  \
 {                                                                                                  \
  return Left = Left & Right;                                                                       \
 }                                                                                                  \
                                                                                                    \
 inline constexpr BITMASK& operator|=(BITMASK& Left, const BITMASK Right) noexcept                  \
 {                                                                                                  \
  return Left = Left | Right;                                                                       \
 }                                                                                                  \
                                                                                                    \
 inline constexpr BITMASK& operator^=(BITMASK& Left, const BITMASK Right) noexcept                  \
 {                                                                                                  \
  return Left = Left ^ Right;                                                                       \
 }                                                                                                  \
                                                                                                    \
 [[nodiscard]] inline constexpr BITMASK operator~(const BITMASK Left) noexcept                      \
 {                                                                                                  \
  using IntType = std::underlying_type_t<BITMASK>;                                                  \
  return static_cast<BITMASK>(~static_cast<IntType>(Left));                                         \
 }
