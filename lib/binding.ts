const addon = require('../build/Release/windows-iap-wrapper.node');

interface IStoreProduct {
	inAppOfferToken: string;
	price: {
		formattedRecurrencePrice: string;
		formattedBasePrice: string;
		formattedPrice: string;
		currencyCode: string;
	};
	storeId: string;
}

type ProductKind = 'Durable' | 'Application' | 'Game' | 'Consumable' | 'UnmanagedConsumable';

interface IStorePurchaseResult {
	status_null?: boolean;
	status: 0 | 1 | 2 | 3 | 4;
}

interface IWindowsIap {
	initialize(hwnd: Uint8Array): boolean;
	getAssociatedStoreProductsAsync(
		productKinds: ProductKind[],
		callback: (error: Error, result: IStoreProduct[]) => void
	): void;
	requestPurchaseAsync(storeId: String, callback: (error: Error, result: IStorePurchaseResult) => void): void;
	getCustomerPurchaseIdAsync(token: String, userId: string, callback: (error: Error, result: string) => void): void;
	getCustomerCollectionsIdAsync(
		token: String,
		userId: string,
		callback: (error: Error, result: string) => void
	): void;
}

class WindowsIapWrapper {
	constructor() {
		this._windowsIAP = new addon.WindowsIAP();
	}

	initialize(hwnd: Uint8Array) {
		return this._windowsIAP.initialize(hwnd);
	}

	getAssociatedStoreProductsAsync(productKinds: ProductKind[]): Promise<IStoreProduct[]> {
		return new Promise((resolve, reject) => {
			this._windowsIAP.getAssociatedStoreProductsAsync(
				productKinds,
				(error: Error, products: IStoreProduct[]) => {
					if (error) {
						reject({
							message: 'ERR_GET_PRODUCTS_UNKNOWN',
							error
						});
						return;
					}

					resolve(products);
				}
			);
		});
	}

	getAssociatedStoreProductAsync(productKinds: ProductKind[], inAppOfferToken: string): Promise<IStoreProduct> {
		return new Promise(async (resolve, reject) => {
			try {
				const products = await this.getAssociatedStoreProductsAsync(productKinds);
				const product = products.find((p: IStoreProduct) => p.inAppOfferToken === inAppOfferToken);

				if (!product) {
					throw { message: 'ERR_PRODUCT_NOT_FOUND' };
				}

				resolve(product);
			} catch (e) {
				reject(e);
			}
		});
	}

	requestPurchaseAsync(storeId: string): Promise<boolean> {
		return new Promise((resolve, reject) => {
			this._windowsIAP.requestPurchaseAsync(storeId, (error, result) => {
				if (error) {
					reject({
						message: 'ERR_PURCHASE_UNKNOWN',
						error
					});
					return;
				}

				const statusText = ['Succeeded', 'AlreadyPurchased', 'NotPurchased', 'NetworkError', 'ServerError'];
				
				if (result.status !== 0 && statusText[result.status]) {
					reject({
						message: statusText[result.status]
					});
					return;
				}

				resolve(true);
			});
		});
	}

	getCustomerPurchaseIdAsync(token: string, userId: string): Promise<string> {
		return new Promise((resolve, reject) => {
			this._windowsIAP.getCustomerPurchaseIdAsync(token, userId, (error, result) => {
				if (error) {
					reject({
						message: 'ERR_CUSTOMER_PURCHASE_ID_UNKNOWN',
						error
					});
					return;
				}

				resolve(result);
			});
		});
	}

	getCustomerCollectionsIdAsync(token: string, userId: string): Promise<string> {
		return new Promise((resolve, reject) => {
			this._windowsIAP.getCustomerCollectionsIdAsync(token, userId, (error, result) => {
				if (error) {
					reject({
						message: 'ERR_CUSTOMER_COLLECTIONS_ID_UNKNOWN',
						error
					});
					return;
				}

				resolve(result);
			});
		});
	}

	// private members
	private _windowsIAP: IWindowsIap;
}

export = WindowsIapWrapper;
