#include "Solve.h"
#include <iostream>

using namespace std;
int Solve::get_max(int * a,int num)
{
	for (int i = 0; i < 26; i++)
	{
		if (a[i] == num)
			return i;
	}
}
void Solve::printhe(WordList& wordlist)
{
	char c = ' ';
	if (m_Mode == LENGTH) max_num = m_FinalLen;
	cout << max_num << endl;
	for (int i = 0; i < 26; i++)
		cout << i << "   " << max_dfs[i] << endl;
	while (max_num > 0)
	{
		int id1 = get_max(max_dfs, max_num);
		//cout << id1 << endl;
		int id2;
		string next_word(wordlist.getWordAt(id1 + 'a', 'a' + id1,false));
		if (!next_word.empty())
		{
			int len;
			if (m_Mode == NUM)
				len = 2;
			else if(m_Mode = LENGTH)
			{
				len = next_word.size();
			}
			max_num -= len;
			if (m_Mode == LENGTH)
			{
				int mid = 0;
				for (int i = 0; i < 26; i++)
				{
					if (i == id1) continue;
					
					int lenth_cir = wordlist.getWordAt(id1 + 'a', 'a' + i, false).size();
					
					if (!wordlist.getWordAt(id1 + 'a', 'a' + i, false).empty() && (max_num - lenth_cir) == max_dfs[i])
					{
						mid = max_dfs[i];
					}
				}
				max_num = mid;
			}
			id2 = get_max(max_dfs, max_num);
			//cout << next_word << endl;
			
		}
		else
		{
			int len;
			if (m_Mode == NUM)
				len = 1;
			else if (m_Mode = LENGTH)
			{
				int mid = 0;
				for (int i = 0; i < 26; i++)
				{
					if (i == id1) continue;

					int lenth_cir = wordlist.getWordAt(id1 + 'a', 'a' + i, false).size();

					if (!wordlist.getWordAt(id1 + 'a', 'a' + i, false).empty() && (max_num - lenth_cir) == max_dfs[i])
					{
						mid = max_dfs[i];
					}
				}
				max_num = mid;
			}
			id2 = get_max(max_dfs, max_num -len );
			max_num -= len;
		}
			
		string next_word2(wordlist.getWordAt(id1 + 'a', 'a' + id2,false));
		if(id1 != id2)
			cout << next_word2 << endl;	
		c = next_word2[next_word2.size() - 1];
		if (c == m_ModeTail)
			break;
	}
}

void Solve::cmp_he()
{
	if (m_Mode == NUM)
	{
		if (max_num < temp_num)
			max_num = temp_num;
	}
	else if (m_Mode == LENGTH)
	{
		if (m_FinalLen < m_TemLen )
		{
			m_FinalLen = m_TemLen;
		}

	}
}

void Solve::Dfs_solvehe(WordList& wordlist, int c)
{
	int i,flag=0;
	int dis;
	for (i = 0; i < 26; i++)
	{
		string next_word(wordlist.getWordAt(c+ 'a', 'a' + i, false));
		if (!next_word.empty() && c==i)
		{
			flag = 1;
			if (m_Mode == NUM) dis = 1;
			if (m_Mode == LENGTH) dis = int(next_word.size());
			continue;
		}
		bool is_em = next_word.empty();
		if (is_em)
		{
			cmp_he();
		}
		else
		{
			int l1 = int(next_word.length());
			m_ihead[i] = 1;
			int distance = 0;
			if (m_Mode == NUM) distance = 1;
			if (m_Mode == LENGTH) distance = l1;
			if (max_dfs[i] !=-1)
			{
				/*
				if ((temp_num + 1 + max_dfs[i]) > max_num)
					max_num = temp_num + 1 + max_dfs[i];
					*/
				temp_num += 1 + max_dfs[i];
				m_TemLen += l1 + max_dfs[i];
				cmp_he();
				temp_num -= (1 + max_dfs[i]);
				m_TemLen -= (l1 + max_dfs[i]);
				if (max_dfs[c] < (max_dfs[i] + distance))
				{
					max_dfs[c] = max_dfs[i] + distance;
				}
				continue;
			}
			temp_num += 1;
			m_TemLen += l1;
			Dfs_solvehe(wordlist, i);

			if (max_dfs[i] == -1)
				max_dfs[i] = 0;
			if (max_dfs[c] < (max_dfs[i] + distance))
			{
				max_dfs[c] = max_dfs[i] + distance;
			}
			m_TemLen -= l1;
			temp_num -= 1;
			m_ihead[i] = 0;
		}
	}
	if (max_dfs[c] == -1) max_dfs[c] = 0;
	if (flag == 1)
	{
		max_num += 1;
		m_FinalLen += dis;
		max_dfs[c] += dis;
	}
}

void Solve::solve_he(WordList& wordlist)
{
	int i;
	head = m_ModeHead - 'a';
	m_ihead[head] = 1;
	Dfs_solvehe(wordlist, head);
	m_ihead[head] = 0;
	printhe(wordlist);
}

void Solve::printChain()
{
	if (is_circle)
	{
		cout << "the input has a circle\n" << endl;
	}
	else
	{
		for (int i = 0; i < int(m_FinalChain.size()); i++)
		{
			cout << m_FinalChain.at(i) << "\n";
		}
	}
}
void Solve::cmp()
{
	if (m_Mode == NUM)
	{
		if (m_FinalChain.size() < m_TempChain.size())
		{
			m_FinalChain.clear();
			m_FinalChain.assign(m_TempChain.begin(), m_TempChain.end());
		}
	}
	else if (m_Mode == LENGTH)
	{
		if (m_FinalLen < m_TemLen)
		{
			m_FinalChain.clear();
			m_FinalChain.assign(m_TempChain.begin(), m_TempChain.end());
			m_FinalLen = m_TemLen;
		}

	}
}
void Solve::Dfs_solve1(WordList& wordlist, char c)
{
	if (is_circle == 1) return;
	int i;
	for (i = 0; i < 26; i++)
	{
		string next_word(wordlist.getWordAt(c, 'a' + i));

		if (next_word.empty() && !(m_ModeTail != '&' && m_ModeTail != c))
		{
			cmp();
		}
		else if (!next_word.empty())
		{
			int l1 = int(next_word.length());
			if (!m_ModeRing && m_ihead[i] == 1 && ((c - 'a') != i || ((c - 'a') == i && m_iSigned[i][i] == 1)))
			{
				is_circle = 1;
				return;
			}
			m_iSigned[c - 'a'][i] = 1;
			m_TempChain.push_back(next_word);
			m_TemLen += l1;
			m_ihead[i] = 1;
			Dfs_solve1(wordlist, 'a' + i);
			m_ihead[i] = 0;
			m_TemLen -= l1;
			m_TempChain.pop_back();
			wordlist.undoGetWordAt(c, 'a' + i);
			m_iSigned[c - 'a'][i] = 0;
		}
	}
}
void Solve::Solve1(WordList& wordlist, bool is_ring)
{
	int i;
	m_ModeRing = is_ring;
	if (m_ModeHead == '&')
	{
		for (i = 0; i < 26; i++)
		{
			m_ihead[i] = 1;
			Dfs_solve1(wordlist, 'a' + i);
			m_ihead[i] = 0;
		}
	}
	else
	{
		m_ihead[m_ModeHead - 'a'] = 1;
		Dfs_solve1(wordlist, m_ModeHead);
		m_ihead[m_ModeHead - 'a'] = 0;
	}
	printChain();
}
