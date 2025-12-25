#include "btree.h"

int8_t cmp(int a, int b) {
    return a == b;
}

int main() {

    struct btree_t* btree = malloc(sizeof(struct btree_t));

    btree_init(btree);
    btree_add(btree, 10);
    btree_add(btree, 5);
    btree_add(btree, 15);
    btree_add(btree, 1);
    btree_add(btree, 20);

    printf("cheguei aqui\n");

    btree_print(btree);

    printf("printado\n");

    // btree_remove(btree, 10);

    // printf("removi\n");

    // btree_print(btree);

    // btree_clear_all(btree);

    // printf("removeu tudo: size -> %d\n", btree->size);
    
    int val = 15;
    struct btree_node_t* ret = btree_find(btree, cmp, val);

    if(ret == NULL) {
        printf("not found %d\n", val);
    } else {
        printf("ret->value %d\n", ret->value);
    }

    struct btree_node_t* list[btree->size];
    
    int val_ret = btree_dfs(btree, list, btree->size);

    if(val_ret < 0) 
        printf("error dfs\n");

    printf("[ ");
    for(int i = 0; i < btree->size; i++) {
        printf("%d, ", list[i]->value);
    }
    printf("]\n");


    struct btree_node_t* list_2[btree->size];

    val_ret = btree_bfs(btree, list_2, btree->size);

    if(val_ret < 0) 
        printf("error bfs\n");

    printf("[ ");
    for(int i = 0; i < btree->size; i++) {
        printf("%d, ", list_2[i]->value);
    }
    printf("]\n");




    printf("ok\n");


    btree_clear(btree);

    return 0;
}