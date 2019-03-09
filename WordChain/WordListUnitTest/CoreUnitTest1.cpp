#include "stdafx.h"
#include "CppUnitTest.h"
#include "../WordChain/Core.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace CoreUnitTest
{
	TEST_CLASS(TEST)
	{
	public:

		Core *CORE;

		TEST_METHOD_INITIALIZE(initEnv)
		{
			CORE = new Core();
		}

		TEST_METHOD_CLEANUP(cleanWordList)
		{
			delete CORE;
			CORE = NULL;
		}

		TEST_METHOD(Test_1)
		{

		}

	};
}