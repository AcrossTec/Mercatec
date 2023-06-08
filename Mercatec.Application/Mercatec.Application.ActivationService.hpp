#pragma once

#include <winrt/Mercatec.ViewModels.h>
#include <winrt/Mercatec.Helpers.ViewModels.h>
#include <winrt/Windows.UI.Xaml.Interop.h>

namespace Mercatec::Application
{
    struct ActivationInfo : winrt::implements<ActivationInfo, winrt::IInspectable>
    {
        static winrt::com_ptr<ActivationInfo> CreateDefault();

        template <typename TViewModel>
        requires /* std::is_base_of_v<winrt::Mercatec::Helpers::ViewModels::ViewModelBase, TViewModel> and */ requires { winrt::xaml_typename<TViewModel>(); }
        static winrt::com_ptr<ActivationInfo> Create(const IInspectable& entry_args = nullptr)
        {
            winrt::com_ptr<ActivationInfo> Info{ winrt::make_self<ActivationInfo>() };
            Info->EntryViewModel = winrt::xaml_typename<TViewModel>();
            Info->EntryArgs      = entry_args;
            return Info;
        }

        winrt::Windows::UI::Xaml::Interop::TypeName EntryViewModel;
        winrt::IInspectable                         EntryArgs;
    };

    //struct ActivationService sealed abstract
    //{
    //public:
    //    static winrt::com_ptr<ActivationInfo> GetActivationInfo(IActivatedEventArgs args)
    //    {
    //        switch ( args.Kind )
    //        {
    //            case ActivationKind.Protocol:
    //                return GetProtocolActivationInfo(args as ProtocolActivatedEventArgs);

    //            case ActivationKind.Launch:
    //            default:
    //                return ActivationInfo.CreateDefault();
    //        }
    //    }

    //private:
    //    static winrt::com_ptr<ActivationInfo> GetProtocolActivationInfo(ProtocolActivatedEventArgs args)
    //    {
    //        if ( args != null )
    //        {
    //            switch ( args.Uri.AbsolutePath.ToLowerInvariant() )
    //            {
    //                case "customer":
    //                case "customers":
    //                    long customerID = args.Uri.GetInt64Parameter("id");
    //                    if ( customerID > 0 )
    //                    {
    //                        return ActivationInfo.Create<CustomerDetailsViewModel>(new CustomerDetailsArgs{ CustomerID = customerID });
    //                    }
    //                    return ActivationInfo.Create<CustomersViewModel>(new CustomerListArgs());
    //                case "order":
    //                case "orders":
    //                    long orderID = args.Uri.GetInt64Parameter("id");
    //                    if ( orderID > 0 )
    //                    {
    //                        return ActivationInfo.Create<OrderDetailsViewModel>(new OrderDetailsArgs{ OrderID = orderID });
    //                    }
    //                    return ActivationInfo.Create<OrdersViewModel>(new OrderListArgs());
    //                case "product":
    //                case "products":
    //                    string productID = args.Uri.GetParameter("id");
    //                    if ( productID != null )
    //                    {
    //                        return ActivationInfo.Create<ProductDetailsViewModel>(new ProductDetailsArgs{ ProductID = productID });
    //                    }
    //                    return ActivationInfo.Create<ProductsViewModel>(new ProductListArgs());
    //            }
    //        }
    //        return ActivationInfo.CreateDefault();
    //    }
    //};


} // namespace Mercatec::Application
