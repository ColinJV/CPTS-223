#ifndef PRODUCT_H
#define PRODUCT_H

#include <string>
#include <ostream>

using namespace std;

class Product {
public:
	// Constructor
	Product(const string& newUniqueID = "", const string & newProductName = "", const string & newBrandName = "",
		const string & newAsin = "", const string& newCategory = "", const string& newUpcEanCode = "",
		const string& newListPrice = "", const string& newSellingPrice = "", const string& newQuantity = "", const string& newModelNumber = "",
		const string& newAboutProduct = "",	const string& newProductSpecification = "", const string& newTechnicalDetails = "",
		const string& newShippingWeight = "", const string& newProductDimensions = "", const string& newImage = "",
		const string& newVariants = "",	const string& newSKU = "", const string& newProductURL = "", const string& newStock = "",
		const string& newProductDetails = "", const string& newDimensions = "", const string& newColor = "",
		const string& newIngredients = "", const string& newDirectionToUse = "", const string& newIsAmazonSeller = "",
		const string& newSizeQuantityVariant = "", const string& newProductDescription = "");
	void fillEmptyFields();

	// Destructor
	~Product();

	// Copy Constructor
	Product(Product& original);

	// Accessors
	string getUniqueID() const;
	string getProductName() const;
	string getBrandName() const;
	string getAsin() const;
	string getCategory() const;
	string getUpcEanCode() const;
	string getListPrice() const;
	string getSellingPrice() const;
	string getQuantity() const;
	string getModelNumber() const;
	string getAboutProduct() const;
	string getProductSpecification() const;
	string getTechnicalDetails() const;
	string getShippingWeight() const;
	string getProductDimensions() const;
	string getImage() const;
	string getVariants() const;
	string getSKU() const;
	string getProductURL() const;
	string getStock() const;
	string getProductDetails() const;
	string getDimensions() const;
	string getColor() const;
	string getIngredients() const;
	string getDirectionsToUse() const;
	string getIsAmazonSeller() const;
	string getSizeQuantityVariant() const;
	string getProductDescription() const;
	
	// Contains
	bool hasCategory(const string& searchCategory);

	// Display
	void displayProduct(ostream& out);
	void displayIDandName(ostream& out);

private:
	string uniqueID;
	string productName;
	string brandName;
	string Asin;
	string category;
	string upcEanCode;
	string listPrice;
	string sellingPrice;
	string quantity;
	string modelNumber;
	string aboutProduct;
	string productSpecification;
	string technicalDetails;
	string shippingWeight;
	string productDimensions;
	string image;
	string variants;
	string SKU;
	string productURL;
	string stock;
	string productDetails;
	string dimensions;
	string color;
	string ingredients;
	string directionToUse;
	string isAmazonSeller;
	string sizeQuantityVariant;
	string productDescription;
};

#endif