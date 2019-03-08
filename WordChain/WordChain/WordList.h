#ifndef __WORD_LIST_H_
#define __WORD_LIST_H_
#include <vector>
#include <string>
#define SUM_ALPH (26)
using namespace std;

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
		m_iListSize = new int[MAX_SIZE + 1];
		m_iListGetPoint = new int[MAX_SIZE + 1];
		for (int i = 0; i < 26; i++)
		{
			m_iArrayNodeIn[i] = 0;
			m_iArryMatrix[i] = 0;
		}
		for (int i = 0; i < MAX_SIZE + 1; i++)
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

	/*
		������
			��ȡ������β�����ĵ��ʡ�ʣ�ࡱ������
		���룺
			_c1������ĸ��
			_c2��β��ĸ��
		�����
			������β�����ĵ���ʣ��������

	*/
	int getWordRemainingAt(char _c1, char _c2);

	/*
		������
			�������ʻ�ȡ������
		���룺
			_c1������ĸ��
			_c2��β��ĸ��
		�����
			��
		Ч����
			����������β�����ĵ���ǰһ�λ�ȡ������
		ע�⣺
			����ʱ���ã����Գ���һ�λ�ȡ������
	*/
	void undoGetWordAt(char _c1, char _c2);

	int getNodeIn(char _c)
	{
		return getNodeIn(_c - 'a');
	}

	int getNodeIn(int _index)
	{
		if (_index >= 0 && _index < SUM_ALPH)
		{
			return m_iArrayNodeIn[_index];
		}
		return 0;
	}

	int getNodeNext(char _c)
	{
		return getNodeNext(_c - 'a');
	}

	int getNodeNext(int _index)
	{
		if (_index >= 0 && _index < SUM_ALPH)
		{
			return m_iArryMatrix[_index];
		}
		return 0;
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

private:
	const int MAX_SIZE = 676;
	vector<string> m_list[677];

	int *m_iListSize;
	int *m_iListGetPoint;

	int m_iArryMatrix[26];		// �ڽӾ���
	int m_iArrayNodeIn[26];

	void addWord(const string &_word);
};

#endif // !__WORD_LIST_

