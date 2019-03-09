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

		TEST_METHOD(Test_1)		// 输入空字符串
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

		TEST_METHOD(Test_2)		// 输入非单词字符串
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

		TEST_METHOD(Test_3)	// 全覆盖测试
		{
			char h('a');
			char t('a');
			while (h <= 'z')
			{
				while (t <= 'z')
				{
					string str_1(5, h);
					string str_2(5, t);
					string str_3(6, t);
					string str_in_1(str_1 + str_2);
					string str_in_2(str_1 + str_3);

					// 初始值为0
					Assert::AreEqual(0, WORDLIST->getWordSumAt(h, t));
					Assert::AreEqual(0, WORDLIST->getWordRemainingAt(h, t));

					// 加入一个单词
					WORDLIST->parseString(str_in_1);
					Assert::AreEqual(1, WORDLIST->getWordSumAt(h, t));
					Assert::AreEqual(1, WORDLIST->getWordRemainingAt(h, t));

					// 加入一个相同单词
					WORDLIST->parseString(str_in_1);
					Assert::AreEqual(1, WORDLIST->getWordSumAt(h, t));
					Assert::AreEqual(1, WORDLIST->getWordRemainingAt(h, t));

					// 加入一个不同单词
					WORDLIST->parseString(str_in_2);
					Assert::AreEqual(2, WORDLIST->getWordSumAt(h, t));
					Assert::AreEqual(2, WORDLIST->getWordRemainingAt(h, t));

					// 获取开头单词
					Assert::AreEqual(str_in_2, WORDLIST->getWordAt(h, t, false));
					Assert::AreEqual(2, WORDLIST->getWordSumAt(h, t));
					Assert::AreEqual(2, WORDLIST->getWordRemainingAt(h, t));

					// 取出开头单词
					Assert::AreEqual(str_in_2, WORDLIST->getWordAt(h, t, true));
					Assert::AreEqual(2, WORDLIST->getWordSumAt(h, t));
					Assert::AreEqual(1, WORDLIST->getWordRemainingAt(h, t));

					// 取出开头单词
					Assert::AreEqual(str_in_1, WORDLIST->getWordAt(h, t, true));
					Assert::AreEqual(2, WORDLIST->getWordSumAt(h, t));
					Assert::AreEqual(0, WORDLIST->getWordRemainingAt(h, t));

					// 撤销取出
					WORDLIST->undoGetWordAt(h, t);
					Assert::AreEqual(str_in_1, WORDLIST->getWordAt(h, t, false));
					Assert::AreEqual(2, WORDLIST->getWordSumAt(h, t));
					Assert::AreEqual(1, WORDLIST->getWordRemainingAt(h, t));

					// 撤销取出
					WORDLIST->undoGetWordAt(h, t);
					Assert::AreEqual(str_in_2, WORDLIST->getWordAt(h, t, false));
					Assert::AreEqual(2, WORDLIST->getWordSumAt(h, t));
					Assert::AreEqual(2, WORDLIST->getWordRemainingAt(h, t));


					t++;
				}
				h++;
			}
		}

		TEST_METHOD(Test_4)		// 同种单词重复测试
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
	
		TEST_METHOD(Test_5)
		{
			string str_list[] = {
				"ac", "abc" , "abc", "abbc"
			};
			Assert::AreEqual(0, WORDLIST->getNodeIn(2));
			WORDLIST->parseString(str_list[0]);
			Assert::AreEqual(1, WORDLIST->getNodeIn(2));
			WORDLIST->parseString(str_list[1]);
			Assert::AreEqual(1, WORDLIST->getNodeIn(2));
			WORDLIST->parseString(str_list[2]);
			Assert::AreEqual(1, WORDLIST->getNodeIn(2));
			WORDLIST->parseString(str_list[3]);
			Assert::AreEqual(1, WORDLIST->getNodeIn(2));
			Assert::AreEqual(1 << 2, WORDLIST->getNodeNext(0));
		}

		TEST_METHOD(Test_6)
		{
			string str_list[] = {
				"aa", "aba" , "aba", "abba"
			};
			Assert::AreEqual(0, WORDLIST->getNodeIn(0));
			WORDLIST->parseString(str_list[0]);
			Assert::AreEqual(0, WORDLIST->getNodeIn(0));
			WORDLIST->parseString(str_list[1]);
			Assert::AreEqual(1, WORDLIST->getNodeIn(0));
			WORDLIST->parseString(str_list[2]);
			Assert::AreEqual(2, WORDLIST->getNodeIn(0));
			WORDLIST->parseString(str_list[3]);
			Assert::AreEqual(3, WORDLIST->getNodeIn(0));
			Assert::AreEqual(1, WORDLIST->getNodeNext(0));
		}
	};
}