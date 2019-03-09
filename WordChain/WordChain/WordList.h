#ifndef __WORD_LIST_H_
#define __WORD_LIST_H_
#include "GlobalDef.h"
#include <vector>
#include <string>
using namespace std;

/*
	类名：
		字典
	功能：
		1.解析字符串，提取“单词”并将新单词加入词典。
		2.提供“首尾字母”相关的查询功能。
		3.提供单词表打印功能。
	注意：
		1.不区分大小写。
*/
class WordList
{
public:
	WordList()
	{
		m_iListSize = new int[SUM_ALPH_2 + 1];
		m_iListGetPoint = new int[SUM_ALPH_2 + 1];
		for (int i = 0; i < 26; i++)
		{
			m_iArrayNodeIn[i] = 0;
			m_iArryMatrix[i] = 0;
		}
		for (int i = 0; i < SUM_ALPH_2 + 1; i++)
		{
			m_iListSize[i] = 0;
			m_iListGetPoint[i] = 0;
		}
	}
	~WordList()
	{
		delete m_iListSize;
		delete m_iListGetPoint;
		m_iListSize = NULL;
		m_iListGetPoint = NULL;
	}

	/*
		方法：
			解析字符串，提取单词。
		输入：
			_str：需要解析的字符串。
		输出：
			无
		效果：
			在字典中增加新识别的单词。
	*/
	void parseString(const string &_str);

	/*
		方法：
			获取符合首尾条件的单词。
		输入：
			_c1：首字母；
			_c2：尾字母；
		输出：
			若存在符合首尾条件的单词，返回最长的单词；
			若不存在，返回NULL。
		注意：
			连续获取时会按照长度由长至短的顺序返回单词。
			
	*/
	string getWordAt(char _c1, char _c2);
	string getWordAt(char _c1, char _c2, bool _ifDelete);

	/*
		方法：
			获取符合首尾条件的单词“总”数量。
		输入：
			_c1：首字母；
			_c2：尾字母；
		输出：
			符合首尾条件的单词总数量。

	*/
	int getWordSumAt(char _c1, char _c2);

	/*
		方法：
			获取符合首尾条件的单词“剩余”数量。
		输入：
			_c1：首字母；
			_c2：尾字母；
		输出：
			符合首尾条件的单词剩余数量。

	*/
	int getWordRemainingAt(char _c1, char _c2);

	/*
		方法：
			撤销单词获取操作。
		输入：
			_c1：首字母；
			_c2：尾字母；
		输出：
			无
		效果：
			撤销符合首尾条件的单词前一次获取操作。
		注意：
			回溯时调用，可以撤销一次获取操作。
	*/
	void undoGetWordAt(char _c1, char _c2);

	int getNodeIn(int _index)
	{
		return m_iArrayNodeIn[_index];
	}

	int getNodeNext(int _index)
	{
		return m_iArryMatrix[_index];
	}

	/*
		方法：
			字典打印。
		输入/输出：
			无
		效果：
			将字典内容格式化输出至文件“WordList.txt”
	*/
	void showAllWord();

private:
	vector<string> m_list[SUM_ALPH_2 + 1];

	int *m_iListSize;
	int *m_iListGetPoint;

	int m_iArryMatrix[26];		// 邻接矩阵
	int m_iArrayNodeIn[26];

	void addWord(const string &_word);
};

#endif // !__WORD_LIST_

