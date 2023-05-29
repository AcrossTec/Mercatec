#pragma once

#include <Windows.h>
#include "Mercatec.WinUIEx.Enum.hpp"

namespace Windows::Win32
{
    namespace UI
    {
        namespace WindowsAndMessaging
        {
            enum struct SystemMetricsIndex : int32_t
            {
                SmArrange                     = SM_ARRANGE,
                SmCleanBoot                   = SM_CLEANBOOT,
                SmCMonitors                   = SM_CMONITORS,
                SmCMouseButtons               = SM_CMOUSEBUTTONS,
                SmConvertiblesLateMode        = SM_CONVERTIBLESLATEMODE,
                SmCxBorder                    = SM_CXBORDER,
                SmCxCursor                    = SM_CXCURSOR,
                SmCxDlgFrame                  = SM_CXDLGFRAME,
                SmCxDoubleClk                 = SM_CXDOUBLECLK,
                SmCxDrag                      = SM_CXDRAG,
                SmCxEdge                      = SM_CXEDGE,
                SmCxFixedFrame                = SM_CXFIXEDFRAME,
                SmCxFocusBorder               = SM_CXFOCUSBORDER,
                SmCxFrame                     = SM_CXFRAME,
                SmCxFullScreen                = SM_CXFULLSCREEN,
                SmCxHScroll                   = SM_CXHSCROLL,
                SmCxHThumb                    = SM_CXHTHUMB,
                SmCxIcon                      = SM_CXICON,
                SmCxIconSpacing               = SM_CXICONSPACING,
                SmCxMaximized                 = SM_CXMAXIMIZED,
                SmCxMaxTrack                  = SM_CXMAXTRACK,
                SmCxMenuCheck                 = SM_CXMENUCHECK,
                SmCxMenuSize                  = SM_CXMENUSIZE,
                SmCxMin                       = SM_CXMIN,
                SmCxMinimized                 = SM_CXMINIMIZED,
                SmCxMinSpacing                = SM_CXMINSPACING,
                SmCxMinTrack                  = SM_CXMINTRACK,
                SmCxPaddedBorder              = SM_CXPADDEDBORDER,
                SmCxScreen                    = SM_CXSCREEN,
                SmCxSize                      = SM_CXSIZE,
                SmCxSizeFrame                 = SM_CXSIZEFRAME,
                SmCxSMIcon                    = SM_CXSMICON,
                SmCxSMsize                    = SM_CXSMSIZE,
                SmCxVirtualScreen             = SM_CXVIRTUALSCREEN,
                SmCxVScroll                   = SM_CXVSCROLL,
                SmCyBorder                    = SM_CYBORDER,
                SmCyCaption                   = SM_CYCAPTION,
                SmCyCursor                    = SM_CYCURSOR,
                SmCyDlgFrame                  = SM_CYDLGFRAME,
                SmCyDoubleClk                 = SM_CYDOUBLECLK,
                SmCyDrag                      = SM_CYDRAG,
                SmCyEdge                      = SM_CYEDGE,
                SmCyFixedFrame                = SM_CYFIXEDFRAME,
                SmCyFocusBorder               = SM_CYFOCUSBORDER,
                SmCyFrame                     = SM_CYFRAME,
                SmCyFullScreen                = SM_CYFULLSCREEN,
                SmCyHScroll                   = SM_CYHSCROLL,
                SmCyIcon                      = SM_CYICON,
                SmCyIconSpacing               = SM_CYICONSPACING,
                SmCyKanjiWindow               = SM_CYKANJIWINDOW,
                SmCyMaximized                 = SM_CYMAXIMIZED,
                SmCyMaxTrack                  = SM_CYMAXTRACK,
                SmCyMenu                      = SM_CYMENU,
                SmCyMenuCheck                 = SM_CYMENUCHECK,
                SmCyMenuSize                  = SM_CYMENUSIZE,
                SmCyMin                       = SM_CYMIN,
                SmCyMinimized                 = SM_CYMINIMIZED,
                SmCyMinSpacing                = SM_CYMINSPACING,
                SmCyMinTrack                  = SM_CYMINTRACK,
                SmCyScreen                    = SM_CYSCREEN,
                SmCySize                      = SM_CYSIZE,
                SmCySizeFrame                 = SM_CYSIZEFRAME,
                SmCySMCaption                 = SM_CYSMCAPTION,
                SmCySMIcon                    = SM_CYSMICON,
                SmCySMSize                    = SM_CYSMSIZE,
                SmCyVirtualScreen             = SM_CYVIRTUALSCREEN,
                SmCyVScroll                   = SM_CYVSCROLL,
                SmCyVThumb                    = SM_CYVTHUMB,
                SmDbCsEnabled                 = SM_DBCSENABLED,
                SmDebug                       = SM_DEBUG,
                SmDigitizer                   = SM_DIGITIZER,
                SmImmEnabled                  = SM_IMMENABLED,
                SmMaximumTouches              = SM_MAXIMUMTOUCHES,
                SmMediaCenter                 = SM_MEDIACENTER,
                SmMenuDropAlignment           = SM_MENUDROPALIGNMENT,
                SmMidEastEnabled              = SM_MIDEASTENABLED,
                SmMousePresent                = SM_MOUSEPRESENT,
                SmMouseHorizontalWheelPresent = SM_MOUSEHORIZONTALWHEELPRESENT,
                SmMouseWheelPresent           = SM_MOUSEWHEELPRESENT,
                SmNetwork                     = SM_NETWORK,
                SmPenWindows                  = SM_PENWINDOWS,
                SmRemoteControl               = SM_REMOTECONTROL,
                SmRemoteSession               = SM_REMOTESESSION,
                SmSameDisplayFormat           = SM_SAMEDISPLAYFORMAT,
                SmSecure                      = SM_SECURE,
                SmServerR2                    = SM_SERVERR2,
                SmShowSounds                  = SM_SHOWSOUNDS,
                SmShuttingDown                = SM_SHUTTINGDOWN,
                SmSlowMachine                 = SM_SLOWMACHINE,
                SmStarter                     = SM_STARTER,
                SmSwapButton                  = SM_SWAPBUTTON,
                SmSystemDocked                = SM_SYSTEMDOCKED,
                SmTabletPC                    = SM_TABLETPC,
                SmXVirtualScreen              = SM_XVIRTUALSCREEN,
                SmYVirtualScreen              = SM_YVIRTUALSCREEN,
            };

