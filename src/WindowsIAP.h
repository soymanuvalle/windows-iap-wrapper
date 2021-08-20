#ifndef WINDOWS_IAP_H
#define WINDOWS_IAP_H

#include <napi.h>
#include <Windows.h>
#include "winrt/Windows.Services.Store.h"
#include "winrt/Windows.Foundation.h"
#include <shobjidl.h>
#include <Shlobj.h>

using namespace winrt;
using namespace Windows::Services::Store;

class WindowsIAP : public Napi::ObjectWrap<WindowsIAP> {
    public:
        static Napi::Object Init(Napi::Env env, Napi::Object exports);
        WindowsIAP(const Napi::CallbackInfo& info);

    private:
        Napi::Value Initialize(const Napi::CallbackInfo &info);
        void GetAssociatedStoreProductsAsync(const Napi::CallbackInfo& info);
        void RequestPurchaseAsync(const Napi::CallbackInfo& info);
        void GetCustomerPurchaseIdAsync(const Napi::CallbackInfo& info);
        void GetCustomerCollectionsIdAsync(const Napi::CallbackInfo& info);
        
        StoreContext m_storeContext;
};

#endif