#include "RequestPurchaseWorker.h"

RequestPurchaseWorker::RequestPurchaseWorker(const Napi::Function &callback, std::string storeId, StoreContext context)
    : Napi::AsyncWorker(callback), m_storeId(storeId), m_storeContext(context), m_status(NULL) {}

void RequestPurchaseWorker::Execute() { 
    auto result = this->m_storeContext.RequestPurchaseAsync(to_hstring(this->m_storeId)).get();

    if (result.ExtendedError() == S_OK) {
        this->m_status = static_cast<int>(result.Status());
    } else {
        Napi::AsyncWorker::SetError(std::to_string(result.ExtendedError()));
    }
}

void RequestPurchaseWorker::OnOK() {
    Napi::Env env = Env();
    Napi::Object obj = Napi::Object::New(env);
    
    if (m_status != NULL) {
        obj.Set("status", m_status);
    } else {
        obj.Set("status_null", true);
        obj.Set("status", 0);
    }

    Callback().MakeCallback(Receiver().Value(), {
        env.Null(),
        obj
    });
}

void RequestPurchaseWorker::OnError(const Napi::Error &e) {
    Napi::Env env = Env();
    Callback().MakeCallback(Receiver().Value(), {
        e.Value(),
        env.Undefined()
    });
}
