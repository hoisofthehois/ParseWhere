#pragma once

#include <tuple>
#include <variant>

template <typename... TCols>
class Table
{

public:

	typedef std::tuple<TCols...> row_t;
	typedef std::variant<TCols...> cell_t;

};