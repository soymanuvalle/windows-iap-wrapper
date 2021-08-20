{
  'targets': [
    {
      'target_name': 'windows-iap-wrapper',
      'sources': [
        'src/main.cc',
        'src/WindowsIAP.cc',
        'src/GetAssociatedStoreProductsWorker.cc',
        'src/RequestPurchaseWorker.cc',
        'src/GetCustomerPurchaseIdWorker.cc',
        'src/GetCustomerCollectionsIdWorker.cc'
      ],
      'include_dirs': ["<!@(node -p \"require('node-addon-api').include\")"],
      'dependencies': ["<!(node -p \"require('node-addon-api').gyp\")"],
      'cflags!': [ '-fno-exceptions' ],
      'cflags_cc!': [ '-fno-exceptions' ],
      'libraries': ['-lruntimeobject.lib'],
      'defines': [ 'NAPI_DISABLE_CPP_EXCEPTIONS' ],
      'msvs_settings': {
        'VCCLCompilerTool': { 'ExceptionHandling': 1, 'AdditionalOptions': ['/std:c++17 /EHsc /await']}
      }
    }
  ]
}