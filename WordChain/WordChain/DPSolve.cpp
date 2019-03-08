#include"DPSolve.h"
#include<iostream>

int DPSolve::DPStep(int indexH)
{
	if (m_iArrayDp[indexH] >= 0)					// �������������Ž�
	{
		return m_iArrayDp[indexH];
	}
	for (int indexT = 0; indexT < SUM_ALPH; indexT++)// �������������Ž�
	{
		int t_iRemaining = m_ptrWordList->getWordRemainingAt('a' + indexH, 'a' + indexT);
		if (t_iRemaining > 0) 
		{
			int temp = m_cMode == 'c' ? 
				m_ptrWordList->getWordAt('a' + indexH, 'a' + indexT, false).length():1;
			if (indexH == indexT && t_iRemaining == 1)	// ������һ����β��ͬ�ĵ���
			{
				temp += m_cMode == 'c' ?
					m_ptrWordList->getWordAt('a' + indexH, 'a' + indexH, false).length() : 1;
				continue;
			}
			temp += DPStep(indexT);
			if (m_iArrayDp[indexH] < temp)			// �Ƚ��Ƿ�Ϊ�
			{
				m_iArrayDp[indexH] = temp;
				m_iArrayNext[indexH] = indexT;
			}
		}
	}
	return m_iArrayDp[indexH] >= 0 ? m_iArrayDp[indexH] : 0;
}

void DPSolve::startDPSolve()
{
	// �жϻ�
	if (!topoSort())
	{
		cout << "ERROR: Found Ring In Article!" << endl;
		return;
	}

	int t_iMaxIndex = 0;
	// �ж��Ƿ��޶���ͷ���β
	if (m_cModeHead != '&' && m_cModeTail != '&')	// �޶���ͷ�ͽ�β
	{

	}
	if (m_cModeHead != '&')							// ���޶���ͷ
	{
		t_iMaxIndex = m_cModeHead - 'a';
		DPStep(t_iMaxIndex);
	}
	else if(m_cModeTail != '&')						// �޶���β
	{
		// TODO:����̬�滮
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
	}
	// ������
	int length = m_iArrayDp[t_iMaxIndex];
	for (int i = 0; i < length; i++)
	{
		if (m_ptrWordList->getWordSumAt(t_iMaxIndex, t_iMaxIndex) > 0)
		{
			cout << m_ptrWordList->getWordAt(t_iMaxIndex + 'a', t_iMaxIndex + 'a') << endl;
		}
		cout << m_ptrWordList->getWordAt(t_iMaxIndex + 'a', m_iArrayNext[t_iMaxIndex] + 'a') << endl;
		t_iMaxIndex = m_iArrayNext[t_iMaxIndex];
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