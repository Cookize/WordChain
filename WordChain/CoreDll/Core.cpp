#define CoreDll
#include "stdafx.h"
#include "Core.h"
#include <string.h>

int Core::gen_chain_word(vector<string> &words, vector<string> &output, char head, char tail, bool enable_loop)
{
	wordList = new WordList();
	dpSolve = new DPSolve(wordList, 'w', head, tail);
	int t_iLength = int(words.size());
	for (int i = 0; i < t_iLength; i++)
	{
		wordList->parseString(words[i]);

	}
	if (!enable_loop && !dpSolve->topoSort())
	{
		return -1;
	}

	if (enable_loop)
	{
		if (head != 0 && tail != 0) {
			solve = new Solve('w', head, tail);
		}
		else if (head != 0)
		{
			solve = new Solve('w', head, true);
		}
		else if (tail != 0)
		{
			solve = new Solve('w', tail, false);
		}
		else
		{
			solve = new Solve('w');
		}
		solve->Solve1(*wordList,true,output);
	}
	else if (head != 0 && tail != 0)
	{
		solve = new Solve('w', head, tail);
		solve->solve_he(*wordList,output);
	}
	else
	{
		dpSolve->startDPSolve();
		dpSolve->getWordChain(output);
	}
	if (output.size() <= 1)
	{
		return -2;
	}
	return 0;
}

int Core::gen_chain_char(vector<string> &words, vector<string> &output, char head, char tail, bool enable_loop)
{
	wordList = new WordList();
	dpSolve = new DPSolve(wordList, 'c', head, tail);
	int t_iLength = int(words.size());
	for (int i = 0; i < t_iLength; i++)
	{
		wordList->parseString(words[i]);
	}
	//wordList->showAllWord();
	// 判断环
	if (!enable_loop && !dpSolve->topoSort())
	{
		return -1;
	}
	if (enable_loop)
	{
		if (head != 0 && tail != 0) {
			solve = new Solve('c', head, tail);
		}
		else if (head != 0)
		{
			solve = new Solve('c', head, true);
		}
		else if (tail != 0)
		{
			solve = new Solve('c', tail, false);
		}
		else
		{
			solve = new Solve('c');
		}
		solve->Solve1(*wordList, true, output);
	}
	else if (head != 0 && tail != 0)
	{
		solve = new Solve('c', head, tail);
		solve->solve_he(*wordList, output);
	}
	else
	{
		dpSolve->startDPSolve();
		dpSolve->getWordChain(output);
	}
	if (output.size() <= 1)
	{
		return -2;
	}
	return 0;
}

int Solve::get_max(WordList& wordlist, int * a, int num, char c)
{
	for (int i = 0; i < 26; i++)
	{
		if (a[i] == num && (c == '&' || !wordlist.getWordAt(c, 'a' + i, false).empty()))
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
		int id1 = get_max(wordlist, max_dfs, max_num, '&');
		int id2;
		string next_word(wordlist.getWordAt(id1 + 'a', 'a' + id1, false));
		if (!next_word.empty())
		{
			int len = 0;
			if (m_Mode == NUM)
				len = 2;
			else if (m_Mode == LENGTH)
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
			id2 = get_max(wordlist, max_dfs, max_num, 'a' + id1);
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
			id2 = get_max(wordlist, max_dfs, max_num - len, 'a' + id1);
			max_num -= len;
		}

		string next_word2(wordlist.getWordAt(id1 + 'a', 'a' + id2, false));
		if (id1 != id2 && !next_word2.empty())
		{
			output.push_back(next_word2);
		}
		c = next_word2[next_word2.size() - 1];
		if (c == m_ModeTail)
		{
			string next_word(wordlist.getWordAt(c, c, false));
			if (!next_word.empty())
			{
				output.push_back(next_word);
			}

			break;
		}
	}
	if (output.size() > 0)
	{
		if (m_ModeTail != '&' && output[output.size() - 1][output[output.size() - 1].length() - 1] != m_ModeTail)
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
		if (m_FinalLen < m_TemLen)
		{
			m_FinalLen = m_TemLen;
		}

	}
}

