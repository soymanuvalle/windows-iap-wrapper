# windows-iap-wrapper

Node addon wrapper for Windows in-app purchases using `winrt::Windows::Services::Store`.

## Requirements

- **Node.js** 18+ (recommended: **24.x LTS**)
- **Python** 3.10+
- **Visual Studio 2022 Build Tools** with **Desktop development with C++**
- **Windows 10/11 SDK** (10.0.17763 or newer)

Native compilation only runs on **Windows**. On macOS/Linux the install script skips the native build (the package is a no-op there).

## Install / rebuild

```bash
npm install
# After installing into an Electron app, rebuild for Electron's ABI:
npx electron-rebuild -f --only windows-iap-wrapper
# Or from this repo:
npm run build:electron -- --target=19.1.9
```

`build:electron` resolves the Electron version from (in order):

1. `--target <version>`
2. `ELECTRON_VERSION` / `npm_config_target`
3. Nearby `node_modules/electron/package.json`

## Usage example with Electron

```ts
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
