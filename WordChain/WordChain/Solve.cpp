#include "Solve.h"
#include <iostream>

using namespace std;
int Solve::get_max(WordList& wordlist,int * a,int num,char c)
{
	for (int i = 0; i < 26; i++)
	{
		if (a[i] == num && (c == '&'|| !wordlist.getWordAt(c, 'a' +i, false).empty()))
			return i;
	}
	return -1;
}
void Solve::printhe(WordList& wordlist, vector<string> &output)
{
	char c = ' ';
	if (m_Mode == LENGTH) max_num = m_FinalLen;

	while (max_num > 0)
	{
		int id1 = get_max(wordlist,max_dfs, max_num,'&');
		int id2;
		string next_word(wordlist.getWordAt(id1 + 'a', 'a' + id1,false));
		if (!next_word.empty())
		{
			int len = 0;
			if (m_Mode == NUM)
				len = 2;
			else if(m_Mode == LENGTH)
			{
				len = int(next_word.size());
			}
			max_num -= len;
			if (m_Mode == LENGTH)
			{
				int mid = 0;
				for (int i = 0; i < 26; i++)
				{
					if (i == id1) continue;
					
					int lenth_cir = int(wordlist.getWordAt(id1 + 'a', 'a' + i, false).size());
					
					if (!wordlist.getWordAt(id1 + 'a', 'a' + i, false).empty() && (max_num - lenth_cir) == max_dfs[i])
					{
						mid = max_dfs[i];
					}
				}
				max_num = mid;
			}
			id2 = get_max(wordlist,max_dfs, max_num,'a'+id1);
			output.push_back(next_word);
			
		}
		else
		{
			int len = 0;
			if (m_Mode == NUM)
				len = 1;
			else if (m_Mode == LENGTH)
			{
				int mid = 0;
				for (int i = 0; i < 26; i++)
				{
					if (i == id1) continue;

					int lenth_cir = int(wordlist.getWordAt(id1 + 'a', 'a' + i, false).size());

					if (!wordlist.getWordAt(id1 + 'a', 'a' + i, false).empty() && (max_num - lenth_cir) == max_dfs[i])
					{
						mid = max_dfs[i];
					}
				}
				len = max_num - mid;
				
			}
			id2 = get_max(wordlist,max_dfs, max_num -len,'a'+ id1);
			max_num -= len;
		}
			
		string next_word2(wordlist.getWordAt(id1 + 'a', 'a' + id2,false));
		if (id1 != id2 && !next_word2.empty())
		{
			output.push_back(next_word2);
		}
		c = next_word2[next_word2.size() - 1];
		if (c == m_ModeTail)
		{
			
			string next_word(wordlist.getWordAt(c,c, false));
			if (!next_word.empty())
			{
				output.push_back(next_word); 
			}

			break;
		}
	}
	if (output.size() > 0)
	{
		if (m_ModeTail != '&' && output[output.size() - 1][output[output.size() - 1].length() - 1] !=m_ModeTail)
		{
			output.clear();
		}
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

void Solve::solve_he(WordList& wordlist, vector<string> &output)
{
	head = m_ModeHead - 'a';
	m_ihead[head] = 1;
	Dfs_solvehe(wordlist, head);
	m_ihead[head] = 0;
	printhe(wordlist,output);
}

void Solve::printChain(vector<string> &output)
{
	if (m_FinalChain.size() <= 1)
	{
		//throw new string("Chain size must be greater than 1\n");
	}
	else
	{
		output.assign(m_FinalChain.begin(), m_FinalChain.end());
	}

}
void Solve::cmp()
{
	if (m_Mode == NUM)
	{
		if (max_num < temp_num)
		{
			max_num = temp_num;
			m_FinalChain.clear();
			int temp_out[26] = { 0 };
			for (int i = 0; i < temp_num; i++)
			{
				temp_out[m_TempChain[i][0] - 'a'] += 1;
				m_FinalChain.push_back(m_TempChain[i]);
				
			}
			for (int i = 0; i < 26; i++)
			{
				if (out[i] == temp_out[i])
					go[i] = 1;
			}
		}
	}
	else if (m_Mode == LENGTH)
	{
		if (m_FinalLen < m_TemLen)
		{
			m_FinalChain.clear();
			int temp_out[26] = { 0 };
			for (int i = 0; i < temp_num; i++)
			{
				temp_out[m_TempChain[i][0] - 'a'] += 1;
				m_FinalChain.push_back(m_TempChain[i]);

			}
			for (int i = 0; i < 26; i++)
			{
				if (out[i] == temp_out[i])
					go[i] = 1;
			}
			m_FinalLen = m_TemLen;
		}

	}
}
void Solve::Dfs_solve1(WordList& wordlist, char c)
{
	int i, j;
	if (next_tag[c - 'a'][0] == -1 || (m_ModeTail != '&' && m_ModeTail == c))
	{
		if (m_ModeTail != '&')
		{
			if (m_ModeTail == c)
			{
				cmp();


			}
		}
		else
		{
			cmp();
		}
	}
	for (j = 0; next_tag[c - 'a'][j] != -1; j++)
	{
		i = next_tag[c - 'a'][j];
		int a = (c - 'a') * 26 + i;
		
		if (word->m_iListGetPoint[a] >= int(word->m_list[a].size())) {
			if (m_ModeTail != '&')
			{
				if (m_ModeTail == c)
				{
					cmp();
				}
			}
			else
			{
				cmp();
			}
			continue;
		}
		if (word->m_flag[a][word->m_iListGetPoint[a]])
		{
			if (m_ModeTail != '&' || (m_ModeTail != '&' && m_ModeTail == c))
			{
				if (m_ModeTail ==c)
				{
					cmp();
				}
			}
			else
			{
				cmp();
			}
			
		}
		else if (!word->m_flag[a][word->m_iListGetPoint[a]])
		{
			int l1 = int(word->m_list[a][word->m_iListGetPoint[a]].length());
			//m_iSigned[c - 'a'][i] = 1;
			m_TempChain.push_back(word->m_list[a][word->m_iListGetPoint[a]]);
			word->m_flag[a][word->m_iListGetPoint[a]] = true;
			temp_num += 1;
			m_TemLen += l1;
			word->m_iListGetPoint[a]++;
			Dfs_solve1(wordlist, 'a' + i);
			word->m_iListGetPoint[a]--;
			word->m_flag[a][word->m_iListGetPoint[a]] = false;
			m_TemLen -= l1;
			temp_num -= 1;
			m_TempChain.pop_back();
			//m_iSigned[c - 'a'][i] = 0;
		}
	}
}
void Solve::Solve1(WordList& wordlist, bool is_ring, vector<string> &output)
{
	int i;
	word = wordlist.getWordList();
	for (i = 0; i < 26; i++)
	{
		out[i] = wordlist.getNodeOut(i);
	}
	m_ModeRing = is_ring;
	for (int i = 0; i < 26; i++)
	{
		int k = 0;
		for (int j = 0; j < 26; j++)
		{
			int id = (i * 26) + j;
			if (word->m_list[id].size() == 0)
				continue;
			next_tag[i][k++] = j;
		
		}
		next_tag[i][k] = -1;
	}
	if (m_ModeHead == '&')
	{
		for (i = 0; i < 26; i++)
		{
			if (go[i] == 1) continue;
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
	printChain(output);

}
