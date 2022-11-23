/*
Author: F.Stapenhorst
Using STL algorithms with STL containers efficiently
Pleasae try to use STL algorythms to solve those tasks
*/

#include <string>
#include <iostream>
#include <vector>
#include <memory>
#include <algorithm>
#include <type_traits>
#include <ranges>
#include <filesystem>
#include <functional>

#pragma region HelperStuff

template<class T>
void Print(T item) noexcept
{
	std::cout << item; // << std::endl;
	if (std::is_integral<T>::value)
		std::cout << ' ';
}

template<class T>
void PrintVector(std::vector<T> v)
{
	for_each(std::begin(v), std::end(v), Print<T>);
	std::cout << std::endl;
}

struct Exercise
{
	Exercise(std::string name) : Name{ name }
	{
		std::cout << "" << Name << "" << std::endl << "-----------" << std::endl << std::endl;
	}
	virtual ~Exercise()
	{
		std::cout << std::endl  << "------------------" << std::endl << std::endl;
	}

	std::string Name;
};

#pragma endregion


void Exercise1()
{
	// Exercise 1: Copy all element from v1 to the end of v2
	Exercise t("Exercise 1");
	std::vector<int> v1 = { 1,2,3,4,5,6,7,8 };
	std::vector<int> v2 = { 10,11,12,13,14,15,16,17,18,19 };

	//Implementation here

	PrintVector(v2);
}

void Exercise2()
{
	// Exercise 2: Copy all elements from v1 that are greater than 5 to the end of v2
	Exercise t("Exercise 2");

	std::vector<int> v1 = { 1,2,3,4,5,6,7,8,9 };
	std::vector<int> v2 = { 10,11,12,13,14,15,16,17,18,19 };

	//Implementation here

	PrintVector(v2);
}

void Exercise3()
{
	// Exercise 3: Move all elements from v1 to the end of v2
	Exercise t("Exercise 3");

	std::vector<int> v1 = { 1,2,3,4,5,6,7,8,9 };
	std::vector<int> v2 = { 10,11,12,13,14,15,16,17,18,19 };

	//Implementation here

	PrintVector(v1);
	PrintVector(v2);
}

void Exercise4()
{
	// Exercise 4: Copy all element from v1 in reverse order to the end of v2
	Exercise t("Exercise 4");

	std::vector<int> v1 = { 1,2,3,4,5,6,7,8,9 };
	std::vector<int> v2 = { 10,11,12,13,14,15,16,17,18,19 };

	//Implementation here

	PrintVector(v1);
	PrintVector(v2);
}

void Exercise5()
{
	// Exercise 5: Copy the first 5 elements of v1 to the position after position 3 of the same vector v1,
	//         so that{ 1,2,3,4,5,6,7,8,9 } will become{ 1,2,3,1,2,3,4,5,9 }

	Exercise t("Exercise 5");
	std::vector<int> v1 = { 1,2,3,4,5,6,7,8,9 };

	//Implementation here

	PrintVector(v1);
}

void Exercise6()
{
	// Exercise 6: Increment each number in v1 by 1 so that v1 becomes { 2,3,4,5,6,7,8,9,10 }
	Exercise t("Exercise 6");
	std::vector<int> v1 = { 1,2,3,4,5,6,7,8,9 };

	//Implementation here

	PrintVector(v1);
}

void Exercise7()
{
	// Exercise 7: Count how many elements in the v1 are even numbers - even though we already know the answer :)
	Exercise t("Exercise 7");
	std::vector<int> v1 = { 1,2,3,4,5,6,7,8,9 };

	//Implementation here
}

void Exercise8()
{
	//Exercise 8: Calculate the items of v1 that are not in v2 and put those items into a new vector v3
	Exercise t("Exercise 8");
	std::vector<int> v1 = { 1,2,3,4,5,6,7,8,9 };
	std::vector<int> v2 = { 4,5,6,7,8,9,10,11,12 };

	//Implementation here
	std::vector<int> v3;

	PrintVector(v3);
}

// +++++++++++++++++++  Advanced  +++++++++++++++++++

void Exercise9()
{
	// Exercise 9:
	// See this vector: std::vector<int> v1 = {2,3,1,4,5,6,7,8,18,16,20,9,11,12,13,15,22};
	//
	// Reorder the elemnts in v1 so that all uneven elements in the range from 1 through 8
	// are moved to the end of that range, and all uneven elements in the range from 9 to the end
	// are moved to the top of that range. Keep the relative order of the elemnts preserved.
	// Before		After
	// 2			2
	// 3  <-		4
	// 1  <-		6
	// 4			8
	// 5  <-		3  <-
	// 6			1  <-
	// 7  <-		5  <-
	// 8			7  <-
	// -----		-----
	// 18			9  <-
	// 16			11 <-
	// 20			13 <-
	// 9  <-		15 <-
	// 11 <-		18
	// 12			16
	// 13 <-		20
	// 15 <-		12
	// 22			22
	Exercise t("Exercise 9");
	std::vector<int> v1 = { 2,3,1,4,5,6,7,8,18,16,20,9,11,12,13,15,22 };

	PrintVector(v1);
}

#pragma region Exercise10

class Product
{
public:
	Product() noexcept = default;
	Product(std::string const name, int const price, bool const freeDelivery) noexcept
		: Name{ name }, Price{ price }, FreeDelivery{ freeDelivery } {}

	[[nodiscard]] bool operator<(const Product& other) const noexcept
	{
		return (Name < other.Name);
	}

	[[nodiscard]] bool operator==(const Product& other) const noexcept
	{
		return (Name == other.Name);
	}

	friend std::ostream& operator<<(std::ostream& os, const Product& dt);
	std::string Name;
	int Price = 0;
	bool FreeDelivery = false;
};

std::ostream& operator<<(std::ostream& os, const Product& product)
{
	os << "Name:" << product.Name << '\t' << " Price:" << product.Price << '\t' << "Shipping:" << (product.FreeDelivery ? "free" : "not free") << std::endl;
	return os;
}

void Exercise10()
{
	//Exercise 10: See sub tasks below
	Exercise t("Exercise 10");
	//The list of existing products
	std::vector<Product> products;
	products.emplace_back(Product{ "P1", 10, true });
	products.emplace_back(Product{ "P5", 5, false });
	products.emplace_back(Product{ "P6", 2, true });
	products.emplace_back(Product{ "P3", 23, false });
	products.emplace_back(Product{ "P4", 69, true });
	products.emplace_back(Product{ "P7", 11, true });
	products.emplace_back(Product{ "P2", 44, false });

	//Exercise 10a: Sort the product list by price

	PrintVector(products);

	//Exercise 10b: Put all elements that are free shipping at the top of the list without breaking the ordering by price

	PrintVector(products);

	//Tast 10c: Find all products that are free shipping and cost less than 20$ and put them in the vector FreeUnder20
	std::vector<Product> FreeUnder20;
	int const MaxPrice = 20;

	PrintVector(FreeUnder20);
}
#pragma endregion


int main()
{
	Exercise1();
	Exercise2();
	Exercise3();
	Exercise4();
	Exercise5();
	Exercise6();
	Exercise7();
	Exercise8();
	Exercise9();
	Exercise10();
}