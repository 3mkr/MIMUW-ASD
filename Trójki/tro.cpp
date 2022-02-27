#include <iostream>
#include <cstdio>
#include <queue>
#include <vector>

/*
 * In this task, given set A = a1...an, where each element ai is an integer
 * and 1 <= ai <= 10, we must find:
 * f(A) = |{(i, j, k): 1 <= i < j < k <= n && ai + aj = ak}|
 */

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    
    int n, temp;
    long long count = 0;
    scanf("%d", &n);
    
    long long values[11] = {0}, possible_sum[11] = {0};
    
    for (int i = 0; i < n; ++i) {
        scanf("%d", &temp);
        for (int j = 1; j < 11; ++j) {
            int temp_sum = j + temp;
            if (temp_sum <= 10)
                possible_sum[temp_sum] += values[j];
        }
        
        ++values[temp];
        
        count += possible_sum[temp];
    }
    
    std::cout << count << '\n';
    
    return 0;
}
