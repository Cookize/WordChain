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

	// ���λ
	int m_iSigned[SUM_ALPH][SUM_ALPH];	// ��¼����β·���Ƿ�ʹ��
	int m_iHead[SUM_ALPH];		// ��¼��ĸ�Ƿ�ʹ��
	bool m_boolIsRing;			// �ж��Ƿ��л�

	// ���ܲ���
	char m_cMode;
	char m_cModeHead;
	char m_cModeTail;
	bool m_boolModeRing;

	// ������
	int m_iArrayDp[SUM_ALPH];				// �洢��ĳ��ĸ��ͷ�������������
	int m_iArrayNext[SUM_ALPH];			// �洢��ĳ��ĸ��ͷ���������
	vector <string> m_FinalChain;	// ���ս��
	vector <string> m_TempChain;	// ��ǰ·��
	
	// ��ʼ������
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

	// ��ʼ�����λ
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