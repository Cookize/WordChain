#include"DPSolve.h"

void DPSolve::startDPSolve(const WordList &wordList)
{
	if (dp[i] > 0) return dp[i];
	for (int j = 0; j < n; j++) { //遍历i的所有可达出边 
		if (wordList.) {
			int temp = DP(j) + map[i][j];//单独计算dp 
			if (dp[i] < temp) {//可以获得更长的路径 
				dp[i] = temp;
				next[i] = j; //保存i的后继顶点j 
			}
		}
	}
	return dp[i];
}