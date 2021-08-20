const WindowsIapWrapper = require('../dist/binding.js');
const assert = require('assert');

// assert(WindowsIapWrapper, "The expected module is undefined");

async function testBasic() {
	try {
		const StoreContext = new WindowsIapWrapper();
		const product = await StoreContext.getAssociatedStoreProductsAsync(['Durable']);
		console.log(product);
	} catch (e) {
		console.error(e);
	}
}

testBasic();

// function testBasic()
// {
//     const instance = new WindowsIapWrapper("mr-yeoman");
//     assert(instance.greet, "The expected method is not defined");
//     assert.strictEqual(instance.greet("kermit"), "mr-yeoman", "Unexpected value returned");
// }

// function testInvalidParams()
// {
//     const instance = new WindowsIapWrapper();
// }

// assert.doesNotThrow(testBasic, undefined, "testBasic threw an expection");
// assert.throws(testInvalidParams, undefined, "testInvalidParams didn't throw");

// console.log("Tests passed- everything looks OK!");
