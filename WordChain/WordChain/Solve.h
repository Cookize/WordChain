#ifndef __SOLVE_H_
#define __SOLVE_H_
#include "WordList.h"
#include <vector>
#include <string>	
#include <string.h>
#define LENGTH 'c'
#define NUM 'w'
using namespace std;
class Solve
{
public:
	Solve(char mode)
	{
		init();
		m_Mode = mode;
		m_ModeHead = '&';
		m_ModeTail = '&';
	}
	Solve(char mode,char c,bool is_head)
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
	Solve(char mode,char mode_head,char mode_tail)
	{
		init();
		m_Mode = mode;
		m_ModeHead = mode_head;
		m_ModeTail = mode_tail;
	}
	void Solve1(WordList & wordlist, bool is_ring);
	void solve_he(WordList& wordlist);

	
private:
	int m_iSigned[26][26]; //问题一 记录 是字母是否使用
	int m_ihead[26];
	int m_ans[676][676]; //记录单词是否使用的变量
	int len_ans[26][26];
	int max_dfs[26];
	int final_dfs[26];
	int ahead[26];
	int m_FinalLen;
	int m_TemLen; 
	int max_num;
	int temp_num;
	bool is_circle; // 判断是否有环 
	int head;
	char m_Mode;
	char m_ModeHead;
	char m_ModeTail;
	bool m_ModeRing;
    vector <string> m_FinalChain; //最终结果
	vector <string> m_TempChain;  // 当前路径
	void Dfs_solve1(WordList& wordlist, char c);
	void cmp();
	void cmp_he();
	void Dfs_solvehe(WordList& wordlist, int c);
	void printChain();
	void printhe(WordList& wordlist);
	int get_max(int * a, int num);
	void init()
	{
		is_circle = 0;
		m_ModeRing = false;
		m_FinalLen = 0;
		m_TemLen = 0;
		max_num = 0;
		temp_num = 0;
		for (int i = 0; i < 26; i++)
		{
			m_ihead[i] = 0;
			for (int j = 0; j < 26; j++)
			{
				m_iSigned[i][j] = 0;
				len_ans[i][j] = 0;
				max_dfs[i] = -1;
				ahead[i] = 0;
				final_dfs[i]=0;
			}
		}

		for (int i = 0; i < 676; i++)
		{
			m_ihead[i] = 0;
			for (int j = 0; j < 676; j++)
			{
				m_ans[i][j] = 0;

			}
		}
	}
};
#endif
