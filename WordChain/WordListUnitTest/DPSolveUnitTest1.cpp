#include "stdafx.h"
#include "CppUnitTest.h"
#include "../WordChain/WordList.h"
#include "../WordChain/DPSolve.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace DPSolveUnitTest
{
	TEST_CLASS(TEST)
	{
	public:

		WordList *WORDLIST = NULL;
		DPSolve *dpSolve = NULL;


		TEST_METHOD_INITIALIZE(initEnv)
		{
			WORDLIST = new WordList();
		}

		TEST_METHOD_CLEANUP(cleanEnv)
		{
			delete WORDLIST;
			WORDLIST = NULL;
			if (dpSolve != NULL)
			{
				delete dpSolve;
				dpSolve = NULL;
			}
		}

		TEST_METHOD(TEST_TopoSort_1)
		{
			string str_list[] = {
				"aa", "abc" , "cbd", "ddd", "da"
			};
			for (int i = 0; i < 5; i++)
			{
				WORDLIST->parseString(str_list[i]);
			}
			dpSolve = new DPSolve(WORDLIST, 'w');
			Assert::AreEqual(false, dpSolve->topoSort());
		}

		TEST_METHOD(TEST_TopoSort_2)
		{
			string str_list[] = {
				"aa", "abc" , "cbd", "ddd", "db"
			};
			for (int i = 0; i < 5; i++)
			{
				WORDLIST->parseString(str_list[i]);
			}
			dpSolve = new DPSolve(WORDLIST, 'w');
			Assert::AreEqual(true, dpSolve->topoSort());
		}
	};
}