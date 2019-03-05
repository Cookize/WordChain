#ifndef __SOLVE_H_
#define __SOLVE_H_
#include "WordList.h"
#include <vector>
#include <string>	
#include <stack>
#include <string.h>

using namespace std;
class Solve
{
public:
	/*
	*/
	void Solve1(const WordList & wordlist );


private:
	int m_iSigned[26]; //����һ ��¼ ����ĸ�Ƿ�ʹ��
	int m_ans[676][676]; //��¼�����Ƿ�ʹ�õı���
	stack <string> m_FinalChain; //���ս��
	stack <string> m_TempChain;  // ��ǰ·��

};



#endif
