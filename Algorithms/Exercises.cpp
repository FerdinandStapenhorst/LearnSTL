/*
Author: Ferdinand Stapenhorst 2022
// https://github.com/FerdinandStapenhorst/LearnSTL
Using STL algorithms with STL containers efficiently
Pleasae try to use STL algorythms and other STL features to solve the below exercises
*/

#include "pch.h" //used for precompiled headers

using namespace std;

#pragma region HelperStuff

namespace my {
	//Printable concept
	template<typename T>
	concept Printable = requires(ostream & os, T & p)
	{
		os << p;		//nee an << operator
		{os << p} -> same_as<ostream&>; //Return of operator << must be an ostream
		p.Print(os);	//need a print methor
	};

	//Our enhanced Regular Type concept
	template<class T>
	concept ExtendedRegularType = regular<T> and totally_ordered<T>; //Our extended regular type adds totally_ordered to the requirement

	//Product type.
	class Product
	{
	public:
		Product() noexcept = default;
		Product(const Product& other) noexcept
			: _Name{ other._Name }, _Price{ other._Price }, _FreeDelivery{ other._FreeDelivery } {}
		Product(string const name, double const price, bool const freeDelivery) noexcept
			: _Name{ name }, _Price{ price }, _FreeDelivery{ freeDelivery } {}

		//These operators are needed for totally_ordering and equality_comparable
		auto operator<=>(const Product& other) const noexcept = default;
		bool operator==(Product const& other) const noexcept = default;

		//Printing a product
		void Print(ostream& os) const
		{
			os << format("Name:{}\t Price:{}\t Shipping:{}\n", _Name, _Price, (_FreeDelivery ? "free" : "not free"));
		}

		string Name() const {
			return _Name;
		}
		double Price() const
		{
			return _Price;
		}
		bool FreeDelivery() const
		{
			return _FreeDelivery;
		}

	private:
		friend ostream& operator<<(ostream& os, const Product& product);
		string _Name{};
		double _Price{ 0 };
		bool _FreeDelivery{ false };
	};

	static_assert(ExtendedRegularType<Product>); //Make sure Product is am (extended) Regular Type (about Regular Type see https://abseil.io/blog/20180531-regular-types)
	static_assert(my::Printable<Product>); //make sure Product is models the Printable concept

	//Print function for a product
	ostream& operator<<(ostream& os, const Product& product)
	{
		product.Print(os);
		return os;
	}

	//Concept for numerics
	template <typename T>
	concept IsNumeric = integral<T> or floating_point<T>;

	//Bool concept
	template <typename T>
	concept IsBool = common_with<T, bool>;

	//Combinde PrintableItem concept
	template<typename T>
	concept PrintableItem = IsNumeric<T> or common_with<T, string> or is_same_v<remove_cv_t<T>, Product>;

	//Print formatted string
	template<typename... Args>
	void PrintF(const string_view fmt_str, Args&&... args) {
		auto fmt_args{ make_format_args(args...) };
		string outstr{ vformat(fmt_str, fmt_args) };
		fputs(outstr.c_str(), stdout);
	}

	//Print single item
	template<PrintableItem T>
	void PrintItem(T item) noexcept
	{
		if constexpr (IsNumeric<T>) //Numerics and bools are separated by a space
		{
			if constexpr (IsBool<T>)
				cout << boolalpha;
			cout << item;
			cout << ' ';
			cout << noboolalpha;
		}
		else
		{
			//Everything else is just sent to cout
			cout << item;
		}
	}

	//Print vertically two vectors
	void PrintTable(vector<string> v1, vector<string> v2)
	{
		for (int i = 0; i < v1.size(); i++)
		{
			cout << v1.at(i) << "\t" << v2.at(i) << endl;
		}
	}

	//printing single items, views and all STL containers
	template <typename T>
	void Print(T item) {
		if constexpr (ranges::input_range<T>)
		{
			using ValueType = ranges::range_value_t<decltype(item)>;
			for_each(begin(item), end(item), PrintItem<ValueType>);
		}
		else
		{
			using ValueType = decltype(item);
			PrintItem<ValueType>(item);
		}
	}

	//Used to print the current exercise to cout
	struct PrintExerciseName
	{
		PrintExerciseName(string name) : Name{ name }
		{
			cout << "" << Name << "" << endl << endl;
		}
		virtual ~PrintExerciseName()
		{
			cout << endl << "------------------" << endl << endl;
		}

		string Name;
	};
}
#pragma endregion

namespace ContainerAlgorithm {
	void Exercise1()
	{
		// Copy all element from v1 to the end of v2
		my::PrintExerciseName t{ "ContainerAlgorithm:Exercise 1" };
		vector v1{ 1,2,3,4,5,6,7,8 };
		vector v2{ 10,11,12,13,14,15,16,17,18,19 };

		//Implementation here

		my::Print(v2);
	}