            enum struct WindowLongPtrIndex : int32_t
            {
                GwlpWndProc    = GWLP_WNDPROC,
                GwlpHInstance  = GWLP_HINSTANCE,
                GwlpHWndParent = GWLP_HWNDPARENT,
                GwlpUserData   = GWLP_USERDATA,
                GwlpId         = GWLP_ID,
                GwlWndProc     = GWLP_WNDPROC,    // GWL_WNDPROC
                GwlHInstance   = GWLP_HINSTANCE,  // GWL_HINSTANCE
                GwlHWndParent  = GWLP_HWNDPARENT, // GWL_HWNDPARENT
                GwlUserData    = GWLP_USERDATA,   // GWL_USERDATA
                GwlStyle       = GWL_STYLE,
                GwlExStyle     = GWL_EXSTYLE,
                GwlId          = GWL_ID,
            };

            enum struct ShowWindowCmd : int32_t
            {
                SwForceMinimize   = SW_FORCEMINIMIZE,
                SwHide            = SW_HIDE,
                SwMaximize        = SW_MAXIMIZE,
                SwMinimize        = SW_MINIMIZE,
                SwRestore         = SW_RESTORE,
                SwShow            = SW_SHOW,
                SwShowDefault     = SW_SHOWDEFAULT,
                SwShowMaximized   = SW_SHOWMAXIMIZED,
                SwShowMinimized   = SW_SHOWMINIMIZED,
                SwShowMinNoActive = SW_SHOWMINNOACTIVE,
                SwShowNa          = SW_SHOWNA,
                SwShowNoActivate  = SW_SHOWNOACTIVATE,
                SwShowNormal      = SW_SHOWNORMAL,
                SwNormal          = SW_NORMAL,
                SwMax             = SW_MAX,
                SwParentClosing   = SW_PARENTCLOSING,
                SwOtherZoom       = SW_OTHERZOOM,
                SwParentOpening   = SW_PARENTOPENING,
                SwOtherUnZoom     = SW_OTHERUNZOOM,
                SwScrollChildren  = SW_SCROLLCHILDREN,
                SwInvalidate      = SW_INVALIDATE,
                SwErase           = SW_ERASE,
                SwSmoothScroll    = SW_SMOOTHSCROLL,
            };

