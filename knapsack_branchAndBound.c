#include <stdio.h>

typedef struct {
    int weight;
    int value;
} Item;

typedef struct {
    int level;
    int weight;
    int value;
    int bound;
} Node;

int N; //최대 개수
Item items[101];
int maxWeight = 0; //최대 무게
int maxValue = 0; // 최대 가치

int promising(Node node, int maxWeight) {
    if (node.weight >= maxWeight)
        return 0;

    int bound = node.value;
    int totalWeight = node.weight;
    int level = node.level + 1;

    while (level < N && totalWeight + items[level].weight <= maxWeight) {
        totalWeight += items[level].weight;
        bound += items[level].value;
        level++;
    }

    if (level < N)
        bound += (maxWeight - totalWeight) * items[level].value / items[level].weight;

    return bound > maxValue;
}

void knapsack() {
    Node current, new;
    current.level = -1;
    current.value = 0;
    current.weight = 0;

    int queueSize = 1;
    Node queue[1000];
    queue[0] = current;

    while (queueSize > 0) {
        current = queue[--queueSize];

        if (current.level == N - 1)
            continue;

        new.level = current.level + 1;
        new.weight = current.weight + items[new.level].weight;
        new.value = current.value + items[new.level].value;

        if (new.weight <= maxWeight && new.value > maxValue)
            maxValue = new.value;

        if (promising(new, maxWeight))
            queue[queueSize++] = new;

        new.weight = current.weight;
        new.value = current.value;

        if (promising(new, maxWeight))
            queue[queueSize++] = new;
    }
}

int main() {
    printf("물건의 개수를 입력하시오: ");
    scanf_s("%d", &N);

    printf("배낭의 최대 무게를 입력하시오: ");
    scanf_s("%d", &maxWeight);

    printf("물건의 무게와 가치를 입력하시오: \n");
    for (int i = 0; i < N; i++) {
        scanf_s("%d %d", &items[i].weight, &items[i].value);
    }

    knapsack();
    printf("최대 가치 합은 %d입니다.\n", maxValue);
}
