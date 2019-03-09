#include <fstream>
#include <iostream>
#include <vector>
#include "Main.h"
#include "Core.h"

using namespace std;

int main(int argc, char** argv)
{
	string addr("test.txt");
	ifstream file(addr);
	vector<string> *lines = new vector<string>();
	vector<string> *chain = new vector<string>();
	Core *core = new Core();
	if (!file.is_open())
	{
		cout << "ERROR:Illegal Input File!" << endl;
		return -1;
	}
	while (!file.eof())
	{
		string strLine;
		file >> strLine;
		lines->push_back(strLine);
	}
	core->gen_chain_word(*lines, *chain, 0, 0, false);

	

	return 0;
}
