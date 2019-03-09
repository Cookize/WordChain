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

		TEST_METHOD(Test_1)				// -w
		{
			string words[] = {
				"ab",
				"accccccccccccccccccccc",
				"ad",
				"bc",
				"bd",
				"cd",
			};
			string ans[] = {
				"ab", "bc", "cd"
			};
			vector<string> *lines = new vector<string>();
			vector<string> *chain = new vector<string>();
			for(int i = 0; i < 6; i++)
			{
				lines->push_back(words[i]);
			}
			Assert::AreEqual(true, CORE->gen_chain_word(*lines, *chain, 0, 0, false));
			Assert::AreEqual(size_t(3), chain->size());
			Assert::AreEqual(ans[0], (*chain)[0]);
			Assert::AreEqual(ans[1], (*chain)[1]);
			Assert::AreEqual(ans[2], (*chain)[2]);
			delete lines;
			delete chain;
		}

		TEST_METHOD(Test_2)				// -c
		{
			string words[] = {
				"ab",
				"accccccccccccccccccccc",
				"ad",
				"bc",
				"bd",
				"cd",
			};
			string ans[] = {
				"accccccccccccccccccccc", "cd"
			};
			vector<string> *lines = new vector<string>();
			vector<string> *chain = new vector<string>();
			for (int i = 0; i < 6; i++)
			{
				lines->push_back(words[i]);
			}
			Assert::AreEqual(true, CORE->gen_chain_char(*lines, *chain, 0, 0, false));
			Assert::AreEqual(size_t(2), chain->size());
			Assert::AreEqual(ans[0], (*chain)[0]);
			Assert::AreEqual(ans[1], (*chain)[1]);
			delete lines;
			delete chain;
		}

		TEST_METHOD(Test_3)				// -w -h
		{
			string words[] = {
				"ab",
				"accccccccccccccccccccc",
				"ad",
				"bc",
				"bdddd",
				"cd",
			};
			string ans[] = {
				"bc", "cd"
			};
			vector<string> *lines = new vector<string>();
			vector<string> *chain = new vector<string>();
			for (int i = 0; i < 6; i++)
			{
				lines->push_back(words[i]);
			}
			Assert::AreEqual(true, CORE->gen_chain_word(*lines, *chain, 'b', 0, false));
			Assert::AreEqual(size_t(2), chain->size());
			Assert::AreEqual(ans[0], (*chain)[0]);
			Assert::AreEqual(ans[1], (*chain)[1]);
			delete lines;
			delete chain;
		}

		TEST_METHOD(Test_4)				// -c -h
		{
			string words[] = {
				"ab",
				"accccccccccccccccccccc",
				"ad",
				"bc",
				"bdddd",
				"cd",
			};
			string ans[] = {
				"bdddd"
			};
			vector<string> *lines = new vector<string>();
			vector<string> *chain = new vector<string>();
			for (int i = 0; i < 6; i++)
			{
				lines->push_back(words[i]);
			}
			Assert::AreEqual(true, CORE->gen_chain_char(*lines, *chain, 'b', 0, false));
			Assert::AreEqual(size_t(1), chain->size());
			Assert::AreEqual(ans[0], (*chain)[0]);
			delete lines;
			delete chain;
		}

		TEST_METHOD(Test_5)				// -w -t
		{
			string words[] = {
				"ab",
				"accccccccccccccccccccc",
				"ad",
				"bc",
				"bdddd",
				"cd",
			};
			string ans[] = {
				"ab", "bc"
			};
			vector<string> *lines = new vector<string>();
			vector<string> *chain = new vector<string>();
			for (int i = 0; i < 6; i++)
			{
				lines->push_back(words[i]);
			}
			Assert::AreEqual(true, CORE->gen_chain_word(*lines, *chain, 0, 'c', false));
			Assert::AreEqual(size_t(2), chain->size());
			Assert::AreEqual(ans[0], (*chain)[0]);
			Assert::AreEqual(ans[1], (*chain)[1]);
			delete lines;
			delete chain;
		}

		TEST_METHOD(Test_6)				// -c -t
		{
			string words[] = {
				"ab",
				"accccccccccccccccccccc",
				"ad",
				"bc",
				"bdddd",
				"cd",
			};
			string ans[] = {
				"accccccccccccccccccccc"
			};
			vector<string> *lines = new vector<string>();
			vector<string> *chain = new vector<string>();
			for (int i = 0; i < 6; i++)
			{
				lines->push_back(words[i]);
			}
			Assert::AreEqual(true, CORE->gen_chain_char(*lines, *chain, 0, 'c', false));
			Assert::AreEqual(size_t(1), chain->size());
			Assert::AreEqual(ans[0], (*chain)[0]);
			delete lines;
			delete chain;
		}
	};
}