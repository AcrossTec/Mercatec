#pragma once

#include "Mercatec.Helpers.Exports.Api.hpp"

#include <winrt/Windows.Foundation.h>
#include <winrt/Windows.Foundation.Numerics.h>

#include <winrt/Microsoft.UI.Xaml.h>
#include <winrt/Microsoft.UI.Xaml.Hosting.h>
#include <winrt/Microsoft.UI.Composition.h>
#include <winrt/Microsoft.Graphics.Canvas.Effects.h>

namespace Mercatec::Helpers
{
    struct MERCATEC_HELPERS_API AnimationExtensions sealed abstract
    {
        // clang-format off
        static void Fade        (const winrt::Microsoft::UI::Xaml::UIElement&        Element, const double_t Milliseconds, const double_t Start, const double_t End, const winrt::Microsoft::UI::Composition::CompositionEasingFunction& EasingFunction = nullptr);
        static void TranslateX  (const winrt::Microsoft::UI::Xaml::UIElement&        Element, const double_t Milliseconds, const double_t Start, const double_t End, const winrt::Microsoft::UI::Composition::CompositionEasingFunction& EasingFunction = nullptr);
        static void TranslateY  (const winrt::Microsoft::UI::Xaml::UIElement&        Element, const double_t Milliseconds, const double_t Start, const double_t End, const winrt::Microsoft::UI::Composition::CompositionEasingFunction& EasingFunction = nullptr);
        static void Scale       (const winrt::Microsoft::UI::Xaml::FrameworkElement& Element, const double_t Milliseconds, const double_t Start, const double_t End, const winrt::Microsoft::UI::Composition::CompositionEasingFunction& EasingFunction = nullptr);
        static void Blur        (const winrt::Microsoft::UI::Xaml::UIElement&        Element, const double_t Milliseconds, const double_t Start, const double_t End, const winrt::Microsoft::UI::Composition::CompositionEasingFunction& EasingFunction = nullptr);
        static void Blur        (const winrt::Microsoft::UI::Xaml::UIElement&        Element, const double_t Amount);
        static void SetBrush    (const winrt::Microsoft::UI::Xaml::UIElement&        Element, const winrt::Microsoft::UI::Composition::CompositionBrush& Brush);
        static void Grayscale   (const winrt::Microsoft::UI::Xaml::UIElement&        Element);
        static void ClearEffects(const winrt::Microsoft::UI::Xaml::UIElement&        Element);
        
        static winrt::Microsoft::UI::Composition::SpriteVisual CreateSpriteVisual(const winrt::Microsoft::UI::Xaml::UIElement&     Element);
        static winrt::Microsoft::UI::Composition::SpriteVisual CreateSpriteVisual(const winrt::Microsoft::UI::Composition::Visual& ElementVisual);
        
        static void SetCenterPoint(const winrt::Microsoft::UI::Xaml::UIElement& Element, const double_t X, const double_t Y);
        static void StartAnimation(const winrt::Microsoft::UI::Xaml::UIElement& Element, const std::wstring_view PropertyName, const winrt::Microsoft::UI::Composition::CompositionAnimation& Animation);
        
        static winrt::Microsoft::UI::Composition::CompositionAnimation   CreateScalarAnimation     (const double_t Milliseconds, const double_t Start, const double_t End, const winrt::Microsoft::UI::Composition::CompositionEasingFunction& EasingFunction = nullptr);
        static winrt::Microsoft::UI::Composition::CompositionAnimation   CreateVector3Animation    (const double_t Milliseconds, const winrt::Windows::Foundation::Numerics::float3& Start, const winrt::Windows::Foundation::Numerics::float3& End, const winrt::Microsoft::UI::Composition::CompositionEasingFunction& EasingFunction = nullptr);
        static winrt::Microsoft::UI::Composition::CompositionEffectBrush CreateBlurEffectBrush     (const double_t Amount = 0.0);
        static winrt::Microsoft::UI::Composition::CompositionEffectBrush CreateGrayscaleEffectBrush();
        // clang-format on
    };
} // namespace Mercatec::Helpers
