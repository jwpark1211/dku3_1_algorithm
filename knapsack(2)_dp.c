#include <stdio.h>
#include <stdlib.h>
#define max(x, y) (x) > (y) ? (x) : (y) 

int dp[100005];

int main(void)
{
	int n; // ������ ���� 
	int W; // �ִ� ���� ����
	int v; // ������ value
	int w; // ������ weight

	scanf_s("%d %d", &n, &W);

	for (int i = 0; i < n; i++) {
		scanf_s("%d %d", &w, &v);
		for (int j = W; j >= w; j--) {
			dp[j] = max(dp[j - w] + v, dp[j]);
		}
	}

	printf("%d", dp[W]);
}