	void Exercise2()
	{
		// Copy all elements from v1 that are greater than 5 to the end of v2
		my::PrintExerciseName t{ "ContainerAlgorithm:Exercise 2" };

		vector v1{ 3,1,2,6,7,8,5,7,9 };
		vector v2{ 10,11,12,13,14,15,16,17,18,19 };

		//Implementation here

		my::Print(v2);
	}

	void Exercise3()
	{
		// Move all elements from v1 to the end of v2
		my::PrintExerciseName t{ "ContainerAlgorithm:Exercise 3" };

		vector v1{ 1,2,3,4,5,6,7,8,9 };
		vector v2{ 10,11,12,13,14,15,16,17,18,19 };

		//Implementation here
		move(begin(v1), end(v1), back_inserter(v2));
		v1.clear();
		my::Print(v1);
		my::Print(v2);
	}

	void Exercise4()
	{
		// Copy all elements from v1 in reverse order to the end of v2
		my::PrintExerciseName t{ "ContainerAlgorithm:Exercise 4" };

		vector v1{ 1,2,3,4,5,6,7,8,9 };
		vector v2{ 10,11,12,13,14,15,16,17,18,19 };

		//Implementation here

		my::Print(v1);
		my::Print(v2);
	}

	void Exercise5()
	{
		// Copy the first 5 elements of v1 to the position after position 3 of the same vector v1,
		//             so that{ 1,2,3,4,5,6,7,8,9 } will become{ 1,2,3,1,2,3,4,5,9 }

		my::PrintExerciseName t{ "ContainerAlgorithm:Exercise 5" };
		vector v1{ 1,2,3,4,5,6,7,8,9 };

		//Implementation here

		my::Print(v1);
	}

	void Exercise6()
	{
		// Increment each number in v1 by 1 so that v1 becomes { 2,3,4,5,6,7,8,9,10 }
		my::PrintExerciseName t{ "ContainerAlgorithm:Exercise 6" };
		vector v1{ 1,2,3,4,5,6,7,8,9 };

		//Implementation here

		my::Print(v1);
	}

	void Exercise7()
	{
		// Count how many elements in v1 are even numbers
		my::PrintExerciseName t{ "ContainerAlgorithm:Exercise 7" };
		vector v1{ 1,2,3,4,5,6,7,8,9 };

		//Implementation here
	}

	void Exercise8()
	{
		//Calculate the items of v1 that are not in v2 and put those items into a new vector v3
		my::PrintExerciseName t{ "ContainerAlgorithm:Exercise 8" };
		vector v1{ 1,2,3,4,5,6,7,8,9 };
		vector v2{ 4,5,6,7,8,9,10,11,12 };

		//Implementation here
		vector<int> v3;

		my::Print(v3);
	}

	void Exercise9()
	{
		//Create a vector v containing the numbers from 10 to 100
		my::PrintExerciseName t{ "ContainerAlgorithm:Exercise 9" };

		//Implementation here

		//my::Print(v);
	}

	void Exercise10()
	{
		//Change the elements in the vector v to reverse order
		my::PrintExerciseName t{ "ContainerAlgorithm:Exercise 10" };
		vector v{ 1,2,3,4,5,6,7,8,9 };
		//Implementation here

		my::Print(v);
	}

	void Exercise11()
	{
		//See this list v of elements in a vector: { "-", "-", "-", "-" ,"-", "-", "-", "-", "#", "#", "#", "#" ,"-", "-", "-", "-" }
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

		my::PrintExerciseName t{ "ContainerAlgorithm:Exercise 11" };
		vector<string> v{ "-", "-", "-", "-" ,"-", "-", "-", "-", "#", "#", "#", "#" ,"-", "-", "-", "-" };
		int const sizeOfRange{ 4 };  //The number of consecutive selected items in the range (the # elements)
		int const beginOfRange{ 9 }; //The starting point of the original range
		int const endOfRange{ beginOfRange + sizeOfRange - 1 }; //The end of the range

		my::Print("Original " + to_string(beginOfRange) + ":\t");
		my::Print(v);

		vector newBeginOfRangeList{ 15, 3, 0 }; //three new starting points of the range
		for (auto& newBeginOfRange : newBeginOfRangeList)
		{
			//Re-init the vector
			v = { "-", "-", "-", "-" ,"-", "-", "-", "-", "#", "#", "#", "#" ,"-", "-", "-", "-" };
			my::Print("Starting at " + to_string(newBeginOfRange) + ":\t");

			//Implement here

			my::Print(v);
		}
	}

