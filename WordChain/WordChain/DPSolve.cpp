#include"DPSolve.h"
#include<iostream>

int DPSolve::DPStep(WordList &wordList, int indexH)
{
	if (m_iArrayDp[indexH] >= 0)					// 已有子问题最优解
	{
		return m_iArrayDp[indexH];
	}
	for (int indexT = 0; indexT < SUM_ALPH; indexT++)// 计算子问题最优解
	{
		int t_iRemaining = wordList.getWordRemainingAt('a' + indexH, 'a' + indexT);
		if (t_iRemaining > 0) 
		{
			int temp = 1;
			if (indexH == indexT && t_iRemaining == 1)	// 允许有一个首尾相同的单词
			{
				temp++;
				continue;
			}
			temp += DPStep(wordList, indexT);
			if (m_iArrayDp[indexH] < temp)			// 比较是否为最长
			{
				m_iArrayDp[indexH] = temp;
				m_iArrayNext[indexH] = indexT;
			}
		}
	}
	return m_iArrayDp[indexH] >= 0 ? m_iArrayDp[indexH] : 0;
}

void DPSolve::startDPSolve(WordList &wordList)
{
	int t_iMaxIndex = 0;
	for (int i = 0; i < SUM_ALPH; i++)
	{
		initFlag();
		if (DPStep(wordList, i) > m_iArrayDp[t_iMaxIndex])
		{
			t_iMaxIndex = i;
		}
		if (m_boolIsRing)
		{
			cout << "ERROR: Found Ring!" << endl;
			return;
		}
	}
	int length = m_iArrayDp[t_iMaxIndex];
	for (int i = 0; i < length; i++)
	{
		if (wordList.getWordSumAt(t_iMaxIndex, t_iMaxIndex) > 0)
		{
			cout << wordList.getWordAt(t_iMaxIndex + 'a', t_iMaxIndex + 'a') << endl;
		}
		cout << wordList.getWordAt(t_iMaxIndex + 'a', m_iArrayNext[t_iMaxIndex] + 'a') << endl;
		t_iMaxIndex = m_iArrayNext[t_iMaxIndex];
	}
	return;
}