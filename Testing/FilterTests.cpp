#include "stdafx.h"
#include "CppUnitTest.h"

#include "Table.h"
#include "TableRow.h"
#include <tuple>


using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Testing
{		
	TEST_CLASS(FilterTests)
	{
	public:
		
		TEST_METHOD(equals)
		{
			// Arrange
			Table<int, long, float, double, std::string> tab;
			TableRow<decltype(tab)> row;

			// Act

			// Assert
		}

	};
}