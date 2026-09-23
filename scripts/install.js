'use strict';

/**
 * Native rebuild against host Node is skipped here on purpose.
 * This package is consumed by Electron apps; rebuild for Electron's ABI via:
 *   npx electron-rebuild -f --only windows-iap-wrapper
 *   npm run build:electron -- --target=<electron-version>
 * ecrome-electron runs this in postinstall (scripts/rebuildNative.js).
 */
console.log(
	'windows-iap-wrapper: skipping host Node native build (use electron-rebuild / build:electron)'
);
process.exit(0);
