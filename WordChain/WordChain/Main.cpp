#include <fstream>
#include <iostream>
#include <vector>
#include <string.h>
#include "Main.h"
#include "Core.h"

using namespace std;

int paraFlag[] = { 0, 0, 0, 0};	// -w/-c, -h, -t, -r 
char head = 0;
char tail = 0;
string addrIn("");

bool handleArgv(int argc, char** argv)
{
	for (int i = 1; i < argc; i++)
	{
		if (strcmp("-w", argv[i]) == 0 && paraFlag[0] == 0)
		{
			paraFlag[0] = 1;
		}
		else if (strcmp("-c", argv[i]) == 0 && paraFlag[0] == 0)
		{
			paraFlag[0] = 2;
		}
		else if (strcmp("-r", argv[i]) == 0 && paraFlag[3] == 0)
		{
			paraFlag[3] = 1;
		}
		else if (strcmp("-h", argv[i]) == 0 && paraFlag[1] == 0)
		{
			paraFlag[1] = 1;
			i++;
			if (strlen(argv[i]) == 1 && (argv[i][0] >= 'a' && argv[i][0] <= 'z' || argv[i][0] >= 'A' && argv[i][0] <= 'Z'))
			{
				head = argv[i][0];
			}
			else
			{
				return false;
			}
		}
		else if (strcmp("-t", argv[i]) == 0 && paraFlag[2] == 0)
		{
			paraFlag[2] = 1;
			i++;
			if (strlen(argv[i]) == 1 && (argv[i][0] >= 'a' && argv[i][0] <= 'z' || argv[i][0] >= 'A' && argv[i][0] <= 'Z'))
			{
				tail = argv[i][0];
			}
			else
			{
				return false;
			}
		}
		else if (i == argc - 1) {
			string addr(argv[i]);
			addrIn = addrIn + addr;
		}
		else
		{
			return false;
		}
	}
	return true;
}

int main(int argc, char** argv)
{
	if (!handleArgv(argc, argv))
	{
		cout << "ERROR:Illegal Parameter!" << endl;
		return 0;
	}
	ifstream fileIn(addrIn);
	vector<string> *lines = new vector<string>();
	vector<string> *chain = new vector<string>();
	if (!fileIn.is_open())
	{
		cout << "ERROR:Illegal Input File!" << endl;
		return 0;
	}
	while (!fileIn.eof())
	{
		string strLine;
		fileIn >> strLine;
		lines->push_back(strLine);
	}
	fileIn.close();

	Core *core = new Core();
	if (paraFlag[0] == 2) {
		if (!core->gen_chain_char(*lines, *chain, head, tail, paraFlag[3] == 1))
		{
			cout << "ERROR!" << endl;
			return 0;
		}
	}
	else
	{
		if (!core->gen_chain_word(*lines, *chain, head, tail, paraFlag[3] == 1))
		{
			cout << "ERROR!" << endl;
			return 0;
		}
	}
	delete core;
	core = NULL;
	
	string addrOut("output.txt");
	ofstream fileOut(addrOut);
	int length = chain->size();
	if (!fileOut.is_open())
	{
		cout << "ERROR:Illegal Output File!" << endl;
		return -1;
	}
	for(int i = 0; i < length; i++)
	{
		fileOut << (*chain)[i] << endl;
	}
	fileOut.close();
	return 0;
}
