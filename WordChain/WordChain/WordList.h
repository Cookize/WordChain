#ifndef __WORD_LIST_H_
#define __WORD_LIST_H_
#include "GlobalDef.h"
#include <vector>
#include <string>
using namespace std;

typedef struct
{
	vector<string> m_list[SUM_ALPH_2 + 1];
	vector<bool> m_flag[SUM_ALPH_2 + 1];
	int m_iListGetPoint[SUM_ALPH_2 + 1] = { 0 };
}WORD;

/*
	������
		�ֵ�
	���ܣ�
		1.�����ַ�������ȡ�����ʡ������µ��ʼ���ʵ䡣
		2.�ṩ����β��ĸ����صĲ�ѯ���ܡ�
		3.�ṩ���ʱ��ӡ���ܡ�
	ע�⣺
		1.�����ִ�Сд��
*/
class WordList
{
public:
	WordList()
	{
		m_iListSize = new int[SUM_ALPH_2 + 1];
		m_words = new WORD;
		for (int i = 0; i < 26; i++)
		{
			m_iArrayNodeIn[i] = 0;
			m_iArryMatrix[i] = 0;
			m_iArrayNodeOut[i] = 0;
		}
		for (int i = 0; i < SUM_ALPH_2 + 1; i++)
		{
			m_iListSize[i] = 0;
			m_words->m_iListGetPoint[i] = 0;
		}
	}
	~WordList()
	{
		delete m_iListSize;
		delete m_words;
		m_words = NULL;
		m_iListSize = NULL;
	}

	/*
		������
			�����ַ�������ȡ���ʡ�
		���룺
			_str����Ҫ�������ַ�����
		�����
			��
		Ч����
			���ֵ���������ʶ��ĵ��ʡ�
	*/
	void parseString(const string &_str);

	/*
		������
			��ȡ������β�����ĵ��ʡ�
		���룺
			_c1������ĸ��
			_c2��β��ĸ��
		�����
			�����ڷ�����β�����ĵ��ʣ�������ĵ��ʣ�
			�������ڣ�����NULL��
		ע�⣺
			������ȡʱ�ᰴ�ճ����ɳ����̵�˳�򷵻ص��ʡ�
			
	*/
	string getWordAt(char _c1, char _c2);
	string getWordAt(char _c1, char _c2, bool _ifDelete);

	/*
		������
			��ȡ������β�����ĵ��ʡ��ܡ�������
		���룺
			_c1������ĸ��
			_c2��β��ĸ��
		�����
			������β�����ĵ�����������

	*/
	int getWordSumAt(char _c1, char _c2);

	int getNodeIn(int _index)
	{
		return m_iArrayNodeIn[_index];
	}

	int getNodeOut(int _index)
	{
		return m_iArrayNodeOut[_index];
	}

	int getNodeNext(int _index)
	{
		return m_iArryMatrix[_index];
	}

	/*
		������
			�ֵ��ӡ��
		����/�����
			��
		Ч����
			���ֵ����ݸ�ʽ��������ļ���WordList.txt��
	*/
	void showAllWord();

	WORD* getWordList()
	{
		return m_words;
	}

private:
	WORD *m_words = NULL;

	int *m_iListSize = NULL;
	

	int m_iArryMatrix[26] = { 0 };		// �ڽӾ���
	int m_iArrayNodeIn[26] = { 0 };
	int m_iArrayNodeOut[26] = { 0 };

	void addWord(const string &_word);
};

#endif // !__WORD_LIST_

