#include "Core.h"

bool Core::gen_chain_word(vector<string> &words, vector<string> &output, char head, char tail, bool enable_loop)
{
	WordList *wordList = new WordList();
	DPSolve *dpSolve = new DPSolve(wordList, 'w', head, tail);
	int t_iLength = words.size();
	for (int i = 0; i < t_iLength; i++)
	{
		wordList->parseString(words[i]);
	}
	wordList->showAllWord();
	// 判断环
	if (!enable_loop && !dpSolve->topoSort())
	{
		return false;
	}

	if (enable_loop)
	{
		Solve *solve = new Solve('w');
		solve->Solve1(*wordList,true,output);
		// TODO:格式化输出路径
		delete solve;
		solve = NULL;
	}
	else if (head != 0 && tail != 0)
	{
		// TODO:dfs
		Solve *solve = new Solve('w', head, tail);
		solve->solve_he(*wordList,output);
		 // TODO:格式化输出路径
		delete solve;
		solve = NULL;
	}
	else
	{
		dpSolve->startDPSolve();
		dpSolve->getWordChain(output);
		delete dpSolve;
		dpSolve = NULL;
	}
	return true;
}

bool Core::gen_chain_char(vector<string> &words, vector<string> &output, char head, char tail, bool enable_loop)
{
	WordList *wordList = new WordList();
	DPSolve *dpSolve = new DPSolve(wordList, 'c', head, tail);

	int t_iLength = words.size();
	for (int i = 0; i < t_iLength; i++)
	{
		wordList->parseString(words[i]);
	}
	wordList->showAllWord();
	// 判断环
	if (!enable_loop && !dpSolve->topoSort())
	{
		return false;
	}
	if (enable_loop)
	{
		Solve *solve = new Solve('c');
		solve->Solve1(*wordList, true, output);
		// TODO:格式化输出路径
		delete solve;
		solve = NULL;
	}
	else if (head != 0 && tail != 0)
	{
		// TODO:dfs
		Solve *solve = new Solve('c', head, tail);
		solve->solve_he(*wordList, output);
		// TODO:格式化输出路径
		delete solve;
		solve = NULL;
	}
	else
	{
		dpSolve->startDPSolve();
		dpSolve->getWordChain(output);
		delete dpSolve;
		dpSolve = NULL;
	}
	return true;
}