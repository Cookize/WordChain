#include"WordList.h"
#include<iostream>
#include <fstream>
using namespace std;

/*

*/
bool isAlph(const char _c)
{
	return (_c >= 'a' && _c <= 'z') || (_c >= 'A' && _c <= 'Z');
}

void toLower(string &_str)
{
	size_t length(_str.length());
	for (size_t i = 0; i < length; i++)
	{
		if (_str[i] >= 'A' && _str[i] <= 'Z')
		{
			_str[i] += 'a' - 'A';
		}
	}
}

void WordList::addWord(const string &_word)
{
	string t_strNewWord(_word);
	toLower(t_strNewWord);
	size_t t_iWordLength(t_strNewWord.length());
	int t_iIndexH = t_strNewWord[0] - 'a';
	int t_iIndexT = t_strNewWord[t_iWordLength - 1] - 'a';
	int t_iIndex(t_iIndexH * 26 + t_iIndexT);

	if ((m_iArryMatrix[t_iIndexH] >> t_iIndexT) % 2 == 0)			// 更新邻接矩阵和入度计数器
	{
		if (t_iIndexH != t_iIndexT)
		{
			m_iArrayNodeIn[t_iIndexT]++;
		}
		m_iArryMatrix[t_iIndexH] |= (1 << t_iIndexT);
	}
	else if(t_iIndexH == t_iIndexT)								// 过滤一次首位相同的单词
	{
		m_iArrayNodeIn[t_iIndexT]++;
	}
	m_iArrayNodeOut[t_iIndexH]++;

	for (int i = 0; i < m_iListSize[t_iIndex]; i++)
	{
		if (m_words->m_list[t_iIndex][i] == t_strNewWord) 
		{
			return;
		}
		if (m_words->m_list[t_iIndex][i].length() < t_iWordLength)
		{
			m_words->m_list[t_iIndex].insert(m_words->m_list[t_iIndex].begin() + i, t_strNewWord);
			m_words->m_flag[t_iIndex].push_back(false);
			m_iListSize[t_iIndex]++;
			return;
		}
	}
	m_words->m_list[t_iIndex].push_back(t_strNewWord);
	m_words->m_flag[t_iIndex].push_back(false);
	m_iListSize[t_iIndex]++;
}

void WordList::parseString(const string &_str)
{
	size_t t_iStrLength(_str.length());
	size_t i, j;
	for (i = j = 0; i <= t_iStrLength; i++)
	{
		if (i == t_iStrLength || !isAlph(_str[i]))
		{
			if (i > j)
			{
				string t_strNewWord(_str, j, i - j);
				addWord(t_strNewWord);
			}
			j = i + 1;
		}
	}
}

string WordList::getWordAt(char _c1, char _c2, bool _ifDelete)
{
	int t_iIndex((_c1 - 'a') * 26 + _c2 - 'a');
	if (m_words->m_list[t_iIndex].size() == 0)
		return "";
	return m_words->m_list[t_iIndex][0];
}

string WordList::getWordAt(char _c1, char _c2)
{
	return getWordAt(_c1, _c2, true);
}

int WordList::getWordSumAt(char _c1, char _c2)
{
	int t_iIndex((_c1 - 'a') * 26 + _c2 - 'a');
	if(t_iIndex < 0 || t_iIndex > SUM_ALPH_2)
	{
		return 0;
	}
	return m_iListSize[t_iIndex];
}

// test
void WordList::showAllWord()
{
	int count = 0;
	ofstream out("WordList.txt");
	if (!out.is_open())
	{
		cout << "ERROR:Illegal Output File!" << endl;
		return;
	}
	for (int i = 0; i < SUM_ALPH_2; i++)
	{
		if (m_iListSize[i] == 0)
		{
			continue;
		}
		out << (char)(i / 26 + 'a') << "->" << (char)(i % 26 + 'a') << endl;
		for (int j = 0; j < m_iListSize[i]; j++)
		{
			out << m_words->m_list[i][j] << endl;
			count++;
		}
		out << "-----------------------------" << endl;
	}
	out << count << endl;
}