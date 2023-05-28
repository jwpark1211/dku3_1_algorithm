#include <stdio.h>
#include <stdlib.h>
#define max(x, y) (x) > (y) ? (x) : (y) 

int dp[100005];

int main(void)
{
	int n; // 물건의 개수 
	int W; // 최대 적재 무게
	int v; // 물건의 value
	int w; // 물건의 weight

	scanf_s("%d %d", &n, &W);

	for (int i = 0; i < n; i++) {
		scanf_s("%d %d", &w, &v);
		for (int j = W; j >= w; j--) {
			dp[j] = max(dp[j - w] + v, dp[j]);
		}
	}

	printf("%d", dp[W]);
}