#include "Product.h"

// Product constructor
Product::Product(const string& newUniqueID, const string& newProductName, const string& newBrandName,
	const string& newAsin, const string& newCategory, const string& newUpcEanCode,
	const string& newListPrice, const string& newSellingPrice, const string& newQuantity, const string& newModelNumber,
	const string& newAboutProduct, const string& newProductSpecification, const string& newTechnicalDetails,
	const string& newShippingWeight, const string& newProductDimensions, const string& newImage,
	const string& newVariants, const string& newSKU, const string& newProductURL, const string& newStock,
	const string& newProductDetails, const string& newDimensions, const string& newColor, const string& newIngredients,
	const string& newDirectionToUse, const string& newIsAmazonSeller, const string& newSizeQuantityVariant,
	const string& newProductDescription)
{
	uniqueID = newUniqueID;
	productName = newProductName;
	brandName = newBrandName;
	Asin = newAsin;
	category = newCategory;
	upcEanCode = newUpcEanCode;
	listPrice = newListPrice;
	sellingPrice = newSellingPrice;
	quantity = newQuantity;
	modelNumber = newModelNumber;
	aboutProduct = newAboutProduct;
	productSpecification = newProductSpecification;
	technicalDetails = newTechnicalDetails;
	shippingWeight = newShippingWeight;
	productDimensions = newProductDimensions;
	image = newImage;
	variants = newVariants;
	SKU = newSKU;
	productURL = newProductURL;
	stock = newStock;
	productDetails = newProductDetails;
	dimensions = newDimensions;
	color = newColor;
	ingredients = newIngredients;
	directionToUse = newDirectionToUse;
	isAmazonSeller = newIsAmazonSeller;
	sizeQuantityVariant = newSizeQuantityVariant;
	productDescription = newProductDescription;
	this->fillEmptyFields();
}

// Checks every data member of a Product. If that member is an empty string, assigns it the value "NA"
void Product::fillEmptyFields() {
	if (uniqueID == "") {
		uniqueID = "NA";
	}
	if (productName == "") {
		productName = "NA";
	}
	if (brandName == "") {
		brandName = "NA";
	}
	if (Asin == "") {
		Asin = "NA";
	}
	if (category == "") {
		category = "NA";
	}
	if (upcEanCode == "") {
		upcEanCode = "NA";
	}
	if (listPrice == "") {
		listPrice = "NA";
	}
	if (sellingPrice == "") {
		sellingPrice = "NA";
	}
	if (quantity == "") {
		quantity = "NA";
	}
	if (modelNumber == "") {
		modelNumber = "NA";
	}
	if (aboutProduct == "") {
		aboutProduct = "NA";
	}
	if (productSpecification == "") {
		productSpecification = "NA";
	}
	if (technicalDetails == "") {
		technicalDetails = "NA";
	}
	if (shippingWeight == "") {
		shippingWeight = "NA";
	}
	if (productDimensions == "") {
		productDimensions = "NA";
	}
	if (image == "") {
		image = "NA";
	}
	if (variants == "") {
		variants = "NA";
	}
	if (SKU == "") {
		SKU = "NA";
	}
	if (productURL == "") {
		productURL = "NA";
	}
	if (stock == "") {
		stock = "NA";
	}
	if (productDetails == "") {
		productDetails = "NA";
	}
	if (dimensions == "") {
		dimensions = "NA";
	}
	if (color == "") {
		color = "NA";
	}
	if (ingredients == "") {
		ingredients = "NA";
	}
	if (directionToUse == "") {
		directionToUse = "NA";
	}
	if (isAmazonSeller == "") {
		isAmazonSeller = "NA";
	}
	if (sizeQuantityVariant == "") {
		sizeQuantityVariant = "NA";
	}
	if (productDescription == "") {
		productDescription = "NA";
	}
}

// Product destructor
Product::~Product() {

}

// Product copy constructor
Product::Product(Product& original) {
	uniqueID = original.getUniqueID();
	productName = original.getProductName();
	brandName = original.getBrandName();
	Asin = original.getAsin();
	category = original.getCategory();
	upcEanCode = original.getUpcEanCode();
	listPrice = original.getListPrice();
	sellingPrice = original.getSellingPrice();
	quantity = original.getQuantity();
	modelNumber = original.getModelNumber();
	aboutProduct = original.getAboutProduct();
	productSpecification = original.getProductSpecification();
	technicalDetails = original.getTechnicalDetails();
	shippingWeight = original.getShippingWeight();
	productDimensions = original.getProductDimensions();
	image = original.getImage();
	variants = original.getVariants();
	SKU = original.getSKU();
	productURL = original.getProductURL();
	stock = original.getStock();
	productDetails = original.getProductDetails();
	dimensions = original.getDimensions();
	color = original.getColor();
	ingredients = original.getIngredients();
	directionToUse = original.getDirectionsToUse();
	isAmazonSeller = original.getIsAmazonSeller();
	sizeQuantityVariant = original.getSizeQuantityVariant();
	productDescription = original.getProductDescription();
}

