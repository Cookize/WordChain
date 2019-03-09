#include "Core.h"

int Core::gen_chain_word(vector<string> &words, vector<string> &output, char head, char tail, bool enable_loop)
{
	WordList *wordList = new WordList();
	int t_iLength = words.size();
	for (int i = 0; i < t_iLength; i++)
	{
		wordList->parseString(words[i]);
	}
	if (enable_loop)
	{
		// TODO:有环
	}
	else if (head != 0 && tail != 0)
	{
		// TODO:dfs
		Solve *solve = new Solve('w', head, tail);
		solve->Solve1(*wordList, true);
		 // TODO:格式化输出路径
		delete solve;
		solve = NULL;
	}
	else
	{
		DPSolve *dpSolve = new DPSolve(wordList, 'w', head, tail);
		dpSolve->startDPSolve();
		dpSolve->getWordChain(output);
		delete dpSolve;
		dpSolve = NULL;
	}
	return 0;
}

int Core::gen_chain_char(vector<string> &words, vector<string> &output, char head, char tail, bool enable_loop)
{
	WordList *wordList = new WordList();
	int t_iLength = words.size();
	for (int i = 0; i < t_iLength; i++)
	{
		wordList->parseString(words[i]);
	}
	if (enable_loop)
	{
		// TODO:有环
	}
	else if (head != 0 && tail != 0)
	{
		// TODO:dfs
		Solve *solve = new Solve('c', head, tail);
		solve->Solve1(*wordList, true);
		// TODO:格式化输出路径
		delete solve;
		solve = NULL;
	}
	else
	{
		DPSolve *dpSolve = new DPSolve(wordList, 'c', head, tail);
		dpSolve->startDPSolve();
		dpSolve->getWordChain(output);
		delete dpSolve;
		dpSolve = NULL;
	}
	return 0;
}