#include <stdio.h>

void inputScores(int scores[100], int num) {
    for (int i = 0; i < num; i++) {
        scanf("%d", &scores[i]);
    }
    // return scores[100];
}
void printScores(int scores[100], int num) {
    printf("Scores: ");
    for (int i = 0; i < num; i++) { 
        printf("%d ", scores[i]);
    }
    printf("\n");
}
int findMaxScore(int scores[100], int num) {
    int max = scores[0];
    for (int i = 0; i < num; i++) {
        if (max < scores[i]) {
            max = scores[i];
        }
    }
    return max;
}
int findMinScore(int scores[100], int num) {
    int min = scores[0];
    for (int i = 0; i < num; i++) {
        if (min > scores[i]) {
            min = scores[i];
        }
    }
    return min;
}

int main() {
    int num;
    printf("Enter the number of scores (up to 100): ");
    scanf("%d", &num);
    printf("Enter %d scores:\n", num);
    int scores[100] = { 0 };
    
    inputScores(scores, num);
    // scores[100] = inputScores(scores, num);
    
    printf("\n");

    printScores(scores, num);

    printf("Highest score: %d\n", findMaxScore(scores, num));
    printf("Lowest score: %d\n", findMinScore(scores, num));
}