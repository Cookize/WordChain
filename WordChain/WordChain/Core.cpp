#include "Core.h"

bool Core::gen_chain_word(vector<string> &words, vector<string> &output, char head, char tail, bool enable_loop)
{
	if (!checkChar(head) || !checkChar(tail)) return false;
	wordList = new WordList();
	dpSolve = new DPSolve(wordList, 'w', head, tail);
	int t_iLength = words.size();
	for (int i = 0; i < t_iLength; i++)
	{
		wordList->parseString(words[i]);
	}
	//wordList->showAllWord();
	// ÅÐ¶Ï»·
	if (!enable_loop && !dpSolve->topoSort())
	{
		return false;
	}

	if (enable_loop)
	{
		solve = new Solve('w');
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
		return false;
	}
	return true;
}

bool Core::gen_chain_char(vector<string> &words, vector<string> &output, char head, char tail, bool enable_loop)
{
	if (!checkChar(head) || !checkChar(tail)) return false;
	wordList = new WordList();
	dpSolve = new DPSolve(wordList, 'c', head, tail);

	int t_iLength = words.size();
	for (int i = 0; i < t_iLength; i++)
	{
		wordList->parseString(words[i]);
	}
	//wordList->showAllWord();
	// ÅÐ¶Ï»·
	if (!enable_loop && !dpSolve->topoSort())
	{
		return false;
	}
	if (enable_loop)
	{
		solve = new Solve('c');
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
		return false;
	}
	return true;
}