#include <iostream>
#include <vector>

using namespace std;

/*
 * In this task we must find difference between the greatest and the smallest
 * value in given fragment of a 2D array.
 */

int set_size(int n) {
    int i = 1;

    while (n - i > 0)
        i *= 2;

    return i;
}

class SegmentTree2D {
    vector<vector<int>> stMax;
    vector<vector<int>> stMin;
    vector<vector<int>> mat;
    int m, n;

public:
    SegmentTree2D(vector<vector<int>> &matrix) {
        mat = matrix;
        m = mat.size();
        n = mat[0].size();
        int width = set_size(n), height = set_size(m);
        stMax.assign(2 * height, vector<int> (2 * width, 0));
        stMin.assign(2 * height, vector<int> (2 * width, 0));
        build2D(1, 0, m - 1);
    }

    void build(vector<int> &segTreeMax, vector<int> &segTreeMin,
                            vector<int> &ar, int index, int L, int R) {
        if (L == R) {
            segTreeMax[index] = ar[L];
            segTreeMin[index] = ar[L];
        }
        else {
            int mid = (L + R) / 2;
            build(segTreeMax, segTreeMin, ar, 2 * index, L, mid);
            build(segTreeMax, segTreeMin, ar, 2 * index + 1, mid + 1, R);
            segTreeMax[index] = max(segTreeMax[2 * index], segTreeMax[2 * index + 1]);
            segTreeMin[index] = min(segTreeMin[2 * index], segTreeMin[2 * index + 1]);
        }
    }

    int query(vector<int> &segTree, int index, int L, int R,
                    int queryL, int queryR, bool searchForMaxFlag) {
        if(queryL > R || queryR < L) {
            if (searchForMaxFlag)
                return -1;
            else
                return 1e9 + 1;
        }

        if (L >= queryL and R <= queryR) {
            if (searchForMaxFlag)
                return segTree[index];
            else
                return segTree[index];
        }

        int mid = (L + R) / 2;
        int left = query(segTree, 2 * index, L, mid, queryL, queryR, searchForMaxFlag);
        int right = query(segTree, 2 * index + 1, mid + 1, R, queryL, queryR, searchForMaxFlag);

        if(left == -1)
            return right;
        if(right == -1)
            return left;

        if (searchForMaxFlag)
            return max(left, right);
        else
            return min(left, right);
    }

    void build2D(int index, int L, int R) {
        if(L == R) {
            build(stMax[index], stMin[index], mat[L], 1, 0, n - 1);
        }
        else {
            int mid = (L + R) / 2;

            build2D(2 * index, L, mid);
            build2D(2 * index + 1, mid + 1, R);

            int stSize = stMax[index].size();
            for (int i = 0; i < stSize; ++i) {
                stMax[index][i] = max(stMax[2 * index][i], stMax[2 * index + 1][i]);
                stMin[index][i] = min(stMin[2 * index][i], stMin[2 * index + 1][i]);
            }
        }
    }

    int query2D(int index, int L, int R, int x1, int y1, int x2, int y2, bool searchForMaxFlag) {
        if(L > x2 || R < x1) {
            if (searchForMaxFlag)
                return -1;
            else
                return 1e9 + 1;
        }


        if(L >= x1 and R <= x2) {
            if (searchForMaxFlag)
                return query(stMax[index], 1, 0, n - 1, y1, y2, searchForMaxFlag);
            else
                return query(stMin[index], 1, 0, n - 1, y1, y2, searchForMaxFlag);
        }

        int mid = (L + R) / 2;

        int left = query2D(2 * index, L, mid, x1, y1, x2, y2, searchForMaxFlag);
        int right = query2D(2 * index + 1, mid + 1, R, x1, y1, x2, y2, searchForMaxFlag);

        if(left == -1)
            return right;
        if(right == -1)
            return left;

        if (searchForMaxFlag)
            return max(left, right);
        else
            return min(left, right);
    }

    int query(int x1, int y1, int x2, int y2, bool searchForMaxFlag) {
        return query2D(1, 0, m - 1, x1, y1, x2, y2, searchForMaxFlag);
    }
};

int main() {
    vector<vector<int>> matrix;

    int N, K, M;
    scanf("%d", &N);
    scanf("%d", &M);
    scanf("%d", &K);

    int temp;
    for (int i = 0; i < N; i++) {
        vector<int> v1;
        for (int j = 0; j < M; j++) {
            scanf("%d", &temp);
            v1.push_back(temp);
        }
        matrix.push_back(v1);
    }

    SegmentTree2D st(matrix);

    int x1, y1;
    int x2, y2;
    for (int i = 0; i < K; ++i) {
        scanf("%d", &x1);
        scanf("%d", &y1);
        scanf("%d", &x2);
        scanf("%d", &y2);

        printf("%d\n", st.query(x1, y1, x2, y2, true) - st.query(x1, y1, x2, y2, false));
    }
    return 0;
}
