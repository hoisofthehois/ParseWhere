#pragma once

#include <vector>
#include <utility>

#include "TableDef.h"
#include "TableRow.h"

template <typename... TCols>
class Table : private TableDef<TCols...>
{

private:

	std::vector<TableRow<TableDef<TCols...>>> m_vecRows;

public:

	using row_t = TableRow<TableDef<TCols...>>;

	template <typename... TVal>
	row_t& Append(TVal... tpValues)
	{
		m_vecRows.emplace_back(std::forward<TVal>(tpValues)...);
		return m_vecRows.back();
	}

};