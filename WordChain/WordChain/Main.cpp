#include <fstream>
#include <iostream>
#include "Main.h"
#include "WordList.h"
#include "DPSolve.h"
#include "Solve.h"

using namespace std;

WordList *WORDLIST = new WordList();

int parseFile(string addr)
{
	ifstream file(addr);
	string strLine;
	if (!file.is_open())
	{
		cout << "ERROR:Illegal Input File!" << endl;
		return -1;
	}
	while (!file.eof())
	{
		file >> strLine;
		WORDLIST->parseString(strLine);
		strLine.clear();
	}
	return 0;
}

int main(int argc, char** argv)
{
	string path("test.txt");
	if (parseFile(path) == 0)
	{
		WORDLIST->showAllWord();
	}
	cout << "Load Finished......" << endl;
	cout << "Start Calculate......" << endl;

	DPSolve *dpSolve = new DPSolve(WORDLIST, 'w', 'c', false);
	dpSolve->startDPSolve();

	vector<string> ans(dpSolve->getWordChain());
	size_t length = ans.size();
	for (size_t i = 0; i < length; i++)
	{
		cout << ans[i] << endl;
	}

	delete dpSolve;
	dpSolve = NULL;

	//Solve *solve = new Solve('w');
	//solve->Solve1(*WORDLIST, false);
	//delete solve;
	delete WORDLIST;
	WORDLIST = NULL;
	return 0;
}
