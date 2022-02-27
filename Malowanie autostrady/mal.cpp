#include <iostream>
#include <stdio.h>

using namespace std;

#define MAXD 8000001
#define WHITE 1
#define BLACK -1
#define MIXED 0

/*
 * Respectively:
 * colours of individual nodes, number of white road sections in a given sub-tree
 */
int tree[MAXD], sum[MAXD];
long n, m, leafs;

int set_size(int n) {
    int i = 1;

    while (n - i > 0)
        i *= 2;

    return i;
}

void reset_tree() {
    for (int i = 0; i < 2 * leafs + 1; i++) {
        tree[i] = BLACK;
        sum[i] = 0;
    }
}

void unpack_subtree(int v) {

    tree[2 * v] = tree[v];
    tree[2 * v + 1] = tree[v];
    tree[v] = MIXED;

    sum[2 * v] = sum[v] / 2;
    sum[2 * v + 1] = sum[v] / 2;

}
/*
 * a, b         - section to paint
 * v            - current node
 * left, right  - road section under current node
 * We don't always have to go to the leaves, it is enough to reach an
 * unambiguous piece and do fixes using unpacking in more difficult cases
 * to keep the tree working properly.
 */
void paint_road(int a, int b, int colour, int v, int left, int right) {
    if(tree[v] != colour) {
        
        if(right < a || left > b) {
            /*
             * If the sections are disjointed, we do nothing.
             */
        }
        else {
            if (a <= left && right <= b) {  
                /*
                 * If the current sub-tree is within the painted section.
                 */
                tree[v] = colour;
                if (colour == WHITE)
                    sum[v] = (right - left + 1);
                else
                    sum[v] = 0;
            }
            else {
                /*
                 * If the section is within the current tree but not the whole tree.
                 */
                if (tree[v] != MIXED)
                    unpack_subtree(v);
                int s = (left + right) / 2;
                paint_road(a, b, colour, 2 * v, left, s);
                paint_road(a, b, colour, 2 * v + 1, s + 1, right);
                sum[v] = sum[2 * v] + sum[2 * v + 1];

            }
        }
    }
}

int main() {
    scanf("%ld", &n);
    scanf("%ld", &m);

    long a, b;
    char c;
    leafs = set_size(n);
    reset_tree();

    for (int i = 0; i < m; i++) {
        scanf("%ld", &a);
        scanf("%ld", &b);
        scanf(" %c", &c);

        if (c == 'B')
            paint_road(a, b, WHITE, 1, 1, leafs);
        else
            paint_road(a, b, BLACK, 1, 1, leafs);


        printf("%d\n", sum[1]);

    }

    return 0;
}
