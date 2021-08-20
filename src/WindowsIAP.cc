#include "WindowsIAP.h"
#include "GetAssociatedStoreProductsWorker.h"
#include "RequestPurchaseWorker.h"
#include "GetCustomerPurchaseIdWorker.h"
#include "GetCustomerCollectionsIdWorker.h"

Napi::Object WindowsIAP::Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func =
        DefineClass(env,
                    "WindowsIAP",
                    {
                        InstanceMethod("initialize", &WindowsIAP::Initialize),
                        InstanceMethod("getAssociatedStoreProductsAsync", &WindowsIAP::GetAssociatedStoreProductsAsync),
                        InstanceMethod("requestPurchaseAsync", &WindowsIAP::RequestPurchaseAsync),
                        InstanceMethod("getCustomerPurchaseIdAsync", &WindowsIAP::GetCustomerPurchaseIdAsync),
                        InstanceMethod("getCustomerCollectionsIdAsync", &WindowsIAP::GetCustomerCollectionsIdAsync)
                    });

    Napi::FunctionReference* constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);

    exports.Set("WindowsIAP", func);
    return exports;
}

WindowsIAP::WindowsIAP(const Napi::CallbackInfo& info): Napi::ObjectWrap<WindowsIAP>(info), m_storeContext(nullptr) {}

Napi::Value WindowsIAP::Initialize(const Napi::CallbackInfo &info) {
    // Get hwnd
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    Napi::Buffer<char *> bufferData = info[0].As<Napi::Buffer<char *>>();
    uint32_t handle = *reinterpret_cast<uint32_t *>(bufferData.Data());
    HWND hwnd = (HWND)handle;

    // Initialize StoreContext
    this->m_storeContext = StoreContext::GetDefault();
    auto initWindow = this->m_storeContext.try_as<IInitializeWithWindow>();
    
    if (initWindow == nullptr) {
        return Napi::Boolean::New(info.Env(), false);
    }

    HRESULT hr = initWindow->Initialize(hwnd);
    winrt::init_apartment();
    return Napi::Boolean::New(info.Env(), true);
}

void WindowsIAP::GetAssociatedStoreProductsAsync(const Napi::CallbackInfo &info) {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    Napi::Array productKinds = info[0].As<Napi::Array>();

    IVector<hstring> finalProductKinds {
        single_threaded_vector<hstring>()
    };
    
    for(int i = 0; i < productKinds.Length(); i++)
    {
      Napi::Value v = productKinds[i];
      if (v.IsString())
      {
        std::string value = (std::string)v.As<Napi::String>();
        finalProductKinds.Append(to_hstring(value));
      }
    }

    Napi::Function cb = info[1].As<Napi::Function>();
    (new GetAssociatedStoreProductsWorker(cb, finalProductKinds, this->m_storeContext))->Queue();
}

void WindowsIAP::RequestPurchaseAsync(const Napi::CallbackInfo &info) {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    Napi::String storeId = info[0].As<Napi::String>();
    Napi::Function cb = info[1].As<Napi::Function>();
    (new RequestPurchaseWorker(cb, storeId, this->m_storeContext))->Queue();
}

void WindowsIAP::GetCustomerPurchaseIdAsync(const Napi::CallbackInfo &info) {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    Napi::String token = info[0].As<Napi::String>();
    Napi::String userId = info[1].As<Napi::String>();
    Napi::Function cb = info[2].As<Napi::Function>();
    (new GetCustomerPurchaseIdWorker(cb, token, userId, this->m_storeContext))->Queue();
}

void WindowsIAP::GetCustomerCollectionsIdAsync(const Napi::CallbackInfo &info) {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    Napi::String token = info[0].As<Napi::String>();
    Napi::String userId = info[1].As<Napi::String>();
    Napi::Function cb = info[2].As<Napi::Function>();
    (new GetCustomerCollectionsIdWorker(cb, token, userId, this->m_storeContext))->Queue();
}