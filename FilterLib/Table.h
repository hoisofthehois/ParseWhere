#pragma once

#include <vector>
#include <utility>

#include "TableDef.h"
#include "TableRow.h"

template <typename... TCols>
class Table : private TableDef<TCols...>
{

public:

	using tableRow_t = typename TableRow<TableDef<TCols...>>;
	typedef typename std::vector<tableRow_t>::iterator iterator;
	typedef typename std::vector<tableRow_t>::const_iterator const_iterator;
	typedef typename std::vector<tableRow_t>::allocator_type allocator_type;
	typedef typename tableRow_t value_type;
	typedef typename tableRow_t& reference;
	typedef typename const tableRow_t& const_reference;
	typedef typename std::vector<tableRow_t>::difference_type difference_type;
	typedef typename size_t size_type;

private:

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
		typename TRow = std::enable_if_t<(sizeof...(TVal) == NumColumns), tableRow_t>
	>
	TRow& Append(TVal&&... tpValues)
	{
		m_vecRows.emplace_back(fillRow<NumColumns>(std::tie(tpValues...)));
		return m_vecRows.back();
	}

	template<class ...Args>
	void emplace_back(Args&&... args) { Append(std::forward<Args>(args)...); }

	iterator begin() { return m_vecRows.begin(); }
	const_iterator begin() const { return m_vecRows.begin(); }
	const_iterator cbegin() const { return m_vecRows.cbegin(); }
	iterator end() { return m_vecRows.end(); }
	const_iterator end() const { return m_vecRows.cend(); }
	const_iterator cend() const { return m_vecRows.cend(); }

	reference front() { return m_vecRows.front(); }
	const_reference front() const { return m_vecRows.front(); }
	reference back() { return m_vecRows.back(); }
	const_reference back() const { return m_vecRows.back(); }
	reference operator[](size_type k) { return m_vecRows[k]; }
	const_reference operator[](size_type k) const { return m_vecRows[k]; }
	reference at(size_type k) { return m_vecRows.at(k); }
	const_reference at(size_type) const { return m_vecRows.at(k); }

	size_type size() const { return m_vecRows.size(); }
	size_type max_size() const { return m_vecRows.max_size(); }
	bool empty() const { return m_vecRows.empty(); }

	TableDef<TCols...>::cell_t operator()(size_t nRow, const std::string& strCol) const
	{
		auto&& row = m_vecRows.at(nRow);
		return row.getValue(strCol);
	}

};