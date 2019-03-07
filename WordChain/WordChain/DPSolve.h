#pragma once
#include"WordList.h"
class DPSolve
{
public:
	/*
	*/
	DPSolve(char mode)
	{
		init();
		m_Mode = mode;
		m_ModeHead = '&';
		m_ModeTail = '&';
	}
	DPSolve(char mode, char c, bool is_head)
	{
		init();
		m_Mode = mode;
		if (is_head)
		{
			m_ModeHead = c;
			m_ModeTail = '&';
		}
		else
		{
			m_ModeHead = '&';
			m_ModeTail = c;
		}
	}
	DPSolve(char mode, char mode_head, char mode_tail)
	{
		init();
		m_Mode = mode;
		m_ModeHead = mode_head;
		m_ModeTail = mode_tail;
	}
	void startDPSolve(const WordList &wordList);

private:
	int m_iSigned[26][26]; //问题一 记录 是字母是否使用
	int m_ihead[26];
	int m_FinalLen;
	int m_TemLen;
	bool is_circle; // 判断是否有环

	char m_Mode;
	char m_ModeHead;
	char m_ModeTail;
	bool m_ModeRing;

	int dp[26];
	vector <string> m_FinalChain; //最终结果
	vector <string> m_TempChain;  // 当前路径
	void init()
	{
		is_circle = 0;
		m_ModeRing = false;
		m_FinalLen = 0;
		m_TemLen = 0;
		for (int i = 0; i < 26; i++)
		{
			m_ihead[i] = 0;
			for (int j = 0; j < 26; j++)
			{
				m_iSigned[i][j] = 0;
			}
		}
	}

};