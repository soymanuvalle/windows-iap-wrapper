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
declare type ProductKind = 'Durable' | 'Application' | 'Game' | 'Consumable' | 'UnmanagedConsumable';
declare class WindowsIapWrapper {
    constructor();
    initialize(hwnd: Uint8Array): boolean;
    getAssociatedStoreProductsAsync(productKinds: ProductKind[]): Promise<IStoreProduct[]>;
    getAssociatedStoreProductAsync(productKinds: ProductKind[], inAppOfferToken: string): Promise<IStoreProduct>;
    requestPurchaseAsync(storeId: string): Promise<boolean>;
    getCustomerPurchaseIdAsync(token: string, userId: string): Promise<string>;
    getCustomerCollectionsIdAsync(token: string, userId: string): Promise<string>;
    private _windowsIAP;
}
export = WindowsIapWrapper;
