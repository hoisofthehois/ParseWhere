#pragma once

#include <vector>
#include <utility>

#include "TableDef.h"
#include "TableRow.h"

template <typename... TCols>
class Table : private TableDef<TCols...>
{

private:

	using tableRow_t = typename TableRow<TableDef<TCols...>>;

	std::vector<tableRow_t> m_vecRows;

	template <size_t N>
	constexpr tableRow_t fillRow(const TableDef<TCols...>::types& tpValues)
	{
		auto row = fillRow<N - 1>(tpValues);
		row.setValue<N-1>(std::get<N-1>(tpValues));
		return row;
	}

	template <>
	constexpr tableRow_t fillRow<0U>(const TableDef<TCols...>::types& tpValues)
	{
		tableRow_t row;
		row.setValue<0>(std::get<0>(tpValues));
		return row;
	}

public:

	template <
		typename... TVal,
		typename TRow = std::enable_if_t<(sizeof...(TVal) == NumColumns), TableRow<TableDef<TCols...>>>
	>
	constexpr TRow& Append(TVal... tpValues)
	{
		m_vecRows.emplace_back(fillRow<NumColumns>(std::tie(tpValues...)));
		return m_vecRows.back();
	}

};