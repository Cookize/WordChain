#include "stdafx.h"
#include "CppUnitTest.h"
#include "../WordChain/WordList.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace WordListUnitTest
{		
	TEST_CLASS(TEST)
	{
	public:
		
		WordList *WORDLIST;

		TEST_METHOD_INITIALIZE(initWordList)
		{
			WORDLIST = new WordList();
		}

		TEST_METHOD_CLEANUP(cleanWordList)
		{
			delete WORDLIST;
			WORDLIST = NULL;
		}

		TEST_METHOD(TestMethod_1)
		{
			string str("");
			WORDLIST->parseString(str);
			char h('a');
			char t('a');
			while(h <= 'z')
			{
				while (t <= 'z')
				{
					Assert::AreEqual(0, WORDLIST->getWordSumAt(h, t));
					Assert::AreEqual(0, WORDLIST->getWordRemainingAt(h, t));
					t++;
				}
				h++;
			}
		}

		TEST_METHOD(TestMethod_2)
		{
			string str("1234567890-=_+[]{}\\|;':\",.<>/?");
			WORDLIST->parseString(str);
			char h('a');
			char t('a');
			while (h <= 'z')
			{
				while (t <= 'z')
				{
					Assert::AreEqual(0, WORDLIST->getWordSumAt(h, t));
					Assert::AreEqual(0, WORDLIST->getWordRemainingAt(h, t));
					t++;
				}
				h++;
			}
		}

		TEST_METHOD(TestMethod_3)
		{
			char h('a');
			char t('a');
			while (h <= 'z')
			{
				while (t <= 'z')
				{
					Assert::AreEqual(0, WORDLIST->getWordSumAt(h, t));
					Assert::AreEqual(0, WORDLIST->getWordRemainingAt(h, t));
					string str_1(5, h);
					string str_2(6, t);
					string str_in(str_1 + str_2);
					WORDLIST->parseString(str_in);
					Assert::AreEqual(1, WORDLIST->getWordSumAt(h, t));
					Assert::AreEqual(1, WORDLIST->getWordRemainingAt(h, t));
					Assert::AreEqual(str_in, WORDLIST->getWordAt(h, t));
					Assert::AreEqual(1, WORDLIST->getWordSumAt(h, t));
					Assert::AreEqual(0, WORDLIST->getWordRemainingAt(h, t));
					WORDLIST->undoGetWordAt(h, t);
					Assert::AreEqual(1, WORDLIST->getWordSumAt(h, t));
					Assert::AreEqual(1, WORDLIST->getWordRemainingAt(h, t));
					t++;
				}
				h++;
			}
		}

		TEST_METHOD(TestMethod_4)
		{
			string str_list[] = {
				"ac", "abc", "abbc", "abbbc", "abbbbc"
			};
			for (int i = 0; i < 1000; i++) {
				WORDLIST->parseString(str_list[i % 5]);
			}
			char h('a');
			char t('a');
			while (h <= 'z')
			{
				while (t <= 'z')
				{
					if (h == 'a' && t == 'c')
					{
						Assert::AreEqual(5, WORDLIST->getWordSumAt(h, t));
						Assert::AreEqual(5, WORDLIST->getWordRemainingAt(h, t));
						for (int i = 0; i < 5; i++)
						{
							Assert::AreEqual(str_list[4 - i], WORDLIST->getWordAt(h, t));
							Assert::AreEqual(5, WORDLIST->getWordSumAt(h, t));
							Assert::AreEqual(5 - (i + 1), WORDLIST->getWordRemainingAt(h, t));
						}
					}
					else
					{
						Assert::AreEqual(0, WORDLIST->getWordSumAt(h, t));
						Assert::AreEqual(0, WORDLIST->getWordRemainingAt(h, t));
					}
					t++;
				}
				h++;
			}
		}
	};
}