void Solve::Dfs_solvehe(WordList& wordlist, int c)
{
	int i, flag = 0;
	int dis;
	for (i = 0; i < 26; i++)
	{
		string next_word(wordlist.getWordAt(c + 'a', 'a' + i, false));
		if (!next_word.empty() && c == i)
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
			if (max_dfs[i] != -1)
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
	printhe(wordlist, output);
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
		if (m_iSigned[c - 'a'][i] == 1)
		{
			if (m_ModeTail != '&' || (m_ModeTail != '&' && m_ModeTail == c))
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
		else if (m_iSigned[c - 'a'][i] == 0)
		{
			int l1 = int(word->m_list[a][word->m_iListGetPoint[a]].length());
			m_iSigned[c - 'a'][i] = 1;
			m_TempChain.push_back(word->m_list[a][word->m_iListGetPoint[a]]);
			temp_num += 1;
			m_TemLen += l1;
			word->m_iListGetPoint[a]++;
			Dfs_solve1(wordlist, 'a' + i);
			word->m_iListGetPoint[a]--;
			m_TemLen -= l1;
			temp_num -= 1;
			m_TempChain.pop_back();
			m_iSigned[c - 'a'][i] = 0;
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

int DPSolve::DPStep(int indexH)
{
	if (m_iArrayDp[indexH] >= 0)					// 已有子问题最优解
	{
		return m_iArrayDp[indexH];
	}
	for (int indexT = 0; indexT < SUM_ALPH; indexT++)// 计算子问题最优解
	{
		int t_iRemaining = m_ptrWordList->getWordSumAt(Index2char(indexH), Index2char(indexT));
		if (t_iRemaining > 0)
		{
			int temp = m_cMode == 'c' ?
				int(m_ptrWordList->getWordAt(Index2char(indexH), Index2char(indexT), false).length()) : 1;
			if (indexH == indexT && t_iRemaining == 1)	// 允许有一个首尾相同的单词
			{
				temp += m_cMode == 'c' ?
					int(m_ptrWordList->getWordAt(Index2char(indexH), Index2char(indexH), false).length()) : 1;
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
		int t_iRemaining = m_ptrWordList->getWordSumAt(Index2char(indexH), Index2char(indexT));
		if (t_iRemaining > 0)
		{
			int temp = m_cMode == 'c' ?
				int(m_ptrWordList->getWordAt(Index2char(indexH), Index2char(indexT), false).length()) : 1;
			if (indexH == indexT && t_iRemaining == 1)	// 允许有一个首尾相同的单词
			{
				temp += m_cMode == 'c' ?
					int(m_ptrWordList->getWordAt(Index2char(indexT), Index2char(indexT), false).length()) : 1;
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

int DPSolve::DPStepLimited(int indexH)
{
	if (m_iArrayDp[indexH] >= 0)					// 已有子问题最优解
	{
		return m_iArrayDp[indexH];
	}
	for (int indexT = 0; indexT < SUM_ALPH; indexT++)// 计算子问题最优解
	{
		int t_iRemaining = m_ptrWordList->getWordSumAt(Index2char(indexH), Index2char(indexT));
		if (t_iRemaining > 0)
		{
			int temp = m_cMode == 'c' ?
				int(m_ptrWordList->getWordAt(Index2char(indexH), Index2char(indexT), false).length()) : 1;
			if (indexH == indexT && t_iRemaining == 1)	// 允许有一个首尾相同的单词
			{
				temp += m_cMode == 'c' ?
					int(m_ptrWordList->getWordAt(Index2char(indexH), Index2char(indexH), false).length()) : 1;
				continue;
			}
			temp += DPStep(indexT);
			if (m_iArrayDp[indexH] < temp
				&& (temp < m_iMaxLength || (temp == m_iMaxLength && indexT != Char2index(m_cModeTail))))			// 比较是否为最长
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
	int t_iMaxIndex = 0;
	// 判断是否限定开头或结尾
	if (m_cModeHead != 0 && m_cModeTail != 0)	// 限定开头和结尾
	{
		int indexT;
		do
		{
			t_iMaxIndex = Char2index(m_cModeHead);
			DPStepLimited(t_iMaxIndex);
			m_iMaxLength = m_iArrayDp[t_iMaxIndex];
			for (indexT = m_iArrayDp[t_iMaxIndex]; m_iArrayNext[indexT] != -1; indexT = m_iArrayDp[indexT])
			{

			}
		} while (indexT != Char2index(m_cModeTail));
		genChain(t_iMaxIndex, true);
	}
	if (m_cModeHead != 0)							// 仅限定开头
	{
		t_iMaxIndex = Char2index(m_cModeHead);
		DPStep(t_iMaxIndex);
		genChain(t_iMaxIndex, true);
	}
	else if (m_cModeTail != 0)						// 限定结尾
	{
		t_iMaxIndex = Char2index(m_cModeTail);
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
		if (m_ptrWordList->getWordSumAt(Index2char(index), Index2char(index)) > 0)
		{
			m_strVecWordChain.push_back(m_ptrWordList->getWordAt(Index2char(index), Index2char(index)));
		}
		while (m_iArrayNext[index] != -1)
		{
			m_strVecWordChain.push_back(m_ptrWordList->getWordAt(Index2char(index), Index2char(m_iArrayNext[index])));
			index = m_iArrayNext[index];
			if (m_ptrWordList->getWordSumAt(Index2char(index), Index2char(index)) > 0)
			{
				m_strVecWordChain.push_back(m_ptrWordList->getWordAt(Index2char(index), Index2char(index)));
			}
		}
	}
	else
	{
		if (m_ptrWordList->getWordSumAt(Index2char(index), Index2char(index)) > 0)
		{
			m_strVecWordChain.insert(m_strVecWordChain.begin(), m_ptrWordList->getWordAt(Index2char(index), Index2char(index)));
		}
		while (m_iArrayBefore[index] != -1)
		{
			m_strVecWordChain.insert(m_strVecWordChain.begin(), m_ptrWordList->getWordAt(m_iArrayBefore[index] + 'a', Index2char(index)));
			index = m_iArrayBefore[index];
			if (m_ptrWordList->getWordSumAt(Index2char(index), Index2char(index)) > 0)
			{
				m_strVecWordChain.insert(m_strVecWordChain.begin(), m_ptrWordList->getWordAt(Index2char(index), Index2char(index)));
			}
		}
	}

}

bool isAlph(const char _c)
{
	return (_c >= 'a' && _c <= 'z') || (_c >= 'A' && _c <= 'Z');
}

void toLower(string &_str)
{
	size_t length(_str.length());
	for (size_t i = 0; i < length; i++)
	{
		if (_str[i] >= 'A' && _str[i] <= 'Z')
		{
			_str[i] += 'a' - 'A';
		}
	}
}

void WordList::addWord(const string &_word)
{
	string t_strNewWord(_word);
	toLower(t_strNewWord);
	size_t t_iWordLength(t_strNewWord.length());
	int t_iIndexH = t_strNewWord[0] - 'a';
	int t_iIndexT = t_strNewWord[t_iWordLength - 1] - 'a';
	int t_iIndex(t_iIndexH * 26 + t_iIndexT);

	if ((m_iArryMatrix[t_iIndexH] >> t_iIndexT) % 2 == 0)			// 更新邻接矩阵和入度计数器
	{
		if (t_iIndexH != t_iIndexT)
		{
			m_iArrayNodeIn[t_iIndexT]++;
		}
		m_iArryMatrix[t_iIndexH] |= (1 << t_iIndexT);
	}
	else if (t_iIndexH == t_iIndexT)								// 过滤一次首位相同的单词
	{
		m_iArrayNodeIn[t_iIndexT]++;
	}
	m_iArrayNodeOut[t_iIndexH]++;

	for (int i = 0; i < m_iListSize[t_iIndex]; i++)
	{
		if (m_words->m_list[t_iIndex][i] == t_strNewWord)
		{
			return;
		}
		if (m_words->m_list[t_iIndex][i].length() < t_iWordLength)
		{
			m_words->m_list[t_iIndex].insert(m_words->m_list[t_iIndex].begin() + i, t_strNewWord);
			m_iListSize[t_iIndex]++;
			return;
		}
	}
	m_words->m_list[t_iIndex].push_back(t_strNewWord);
	m_iListSize[t_iIndex]++;
}

void WordList::parseString(const string &_str)
{
	size_t t_iStrLength(_str.length());
	size_t i, j;
	for (i = j = 0; i <= t_iStrLength; i++)
	{
		if (i == t_iStrLength || !isAlph(_str[i]))
		{
			if (i > j)
			{
				string t_strNewWord(_str, j, i - j);
				addWord(t_strNewWord);
			}
			j = i + 1;
		}
	}
}

string WordList::getWordAt(char _c1, char _c2, bool _ifDelete)
{
	int t_iIndex((_c1 - 'a') * 26 + _c2 - 'a');
	if (m_words->m_list[t_iIndex].size() == 0)
		return "";
	return m_words->m_list[t_iIndex][0];
}

string WordList::getWordAt(char _c1, char _c2)
{
	return getWordAt(_c1, _c2, true);
}

int WordList::getWordSumAt(char _c1, char _c2)
{
	int t_iIndex((_c1 - 'a') * 26 + _c2 - 'a');
	if (t_iIndex < 0 || t_iIndex > SUM_ALPH_2)
	{
		return 0;
	}
	return m_iListSize[t_iIndex];
}

bool checkChar(char &c)
{
	if (c >= 'a' && c <= 'z')
	{
		return true;
	}
	if (c >= 'A' && c <= 'Z')
	{
		c += 'a' - 'A';
		return true;
	}
	if (c == 0)
	{
		return true;
	}
	return false;
}

int gen_chain_word(char* words[], int len, char* output[], char head, char tail, bool enable_loop)
{
	if (!checkChar(head)) return -1;			// 抛出首尾字母异常
	if (!checkChar(tail)) return -2;
	int ret = 0;
	Core *core = new Core;
	vector<string> *list = new vector <string>;
	vector<string> *outputList = new vector <string>;
	for (int i = 0; i < len; i++)
	{
		if (words[i] == NULL)
		{
			delete core;
			return -3;							// 抛出输入单词错误
		}
		string newWords(words[i]);
		list->push_back(newWords);
	}
	if ((ret = core->gen_chain_word(*list, *outputList, head, tail, enable_loop)) != 0)
	{
		delete core;
		if (ret == -1)
		{
			return -4;									// 抛出无环情况有环异常
		}
		else if (ret == -2)
		{
			return -5;						// 抛出未找到环
		}
		else
		{
			return -6;
		}
		return ret;
	}

	int length = int(outputList->size());

	for (int i = 0; i < length; i++)
	{
		int len = int((*outputList)[i].length());
		output[i] = new char[len + 1];
		strcpy_s(output[i], len + 1, (*outputList)[i].c_str());
	}
	delete core;
	core = NULL;
	return length;
}

int gen_chain_char(char* words[], int len, char*output[], char head, char tail, bool enable_loop)
{
	if (!checkChar(head)) return -1;			// 抛出首尾字母异常
	if (!checkChar(tail)) return -2;
	int ret = 0;
	Core *core = new Core;
	vector<string> *list = new vector <string>;
	vector<string> *outputList = new vector <string>;
	for (int i = 0; i < len; i++)
	{
		if (words[i] == NULL)
		{
			delete core;
			return -3;							// 抛出输入单词错误
		}
		string newWords(words[i]);
		list->push_back(newWords);
	}
	if ((ret = core->gen_chain_char(*list, *outputList, head, tail, enable_loop)) != 0)
	{
		delete core;
		if (ret == -1)
		{
			return -4;									// 抛出无环情况有环异常
		}
		else if (ret == -2)
		{
			return -5;						// 抛出未找到环
		}
		else
		{
			return -6;
		}
		return ret;
	}

	int length = int(outputList->size());
	for (int i = 0; i < length; i++)
	{
		int len = int((*outputList)[i].length());
		output[i] = new char[len + 1];
		strcpy_s(output[i], len + 1, (*outputList)[i].c_str());
	}
	delete core;
	core = NULL;
	return length;
}