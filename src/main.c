#include "btree.h"
#include <string.h>

int8_t cmp(void *a, void *b) {

    char* a_temp = (char *)a;
    char* b_temp = (char *)b;

    return a_temp[7] == b_temp[7];
}

int main() {

    struct btree_t* btree = malloc(sizeof(struct btree_t));

    int num_values = 5;
    char* values[5];

    for(int i = 0; i < num_values; i++) 
    {
        values[i] = malloc(50);
        sprintf(values[i], "abc... %d", i);
    }

    for(int i = 0; i < num_values; i++)
    {
        printf("%s\n", values[i]);
    }

    btree_init(btree);
    btree_add(btree, 10, values[0]);
    btree_add(btree, 5, values[1]);
    btree_add(btree, 15, values[2]);
    btree_add(btree, 1, values[3]);
    btree_add(btree, 20, values[4]);
    
    btree_print(btree);

    btree_remove(btree, 10);

    btree_print(btree);

    struct btree_node_t* ret = btree_find(btree, cmp, values[3]);

    if(ret == NULL) {
        printf("not found %s\n", values[2]);
    } else {
        printf("ret->weight %d\n", ret->weight);
        printf("ret->data %s\n", (char*)ret->data);
    }

    struct btree_node_t* list[btree->size];
    
    int val_ret = btree_dfs(btree, list, btree->size);

    if(val_ret < 0) 
        printf("error dfs\n");

    printf("[ ");
    for(int i = 0; i < btree->size; i++) {
        printf("%d, ", list[i]->weight);
    }
    printf("]\n");


    struct btree_node_t* list_2[btree->size];

    val_ret = btree_bfs(btree, list_2, btree->size);

    if(val_ret < 0) 
        printf("error bfs\n");

    printf("[ ");
    for(int i = 0; i < btree->size; i++) {
        printf("%d, ", list_2[i]->weight);
    }
    printf("]\n");


    printf("ok\n");

    printf("all working\n");

    btree_clear(btree);

    printf("ending...\n");

    return 0;
}