#include <iostream>
#include <cstdio>
#include <queue>
#include <vector>


typedef struct field {
    int value;
    int id;
    struct field *rep;
} field_t;

field_t* find(field_t *r) {
    if (r != r->rep)
        r->rep = find(r->rep);
    return r->rep;
}

/*
 * Each component is determined by its representative - the largest element,
 * which belongs to it. When we load the next element of the permutation,
 * we compare its value with the value of the representative of the last component.
 * 1) if the new value is greater, it creates a new component
 * 2) otherwise we compare the new value with the values ​​of all representatives,
 * until the end / we find representative smaller then new value. 
 * The added element will connect all components, represented by elements
 * greater than it, that are before him in the permutation.
 */

int main() {
    
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    
    std::vector<field_t> components;
    
    int n, temp, parts = 0;
    scanf("%d", &n);
    field_t t[n];
    
    scanf("%d", &temp);
    t[0].value = temp;
    t[0].id = 0;
    t[0].rep = &(t[0]);
    components.push_back(t[0]);
    
    for (int i = 1; i < n; ++i) {
        scanf("%d", &temp);
        t[i].value = temp;
        t[i].id = i;
        
        if (t[i].value > t[i - 1].rep->value) {
            t[i].rep = &(t[i]);
            components.push_back(t[i]);
        }
        else {
            field_t *new_rep = t[i - 1].rep;
            t[i].rep = new_rep;
            int j = components.size() - 1;
            while (j >= 0 && components[j].rep->value > t[i].value) {
                t[components[j].id].rep = find(&(t[i]));
                components.erase(components.end() - 1);
                --j;
            }
            components.push_back(*(t[i].rep));
        }
    }
    
    /* 
     * Queues store and automatically sort the items that belong to
     * consecutive components.
     */
     
    std::priority_queue<int, std::vector<int>, std::greater<int>> outcome[n + 1];
    
    for (int i = 0; i < n; ++i) {
        field_t *r;
        r = find(&(t[i]));
        outcome[r->value].push(t[i].value);
    }
    for (int i = 0; i <= n; ++i) {
        if (outcome[i].size() > 0)
            ++parts;
    }
    
    std::cout << parts << "\n";
    
    for (int i = 0; i <= n; ++i) {
        if (outcome[i].size() > 0) {
            std::cout << outcome[i].size() << " ";
            while (!outcome[i].empty()) {
                std::cout << outcome[i].top() << " ";
                outcome[i].pop();
            }
            std::cout << "\n";
        }
    }

    return 0;
}
