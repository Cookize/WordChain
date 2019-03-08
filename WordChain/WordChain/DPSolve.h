#pragma once
#include"WordList.h"
#include <queue>
#define SUM_ALPH (26)

using namespace std;

/*
	��̬�滮������
		�ϸ�Ч�����޻�����µ������������
*/
class DPSolve
{
public:
	/*
		���캯����
	*/
	DPSolve(WordList *_wordList, char _mode)
	{
		initPara();
		m_ptrWordList = _wordList;
		m_cMode = _mode;
		m_cModeHead = '&';
		m_cModeTail = '&';
	}
	DPSolve(WordList *_wordList, char _mode, char _c, bool _isHead)
	{
		initPara();
		m_ptrWordList = _wordList;
		m_cMode = _mode;
		m_cModeHead = _isHead ? _c:'&';
		m_cModeTail = _isHead ? '&':_c;
	}
	DPSolve(WordList *_wordList, char _mode, char _head, char _tail)
	{
		initPara();
		m_ptrWordList = _wordList;
		m_cMode = _mode;
		m_cModeHead = _head;
		m_cModeTail = _tail;
	}

	/*
		��������
	*/
	void startDPSolve();

	/*
		�������򣬼���Ƿ��л�
	*/
	bool topoSort();

private:
	// ���ʱ�
	WordList *m_ptrWordList;

	// ���ܲ���
	char m_cMode;
	char m_cModeHead;
	char m_cModeTail;

	// ������
	int m_iArrayDp[SUM_ALPH];				// �洢��ĳ��ĸ��ͷ�������������
	int m_iArrayNext[SUM_ALPH];			// �洢��ĳ��ĸ��ͷ���������
	queue<int> m_iQueueTopo;
	
	// ��ʼ������
	void initPara()
	{
		for (int i = 0; i < SUM_ALPH; i++)
		{
			m_iArrayDp[i] = -1;
			m_iArrayNext[i] = -1;
		}
	}

	/*
		��̬�滮�ݹ��Ӻ���
	*/
	int DPStep(int indexH);
	int DPStepRe(int indexH)
};