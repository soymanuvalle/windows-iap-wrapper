#pragma once

#include <napi.h>
#include <Windows.h>
#include "winrt/Windows.Services.Store.h"
#include "winrt/Windows.Foundation.h"
#include <string>

using namespace winrt;
using namespace Windows::Services::Store;
using namespace Windows::Foundation::Collections;

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
