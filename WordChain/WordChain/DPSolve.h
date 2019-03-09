#ifndef __DP_SOLVE_H_
#define __DP_SOLVE_H_
#include "WordList.h"
#include "GlobalDef.h"
#include <queue>

using namespace std;

/*
	动态规划处理类
		较高效处理无环情况下的最长单词连搜索
*/
class DPSolve
{
public:
	/*
		构造函数们
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
		启动函数
	*/
	void startDPSolve();

	/*
		拓扑排序，检查是否有环
	*/
	bool topoSort();

	/*
		获取单词链
	*/
	void getWordChain(vector<string> &output)
	{
		output.assign(m_strVecWordChain.begin(), m_strVecWordChain.end());
	}

private:
	// 单词表
	WordList *m_ptrWordList;

	// 功能参数
	char m_cMode;
	char m_cModeHead;
	char m_cModeTail;

	// 计算结果
	int m_iArrayDp[SUM_ALPH];				// 存储以某字母开头的最长单词链长度
	int m_iArrayNext[SUM_ALPH];			// 存储以某字母开头的最长单词链
	int m_iArrayBefore[SUM_ALPH];
	queue<int> m_iQueueTopo;
	vector<string> m_strVecWordChain;

	// 初始化参数
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
		动态规划递归子函数
	*/
	int DPStep(int indexH);
	int DPStepRe(int indexH);

	/*
		生成单词链
	*/
	void genChain(int indexStart, bool flag);
};

#endif // !__DP_SOLVE_H_