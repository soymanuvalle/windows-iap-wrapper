#include "GetCustomerCollectionsIdWorker.h"

GetCustomerCollectionsIdWorker::GetCustomerCollectionsIdWorker(const Napi::Function &callback, std::string token, std::string userId, StoreContext context)
    : Napi::AsyncWorker(callback), m_token(token), m_userId(userId), m_storeContext(context), m_result("") {}

void GetCustomerCollectionsIdWorker::Execute() { 
    std::wstring token(this->m_token.begin(), this->m_token.end());
    std::wstring userId(this->m_userId.begin(), this->m_userId.end());
    auto result = this->m_storeContext.GetCustomerCollectionsIdAsync(token, userId).get();

    if (result.empty()) {
        Napi::AsyncWorker::SetError("Empty result from Microsoft API. Make sure you've provided a valid Azure AD Token with the Collections resource.");
    } else {
        this->m_result = to_string(result);
    }
}

void GetCustomerCollectionsIdWorker::OnOK() {
    Napi::Env env = Env();
    Callback().MakeCallback(Receiver().Value(), {
        env.Null(),
        Napi::String::New(env, this->m_result)
    });
}

void GetCustomerCollectionsIdWorker::OnError(const Napi::Error &e) {
    Napi::Env env = Env();
    Callback().MakeCallback(Receiver().Value(), {
        e.Value(),
        env.Undefined()
    });
}
