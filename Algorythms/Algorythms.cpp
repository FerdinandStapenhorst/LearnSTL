/*
Author: Ferdinand Stapenhorst 2022
// https://github.com/FerdinandStapenhorst/LearnSTL
Using STL algorithms with STL containers efficiently
Pleasae try to use STL algorythms to solve the below exercises
*/

#include "pch.h" //used for precompiled headers

#pragma region HelperStuff

//Printable concept
template<typename T>
concept Printable = requires(std::ostream & os, T & p)
{
	os << p;		//nee an << operator
	{os << p} -> std::same_as<std::ostream&>; //Return of operator << must be an std::ostream
	p.Print(os);	//need a print methor
};

//Our enhanced Regular Type concept
template<class T>
concept RegularType = std::regular<T> and std::totally_ordered<T>;

//Product type.
class Product
{
public:
	Product() noexcept = default;
	Product(const Product& other) noexcept
		: _Name{ other._Name }, _Price{ other._Price }, _FreeDelivery{ other._FreeDelivery } {}
	Product(std::string const name, int const price, bool const freeDelivery) noexcept
		: _Name{ name }, _Price{ price }, _FreeDelivery{ freeDelivery } {}

	[[nodiscard]] auto operator<=>(const Product& other) const noexcept
	{
		return (_Name <=> other._Name);
	}

	[[nodiscard]] bool operator==(Product const& other) const noexcept
	{
		return (_Name == other._Name);
	}

	void Print(std::ostream& os) const
	{
		os << std::format("Name:{}\t Price:{}\t Shipping:{}\n", _Name, _Price, (_FreeDelivery ? "free" : "not free"));
	}

	std::string Name() const {
		return _Name;
	}
	int Price() const
	{
		return _Price;
	}
	bool FreeDelivery() const
	{
		return _FreeDelivery;
	}

private:
	friend std::ostream& operator<<(std::ostream& os, const Product& product);
	std::string _Name{};
	int _Price{ 0 };
	bool _FreeDelivery{ false };
};

static_assert(RegularType<Product>); //Make sure Product is a Regular Type
static_assert(Printable<Product>);    //make sure Product is models the Printable concept

//Print function for a product
std::ostream& operator<<(std::ostream& os, const Product& product)
{
	product.Print(os);
	return os;
}

//Concept for numerics
template <typename T>
concept IsNumeric = std::integral<T> or std::floating_point<T>;

//Bool concept
template <typename T>
concept IsBool = std::common_with<T, bool>;

//Combinde PrintableItem concept
template<typename T>
concept PrintableItem = IsNumeric<T> or std::common_with<T, std::string> or std::is_same_v<std::remove_cv_t<T>, Product>;

//Print single item
template<PrintableItem T>
void PrintItem(T item) noexcept
{
	if constexpr (IsNumeric<T>) //Numerics and bools are separated by a space
	{
		if constexpr (IsBool<T>)
			std::cout << std::boolalpha;
		std::cout << item;
		std::cout << ' ';
		std::cout << std::noboolalpha;
	}
	else
	{
		//Everything else is just sent to cout
		std::cout << item;
	}
}

//printing views and all STL containers
void Print(std::ranges::range auto& item)
{
	using ValueType = decltype(std::remove_reference_t<decltype(item)>)::value_type;
	std::for_each(std::cbegin(item), std::cend(item), PrintItem<ValueType>);
	std::cout << std::endl;
}

//Used to print the current exercise to cout
struct ExerciseStart
{
	ExerciseStart(std::string name) : Name{ name }
	{
		std::cout << "" << Name << "" << std::endl << std::endl;
	}
	virtual ~ExerciseStart()
	{
		std::cout << std::endl << "------------------" << std::endl << std::endl;
	}

	std::string Name;
};

#pragma endregion

namespace ContainerAlgorithm {
	void Exercise1()
	{
		// Copy all element from v1 to the end of v2
		ExerciseStart t{ "ContainerAlgorithm:Exercise 1" };
		std::vector<int> v1{ 1,2,3,4,5,6,7,8 };
		std::vector<int> v2{ 10,11,12,13,14,15,16,17,18,19 };

		//Implementation here
		Print(v2);
	}

	void Exercise2()
	{
		// Copy all elements from v1 that are greater than 5 to the end of v2
		ExerciseStart t{ "ContainerAlgorithm:Exercise 2" };

		std::vector<int> v1{ 3,1,2,6,7,8,5,7,9 };
		std::vector<int> v2{ 10,11,12,13,14,15,16,17,18,19 };

		//Implementation here

		Print(v2);
	}

