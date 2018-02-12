#pragma once

#include <array>
#include <variant>
#include <tuple>
#include <string>
#include <exception>


template <typename T>
struct ColumnDef
{
	typedef T col_t;

};

struct IDColumn : public ColumnDef<long>
{
	static constexpr const char szName[] = "ID";
};


template <typename... TCols>
class TableDef
{

public:

	static constexpr size_t NumColumns = sizeof...(TCols);

	typedef std::variant<typename TCols::col_t...> cell_t;
	typedef std::array<cell_t, NumColumns> row_t;
	typedef std::tuple<typename TCols::col_t...> types;

	static constexpr const std::array<const char*, NumColumns> arr_names = {TCols::szName...};

	static size_t getColumnNumber(const std::string& strColName)
	{
		auto iCol = std::find_if(arr_names.cbegin(), arr_names.cend(),
			[&strColName](const char* szColName) { return std::string(szColName) == strColName; });
		if (iCol != arr_names.cend())
			return iCol - arr_names.cbegin();
		else
		{
			auto strMsg = "Column " + strColName + " not found.";
			throw std::invalid_argument(strMsg.c_str());
		}
	}



};