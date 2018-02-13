#include "stdafx.h"
#include "CppUnitTest.h"

#include "TableDef.h"
#include "TableRow.h"
#include "Table.h"


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
			using table_t = TableDef<IDColumn, ValueColumn, CommentColumn>;
			TableRow<table_t> row;

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
			using table_t = TableDef<IDColumn, OrderColumn, ValueColumn>;
			TableRow<table_t> row;

			// Act
			row.setValue<0>(12L);
			row.setValue<1>(13L);

			// Assert
			Assert::AreEqual(12L, row.getValue<0>());
			Assert::AreEqual(13L, row.getValue<1>());
		}

		TEST_METHOD(append_row)
		{
			// Arrange
			Table<IDColumn, OrderColumn, ValueColumn, CommentColumn> tab;

			// Act
			auto&& row = tab.Append(12L, 13L, 12.0, "Twelve");

			// Assert
			Assert::AreEqual(12L, row.getValue<0>());
			Assert::AreEqual(13L, row.getValue<1>());
			Assert::AreEqual(12.0, std::get<double>(row.getValue("VALUE")));
			Assert::AreEqual("Twelve", std::get<std::string>(row.getValue("DESCR")).c_str());
		}

		TEST_METHOD(iterate)
		{
			// Arrange
			Table<IDColumn, ValueColumn, CommentColumn> tab;
			std::vector<ValueColumn::col_t> vecExpected{1.0, -3.0, 12.0, 22.2};
			std::vector<ValueColumn::col_t> vecResult;
			auto k = 0U;
			for (auto&& dVal : vecExpected)
				tab.emplace_back(++k, dVal, std::to_string(dVal));

			// Act
			for (auto&& row : tab)
			{
				auto vtVal = row.getValue("VALUE");
				vecResult.push_back(std::get<double>(vtVal));
			}

			// Assert
			Assert::IsTrue(vecExpected == vecResult);

		}

	};
}