	void Exercise3()
	{
		// Move all elements from v1 to the end of v2
		ExerciseStart t{ "ContainerAlgorithm:Exercise 3" };

		std::vector<int> v1{ 1,2,3,4,5,6,7,8,9 };
		std::vector<int> v2{ 10,11,12,13,14,15,16,17,18,19 };

		//Implementation here

		Print(v1);
		Print(v2);
	}

	void Exercise4()
	{
		// Copy all element from v1 in reverse order to the end of v2
		ExerciseStart t{ "ContainerAlgorithm:Exercise 4" };

		std::vector<int> v1{ 1,2,3,4,5,6,7,8,9 };
		std::vector<int> v2{ 10,11,12,13,14,15,16,17,18,19 };

		//Implementation here

		Print(v1);
		Print(v2);
	}

	void Exercise5()
	{
		// Copy the first 5 elements of v1 to the position after position 3 of the same vector v1,
		//             so that{ 1,2,3,4,5,6,7,8,9 } will become{ 1,2,3,1,2,3,4,5,9 }

		ExerciseStart t{ "ContainerAlgorithm:Exercise 5" };
		std::vector<int> v1{ 1,2,3,4,5,6,7,8,9 };

		//Implementation here

		Print(v1);
	}

	void Exercise6()
	{
		// Increment each number in v1 by 1 so that v1 becomes { 2,3,4,5,6,7,8,9,10 }
		ExerciseStart t{ "ContainerAlgorithm:Exercise 6" };
		std::vector<int> v1{ 1,2,3,4,5,6,7,8,9 };

		//Implementation here

		Print(v1);
	}

	void Exercise7()
	{
		// Count how many elements in the v1 are even numbers
		ExerciseStart t{ "ContainerAlgorithm:Exercise 7" };
		std::vector<int> v1{ 1,2,3,4,5,6,7,8,9 };

		//Implementation here
	}

	void Exercise8()
	{
		//Calculate the items of v1 that are not in v2 and put those items into a new vector v3
		ExerciseStart t{ "ContainerAlgorithm:Exercise 8" };
		std::vector<int> v1{ 1,2,3,4,5,6,7,8,9 };
		std::vector<int> v2{ 4,5,6,7,8,9,10,11,12 };

		//Implementation here
		std::vector<int> v3;

		Print(v3);
	}

	void Exercise9()
	{
		//Create a vector<int> v containing the numbers from 10 to 100
		ExerciseStart t{ "ContainerAlgorithm:Exercise 9" };

		//Implementation here

		//Print(v);
	}

	void Exercise10()
	{
		//Change the elements in the vector v to reverse order
		ExerciseStart t{ "ContainerAlgorithm:Exercise 10" };
		std::vector<int> v{ 1,2,3,4,5,6,7,8,9 };
		//Implementation here

		Print(v);
	}

	void Exercise11()
	{
		//Please see this list v of elements in a vector: { "-", "-", "-", "-" ,"-", "-", "-", "-", "#", "#", "#", "#" ,"-", "-", "-", "-" }
		//The list has a size of 16 elements. Four of these elements are consecutively selected - marked with the #-character.
		//The exercise is to move these four elements forwards and backwards within the list v as follows:
		//	- move towards the end to position 15
		//	  Outcome: -----------####-
		//	- move towards the start to position 3
		//	  Outcome: ---####---------
		//	- move to the beginning of the list (= position 0)
		//	  Outcome: ####------------
		//The loop below prepares the list of elements and sets the variable 'newBeginOfRange' to each value 15, 3 and 0.
		//Please implement your solution in the body of the loop below.

		ExerciseStart t{ "ContainerAlgorithm:Exercise 11" };
		std::vector<std::string> v{ "-", "-", "-", "-" ,"-", "-", "-", "-", "#", "#", "#", "#" ,"-", "-", "-", "-" };
		int const sizeOfRange{ 4 };  //The number of consecutive selected items in the range (the # elements)
		int const beginOfRange{ 9 }; //The starting point of the original range
		int const endOfRange{ beginOfRange + sizeOfRange - 1 }; //The end of the range

		PrintItem("Original " + std::to_string(beginOfRange) + ":\t");
		Print(v);

		std::vector<int> newBeginOfRangeList{ 15, 3, 0 }; //three new starting points of the range
		for (auto& newBeginOfRange : newBeginOfRangeList)
		{
			//Re-init the vector
			v = { "-", "-", "-", "-" ,"-", "-", "-", "-", "#", "#", "#", "#" ,"-", "-", "-", "-" };
			PrintItem("Starting at " + std::to_string(newBeginOfRange) + ":\t");

			//Implement here

			Print(v);
		}
	}

