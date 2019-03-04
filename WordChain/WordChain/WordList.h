#ifndef __WORD_LIST_H_
#define __WORD_LIST_H_
#include <vector>
#include <string>
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
		Ч����
			
	*/
	string getWordAt(char _c1, char _c2);



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
	int *m_iListSize;
	vector<string> m_list[677];
	void addWord(const string &_word);
};

#endif // !__WORD_LIST_

