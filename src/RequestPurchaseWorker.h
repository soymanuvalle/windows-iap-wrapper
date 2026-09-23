#pragma once

#include <napi.h>
#include <string>
#include "winrt_store.h"

using namespace winrt;
using namespace Windows::Services::Store;

class RequestPurchaseWorker : public Napi::AsyncWorker {
    public:
        RequestPurchaseWorker(const Napi::Function &callback, std::string storeId, StoreContext context);

    protected:
        virtual void Execute() override;
        virtual void OnOK() override;
        virtual void OnError(const Napi::Error &e) override;

    private:
        StoreContext m_storeContext;
        std::string m_storeId;
        int m_status;
};
