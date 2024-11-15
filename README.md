# windows-iap-wrapper

- Build Tools for Visual Studio 2017 (version 15.9): https://my.visualstudio.com/Downloads?q=visual%20studio%202017&wt.mc_id=o~msft~vscom~older-downloads
- Windows SDK (10.17763.0): https://developer.microsoft.com/en-us/windows/downloads/sdk-archive/

## Usage example with electron
```
import { getCurrentWindow } from '@electron/remote';
import WindowsIapWrapper from 'windows-iap-wrapper';

const getStoreContext = () => {
    const context = new WindowsIapWrapper();
    let hwnd = getCurrentWindow().getNativeWindowHandle();
    const initialized = context.initialize(hwnd);
    if (!initialized) return null;
    return context;
};

const StoreContext = getStoreContext();

const product = await StoreContext.getAssociatedStoreProductAsync(['Durable'], identifier);
const result = await StoreContext.requestPurchaseAsync(product.storeId);
```
