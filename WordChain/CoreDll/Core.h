#ifndef __CORE_H_
#define __CORE_H_

#ifdef CoreDll
#define COREAPI _declspec(dllexport)
#else
#define COREAPI _declspec(dllimport)
#endif
#define LENGTH 'c'
#define NUM 'w'
#define SUM_ALPH		(26)
#define SUM_ALPH_2		(676)
#define Index2char(x)	(x + 'a')
#define Char2index(x)	(x - 'a')
#include <string>
#include <vector>
#include <queue>

using namespace std;

typedef struct
{
	vector<string> m_list[SUM_ALPH_2 + 1];
	int m_iListGetPoint[SUM_ALPH_2 + 1] = { 0 };
}WORDD;

/*
	类名：
		字典
	功能：
		1.解析字符串，提取“单词”并将新单词加入词典。
		2.提供“首尾字母”相关的查询功能。
		3.提供单词表打印功能。
	注意：
		1.不区分大小写。
*/
class  WordList
{
public:
	WordList()
	{
		m_iListSize = new int[SUM_ALPH_2 + 1];
		m_words = new WORDD();
		for (int i = 0; i < 26; i++)
		{
			m_iArrayNodeIn[i] = 0;
			m_iArryMatrix[i] = 0;
			m_iArrayNodeOut[i] = 0;
		}
		for (int i = 0; i < SUM_ALPH_2 + 1; i++)
		{
			m_iListSize[i] = 0;
			m_words->m_iListGetPoint[i] = 0;
		}
	}
	~WordList()
	{
		delete m_iListSize;
		delete m_words;
		m_words = NULL;
		m_iListSize = NULL;
	}

	/*
		方法：
			解析字符串，提取单词。
		输入：
			_str：需要解析的字符串。
		输出：
			无
		效果：
			在字典中增加新识别的单词。
	*/
	void parseString(const string &_str);

	/*
		方法：
			获取符合首尾条件的单词。
		输入：
			_c1：首字母；
			_c2：尾字母；
		输出：
			若存在符合首尾条件的单词，返回最长的单词；
			若不存在，返回NULL。
		注意：
			连续获取时会按照长度由长至短的顺序返回单词。

	*/
	string getWordAt(char _c1, char _c2);
	string getWordAt(char _c1, char _c2, bool _ifDelete);

	/*
		方法：
			获取符合首尾条件的单词“总”数量。
		输入：
			_c1：首字母；
			_c2：尾字母；
		输出：
			符合首尾条件的单词总数量。

	*/
	int getWordSumAt(char _c1, char _c2);

	int getNodeIn(int _index)
	{
		return m_iArrayNodeIn[_index];
	}

	int getNodeOut(int _index)
	{
		return m_iArrayNodeIn[_index];
	}

	int getNodeNext(int _index)
	{
		return m_iArryMatrix[_index];
	}

	/*
		方法：
			字典打印。
		输入/输出：
			无
		效果：
			将字典内容格式化输出至文件“WordList.txt”
	*/
	void showAllWord();

	WORDD* getWordList()
	{
		return m_words;
	}

private:
	WORDD *m_words = NULL;

	int *m_iListSize = NULL;


	int m_iArryMatrix[26] = { 0 };		// 邻接矩阵
	int m_iArrayNodeIn[26] = { 0 };
	int m_iArrayNodeOut[26] = { 0 };

	void addWord(const string &_word);
};

class  Solve
{
public:
	Solve(char mode)
	{
		init();
		temp_num = 0;
		m_Mode = mode;
		m_ModeHead = '&';
		m_ModeTail = '&';
	}
	Solve(char mode, char c, bool is_head)
	{
		init();
		temp_num = 0;
		m_Mode = mode;
		if (is_head)
		{
			m_ModeHead = c;
			m_ModeTail = '&';
		}
		else
		{
			m_ModeHead = '&';
			m_ModeTail = c;
		}
	}
	Solve(char mode, char mode_head, char mode_tail)
	{
		init();
		temp_num = 0;
		m_Mode = mode;
		m_ModeHead = mode_head;
		m_ModeTail = mode_tail;
	}
	void Solve1(WordList & wordlist, bool is_ring, vector<string> &output);
	void solve_he(WordList& wordlist, vector<string> &outputc);


private:
	WORDD * word = NULL;
	int m_iSigned[26][26] = { 0 }; //问题一 记录 是字母是否使用
	int m_ihead[26] = { 0 };
	int m_ans[676][676] = { 0 }; //记录单词是否使用的变量
	int next_tag[26][26] = { 0 };
	int len_ans[26][26] = { 0 };
	int max_dfs[26] = { 0 };
	int go[26] = { 0 };
	int out[26] = { 0 };
	int final_dfs[26] = { 0 };
	int ahead[26] = { 0 };
	int m_FinalLen = 0;
	int m_TemLen = 0;
	int max_num = 0;
	int temp_num = 0;
	bool is_circle = 0; // 判断是否有环 
	int head = 0;
	char m_Mode = NUM;
	char m_ModeHead = '&';
	char m_ModeTail = '&';
	bool m_ModeRing = false;
	vector <string> m_FinalChain; //最终结果
	vector <string> m_TempChain;  // 当前路径
	void Dfs_solve1(WordList& wordlist, char c);
	void cmp();
	void cmp_he();
	void Dfs_solvehe(WordList& wordlist, int c);
	void printChain(vector<string> &output);
	void printhe(WordList& wordlist, vector<string> &output);
	int get_max(WordList& wordlist, int * a, int num, char c);
	void init()
	{
		is_circle = 0;
		m_ModeRing = false;
		m_FinalLen = 0;
		m_TemLen = 0;
		max_num = 0;
		temp_num = 0;
		for (int i = 0; i < 26; i++)
		{
			m_ihead[i] = 0;
			for (int j = 0; j < 26; j++)
			{
				m_iSigned[i][j] = 0;
				len_ans[i][j] = 0;
				max_dfs[i] = -1;
				ahead[i] = 0;
				final_dfs[i] = 0;
			}
		}

		for (int i = 0; i < 676; i++)
		{
			for (int j = 0; j < 676; j++)
			{
				m_ans[i][j] = 0;

			}
		}
	}
};

