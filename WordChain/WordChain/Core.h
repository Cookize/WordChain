#ifndef __CORE_H_
#define __CORE_H_
#include "WordList.h"
#include "Solve.h"
#include "DPSolve.h"
#include <string>
#include <vector>

using namespace std;

class Core
{
public:
	bool gen_chain_word(vector<string> &words, vector<string> &output, char head, char tail, bool enable_loop);
	bool gen_chain_char(vector<string> &words, vector<string> &output, char head, char tail, bool enable_loop);

private:
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
};
#endif // !__CORE_H_

