#pragma once
#include <iostream>
#include <vector>

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

