#include"DPSolve.h"
#include<iostream>

int DPSolve::DPStep(WordList &wordList, int indexH)
{
	if (m_boolIsRing)								// 有环退出
	{
		return -1;
	}
	if (m_iArrayDp[indexH] >= 0)					// 已有子问题最优解
	{
		return m_iArrayDp[indexH];
	}
	bool t_boolHaveNew = false;						// 标记是否有新单词加入
	bool t_boolSelf = false;						// 标记是否有同首尾单词
	m_iHead[indexH] = 1;							// 更新标记
	for (int indexT = 0; indexT < SUM_ALPH; indexT++)// 计算子问题最优解
	{
		int t_iRemaining = wordList.getWordRemainingAt('a' + indexH, 'a' + indexT);
		if (t_iRemaining > 0) 
		{
			if (indexH == indexT && t_iRemaining == 1)
			{
				t_boolSelf = true;
				continue;
			}
			else if (m_iHead[indexT] == 1)
			{
				m_boolIsRing = true;
				return -1;
			}
			int temp = 1;
			temp += DPStep(wordList, indexT);
			if (m_iArrayDp[indexH] < temp)			// 比较是否为最长
			{
				if (t_boolHaveNew)
				{
					m_TempChain.pop_back();
				}
				m_iArrayDp[indexH] = temp;
				m_TempChain.push_back(wordList.getWordAt(indexH + 'a', indexT + 'a', true));
				t_boolHaveNew = true;
			}
		}
	}
	if (t_boolSelf)
	{
		m_iArrayDp[indexH]++;
		m_TempChain.push_back(wordList.getWordAt(indexH + 'a', indexH + 'a', true));
	}
	return m_iArrayDp[indexH] >= 0 ? m_iArrayDp[indexH] : 0;
}

void DPSolve::startDPSolve(WordList &wordList)
{
	int t_iMaxIndex = 0;
	for (int i = 0; i < SUM_ALPH; i++)
	{
		initFlag();
		if (DPStep(wordList, i) > m_iArrayDp[t_iMaxIndex] || i == 0)
		{
			t_iMaxIndex = i;
			m_FinalChain.clear();
			m_FinalChain.assign(m_TempChain.begin(), m_TempChain.end());
		}
		if (m_boolIsRing)
		{
			cout << "ERROR: Found Ring!" << endl;
			return;
		}
	}
	cout << t_iMaxIndex << endl;
	cout << m_iArrayDp[t_iMaxIndex] << endl;
	for (int i = m_FinalChain.size() - 1; i >= 0; i--)
	{
		cout << m_FinalChain[i] << endl;
	}
	return;
}