	void Exercise12()
	{
		// See this vector: vector<string> v {"-2","#3","#1","-4","#5","-6","#7","-8","-18","-16","-20","#9","#11","-12","#13","#15","-22"};
		//
		// Reorder the elemnts in v1 so that all selected elements (the # elements) in the range from 1 through 8
		// are moved to the end of that range, and all selected elements in the range from 9 to the end
		// are moved to the top of that range. Keep the relative order of the elemnts preserved.
		// Before		After
		// -2			-2
		// -3			-4
		// #1  <-		-6
		// -4			-8
		// #5  <-		#3  <-
		// -6			#1  <-
		// #7  <-		#5  <-
		// -8			#7  <-
		// -----		-----
		// -18			#9  <-
		// -16			#11 <-
		// -20			#13 <-
		// #9  <-		#15 <-
		// #11 <-		-18
		// -12			-16
		// #13 <-		-20
		// #15 <-		-12
		// -22			-22
		my::PrintExerciseName t{ "ContainerAlgorithm:Exercise 12" };
		vector<string> shouldBe{ "-2","-4","-6","-8","#3","#1","#5","#7","#9","#11","#13","#15","-18","-16","-20","-12","-22" };
		vector<string> v{ "-2","#3","#1","-4","#5","-6","#7","-8","-18","-16","-20","#9","#11","-12","#13","#15","-22" };

		//Implement here

		my::PrintTable(shouldBe, v);
	}

	void Exercise13()
	{
		//See sub tasks below
		my::PrintExerciseName t{ "ContainerAlgorithm:Exercise 13" };

		//The list of existing products
		vector<my::Product> products;
		products.emplace_back(my::Product{ "P1", 10, true });
		products.emplace_back(my::Product{ "P5", 5, false });
		products.emplace_back(my::Product{ "P6", 2, true });
		products.emplace_back(my::Product{ "P3", 23, false });
		products.emplace_back(my::Product{ "P4", 69, true });
		products.emplace_back(my::Product{ "P7", 11, true });
		products.emplace_back(my::Product{ "P2", 44, false });

		//Exercise 10a: Sort the product list by price

		my::Print(products);

		//Exercise 10b: Put all elements that are free shipping at the top of the list without breaking the ordering by price

		my::Print(products);

		//Tast 10c: Find all products that are free shipping and cost less than 20$ and copy them to the vector FreeUnder20
		vector<my::Product> FreeUnder20;
		int const MaxPrice{ 20 };

		my::Print(FreeUnder20);
	}

	void Exercise14()
	{
		//Remove all uneven numbers from the vector v so that the size of the vector shrinks accordingly
		my::PrintExerciseName t{ "ContainerAlgorithm:Exercise 14" };
		vector v{ 1,2,3,4,5,6,7,8,9,10,11,12,13,14 };

		my::Print(v);
	}

	void Exercise15()
	{
		//Add the element newItem into the vector while keeping the vector ordered.
		//Do not use a static insert position but calculate the position where the new item should be inserted
		my::PrintExerciseName t{ "ContainerAlgorithm:Exercise 15" };
		using Vstr = vector<string>;
		Vstr v{ "A","B","C","D","F","G","H" };
		string newItem{ "E" };

		my::Print(v);
		assert(ranges::is_sorted(v));
	}

	void Exercise16()
	{
		my::PrintExerciseName t{ "ContainerAlgorithm:Exercise 16" };

		// Check out this programming challenge: https://www.hackerrank.com/contests/hourrank-31/challenges/hanging-posters/problem
		// See the solution below and try to find at least one solution that uses STL algorithm(s)

		int h = 6;
		vector wallPoints{ 22,33,19,74 };
		vector lengths{ 2,3,5,6 };

		int accumulator = 0;
		for (int i = 0; i < wallPoints.size(); ++i)
			accumulator = max(accumulator, wallPoints[i] - lengths[i] / 4);
		auto result = max(0, accumulator - h);

		//Implement your solution here
	}
	
	void Exercise17()
	{
		my::PrintExerciseName t{ "ContainerAlgorithm:Exercise 17" };

		//See sorted vector v below.
		//Write a generic algorithm called adjacent_count that returns the number of adjacent elements being equal in a sorted sequence
		//The result for our vector v here would be: 4  (2,2 - 5,5 - 7,7 - 24,24)
		vector v{ 0,1,2,2,3,4,5,5,6,7,7,24,24,33,46 };
		
		//Implement your solution here.
		//Example call would be:
		//auto result = adjacent_count(begin(v), end(v));
	}
}

namespace STLRanges
{
	namespace views = ranges::views;

