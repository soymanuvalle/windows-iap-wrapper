#pragma once

#include <napi.h>
#include <string>
#include "winrt_store.h"

using namespace winrt;
using namespace Windows::Services::Store;

class GetCustomerPurchaseIdWorker : public Napi::AsyncWorker {
    public:
        GetCustomerPurchaseIdWorker(const Napi::Function &callback, std::string token, std::string userId, StoreContext context);

    protected:
        virtual void Execute() override;
        virtual void OnOK() override;
        virtual void OnError(const Napi::Error &e) override;

    private:
        StoreContext m_storeContext;
        std::string m_token, m_userId, m_result;
};
