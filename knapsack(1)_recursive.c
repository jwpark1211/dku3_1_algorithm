#include <stdio.h>
#include <stdlib.h>

// 기본 조건값
int n, W; //n = 물건의 개수, W = 최대 적재량
int wArray[101] = { 0 }; //무게배열, array[0] = 0 (루트값)
int vArray[101] = { 0 }; //가치배열, array[0] = 0 (루트값)
int V = 0; // 최대 Value값

void knapsack(int L, int vResult, int wResult) {
	if (wResult > W || L>n) {
		return;
	}
	else if (vResult > V && L == n) {
		V = vResult;
		return;
	}
	else {
		knapsack(L + 1, vResult + vArray[L+1], wResult + wArray[L+1]); //좌측 자식트리
		knapsack(L + 1, vResult, wResult); //우측 자식트리
	}
}

int main(void)
{ 
	scanf_s("%d %d", &n, &W);
	for (int i = 1; i <= n; i++) {
		scanf_s("%d", &wArray[i]);
		scanf_s("%d", &vArray[i]);
	}
	knapsack(0, 0, 0);
	printf("%d", V);
}