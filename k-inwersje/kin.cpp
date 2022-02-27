#include <iostream>
#include <string>
#include <algorithm>
#include <math.h>
#include <stdio.h>

using namespace std;

#define MOD 1000000000

/* 
 * We count elements larger than a given element to the right of it,
 * calculating them with the weight depending on the result for the previous iteration.
 */
 
int count_right(long long tree[], int loc) {
    int sum = 0;
    while (loc != 1) {
        if (loc % 2 == 0)
            sum = (sum + tree[loc + 1]) % MOD;
        loc /= 2;
    }
    return sum;
}

int set_size(int n) {
    int i = 1;

    while (n - i > 0)
        i *= 2;

    return i;
}

int main() {

    int n, k;
    scanf("%d", &n);
    scanf("%d", &k);
    
    /* 
     * Respectively:
     * number of leaves in a tree, number of nodes in a tree,auxiliary variables
     */
    int leafs = set_size(n), treeSize = (leafs * 2) + 1 , temp, loc;
    
    /* 
     * Permutation from input
     */
    int perm[n];
    
    /*
     * Respectively:
     * tree used to count elements, result for the previous iteration, result for the current iteration
     */
    long long tree[treeSize], prev[n], current[n];    
    
    /*
     * Final result.
     */
    long long sum = 0;

    for (int i = 0; i < n; i++) {
        scanf("%d", &perm[i]);
        
        prev[i] = 1;
        current[i] = 0;
    }

    for (int l = 1; l < k; l++) {

        for (int i = 0; i < treeSize; i++) {
            tree[i] = 0;
        }

        for (int i = 0; i < n; i++) {
            temp = perm[i];
            loc = temp + leafs - 1;
            tree[loc] = prev[i];
            
            while (loc >= 1) {
                loc /= 2;
                tree[loc] = (tree[loc * 2] + tree[loc * 2 + 1]) % MOD;
            }
            current[i] = count_right(tree, temp + leafs - 1);
        }

        for (int i = 0; i < n; i++) {
            prev[i] = current[i];
        }
    }

    for (int i = 0; i < n; i++) {
        sum = (sum + current[i]) % MOD;
    }

    printf("%lld\n", sum);

    return 0;
}
