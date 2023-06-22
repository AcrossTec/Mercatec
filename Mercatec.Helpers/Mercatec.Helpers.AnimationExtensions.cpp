#include "pch.h"
#include "Mercatec.Helpers.AnimationExtensions.hpp"

#include <winrt/Mercatec.Helpers.h>
#include "Mercatec.Helpers.Strings.hpp"

using namespace winrt;
using namespace winrt::Microsoft::UI::Xaml;
using namespace winrt::Microsoft::UI::Xaml::Hosting;
using namespace winrt::Microsoft::UI::Composition;
using namespace winrt::Microsoft::Graphics::Canvas::Effects;
using namespace winrt::Windows::Foundation;
using namespace winrt::Windows::Foundation::Numerics;

namespace Mercatec::Helpers
{
    void AnimationExtensions::Fade(const UIElement& Element, const double_t Milliseconds, const double_t Start, const double_t End, const CompositionEasingFunction& EasingFunction)
    {
        StartAnimation(Element, nameof(Visual::Opacity), CreateScalarAnimation(Milliseconds, Start, End, EasingFunction));
    }

    void AnimationExtensions::TranslateX(const UIElement& Element, const double_t Milliseconds, const double_t Start, const double_t End, const CompositionEasingFunction& EasingFunction)
    {
        ElementCompositionPreview::SetIsTranslationEnabled(Element, true);
        StartAnimation(Element, L"Translation.X", CreateScalarAnimation(Milliseconds, Start, End, EasingFunction));
    }

    void AnimationExtensions::TranslateY(const UIElement& Element, const double_t Milliseconds, const double_t Start, const double_t End, const CompositionEasingFunction& EasingFunction)
    {
        ElementCompositionPreview::SetIsTranslationEnabled(Element, true);
        StartAnimation(Element, L"Translation.Y", CreateScalarAnimation(Milliseconds, Start, End, EasingFunction));
    }

    void AnimationExtensions::Scale(const FrameworkElement& Element, const double_t Milliseconds, const double_t Start, const double_t End, const CompositionEasingFunction& EasingFunction)
    {
        SetCenterPoint(Element, Element.ActualWidth() / 2.0, Element.ActualHeight() / 2.0);

        const float3 VectorStart = { float_t(Start), float_t(Start), 0 };
        const float3 VectorEnd   = { float_t(End), float_t(End), 0 };

        StartAnimation(Element, nameof(Visual::Scale), CreateVector3Animation(Milliseconds, VectorStart, VectorEnd, EasingFunction));
    }

    void AnimationExtensions::Blur(const UIElement& Element, const double_t Amount)
    {
        const CompositionEffectBrush Brush = CreateBlurEffectBrush(Amount);
        SetBrush(Element, Brush);
    }

    void AnimationExtensions::Blur(const UIElement& Element, const double_t Milliseconds, const double_t Start, const double_t End, const CompositionEasingFunction& EasingFunction)
    {
        const CompositionEffectBrush Brush = CreateBlurEffectBrush();
        SetBrush(Element, Brush);
        Brush.StartAnimation(L"Blur.BlurAmount", CreateScalarAnimation(Milliseconds, Start, End, EasingFunction));
    }

    void AnimationExtensions::Grayscale(const UIElement& Element)
    {
        const CompositionEffectBrush Brush = CreateGrayscaleEffectBrush();
        SetBrush(Element, Brush);
    }

    void AnimationExtensions::SetBrush(const UIElement& Element, const CompositionBrush& Brush)
    {
        SpriteVisual SpriteVisual = CreateSpriteVisual(Element);
        SpriteVisual.Brush(Brush);
        ElementCompositionPreview::SetElementChildVisual(Element, SpriteVisual);
    }

    void AnimationExtensions::ClearEffects(const UIElement& Element)
    {
        ElementCompositionPreview::SetElementChildVisual(Element, nullptr);
    }

    SpriteVisual AnimationExtensions::CreateSpriteVisual(const UIElement& Element)
    {
        return CreateSpriteVisual(ElementCompositionPreview::GetElementVisual(Element));
    }

