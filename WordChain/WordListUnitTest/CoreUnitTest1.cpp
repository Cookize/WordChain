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

		TEST_METHOD(Test_7)				// -w -h -t
		{
			string words[] = {
				"ab",
				"accccccccccccccccccccc",
				"ad",
				"ae",
				"bc",
				"bdddd",
				"be",
				"cd",
				"ce",
				"de"
			};
			string ans[] = {
				"bc", "cd"
			};
			vector<string> *lines = new vector<string>();
			vector<string> *chain = new vector<string>();
			for (int i = 0; i < 10; i++)
			{
				lines->push_back(words[i]);
			}
			Assert::AreEqual(true, CORE->gen_chain_word(*lines, *chain, 'b', 'd', false));
			Assert::AreEqual(size_t(2), chain->size());
			Assert::AreEqual(ans[0], (*chain)[0]);
			Assert::AreEqual(ans[1], (*chain)[1]);
			delete lines;
			delete chain;
		}

		TEST_METHOD(Test_8)				// -c -h -t
		{
			string words[] = {
				"ab",
				"accccccccccccccccccccc",
				"ad",
				"ae",
				"bc",
				"bdddd",
				"be",
				"cd",
				"ce",
				"de"
			};
			string ans[] = {
				"bdddd"
			};
			vector<string> *lines = new vector<string>();
			vector<string> *chain = new vector<string>();
			for (int i = 0; i < 10; i++)
			{
				lines->push_back(words[i]);
			}
			Assert::AreEqual(true, CORE->gen_chain_char(*lines, *chain, 'b', 'd', false));
			Assert::AreEqual(size_t(1), chain->size());
			Assert::AreEqual(ans[0], (*chain)[0]);
			delete lines;
			delete chain;
		}

		TEST_METHOD(Test_9)				// -w  but have ring
		{
			string words[] = {
				"ab",
				"accccccccccccccccccccc",
				"ad",
				"ae",
				"bc",
				"bdddd",
				"db",
				"be",
				"cd",
				"ce",
				"de"
			};
			vector<string> *lines = new vector<string>();
			vector<string> *chain = new vector<string>();
			for (int i = 0; i < 11; i++)
			{
				lines->push_back(words[i]);
			}
			Assert::AreEqual(false, CORE->gen_chain_word(*lines, *chain, 0, 0, false));
			delete lines;
			delete chain;
		}

		TEST_METHOD(Test_10)				// -c but have ring
		{
			string words[] = {
				"ab",
				"accccccccccccccccccccc",
				"ad",
				"ae",
				"bc",
				"bdddd",
				"db",
				"be",
				"cd",
				"ce",
				"de"
			};
			vector<string> *lines = new vector<string>();
			vector<string> *chain = new vector<string>();
			for (int i = 0; i < 11; i++)
			{
				lines->push_back(words[i]);
			}
			Assert::AreEqual(false, CORE->gen_chain_char(*lines, *chain, 0, 0, false));
			delete lines;
			delete chain;
		}

		TEST_METHOD(Test_11)				// -w have self
		{
			string words[] = {
				"ab",
				"accccccccccccccccccccc",
				"ad",
				"ae",
				"bb",
				"bc",
				"bdddd",
				"be",
				"cc",
				"cd",
				"ce",
				"dd",
				"de"
			};
			string ans[] = {
				"ab", "bb", "bc", "cc", "cd", "dd", "de"
			};
			vector<string> *lines = new vector<string>();
			vector<string> *chain = new vector<string>();
			for (int i = 0; i < 13; i++)
			{
				lines->push_back(words[i]);
			}
			Assert::AreEqual(true, CORE->gen_chain_word(*lines, *chain, 0, 0, false));
			Assert::AreEqual(size_t(7), chain->size());
			Assert::AreEqual(ans[0], (*chain)[0]);
			Assert::AreEqual(ans[1], (*chain)[1]);
			Assert::AreEqual(ans[2], (*chain)[2]);
			Assert::AreEqual(ans[3], (*chain)[3]);
			Assert::AreEqual(ans[4], (*chain)[4]);
			Assert::AreEqual(ans[5], (*chain)[5]);
			Assert::AreEqual(ans[6], (*chain)[6]);
			delete lines;
			delete chain;
		}

		TEST_METHOD(Test_12){				// -c have self
			string words[] = {
				"ab",
				"accccccccccccccccccccc",
				"ad",
				"ae",
				"bb",
				"bc",
				"bdddd",
				"be",
				"cc",
				"cd",
				"ce",
				"dd",
				"de"
			};
			string ans[] = {
				"accccccccccccccccccccc", "cc", "cd", "dd", "de"
			};
			vector<string> *lines = new vector<string>();
			vector<string> *chain = new vector<string>();
			for (int i = 0; i < 13; i++)
			{
				lines->push_back(words[i]);
			}
			Assert::AreEqual(true, CORE->gen_chain_char(*lines, *chain, 0, 0, false));
			Assert::AreEqual(size_t(5), chain->size());
			Assert::AreEqual(ans[0], (*chain)[0]);
			Assert::AreEqual(ans[1], (*chain)[1]);
			Assert::AreEqual(ans[2], (*chain)[2]);
			Assert::AreEqual(ans[3], (*chain)[3]);
			Assert::AreEqual(ans[4], (*chain)[4]);
			delete lines;
			delete chain;
		}

		TEST_METHOD(Test_13)				// -w -r
		{
			string words[] = {
				"ab", "aaaaabbbbbccccc", "aaaaaddddd",
				"bc",
				"cb", "cd",
				"da",
			};
			string ans[] = {
				"aaaaabbbbbccccc", "cb", "bc", "cd", "da"
			};
			vector<string> *lines = new vector<string>();
			vector<string> *chain = new vector<string>();
			for (int i = 0; i < 7; i++)
			{
				lines->push_back(words[i]);
			}
			Assert::AreEqual(true, CORE->gen_chain_word(*lines, *chain, 0, 0, true));
			Assert::AreEqual(size_t(5), chain->size());
			Assert::AreEqual(ans[0], (*chain)[0]);
			Assert::AreEqual(ans[1], (*chain)[1]);
			Assert::AreEqual(ans[2], (*chain)[2]);
			Assert::AreEqual(ans[3], (*chain)[3]);
			Assert::AreEqual(ans[4], (*chain)[4]);
			delete lines;
			delete chain;
		}

		TEST_METHOD(Test_14) {				// -c -r
			string words[] = {
				"ab", "aaaccc", "aaaaaddddd",
				"bc",
				"cb", "cd",
				"da",
			};
			string ans[] = {
				"aaaaaddddd", "da"
			};
			vector<string> *lines = new vector<string>();
			vector<string> *chain = new vector<string>();
			for (int i = 0; i < 7; i++)
			{
				lines->push_back(words[i]);
			}
			Assert::AreEqual(true, CORE->gen_chain_char(*lines, *chain, 0, 0, true));
			Assert::AreEqual(size_t(2), chain->size());
			Assert::AreEqual(ans[0], (*chain)[0]);
			Assert::AreEqual(ans[1], (*chain)[1]);
			delete lines;
			delete chain;
		}



	};
}