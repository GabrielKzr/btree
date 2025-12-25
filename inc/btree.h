#ifndef BTREE_H
#define BTREE_H

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

struct btree_node_t {
    int value;
    struct btree_node_t* left;
    struct btree_node_t* right;
};

struct btree_t {
    struct btree_node_t* root;
    int size;
};

int8_t btree_init(struct btree_t* btree);
void btree_clear(struct btree_t* btree);
// void btree_clear_all(struct btree_t* btree);
void btree_destroy(struct btree_t* btree);

int8_t btree_add(struct btree_t* btree, int value);
int8_t btree_remove(struct btree_t* btree, int value);

struct btree_node_t* btree_find(struct btree_t* btree, int8_t (*cmp)(int, int), int value);

int8_t btree_dfs(struct btree_t* btree, struct btree_node_t** ret, int size);
int8_t btree_bfs(struct btree_t* btree, struct btree_node_t** ret, int size);

// struct btree_node_t* btree_find_depth(struct btree_t* btree, int8_t (*cmp)(int, int), int value);
// struct btree_node_t* btree_find_breadth(struct btree_t* btree, int8_t (*cmp)(int, int), int value);

void btree_print(struct btree_t* btree);

#endif