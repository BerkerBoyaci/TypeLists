
#include <iostream>
#include <string>
#include <vector>
#include <ranges>
#include <type_traits>
#include "typelists.h"

int main()
{
	static_assert( std::is_same_v<transformer<int, double>::output_types,typelist<int const, double const>>);

	static_assert(length_t<typelist<int, double, char>>::value == 3);
	static_assert(length_v<typelist<int, double, char>> == 3);
	static_assert(length_v<typelist<int, double>> == 2);
	static_assert(length_v<typelist<int>> == 1);
	std::cout << length_v<typelist<int>> << "\n";

	static_assert(std::is_same_v<back_t<typelist<>>, empty_type>);
	static_assert(std::is_same_v<back_t<typelist<int>>, int>);
	static_assert(std::is_same_v<back_t<typelist<int, double, char>>,char>);
	

	static_assert(std::is_same_v<at_t<0, typelist<>>, empty_type>);
	static_assert(std::is_same_v<at_t<0, typelist<int>>, int>);
	static_assert(std::is_same_v<at_t<0, typelist<int, char>>, int>);
	static_assert(std::is_same_v<at_t<1, typelist<>>, empty_type>);
	static_assert(std::is_same_v<at_t<1, typelist<int>>, empty_type>);
	static_assert(std::is_same_v<at_t<1, typelist<int, char>>, char>);
	static_assert(std::is_same_v<at_t<2, typelist<>>, empty_type>);
	static_assert(std::is_same_v<at_t<2, typelist<int>>, empty_type>);
	static_assert(std::is_same_v<at_t<2, typelist<int, char>>,empty_type>);

	static_assert(std::is_same_v<pop_back_t<typelist<>>,typelist<>>);
	static_assert(std::is_same_v<pop_back_t<typelist<double>>,typelist<>>);
	static_assert(std::is_same_v<pop_back_t<typelist<double, char>>,typelist<double>>);
	static_assert(std::is_same_v<pop_back_t<typelist<double, char, int>>,typelist<double, char>>);
	
	return 0;
}