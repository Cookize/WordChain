#ifndef __WORD_LIST_H_
#define __WORD_LIST_H_
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
		m_iListSize = new int[MAX_SIZE + 1];
		for (int i = 0; i < MAX_SIZE + 1; i++)
		{
			m_iListSize[i] = 0;
		}
	}
	~WordList()
	{
		delete m_iListSize;
		m_iListSize = NULL;
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
		效果：
			
	*/
	string getWordAt(char _c1, char _c2);



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
	const int MAX_SIZE = 676;
	int *m_iListSize;
	vector<string> m_list[677];
	void addWord(const string &_word);
};

#endif // !__WORD_LIST_

