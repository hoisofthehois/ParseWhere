#include "stdafx.h"
#include "CppUnitTest.h"

#include "Table.h"
#include "TableRow.h"


using namespace Microsoft::VisualStudio::CppUnitTestFramework;


struct ValueColumn : public ColumnDef<double>
{
	static constexpr const char szName[] = "VALUE";
};

struct CommentColumn : public ColumnDef<std::string>
{
	static constexpr const char szName[] = "DESCR";
};

struct OrderColumn : public ColumnDef<long>
{
	static constexpr const char szName[] = "ORDER";
};


namespace Testing
{		
	TEST_CLASS(TableTests)
	{
	public:
		
		TEST_METHOD(simple_table)
		{
			// Arrange
			Table<IDColumn, ValueColumn, CommentColumn> tab;
			TableRow<decltype(tab)> row;

			// Act
			row.setValue("ID", 12L);
			row.setValue("VALUE", 12.0);
			row.setValue("DESCR", "Twelve");
			auto id = row.getValue("ID");
			auto val = row.getValue("VALUE");
			auto descr = row.getValue("DESCR");

			// Assert
			Assert::AreEqual(12L, std::get<long>(id));
			Assert::AreEqual(12.0, std::get<double>(val));
			Assert::AreEqual("Twelve", std::get<std::string>(descr).c_str());
		}

		TEST_METHOD(duplicate_types)
		{
			// Arrange
			Table<IDColumn, OrderColumn, ValueColumn> tab;
			TableRow<decltype(tab)> row;

			// Act
			row.setValue<0>(12L);
			row.setValue<1>(13L);
			auto id = row.getValue("ID");
			auto order = row.getValue("ORDER");

			// Assert
			Assert::AreEqual(12L, std::get<0>(id));
			Assert::AreEqual(13L, std::get<1>(order));
		}

	};
}