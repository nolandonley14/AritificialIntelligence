#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <cstdlib>
#include <cmath>
using namespace std;

int sumSquared(int N, int currentNum);

int main() {
    cout << sumSquared(6, 0) << endl;

    return 0;
}

int sumSquared(int N, int total) {
    if (N == 1) {
        return 1 + total;
    }
    else {
        int currentNumber = total + pow(N,2);
        return sumSquared(N-1, currentNumber);
    }
}
