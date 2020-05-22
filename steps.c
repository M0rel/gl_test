#include <stdio.h>
#include <stdlib.h>

int main(int argc, char const *argv[]) {
    int K = atoi(argv[2]);
    int N = atoi(argv[1]);
    K++;
    int steps = N % K ? N / K + 1 : N / K;
    printf("%d\n",steps);
    return 0;
}
