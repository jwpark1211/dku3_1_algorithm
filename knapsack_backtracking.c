#include <stdio.h>
#include <stdbool.h>

int maxWeight = 0;
int maxValue = 0;
int weights[101];
int values[101];

bool promising(int i, int value, int weight, int n, int maxWeight) {
    int j, k;
    int totweight;
    float bound;

    if (weight > maxWeight) {
        return false;
    }
    else {
        j = i + 1;
        bound = value;
        totweight = weight;
        while (j <= n && totweight + weights[j] <= maxWeight) {
            totweight += weights[j];
            bound += values[j];
            j++;
        }
        k = j;
        if (k <= n) {
            bound += (maxWeight - totweight) * values[k] / weights[k];
        }
        return bound > maxValue;
    }
}

void knapsack(int i, int value, int weight, int n) {
    if (weight <= maxWeight && value > maxValue) {
        maxValue = value;
    }
    if (promising(i, value, weight, n, maxWeight, weights, values)) {
        knapsack(i + 1, value + values[i + 1], weight + weights[i + 1], n);
        knapsack(i + 1, value, weight, n, weights, values);
    }
}

int main() {
    int n;

    printf("물건의 개수를 입력하시오: ");
    scanf_s("%d", &n);

    printf("배낭의 최대 무게를 입력하시오: ");
    scanf_s("%d", &maxWeight);

    printf("물건의 무게와 가치를 입력하시오: \n");
    for (int i = 0; i < n; i++) {
        scanf_s("%d %d", &weights[i], &values[i]);
    }

    knapsack(0, 0, 0, n);

    printf("최대 가치 합은 %d입니다.\n", maxValue);
    return 0;
}