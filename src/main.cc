#include <napi.h>
#include "WindowsIAP.h"

Napi::Object InitAll(Napi::Env env, Napi::Object exports) {
    return WindowsIAP::Init(env, exports);
}

NODE_API_MODULE(addon, InitAll)