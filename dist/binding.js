"use strict";
var __awaiter = (this && this.__awaiter) || function (thisArg, _arguments, P, generator) {
    function adopt(value) { return value instanceof P ? value : new P(function (resolve) { resolve(value); }); }
    return new (P || (P = Promise))(function (resolve, reject) {
        function fulfilled(value) { try { step(generator.next(value)); } catch (e) { reject(e); } }
        function rejected(value) { try { step(generator["throw"](value)); } catch (e) { reject(e); } }
        function step(result) { result.done ? resolve(result.value) : adopt(result.value).then(fulfilled, rejected); }
        step((generator = generator.apply(thisArg, _arguments || [])).next());
    });
};
const addon = require('../build/Release/windows-iap-wrapper.node');
class WindowsIapWrapper {
    constructor() {
        this._windowsIAP = new addon.WindowsIAP();
    }
    initialize(hwnd) {
        return this._windowsIAP.initialize(hwnd);
    }
    getAssociatedStoreProductsAsync(productKinds) {
        return new Promise((resolve, reject) => {
            this._windowsIAP.getAssociatedStoreProductsAsync(productKinds, (error, products) => {
                if (error) {
                    reject({
                        message: 'ERR_GET_PRODUCTS_UNKNOWN',
                        error
                    });
                    return;
                }
                resolve(products);
            });
        });
    }
    getAssociatedStoreProductAsync(productKinds, inAppOfferToken) {
        return new Promise((resolve, reject) => __awaiter(this, void 0, void 0, function* () {
            try {
                const products = yield this.getAssociatedStoreProductsAsync(productKinds);
                const product = products.find((p) => p.inAppOfferToken === inAppOfferToken);
                if (!product) {
                    throw { message: 'ERR_PRODUCT_NOT_FOUND' };
                }
                resolve(product);
            }
            catch (e) {
                reject(e);
            }
        }));
    }
    requestPurchaseAsync(storeId) {
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
    getCustomerPurchaseIdAsync(token, userId) {
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
    getCustomerCollectionsIdAsync(token, userId) {
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
}
module.exports = WindowsIapWrapper;