// Accessors
string Product::getUniqueID() const
{
	return uniqueID;
}

string Product::getProductName() const
{
	return productName;
}

string Product::getBrandName() const
{
	return brandName;
}

string Product::getAsin() const
{
	return Asin;
}

string Product::getCategory() const
{
	return category;
}

string Product::getUpcEanCode() const
{
	return upcEanCode;
}

string Product::getListPrice() const
{
	return listPrice;
}

string Product::getSellingPrice() const
{
	return sellingPrice;
}

string Product::getQuantity() const
{
	return quantity;
}

string Product::getModelNumber() const
{
	return modelNumber;
}

string Product::getAboutProduct() const
{
	return aboutProduct;
}

string Product::getProductSpecification() const
{
	return productSpecification;
}

string Product::getTechnicalDetails() const
{
	return technicalDetails;
}

string Product::getShippingWeight() const
{
	return shippingWeight;
}

string Product::getProductDimensions() const
{
	return productDimensions;
}

string Product::getImage() const
{
	return image;
}

string Product::getVariants() const
{
	return variants;
}

string Product::getSKU() const
{
	return SKU;
}

string Product::getProductURL() const
{
	return productURL;
}

string Product::getStock() const
{
	return stock;
}

string Product::getProductDetails() const
{
	return productDetails;
}

string Product::getDimensions() const
{
	return dimensions;
}

string Product::getColor() const
{
	return color;
}

string Product::getIngredients() const
{
	return ingredients;
}

string Product::getDirectionsToUse() const
{
	return directionToUse;
}

string Product::getIsAmazonSeller() const
{
	return isAmazonSeller;
}

string Product::getSizeQuantityVariant() const
{
	return sizeQuantityVariant;
}

string Product::getProductDescription() const
{
	return productDescription;
}

bool Product::hasCategory(const string& searchCategory)
{
	return category.find(searchCategory) != std::string::npos;
}

// Displays every data member of a Product to an output stream reference.
// Called by findByUniqueID()
void Product::displayProduct(ostream& out)
{
	out << "Unique ID: " << this->getUniqueID() << "\n";
	out << "Product Name: " << this->getProductName() << "\n";
	out << "Brand Name: " << this->getBrandName() << "\n";
	out << "Asin: " << this->getAsin() << "\n";
	out << "Category: " << this->getCategory() << "\n";
	out << "UPC EAN Code: " << this->getUpcEanCode() << "\n";
	out << "List Price: " << this->getListPrice() << "\n";
	out << "Selling Price: " << this->getSellingPrice() << "\n";
	out << "Quantity: " << this->getQuantity() << "\n";
	out << "Model Number: " << this->getModelNumber() << "\n";
	out << "About Product: " << this->getAboutProduct() << "\n";
	out << "Product Specification: " << this->getProductSpecification() << "\n";
	out << "Technical Details: " << this->getTechnicalDetails() << "\n";
	out << "Shipping Weight: " << this->getShippingWeight() << "\n";
	out << "Product Dimensions: " << this->getProductDimensions() << "\n";
	out << "Image: " << this->getImage() << "\n";
	out << "Variants: " << this->getVariants() << "\n";
	out << "SKU: " << this->getSKU() << "\n";
	out << "Product URL: " << this->getProductURL() << "\n";
	out << "Stock: " << this->getStock() << "\n";
	out << "Product Details: " << this->getProductDetails() << "\n";
	out << "Dimensions: " << this->getDimensions() << "\n";
	out << "Color: " << this->getColor() << "\n";
	out << "Ingredients: " << this->getIngredients() << "\n";
	out << "Direction to Use: " << this->getDirectionsToUse() << "\n";
	out << "Is Amazon Seller?: " << this->getIsAmazonSeller() << "\n";
	out << "Size Quantity Variant: " << this->getSizeQuantityVariant() << "\n";
	out << "Product Description: " << this->getProductDescription() << endl;
}

// Displays the Unique ID and Product Name of a Product to an output stream reference
// Called by listMatchingTargets()
void Product::displayIDandName(ostream& out) {
	out << "Unique ID: " << this->getUniqueID() << "\n";
	out << "Product Name: " << this->getProductName() << "\n" << endl;
}