            enum struct SetWindowPosFlags : UINT
            {
                SwpAsyncWindowPos = SWP_ASYNCWINDOWPOS,
                SwpDeferErase     = SWP_DEFERERASE,
                SwpDrawFrame      = SWP_DRAWFRAME,
                SwpFrameChanged   = SWP_FRAMECHANGED,
                SwpHideWindow     = SWP_HIDEWINDOW,
                SwpNoActivate     = SWP_NOACTIVATE,
                SwpNoCopyBits     = SWP_NOCOPYBITS,
                SwpNoMove         = SWP_NOMOVE,
                SwpNoOwnerZOrder  = SWP_NOOWNERZORDER,
                SwpNoReDraw       = SWP_NOREDRAW,
                SwpNoRePosition   = SWP_NOREPOSITION,
                SwpNoSendChanging = SWP_NOSENDCHANGING,
                SwpNoSize         = SWP_NOSIZE,
                SwpNoZOrder       = SWP_NOZORDER,
                SwpShowWindow     = SWP_SHOWWINDOW,
            };

            enum struct GdiImageType : UINT
            {
                ImageBitmap = IMAGE_BITMAP,
                ImageCursor = IMAGE_CURSOR,
                ImageIcon   = IMAGE_ICON,
            };
        } // namespace WindowsAndMessaging

        namespace Controls
        {
            enum struct ImageFlags : UINT
            {
                LrCreateDibSection = LR_CREATEDIBSECTION,
                LrDefaultColor     = LR_DEFAULTCOLOR,
                LrDefaultSize      = LR_DEFAULTSIZE,
                LrLoadFromFile     = LR_LOADFROMFILE,
                LrLoadMap3DColors  = LR_LOADMAP3DCOLORS,
                LrLoadTransparent  = LR_LOADTRANSPARENT,
                LrMonoChrome       = LR_MONOCHROME,
                LrShared           = LR_SHARED,
                LrVgaColor         = LR_VGACOLOR,
                LrCopyDeleteOrg    = LR_COPYDELETEORG,
                LrCopyFromResource = LR_COPYFROMRESOURCE,
                LrCopyReturnOrg    = LR_COPYRETURNORG,
            };
        } // namespace Controls

    } // namespace UI

    namespace Graphics::Gdi
    {
        enum struct MonitorFromFlags : DWORD
        {
            MonitorDefaultToNearest = MONITOR_DEFAULTTONEAREST,
            MonitorDefaultToNull    = MONITOR_DEFAULTTONULL,
            MonitorDefaultToPrimary = MONITOR_DEFAULTTOPRIMARY,
        };
    } // namespace Graphics::Gdi
} // namespace Windows::Win32

//
// clang-format off
//
#define X LrCreateDibSection, LrDefaultColor , LrDefaultSize, LrLoadFromFile, LrLoadMap3DColors,\
          LrLoadTransparent , LrMonoChrome   , LrShared     , LrVgaColor    , LrCopyDeleteOrg  ,\
          LrCopyFromResource, LrCopyReturnOrg
MAKE_ENUM_TRAITS(Windows::Win32::UI::Controls, ImageFlags)
#undef X

