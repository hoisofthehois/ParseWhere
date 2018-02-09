#pragma once

#include <string>
#include <tuple>

template <typename TTab>
class TableRow
{
	friend TTab;

protected:

	typename TTab::row_t m_data;

public:

	typename TTab::cell_t getValue(const std::string& strField) const;
	void setValue(const std::string& strField, const typename TTab::cell_t& vtVal);

};

template <typename TTab>
typename TTab::cell_t TableRow<TTab>::getValue(const std::string& strField) const
{
	return TTab::cell_t(m_data.get<0>());
}

template <typename TTab>
void TableRow<TTab>::setValue(const std::string& strField, const typename TTab::cell_t& vtVal)
{

}