#pragma once

#include <napi.h>
#include <Windows.h>
#include "winrt/Windows.Services.Store.h"
#include "winrt/Windows.Foundation.h"

using namespace winrt;
using namespace Windows::Services::Store;
using namespace Windows::Foundation::Collections;

class GetAssociatedStoreProductsWorker : public Napi::AsyncWorker {
    public:
        GetAssociatedStoreProductsWorker(const Napi::Function &callback, IVector<hstring> &productKinds, StoreContext context);

    protected:
        virtual void Execute() override;
        virtual void OnOK() override;
        virtual void OnError(const Napi::Error &e) override;

    private:
        StoreContext m_storeContext;
        IVector<hstring> m_productKinds;
        IIterator<IKeyValuePair<hstring, StoreProduct>> m_result;
};
