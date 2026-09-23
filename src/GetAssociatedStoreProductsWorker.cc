#include "GetAssociatedStoreProductsWorker.h"

GetAssociatedStoreProductsWorker::GetAssociatedStoreProductsWorker(
	const Napi::Function &callback,
	IVector<hstring> const& productKinds,
	StoreContext context)
	: Napi::AsyncWorker(callback),
	  m_productKinds(productKinds),
	  m_storeContext(context),
	  m_products(nullptr) {}

void GetAssociatedStoreProductsWorker::Execute() {
	if (m_productKinds.Size() == 0) {
		Napi::AsyncWorker::SetError("Invalid product kinds supplied.");
		return;
	}

	auto res = this->m_storeContext.GetAssociatedStoreProductsAsync(m_productKinds).get();
	this->m_products = res.Products();
}

void GetAssociatedStoreProductsWorker::OnOK() {
	Napi::Env env = Env();
	Napi::Array products = Napi::Array::New(env);
	uint32_t i = 0;

	for (auto const& current : this->m_products) {
		Napi::Object storeProd = Napi::Object::New(env);
		Napi::Object storePrice = Napi::Object::New(env);

		StoreProduct product = current.Value();
		storeProd.Set("inAppOfferToken", to_string(product.InAppOfferToken()));
		auto price = product.Price();
		storePrice.Set("formattedRecurrencePrice", to_string(price.FormattedRecurrencePrice()));
		storePrice.Set("formattedBasePrice", to_string(price.FormattedBasePrice()));
		storePrice.Set("formattedPrice", to_string(price.FormattedPrice()));
		storePrice.Set("currencyCode", to_string(price.CurrencyCode()));
		storeProd.Set("price", storePrice);
		storeProd.Set("storeId", to_string(current.Key()));

		products[i++] = storeProd;
	}

	Callback().MakeCallback(Receiver().Value(), {
		env.Null(),
		products
	});
}

void GetAssociatedStoreProductsWorker::OnError(const Napi::Error &e) {
	Napi::Env env = Env();
	Callback().MakeCallback(Receiver().Value(), {
		e.Value(),
		env.Undefined()
	});
}