	void Exercise1()
	{
		my::PrintExerciseName t{ "STLViews:Exercise 1" };
		vector v{ 1,2,3,4,5,6,7,8,9 };

		//Use views to solve the following exercises.

		//Example: create a view of all elements in v:
		auto view = v | views::all;
		my::Print(view);

		//1): create a view1 of the first 5 elements of v in reverse order.

		//my::Print(view1);

		//2): create a view2 that filters out all uneven numbers out of v.

		//my::Print(view2);

		//3): create a view3 that calculates the square of all even numbers in v.

		//my::Print(view3);
	}
}

namespace Misc {
	void Exercise1()
	{
		//Assuming int x = -1 and unsigned y = 1: write code of the comparison between both
		my::PrintExerciseName t{ "Misc:Exercise 1" };
		int x{ -1 };
		unsigned y{ 1 };
		bool b{ false };

		//implement here, like:
		// b = comparison( x , y );

		//Compare equal

		my::Print(b);

		//Compare not-equal

		my::Print(b);

		//compare  x is less than y

		my::Print(b);

		//compare x is less or equal to y

		my::Print(b);

		//compare x is greater than y

		my::Print(b);

		//compare x is greater or equal than y

		my::Print(b);
	}

	void Exercise2()
	{
		//See the following class Fraction. It represents a Fraction type that stores the denominator and divider.
		//Implement the operator overloads so that the comparisons below prints correctly (uncomment to verify your code).
		//Try to implement as less operator overloads as possible.

		my::PrintExerciseName t{ "Misc:Exercise 2" };

		class Fraction {
		public:
			Fraction() = default;
			Fraction(const Fraction& other) noexcept = default;
			Fraction(int denominator, int divisor) : Denominator{ denominator }, Divisor{ divisor } {}

			//Implement the following comparison operators, so that they return the correct values
			auto operator<=>(const Fraction& rhs) const noexcept = default;
			bool operator==(const Fraction& rhs) const noexcept = default;

		private:

			long Denominator{ 0 };
			long Divisor{ 1 };
		};

		Fraction a{ 10, 15 };
		Fraction b{ 2, 3 };
		Fraction c{ 5, 3 };

		Fraction d{ 1, 3 };
		Fraction e{ 2, 6 };

		Fraction f{ 1, 5 };
		Fraction g{ 2, 10 };

		//Un-comment the following to check your results
		return;

		my::PrintF("a < c  should be true and is: {}\n", (a < c)); assert((a < c));
		my::PrintF("a > c  should be false and is: {}\n", (a > c)); assert(!(a > c));
		my::PrintF("c < a  should be false and is: {}\n", (c < a)); assert(!(c < a));
		my::PrintF("a == b should be true and is: {}\n", (a == b)); assert((a == b));
		my::PrintF("a != b should be false and is: {}\n", (a != b)); assert(!(a != b));
		my::PrintF("a <= b should be true and is: {}\n", (a <= b)); assert((a <= b));
		my::PrintF("a <= c should be true and is: {}\n", (a <= c)); assert((a <= c));
		my::PrintF("a >= c should be false and is: {}\n", (a >= c)); assert(!(a >= c));
		my::PrintF("c >= a should be true and is: {}\n", (c >= a)); assert((c >= a));
		my::PrintF("c <= a should be false and is: {}\n", (c <= a)); assert(!(c <= a));
		my::PrintF("a != c should be true and is: {}\n", (a != c)); assert((a != c));
		my::PrintF("d == e should be true and is: {}\n", (d == e)); assert((d == e));
		my::PrintF("f == g should be true and is: {}\n", (f == g)); assert((f == g));

		assert(my::ExtendedRegularType<Fraction>);  //Uncomment to check if the Fraction is an extended Regular Type
	}

	//See the template function signature below. Write a binary search in the body of that function which returns an iterator
	//pointing to the first element in the range [first, last) that satisfies element >= value,
	//or last if no such element is found. The range[first, last) must be a sorted range.

	template <forward_iterator ForwardIterator, typename ValueType>
	ForwardIterator BinarySearch(ForwardIterator first, const ForwardIterator last, const ValueType& value) {
		//Implement here

		return first;
	}

	void Exercise3()
	{
		my::PrintExerciseName t{ "Misc:Exercise 3" };
		//Implement the binary search above
		vector v{ 1,2,3,4,5,6,7,8,9,10 };
		auto pos = BinarySearch(begin(v), end(v), 5);
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
		Exercise16();
		Exercise17();
	}

	{  //Misc stuff
		using namespace Misc;
		Exercise1();
		Exercise2();
		Exercise3();
	}

	{
		//views
		using namespace STLRanges;
		Exercise1();
	}
}