#ifndef __DP_SOLVE_H_
#define __DP_SOLVE_H_
#include "WordList.h"
#include "GlobalDef.h"
#include <queue>

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
		m_cModeHead = _isHead ? _c : '&';
		m_cModeTail = _isHead ? '&' : _c;
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

	/*
		��ȡ������
	*/
	void getWordChain(vector<string> &output)
	{
		output.assign(m_strVecWordChain.begin(), m_strVecWordChain.end());
	}

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
	int m_iArrayBefore[SUM_ALPH];
	queue<int> m_iQueueTopo;
	vector<string> m_strVecWordChain;

	// ��ʼ������
	void initPara()
	{
		for (int i = 0; i < SUM_ALPH; i++)
		{
			m_iArrayDp[i] = -1;
			m_iArrayNext[i] = -1;
			m_iArrayBefore[i] = -1;
		}
	}

	/*
		��̬�滮�ݹ��Ӻ���
	*/
	int DPStep(int indexH);
	int DPStepRe(int indexH);

	/*
		���ɵ�����
	*/
	void genChain(int indexStart, bool flag);
};

#endif // !__DP_SOLVE_H_