    SpriteVisual AnimationExtensions::CreateSpriteVisual(const Visual& ElementVisual)
    {
        auto Compositor   = ElementVisual.Compositor();
        auto SpriteVisual = Compositor.CreateSpriteVisual();
        auto Expression   = Compositor.CreateExpressionAnimation();

        Expression.Expression(L"Visual.Size");
        Expression.SetReferenceParameter(L"Visual", ElementVisual);
        SpriteVisual.StartAnimation(nameof(Visual::Size), Expression);
        return SpriteVisual;
    }

    void AnimationExtensions::SetCenterPoint(const UIElement& Element, const double_t X, const double_t Y)
    {
        auto Visual = ElementCompositionPreview::GetElementVisual(Element);
        Visual.CenterPoint(float3{ float_t(X), float_t(Y), 0 });
    }

    void AnimationExtensions::StartAnimation(const UIElement& Element, const std::wstring_view PropertyName, const CompositionAnimation& Animation)
    {
        auto Visual = ElementCompositionPreview::GetElementVisual(Element);
        Visual.StartAnimation(PropertyName, Animation);
    }

    CompositionAnimation AnimationExtensions::CreateScalarAnimation(const double_t Milliseconds, const double_t Start, const double_t End, const CompositionEasingFunction& EasingFunction)
    {
        ScalarKeyFrameAnimation Animation = Application::Current().as<winrt::Mercatec::Helpers::IApplication>().MainWindow().Compositor().CreateScalarKeyFrameAnimation();
        Animation.InsertKeyFrame(0.0f, float_t(Start), EasingFunction);
        Animation.InsertKeyFrame(1.0f, float_t(End), EasingFunction);
        Animation.Duration(std::chrono::milliseconds{ std::chrono::milliseconds::rep(Milliseconds) });
        return Animation;
    }

    CompositionAnimation AnimationExtensions::CreateVector3Animation(const double_t Milliseconds, const float3& Start, const float3& End, [[maybe_unused]] const CompositionEasingFunction& EasingFunction)
    {
        Vector3KeyFrameAnimation Animation = Application::Current().as<winrt::Mercatec::Helpers::IApplication>().MainWindow().Compositor().CreateVector3KeyFrameAnimation();
        Animation.InsertKeyFrame(0.0f, Start);
        Animation.InsertKeyFrame(1.0f, End);
        Animation.Duration(std::chrono::milliseconds{ std::chrono::milliseconds::rep(Milliseconds) });
        return Animation;
    }

    CompositionEffectBrush AnimationExtensions::CreateBlurEffectBrush(const double_t Amount)
    {
        GaussianBlurEffect Effect;
        Effect.Name(L"Blur");
        Effect.BlurAmount(float_t(Amount));
        Effect.Source(CompositionEffectSourceParameter{ L"Source" });

        auto Compositor = Application::Current().as<winrt::Mercatec::Helpers::IApplication>().MainWindow().Compositor();
        auto Factory    = Compositor.CreateEffectFactory(Effect, winrt::param::iterable({ hstring(L"Blur.BlurAmount") }));
        auto Brush      = Factory.CreateBrush();

        Brush.SetSourceParameter(L"Source", Compositor.CreateBackdropBrush());
        return Brush;
    }

    CompositionEffectBrush AnimationExtensions::CreateGrayscaleEffectBrush()
    {
        GrayscaleEffect Effect;
        Effect.Name(L"Grayscale");
        Effect.Source(CompositionEffectSourceParameter{ L"Source" });

        auto Compositor = Application::Current().as<winrt::Mercatec::Helpers::IApplication>().MainWindow().Compositor();
        auto Factory    = Compositor.CreateEffectFactory(Effect);
        auto Brush      = Factory.CreateBrush();

        Brush.SetSourceParameter(L"Source", Compositor.CreateBackdropBrush());
        return Brush;
    }
} // namespace Mercatec::Helpers
