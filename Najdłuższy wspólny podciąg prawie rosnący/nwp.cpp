#include <iostream>

using namespace std;

/*
 * Given two sequences A = A1...An and B = B1...Bm and value c,
 * we must find length of the longest common subsequence C = C1...Cx,
 * such that for each i < j Ci <= Cj + c.
 * If the answer is greater then 20, the output is 20.
 */

int find_result(int A[], int n, int B[], int m, int c) {
    int lengths[m];
    int lefts, last;
    bool changeFlag;

    for (int i = 0; i < m; i++) {
        lengths[i] = 0;
    }

    for (int i = 0; i < n; i++) {
        lefts = 1;
        last = 0;
        changeFlag = false;

        for (int j = 0; j < m; j++) {
            changeFlag = false;
            if (A[i] == B[j]) {
                if (lefts > lengths[j]) {
                    lengths[j] = lefts;
                    changeFlag = true;
                }
            }
            if (lengths[j] > 0 && last < lengths[j]) {
                if (A[i] + c >= B[j] && changeFlag == false) {
                    lefts++;
                    last = lengths[j];
                }
            }
        }
    }

    int result = 0;

    for (int i = 0; i < m; i++) {
        if (lengths[i] > result)
           result = lengths[i];
    }

    if (result > 20)
        return 20;
    else
        return result;
}

int main() {
    int n, m, c;

    scanf("%d", &n);
    scanf("%d", &m);
    scanf("%d", &c);

    int A[n], B[m];

    for (int i = 0; i < n; i++) {
        scanf("%d", &A[i]);
    }

    for (int i = 0; i < m; i++) {
        scanf("%d", &B[i]);
    }

    printf("%d\n", find_result(A, n, B, m, c));

    return (0);
}
