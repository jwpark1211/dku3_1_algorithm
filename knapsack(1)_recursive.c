#include <stdio.h>
#include <stdlib.h>

// �⺻ ���ǰ�
int n, W; //n = ������ ����, W = �ִ� ���緮
int wArray[101] = { 0 }; //���Թ迭, array[0] = 0 (��Ʈ��)
int vArray[101] = { 0 }; //��ġ�迭, array[0] = 0 (��Ʈ��)
int V = 0; // �ִ� Value��

void knapsack(int L, int vResult, int wResult) {
	if (wResult > W || L>n) {
		return;
	}
	else if (vResult > V && L == n) {
		V = vResult;
		return;
	}
	else {
		knapsack(L + 1, vResult + vArray[L+1], wResult + wArray[L+1]); //���� �ڽ�Ʈ��
		knapsack(L + 1, vResult, wResult); //���� �ڽ�Ʈ��
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