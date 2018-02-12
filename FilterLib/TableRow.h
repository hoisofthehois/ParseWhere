#pragma once

#include <string>
#include <utility>

template <typename TTab>
class TableRow
{
	friend TTab;

protected:

	typename TTab::row_t m_data;

public:

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

};

