#include <iostream>

void calculation(const int &d, int n, int &res) {
    res += d * n;
    n--;
    if (n != 0) {
        calculation(d,n,res);
    }
}
int main (int argc, char const *argv[]) {
    int N = atoi(argv[1]);
    int D = atoi(argv[2]);
    int res = 0;
    calculation(D,N,res);
    std::cout << res << endl;
    return 0;
}
