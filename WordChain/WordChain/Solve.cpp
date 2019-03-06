#include "Solve.h"
#include <iostream>

using namespace std;

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
		if (m_FinalLen < m_TemLen )
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
		
		if (next_word.empty() && !(m_ModeTail!='&' && m_ModeTail !=c))
		{
			cmp();
		}
		else if(!next_word.empty())
		{
			int l1 = int(next_word.length());
			if (!m_ModeRing && m_ihead[i] == 1 && ((c - 'a') != i || ((c-'a') == i && m_iSigned[i][i] == 1)))
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
void Solve::Solve1(WordList& wordlist,bool is_ring)
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
