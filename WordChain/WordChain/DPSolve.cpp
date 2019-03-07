#include"DPSolve.h"

void DPSolve::startDPSolve(const WordList &wordList)
{
	if (dp[i] > 0) return dp[i];
	for (int j = 0; j < n; j++) { //����i�����пɴ���� 
		if (wordList.) {
			int temp = DP(j) + map[i][j];//��������dp 
			if (dp[i] < temp) {//���Ի�ø�����·�� 
				dp[i] = temp;
				next[i] = j; //����i�ĺ�̶���j 
			}
		}
	}
	return dp[i];
}