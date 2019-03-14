#include "stdafx.h"
#include "CppUnitTest.h"
#include <Windows.h>
#include <string>

typedef int(*genChainWord)(char* words[], int len, char*output[], char head, char tail, bool enable_loop);typedef int(*genChainChar)(char* words[], int len, char*output[], char head, char tail, bool enable_loop);

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;

namespace DllTest
{		
	TEST_CLASS(UnitTest1)
	{
	public:

		HINSTANCE CoreDLL;
		genChainWord gen_chain_word;
		genChainChar gen_chain_char;

		TEST_METHOD_INITIALIZE(init)
		{
			CoreDLL = LoadLibrary(wstring(L"CoreDll.dll").c_str());			if (CoreDLL == NULL) {				Assert::AreEqual(1, 0);			}			genChainWord gen_chain_word = (genChainWord)GetProcAddress(CoreDLL, "gen_chain_word");			genChainChar gen_chain_char = (genChainChar)GetProcAddress(CoreDLL, "gen_chain_char");			if (gen_chain_word == NULL || gen_chain_char == NULL) {				Assert::AreEqual(1, 0);			}
		}
		TEST_METHOD_CLEANUP(cleanUp)
		{

		}
		
		TEST_METHOD(TestMethod1)
		{
			// TODO: 在此输入测试代码
		}

	};
}