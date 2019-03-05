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
	int m_iSigned[26]; //问题一 记录 是字母是否使用
	int m_ans[676][676]; //记录单词是否使用的变量
	stack <string> m_FinalChain; //最终结果
	stack <string> m_TempChain;  // 当前路径

};



#endif
