#include <stdio.h>
#define MAX_ELEMENTS 100

int scores[MAX_ELEMENTS];

int get_max_score(int n) {
    int i, largest;
    largest = scores[0];
    for (i = 1; i < n; i++) {
        if (scores[i] > largest) {
            largest = scores[i];
        }
    }
    return largest;
}

int main() {
    int student = 10;

    for (int i = 0; i < student; i++) {
        scanf("%d", &scores[i]);
    }
    int largest = get_max_score(student);

    printf("%d", largest);
}