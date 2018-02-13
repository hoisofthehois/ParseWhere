#pragma once

#include <string>
#include <utility>

template <typename TTab>
class TableRow
{

protected:

	typename TTab::row_t m_data;


public:

	constexpr TableRow() : m_data() {}

	using cell_t = typename TTab::cell_t;

	cell_t getValue(const std::string& strColName) const
	{
		auto nCol = TTab::getColumnNumber(strColName);
		return m_data[nCol];
	}

	void setValue(const std::string& strColName, cell_t vtVal)
	{
		auto nCol = TTab::getColumnNumber(strColName);
		m_data[nCol] = std::move(vtVal);
	}

	template<size_t Col>
	constexpr std::enable_if_t< (Col < TTab::NumColumns), std::tuple_element_t<Col, typename TTab::types> > getValue()
	{
		return std::get<Col>(m_data[Col]);
	}

	template<size_t Col>
	constexpr void setValue(std::enable_if_t< (Col < TTab::NumColumns), std::tuple_element_t<Col, typename TTab::types> > val)
	{
		m_data[Col] = TTab::cell_t{std::in_place_index<Col>, std::move(val)};
	}

};

