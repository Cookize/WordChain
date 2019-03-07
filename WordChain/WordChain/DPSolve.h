#pragma once
#include"WordList.h"
#define SUM_ALPH (26)

class DPSolve
{
public:
	DPSolve(char mode)
	{
		initPara();
		m_cMode = mode;
		m_cModeHead = '&';
		m_cModeTail = '&';
	}
	DPSolve(char mode, char c, bool is_head)
	{
		initPara();
		m_cMode = mode;
		if (is_head)
		{
			m_cModeHead = c;
			m_cModeTail = '&';
		}
		else
		{
			m_cModeHead = '&';
			m_cModeTail = c;
		}
	}
	DPSolve(char mode, char mode_head, char mode_tail)
	{
		initPara();
		m_cMode = mode;
		m_cModeHead = mode_head;
		m_cModeTail = mode_tail;
	}
	void startDPSolve(WordList &wordList);
	int DPStep(WordList &wordList, int indexH);

private:

	// 标记位
	int m_iSigned[SUM_ALPH][SUM_ALPH];	// 记录是首尾路径是否使用
	int m_iHead[SUM_ALPH];		// 记录字母是否使用
	bool m_boolIsRing;			// 判断是否有环

	// 功能参数
	char m_cMode;
	char m_cModeHead;
	char m_cModeTail;
	bool m_boolModeRing;

	// 计算结果
	int m_iArrayDp[SUM_ALPH];				// 存储以某字母开头的最长单词链长度
	int m_iArrayNext[SUM_ALPH];			// 存储以某字母开头的最长单词链
	vector <string> m_FinalChain;	// 最终结果
	vector <string> m_TempChain;	// 当前路径
	
	// 初始化参数
	void initPara()
	{
		m_boolIsRing = 0;
		m_boolModeRing = false;
		for (int i = 0; i < SUM_ALPH; i++)
		{
			m_iArrayDp[i] = -1;
			m_iArrayNext[i] = -1;
		}
	}

	// 初始化标记位
	void initFlag()
	{
		for (int i = 0; i < SUM_ALPH; i++)
		{
			m_iHead[i] = 0;
			for (int j = 0; j < SUM_ALPH; j++)
			{
				m_iSigned[i][j] = 0;
			}
		}
	}

};