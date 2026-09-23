{
  "targets": [
    {
      "target_name": "windows-iap-wrapper",
      "sources": [
        "src/main.cc",
        "src/WindowsIAP.cc",
        "src/GetAssociatedStoreProductsWorker.cc",
        "src/RequestPurchaseWorker.cc",
        "src/GetCustomerPurchaseIdWorker.cc",
        "src/GetCustomerCollectionsIdWorker.cc"
      ],
      "include_dirs": [
        "<!@(node -p \"require('node-addon-api').include\")"
      ],
      "defines": [ "NAPI_DISABLE_CPP_EXCEPTIONS" ],
      "cflags!": [ "-fno-exceptions" ],
      "cflags_cc!": [ "-fno-exceptions" ],
      "conditions": [
        ["OS=='win'", {
          "libraries": [ "-lruntimeobject.lib" ],
          "msvs_settings": {
            "VCCLCompilerTool": {
              "ExceptionHandling": 1,
              "AdditionalOptions": [ "/std:c++20", "/EHsc", "/await" ]
            }
          }
        }]
      ]
    }
  ]
}