	void Exercise12()
	{
		// See this vector: std::vector<int> v1 {2,3,1,4,5,6,7,8,18,16,20,9,11,12,13,15,22};
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
		ExerciseStart t{ "ContainerAlgorithm:Exercise 12" };
		std::vector<int> v1{ 2,3,1,4,5,6,7,8,18,16,20,9,11,12,13,15,22 };

		Print(v1);
	}

	void Exercise13()
	{
		//See sub tasks below
		ExerciseStart t{ "ContainerAlgorithm:Exercise 13" };

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

		Print(products);

		//Exercise 10b: Put all elements that are free shipping at the top of the list without breaking the ordering by price

		Print(products);

		//Tast 10c: Find all products that are free shipping and cost less than 20$ and copy them to the vector FreeUnder20
		std::vector<Product> FreeUnder20;
		int const MaxPrice{ 20 };

		Print(FreeUnder20);
	}

	void Exercise14()
	{
		//Remove all uneven numbers in the vector v so that the size of the vector shrinks accordingly
		ExerciseStart t{ "ContainerAlgorithm:Exercise 14" };
		std::vector<int> v{ 1,2,3,4,5,6,7,8,9,10,11,12,13,14 };

		Print(v);
	}

	void Exercise15()
	{
		//Add the new element into the vector while keeping the vector ordered.
		ExerciseStart t{ "ContainerAlgorithm:Exercise 15" };
		using Vstr = std::vector<std::string>;
		Vstr v{ "A","B","D","F","H" };
		std::string newItem{ "E" };

		Print(v);
		assert(std::ranges::is_sorted(v));
	}
}

namespace Misc {
	void Exercise1()
	{
		//Assuming int x = -1 and unsigned y = 1: write code of the comparison between both
		ExerciseStart t{ "Misc:Exercise 1" };
		int x{ -1 };
		unsigned y{ 1 };
		bool b{ false };

		//implement here, like:
		// b = comparison of x and y;

		////Compare equal

		PrintItem(b);

		////Compare not-equal

		PrintItem(b);

		////compare  x is less than y

		PrintItem(b);

		////compare x is less or equal to y

		PrintItem(b);

		////compare x is greater than y

		PrintItem(b);

		////compare x is greater or equal than y

		PrintItem(b);
	}

	void Exercise2()
	{
		//See the following struct. It represents a Fraction type that stores the denominator and divider.
		//Implement the operator overloads so that the comparisons below prints correctly (uncomment to verify your code).
		//Try to implement as less operator overloads as possible.

		ExerciseStart t{ "Misc:Exercise 2" };

		struct Frac {
			Frac(int denominator, int divisor) : Denominator{ denominator }, Divisor{ divisor } {}

			//Implement comparison operators here

			long Denominator;
			long Divisor;
		};

		Frac a{ 10, 15 };
		Frac b{ 2, 3 };
		Frac c{ 5, 3 };

		//Un-comment the following block to chek your results
		/*
		PrintF("a < c  should be true and is: {}\n", (a < c));
		PrintF("c > a  should be true and is: {}\n", (c > a));
		PrintF("a == b should be true and is: {}\n", (a == b));
		PrintF("a != b should be false and is: {}\n", (a != b));
		PrintF("a <= b should be true and is: {}\n", (a <= b));
		PrintF("a <= c should be true and is: {}\n", (a <= c));
		PrintF("c >= a should be true and is: {}\n", (c >= a));
		PrintF("a != c should be true and is: {}\n", (a != c));
		*/
	}
}

namespace STLRanges
{
	namespace views = std::ranges::views;

	void Exercise1()
	{
		//Use views to solve the following exercises.
		//Example: create a view of all elements in v.
		// auto view1 = v | views::all;

		ExerciseStart t{ "STLViews:Exercise 1" };

		std::vector<int> v{ 1,2,3,4,5,6,7,8,9 };

		//1): create a view of the first 5 elements of v in reverse order.

		//Print<int>(view1);

		//2): create a view that filters out all uneven numbers out of v.

		//Print<int>(view2);

		//3): create a view that calculates the square of all even numbers in v.

		//Print<int>(view3);
	}
}

int main()
{
	{ //Container stuff
		using namespace ContainerAlgorithm;
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
		Exercise11();
		Exercise12();
		Exercise13();
		Exercise14();
		Exercise15();
	}

	{  //Misc stuff
		using namespace Misc;
		Exercise1();
		Exercise2();
	}

	{
		//views
		using namespace STLRanges;
		Exercise1();
	}
}