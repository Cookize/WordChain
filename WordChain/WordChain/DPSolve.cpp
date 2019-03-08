#include"DPSolve.h"
#include<iostream>

int DPSolve::DPStep(int indexH)
{
	if (m_iArrayDp[indexH] >= 0)					// 已有子问题最优解
	{
		return m_iArrayDp[indexH];
	}
	for (int indexT = 0; indexT < SUM_ALPH; indexT++)// 计算子问题最优解
	{
		int t_iRemaining = m_ptrWordList->getWordRemainingAt('a' + indexH, 'a' + indexT);
		if (t_iRemaining > 0) 
		{
			int temp = m_cMode == 'c' ? 
				m_ptrWordList->getWordAt('a' + indexH, 'a' + indexT, false).length():1;
			if (indexH == indexT && t_iRemaining == 1)	// 允许有一个首尾相同的单词
			{
				temp += m_cMode == 'c' ?
					m_ptrWordList->getWordAt('a' + indexH, 'a' + indexH, false).length() : 1;
				continue;
			}
			temp += DPStep(indexT);
			if (m_iArrayDp[indexH] < temp)			// 比较是否为最长
			{
				m_iArrayDp[indexH] = temp;
				m_iArrayNext[indexH] = indexT;
			}
		}
	}
	return m_iArrayDp[indexH] >= 0 ? m_iArrayDp[indexH] : 0;
}

int DPSolve::DPStepRe(int indexT)
{
	if (m_iArrayDp[indexT] >= 0)					// 已有子问题最优解
	{
		return m_iArrayDp[indexT];
	}
	for (int indexH = 0; indexH < SUM_ALPH; indexH++)// 计算子问题最优解
	{
		int t_iRemaining = m_ptrWordList->getWordRemainingAt('a' + indexH, 'a' + indexT);
		if (t_iRemaining > 0)
		{
			int temp = m_cMode == 'c' ?
				m_ptrWordList->getWordAt('a' + indexH, 'a' + indexT, false).length() : 1;
			if (indexH == indexT && t_iRemaining == 1)	// 允许有一个首尾相同的单词
			{
				temp += m_cMode == 'c' ?
					m_ptrWordList->getWordAt('a' + indexT, 'a' + indexT, false).length() : 1;
				continue;
			}
			temp += DPStepRe(indexH);
			if (m_iArrayDp[indexT] < temp)			// 比较是否为最长
			{
				m_iArrayDp[indexT] = temp;
				m_iArrayBefore[indexT] = indexH;
			}
		}
	}
	return m_iArrayDp[indexT] >= 0 ? m_iArrayDp[indexT] : 0;
}

void DPSolve::startDPSolve()
{
	// 判断环
	if (!topoSort())
	{
		cout << "ERROR: Found Ring In Article!" << endl;
		return;
	}

	int t_iMaxIndex = 0;
	// 判断是否限定开头或结尾
	if (m_cModeHead != '&' && m_cModeTail != '&')	// 限定开头和结尾
	{

	}
	if (m_cModeHead != '&')							// 仅限定开头
	{
		t_iMaxIndex = m_cModeHead - 'a';
		DPStep(t_iMaxIndex);
		genChain(t_iMaxIndex, true);
	}
	else if(m_cModeTail != '&')						// 限定结尾
	{
		t_iMaxIndex = m_cModeTail - 'a';
		DPStepRe(t_iMaxIndex);
		genChain(t_iMaxIndex, false);
	}
	else
	{
		for (int i = 0; i < SUM_ALPH; i++)
		{
			if (DPStep(i) > m_iArrayDp[t_iMaxIndex])
			{
				t_iMaxIndex = i;
			}
		}
		genChain(t_iMaxIndex, true);
	}
	return;
}

bool DPSolve::topoSort()
{
	queue<int> t_iQueueTemp;
	int t_iArrayNodeIn[SUM_ALPH];
	for (int i = 0; i < SUM_ALPH; i++)
	{
		t_iArrayNodeIn[i] = m_ptrWordList->getNodeIn(i);
		if (t_iArrayNodeIn[i] == 0)
		{
			t_iQueueTemp.push(i);
		}
	}
	while (!t_iQueueTemp.empty())
	{
		int queueFront = t_iQueueTemp.front();
		t_iQueueTemp.pop();
		int nextList = m_ptrWordList->getNodeNext(queueFront);
		for (int i = 0; i < SUM_ALPH; i++)
		{
			if ((nextList >> i) % 2 == 1)
			{
				t_iArrayNodeIn[i]--;
				if (t_iArrayNodeIn[i] == 0)
				{
					t_iQueueTemp.push(i);
				}
			}
		}
		m_iQueueTopo.push(queueFront);
	}
	if (m_iQueueTopo.size() == SUM_ALPH) return true;
	else return false;
}

void DPSolve::genChain(int index, bool flag) {
	// 输出结果
	int length = m_iArrayDp[index];
	m_strVecWordChain.clear();
	if (flag)
	{
		if (m_ptrWordList->getWordSumAt(index + 'a', index + 'a') > 0)
		{
			m_strVecWordChain.push_back(m_ptrWordList->getWordAt(index + 'a', index + 'a'));
		}
		for (int i = 0; i < length; i++)
		{
			m_strVecWordChain.push_back(m_ptrWordList->getWordAt(index + 'a', m_iArrayNext[index] + 'a'));
			index = m_iArrayNext[index];
			if (m_ptrWordList->getWordSumAt(index + 'a', index + 'a') > 0)
			{
				m_strVecWordChain.push_back(m_ptrWordList->getWordAt(index + 'a', index + 'a'));
			}
		}
	}
	else
	{
		if (m_ptrWordList->getWordSumAt(index + 'a', index + 'a') > 0)
		{
			m_strVecWordChain.insert(m_strVecWordChain.begin(), m_ptrWordList->getWordAt(index + 'a', index + 'a'));
		}
		for (int i = 0; i < length; i++)
		{
			m_strVecWordChain.insert(m_strVecWordChain.begin(), m_ptrWordList->getWordAt(m_iArrayBefore[index] + 'a', index + 'a'));
			index = m_iArrayBefore[index];
			if (m_ptrWordList->getWordSumAt(index + 'a', index + 'a') > 0)
			{
				m_strVecWordChain.insert(m_strVecWordChain.begin(), m_ptrWordList->getWordAt(index + 'a', index + 'a'));
			}
		}
	}
	
}