#include "stdafx.h"
#include "CppUnitTest.h"
#include <Windows.h>
#include <string>
#include <vector>
#include <string.h>

typedef int(*genChainWord)(char* words[], int len, char*output[], char head, char tail, bool enable_loop);
typedef int(*genChainChar)(char* words[], int len, char*output[], char head, char tail, bool enable_loop);


using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;

namespace DllTest
{		
	HINSTANCE CoreDLL = LoadLibrary("CoreDll.dll");
	genChainWord gen_chain_word = (genChainWord)GetProcAddress(CoreDLL, "gen_chain_word");
	genChainChar gen_chain_char = (genChainChar)GetProcAddress(CoreDLL, "gen_chain_char");
	TEST_CLASS(UnitTest1)
	{
	public:
		TEST_METHOD_INITIALIZE(init)
		{
		}
		TEST_METHOD_CLEANUP(cleanUp)
		{
		}
		
		TEST_METHOD(Test_1)				// -w
		{
			char* words[] = {
				"ab",
				"accccccccccccccccccccc",
				"ad",
				"bc",
				"bd",
				"cd",
			};
			char* chain[100];
			char* ans[] = {
				"ab", "bc", "cd"
			};
			Assert::AreEqual(3, gen_chain_word(words, 6, chain, 0, 0, false));
			Assert::AreEqual(0, strcmp(chain[0], ans[0]));
			Assert::AreEqual(0, strcmp(chain[1], ans[1]));
			Assert::AreEqual(0, strcmp(chain[2], ans[2]));
		}

		TEST_METHOD(Test_2)				// -c
		{
			char* words[] = {
				"ab",
				"accccccccccccccccccccc",
				"ad",
				"bc",
				"bd",
				"cd",
			};
			char* chain[100];
			char* ans[] = {
				"accccccccccccccccccccc", "cd"
			};
			Assert::AreEqual(2, gen_chain_char(words, 6, chain, 0, 0, false));
			Assert::AreEqual(0, strcmp(chain[0], ans[0]));
			Assert::AreEqual(0, strcmp(chain[1], ans[1]));
		}

		TEST_METHOD(Test_3)				// -w -h
		{
			char* words[] = {
				"ab",
				"accccccccccccccccccccc",
				"ad",
				"bc",
				"bdddd",
				"cd",
			};
			char* chain[100];
			char* ans[] = {
				"bc", "cd"
			};
			Assert::AreEqual(2, gen_chain_word(words, 6, chain, 'b', 0, false));
			Assert::AreEqual(0, strcmp(chain[0], ans[0]));
			Assert::AreEqual(0, strcmp(chain[1], ans[1]));
		}

		TEST_METHOD(Test_4)				// -c -h
		{
			char* words[] = {
				"ab",
				"accccccccccccccccccccc",
				"ad",
				"bc",
				"bdddd",
				"cd",
				"dd",
			};
			char* chain[100];
			char* ans[] = {
				"bdddd", "dd"
			};
			Assert::AreEqual(2, gen_chain_char(words, 7, chain, 'b', 0, false));
			Assert::AreEqual(0, strcmp(chain[0], ans[0]));
			Assert::AreEqual(0, strcmp(chain[1], ans[1]));
		}

		TEST_METHOD(Test_5)				// -w -t
		{
			char* words[] = {
				"ab",
				"accccccccccccccccccccc",
				"ad",
				"bc",
				"bdddd",
				"cd",
			};
			char* chain[100];
			char* ans[] = {
				"ab", "bc"
			};
			Assert::AreEqual(2, gen_chain_word(words, 6, chain, 0, 'c', false));
			Assert::AreEqual(0, strcmp(chain[0], ans[0]));
			Assert::AreEqual(0, strcmp(chain[1], ans[1]));
		}

		TEST_METHOD(Test_6)				// -c -t
		{
			char* words[] = {
				"ab",
				"accccccccccccccccccccc",
				"ad",
				"bc",
				"bdddd",
				"cd",
				"cc"
			};
			char* chain[100];
			char* ans[] = {
				"accccccccccccccccccccc", "cc"
			};
			Assert::AreEqual(2, gen_chain_char(words, 7, chain, 0, 'c', false));
			Assert::AreEqual(0, strcmp(chain[0], ans[0]));
			Assert::AreEqual(0, strcmp(chain[1], ans[1]));
		}

		TEST_METHOD(Test_7)				// -w -h -t
		{
			char* words[] = {
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
			char* chain[100];
			char* ans[] = {
				"bc", "cd"
			};
			Assert::AreEqual(2, gen_chain_word(words, 10, chain, 'b', 'd', false));

			Assert::AreEqual(0, strcmp(chain[0], ans[0]));
			Assert::AreEqual(0, strcmp(chain[1], ans[1]));
		}

		TEST_METHOD(Test_8)				// -c -h -t
		{
			char* words[] = {
				"ab",
				"accccccccccccccccccccc",
				"ad",
				"ae",
				"bc",
				"bdddd",
				"be",
				"cd",
				"ce",
				"de",
				"dd",
			};
			char* chain[100];
			char* ans[] = {
				"bdddd", "dd"
			};
			Assert::AreEqual(2, gen_chain_char(words, 11, chain, 'b', 'd', false));
			Assert::AreEqual(0, strcmp(chain[0], ans[0]));
			Assert::AreEqual(0, strcmp(chain[1], ans[1]));
		}

		TEST_METHOD(Test_9)				// -w  but have ring
		{
			char* words[] = {
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
			char* chain[100];
			Assert::AreEqual(-4, gen_chain_word(words, 11, chain, 0, 0, false));
		}

		TEST_METHOD(Test_10)				// -c but have ring
		{
			char* words[] = {
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
			char* chain[100];
			Assert::AreEqual(-4, gen_chain_char(words, 11, chain, 0, 0, false));
		}

		TEST_METHOD(Test_11)				// -w have self
		{
			char* words[] = {
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
			char* chain[100];
			char* ans[] = {
				"ab", "bb", "bc", "cc", "cd", "dd", "de"
			};
			Assert::AreEqual(7, gen_chain_word(words, 13, chain, 0, 0, false));
			Assert::AreEqual(0, strcmp(chain[0], ans[0]));
			Assert::AreEqual(0, strcmp(chain[1], ans[1]));
			Assert::AreEqual(0, strcmp(chain[2], ans[2]));
			Assert::AreEqual(0, strcmp(chain[3], ans[3]));
			Assert::AreEqual(0, strcmp(chain[4], ans[4]));
			Assert::AreEqual(0, strcmp(chain[5], ans[5]));
			Assert::AreEqual(0, strcmp(chain[6], ans[6]));
		}

		TEST_METHOD(Test_12) {				// -c have self
			char* words[] = {
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
			char* chain[100];
			char* ans[] = {
				"accccccccccccccccccccc", "cc", "cd", "dd", "de"
			};
			Assert::AreEqual(5, gen_chain_char(words, 13, chain, 0, 0, false));
			Assert::AreEqual(0, strcmp(chain[0], ans[0]));
			Assert::AreEqual(0, strcmp(chain[1], ans[1]));
			Assert::AreEqual(0, strcmp(chain[2], ans[2]));
			Assert::AreEqual(0, strcmp(chain[3], ans[3]));
			Assert::AreEqual(0, strcmp(chain[4], ans[4]));
		}

		TEST_METHOD(Test_13)				// -w -r
		{
			char* words[] = {
				"ab", "aaaaabbbbbccccc", "aaaaaddddd",
				"bc",
				"cb", "cd",
			};
			char* chain[100];
			char* ans[] = {
				"aaaaabbbbbccccc", "cb", "bc", "cd"
			};
			Assert::AreEqual(4, gen_chain_word(words, 6, chain, 0, 0, true));
			Assert::AreEqual(0, strcmp(chain[0], ans[0]));
			Assert::AreEqual(0, strcmp(chain[1], ans[1]));
			Assert::AreEqual(0, strcmp(chain[2], ans[2]));
			Assert::AreEqual(0, strcmp(chain[3], ans[3]));
		}

		TEST_METHOD(Test_14) {				// -c -r
			char* words[] = {
				"ab", "aaaccc", "aaaaabbbbbcccccddddd",
				"bc",
				"cb", "cd",
				"dd",
			};
			char* ans[] = {
				"aaaaabbbbbcccccddddd", "dd"
			};
			char* chain[100];
			Assert::AreEqual(2, gen_chain_char(words, 7, chain, 0, 0, true));
			Assert::AreEqual(0, strcmp(chain[0], ans[0]));
			Assert::AreEqual(0, strcmp(chain[1], ans[1]));
		}

		TEST_METHOD(Test_15) {				// -w -r -h -t
			char* words[] = {
				"ab",
				"bccccccccccccccccccccccccccc", "bd",
				"cd",
				"da", "dc",
			};
			char* ans[] = {
				"bd", "dc", "cd", "da"
			};
			char* chain[100];
			Assert::AreEqual(4, gen_chain_word(words, 6, chain, 'b', 'a', true));
			Assert::AreEqual(0, strcmp(chain[0], ans[0]));
			Assert::AreEqual(0, strcmp(chain[1], ans[1]));
			Assert::AreEqual(0, strcmp(chain[2], ans[2]));
			Assert::AreEqual(0, strcmp(chain[3], ans[3]));
		}

		TEST_METHOD(Test_16) {				// -c -r -h
			char* words[] = {
				"ab",
				"bccccccccccccccccccccccccccc", "bd",
				"cd",
				"da", "dc",
			};
			char* ans[] = {
				"bccccccccccccccccccccccccccc","cd", "da"
			};
			char* chain[100];
			Assert::AreEqual(3, gen_chain_char(words, 6, chain, 'b', 'a', true));
			Assert::AreEqual(0, strcmp(chain[0], ans[0]));
			Assert::AreEqual(0, strcmp(chain[1], ans[1]));
			Assert::AreEqual(0, strcmp(chain[2], ans[2]));
		}

	};

	TEST_CLASS(ExceptionTest1)
	{
	public:
		TEST_METHOD(Test_1)
		{
			char* words[] = {
				NULL,
				NULL,
				"ad",
				"bc",
				"bd",
				"cd",
			};
			char* chain[100];
			Assert::AreEqual(-3, gen_chain_word(words, 6, chain, 0, 0, false));
		}

		TEST_METHOD(Test_2)
		{
			char* words[] = {
				"ab",
				"accccccccccccccccccccc",
				"ad",
				"bc",
				"bd",
				"cd",
			};
			char* chain[100];
			Assert::AreEqual(-1, gen_chain_word(words, 6, chain, '-', 0, false));
		}

		TEST_METHOD(Test_3)
		{
			char* words[] = {
				"ab",
				"accccccccccccccccccccc",
				"ad",
				"bc",
				"bd",
				"cd",
			};
			char* chain[100];
			Assert::AreEqual(-2, gen_chain_word(words, 6, chain, 0, '-', false));
		}

		TEST_METHOD(Test_4)
		{
			char* words[] = {
				"ab",
				"accccccccccccccccccccc",
				"ad",
			};
			char* chain[100];
			Assert::AreEqual(-5, gen_chain_word(words, 3, chain, 0, 0, false));
		}

		TEST_METHOD(Test_6)
		{
			char* words[] = {
				"ab",
				"accccccccccccccccccccc",
				"ad",
			};
			char* chain[100];
			Assert::AreEqual(-5, gen_chain_word(words, 3, chain, 0, 0, false));
		}
	};
}