/*
	动态规划处理类
		较高效处理无环情况下的最长单词连搜索
*/
class  DPSolve
{
public:
	/*
		构造函数们
	*/
	DPSolve(WordList *_wordList, char _mode)
	{
		initPara();
		m_ptrWordList = _wordList;
		m_cMode = _mode;
		m_cModeHead = '&';
		m_cModeTail = '&';
	}
	DPSolve(WordList *_wordList, char _mode, char _c, bool _isHead)
	{
		initPara();
		m_ptrWordList = _wordList;
		m_cMode = _mode;
		m_cModeHead = _isHead ? _c : '&';
		m_cModeTail = _isHead ? '&' : _c;
	}
	DPSolve(WordList *_wordList, char _mode, char _head, char _tail)
	{
		initPara();
		m_ptrWordList = _wordList;
		m_cMode = _mode;
		m_cModeHead = _head;
		m_cModeTail = _tail;
	}

	/*
		启动函数
	*/
	void startDPSolve();

	/*
		拓扑排序，检查是否有环
	*/
	bool topoSort();

	/*
		获取单词链
	*/
	void getWordChain(vector<string> &output)
	{
		output.assign(m_strVecWordChain.begin(), m_strVecWordChain.end());
	}

private:
	// 单词表
	WordList *m_ptrWordList = NULL;

	// 标志位
	int  m_iMaxLength = 0;

	// 功能参数
	char m_cMode = 'w';
	char m_cModeHead = 0;
	char m_cModeTail = 0;

	// 计算结果
	int m_iArrayDp[SUM_ALPH] = { 0 };				// 存储以某字母开头的最长单词链长度
	int m_iArrayNext[SUM_ALPH] = { -1 };			// 存储以某字母开头的最长单词链
	int m_iArrayBefore[SUM_ALPH] = { -1 };
	queue<int> m_iQueueTopo;
	vector<string> m_strVecWordChain;

	// 初始化参数
	void initPara()
	{
		m_iMaxLength = 1000;
		for (int i = 0; i < SUM_ALPH; i++)
		{
			m_iArrayDp[i] = -1;
			m_iArrayNext[i] = -1;
			m_iArrayBefore[i] = -1;
		}
	}

	/*
		动态规划递归子函数
	*/
	int DPStep(int indexH);
	int DPStepRe(int indexH);
	int DPStepLimited(int indexH);

	/*
		生成单词链
	*/
	void genChain(int indexStart, bool flag);
};

class  Core
{
public:
	~Core()
	{
		if (wordList != NULL)
		{
			delete wordList;
			wordList = NULL;
		}
		if (dpSolve != NULL)
		{
			delete dpSolve;
			dpSolve = NULL;
		}
		if (solve != NULL)
		{
			delete solve;
			solve = NULL;
		}
	}
	int gen_chain_word(vector<string> &words, vector<string> &output, char head, char tail, bool enable_loop);
	int gen_chain_char(vector<string> &words, vector<string> &output, char head, char tail, bool enable_loop);

private:
	WordList *wordList = NULL;
	DPSolve *dpSolve = NULL;
	Solve *solve = NULL;
};

extern "C" COREAPI int gen_chain_word(char* words[], int len, char*output[], char head, char tail, bool enable_loop);
extern "C" COREAPI int gen_chain_char(char* words[], int len, char*output[], char head, char tail, bool enable_loop);
#endif // !__CORE_H_

