#include <fstream>
#include <iostream>
#include <vector>
#include "Main.h"
#include "Core.h"

using namespace std;

int main(int argc, char** argv)
{
	string addrIn("test.txt");
	ifstream fileIn(addrIn);
	vector<string> *lines = new vector<string>();
	vector<string> *chain = new vector<string>();
	Core *core = new Core();
	if (!fileIn.is_open())
	{
		cout << "ERROR:Illegal Input File!" << endl;
		return -1;
	}
	while (!fileIn.eof())
	{
		string strLine;
		fileIn >> strLine;
		lines->push_back(strLine);
	}
	fileIn.close();


	core->gen_chain_word(*lines, *chain, 0, 0, false);


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