#define X SmArrange        , SmCleanBoot    , SmCMonitors                  , SmCMouseButtons    , SmConvertiblesLateMode,\
          SmCxBorder       , SmCxCursor     , SmCxDlgFrame                 , SmCxDoubleClk      , SmCxDrag              ,\
          SmCxEdge         , SmCxFixedFrame , SmCxFocusBorder              , SmCxFrame          , SmCxFullScreen        ,\
          SmCxHScroll      , SmCxHThumb     , SmCxIcon                     , SmCxIconSpacing    , SmCxMaximized         ,\
          SmCxMaxTrack     , SmCxMenuCheck  , SmCxMenuSize                 , SmCxMin            , SmCxMinimized         ,\
          SmCxMinSpacing   , SmCxMinTrack   , SmCxPaddedBorder             , SmCxScreen         , SmCxSize              ,\
          SmCxSizeFrame    , SmCxSMIcon     , SmCxSMsize                   , SmCxVirtualScreen  , SmCxVScroll           ,\
          SmCyBorder       , SmCyCaption    , SmCyCursor                   , SmCyDlgFrame       , SmCyDoubleClk         ,\
          SmCyDrag         , SmCyEdge       , SmCyFixedFrame               , SmCyFocusBorder    , SmCyFrame             ,\
          SmCyFullScreen   , SmCyHScroll    , SmCyIcon                     , SmCyIconSpacing    , SmCyKanjiWindow       ,\
          SmCyMaximized    , SmCyMaxTrack   , SmCyMenu                     , SmCyMenuCheck      , SmCyMenuSize          ,\
          SmCyMin          , SmCyMinimized  , SmCyMinSpacing               , SmCyMinTrack       , SmCyScreen            ,\
          SmCySize         , SmCySizeFrame  , SmCySMCaption                , SmCySMIcon         , SmCySMSize            ,\
          SmCyVirtualScreen, SmCyVScroll    , SmCyVThumb                   , SmDbCsEnabled      , SmDebug               ,\
          SmDigitizer      , SmImmEnabled   , SmMaximumTouches             , SmMediaCenter      , SmMenuDropAlignment   ,\
          SmMidEastEnabled , SmMousePresent , SmMouseHorizontalWheelPresent, SmMouseWheelPresent, SmNetwork             ,\
          SmPenWindows     , SmRemoteControl, SmRemoteSession              , SmSameDisplayFormat, SmSecure              ,\
          SmServerR2       , SmShowSounds   , SmShuttingDown               , SmSlowMachine      , SmStarter             ,\
          SmSwapButton     , SmSystemDocked , SmTabletPC                   , SmXVirtualScreen   , SmYVirtualScreen
MAKE_ENUM_TRAITS(Windows::Win32::UI::WindowsAndMessaging, SystemMetricsIndex)
#undef X

#define X GwlpWndProc, GwlpHInstance, GwlpHWndParent, GwlpUserData, GwlpId  ,\
          GwlWndProc , GwlHInstance , GwlHWndParent , GwlUserData , GwlStyle,\
          GwlExStyle , GwlId
MAKE_ENUM_TRAITS(Windows::Win32::UI::WindowsAndMessaging, WindowLongPtrIndex)
#undef X

#define X SwForceMinimize, SwHide          , SwMaximize     , SwMinimize     , SwRestore        ,\
          SwShow         , SwShowDefault   , SwShowMaximized, SwShowMinimized, SwShowMinNoActive,\
          SwShowNa       , SwShowNoActivate, SwShowNormal   , SwNormal       , SwMax            ,\
          SwParentClosing, SwOtherZoom     , SwParentOpening, SwOtherUnZoom  , SwScrollChildren ,\
          SwInvalidate   , SwErase         , SwSmoothScroll
MAKE_ENUM_TRAITS(Windows::Win32::UI::WindowsAndMessaging, ShowWindowCmd)
#undef X

#define X SwpAsyncWindowPos, SwpDeferErase    , SwpDrawFrame, SwpFrameChanged , SwpHideWindow,\
          SwpNoActivate    , SwpNoCopyBits    , SwpNoMove   , SwpNoOwnerZOrder, SwpNoReDraw  ,\
          SwpNoRePosition  , SwpNoSendChanging, SwpNoSize   , SwpNoZOrder     , SwpShowWindow
MAKE_ENUM_TRAITS(Windows::Win32::UI::WindowsAndMessaging, SetWindowPosFlags)
#undef X

#define X ImageBitmap, ImageCursor, ImageIcon
MAKE_ENUM_TRAITS(Windows::Win32::UI::WindowsAndMessaging, GdiImageType)
#undef X

#define X MonitorDefaultToNearest, MonitorDefaultToNull, MonitorDefaultToPrimary
MAKE_ENUM_TRAITS(Windows::Win32::Graphics::Gdi, MonitorFromFlags)
#undef X

ENUM_BITMASK_OPS(Windows::Win32::UI::Controls::ImageFlags)
ENUM_BITMASK_OPS(Windows::Win32::UI::WindowsAndMessaging::SystemMetricsIndex)
ENUM_BITMASK_OPS(Windows::Win32::UI::WindowsAndMessaging::WindowLongPtrIndex)
ENUM_BITMASK_OPS(Windows::Win32::UI::WindowsAndMessaging::ShowWindowCmd)
ENUM_BITMASK_OPS(Windows::Win32::UI::WindowsAndMessaging::SetWindowPosFlags)
ENUM_BITMASK_OPS(Windows::Win32::UI::WindowsAndMessaging::GdiImageType)
ENUM_BITMASK_OPS(Windows::Win32::Graphics::Gdi::MonitorFromFlags)

//
// clang-format on
//
