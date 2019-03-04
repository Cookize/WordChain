#include <fstream>
#include <iostream>
#include "Main.h"
#include "WordList.h"

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
	delete WORDLIST;
	WORDLIST = NULL;
	return 0;
}