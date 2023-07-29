#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <fstream>

using namespace std;

class Product
{
	string title;
	int price;
public:
	Product(string title, int price)
		: title{ title }, price{ price } {}
	string& Title() { return title; }
	int& Price() { return price; }
};


class ProductStore
{
	vector<Product> products;
public:
	vector<Product>& Products(){ return products; }

	void Process()
	{
		string title;
		int price;
		// input product:
		cout << "Input title: ";
		cin >> title;
		cout << "Input price: ";
		cin >> price;

		// validate
		if (price < 0)
		{
			cout << "incorrect price!\n";
			return;
		}

		// add in vector
		products.push_back(Product(title, price));
		cout << "product add to store\n";

		// save to file:

	}
};

class IProductReader
{
public:
	virtual string* GetData() = 0;
};

class ConsoleProductReader : public IProductReader
{
public:
	string* GetData() override
	{
		string* data = new string[2];
		cout << "Input title: ";
		cin >> data[0];
		cout << "Input price: ";
		cin >> data[1];
		return data;
	}
};

class IProductCreate
{
public:
	virtual Product GetProduct(string* data) = 0;
};

class SimpleProductCreate : public IProductCreate
{
public:
	Product GetProduct(string* data) override
	{
		int price;
		try
		{
			price = stoi(data[1]);
		}
		catch (exception e)
		{
			cout << e.what() << "\n";
			throw e;
		}
		return Product(data[0], price);
	}
};

class IProductValidate
{
public:
	virtual bool IsValid(Product product) = 0;
};

class PriceProductValidate : public IProductValidate
{
public:
	bool IsValid(Product product) override
	{
		return product.Price() >= 0;
	}
};

class IProductSave
{
public:
	virtual void Save(Product product, string name) = 0;
};

class FileProductSave : public IProductSave
{
public:
	void Save(Product product, string name) override
	{
		fstream file;
		file.open(name, ios::app);
		file << "Product title: " << product.Title() << "\n";
		file << "Product price: " << product.Price() << "\n";
		file << string(20, '-') << "\n";
		file.close();
	}
};

class ProductStoreGood
{
	vector<Product> products;
	
	IProductReader* reader;
public:
	IProductReader*& Reader() { return reader; }

	IProductCreate* Creator;
	IProductValidate* Validator;
	IProductSave* Saver;

	vector<Product>& Products() { return products; }

	ProductStoreGood(IProductReader* reader,
		IProductCreate* creator,
		IProductValidate* validator,
		IProductSave* saver)
		: reader{ reader },
		Creator{ creator },
		Validator{ validator },
		Saver{ saver }{}

	void Process()
	{
		string* data = new string[2];
		data = Reader()->GetData();
		Product product = Creator->GetProduct(data);

		if (Validator->IsValid(product))
		{
			products.push_back(product);
			Saver->Save(product, "products.store");
		}
		else
			cout << "product not add\n";
	}
};
