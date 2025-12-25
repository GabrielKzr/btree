#include "btree.h"

int8_t btree_init(struct btree_t* btree) {

    if(btree == NULL)
        return -1;

    btree->root = 0;
    btree->size = 0;

    return 0;
}

static void _btree_clear(struct btree_t* btree, struct btree_node_t** node) {
    if(*node == NULL) return;
    else 
    {
        _btree_clear(btree, &(*node)->left);
        _btree_clear(btree, &(*node)->right);
    
        // free
        free(*node);
        *node = NULL;
        btree->size--;
    }
}

void btree_clear(struct btree_t* btree) {

    if(btree == NULL) 
        return;

    _btree_clear(btree, &btree->root);  
}

void btree_destroy(struct btree_t* btree) {
    if(btree == NULL) 
        return;

    _btree_clear(btree, &btree->root);  
    free(btree);
}

static int8_t _btree_add(struct btree_t* btree, int value, struct btree_node_t** node) {

    if(*node == NULL) {

        *node = malloc(sizeof(struct btree_node_t));

        (*node)->value = value;
        btree->size++;
        
        return btree->size;

    } else {

        if(value == (*node)->value) 
            return -1;
        else if(value < (*node)->value)
            return _btree_add(btree, value, &(*node)->left);
        else
            return _btree_add(btree, value, &(*node)->right);
    }
}

int8_t btree_add(struct btree_t* btree, int value) {

    if(btree == NULL) 
        return -1;

    return _btree_add(btree, value, &btree->root);
}

static int8_t _btree_remove(struct btree_t* btree, int value, struct btree_node_t** node) {
    if(*node == NULL) return 0;
    else
    {   
        if((*node)->value == value) {

            if((*node)->right != NULL) { // rigth first (is bigger) to keep tree rule
            (*node)->value = (*node)->right->value; // here is "removing" the value
            
            return _btree_remove(btree, (*node)->value, &(*node)->right);
            
        } else if((*node)->left != NULL) {
            (*node)->value = (*node)->left->value; // here is "removing" the value
            
                return _btree_remove(btree, (*node)->value, &(*node)->left);

            } else { // case is leaf
                free(*node);
                *node = NULL;
                btree->size--;
                return 2;            
            }
        } 
        else {
            if(value < (*node)->value) 
                return _btree_remove(btree, value, &(*node)->left);
            else 
                return _btree_remove(btree, value, &(*node)->right);     
        }
        
    }
}

int8_t btree_remove(struct btree_t* btree, int value) {
    if(btree == NULL) 
        return -1;

    return _btree_remove(btree, value, &btree->root);
}

static struct btree_node_t* _btree_find(int8_t (*cmp)(int, int), int value, struct btree_node_t* node) {
    if(node == NULL) return NULL;
    else {
        if(cmp(value, node->value)) 
            return node;
            
        else if(value > node->value)
            return _btree_find(cmp, value, node->right);

        else 
            return _btree_find(cmp, value, node->left);
    }
}

struct btree_node_t* btree_find(struct btree_t* btree, int8_t (*cmp)(int, int), int value) {
    if(btree == NULL)
        return NULL;

    return _btree_find(cmp, value, btree->root);
}

static void _btree_print(struct btree_node_t* node) {
    if(node == NULL) return;
    else {
        printf("[ %d : ", node->value);       
        _btree_print(node->left);
        printf(", ");
        _btree_print(node->right);
        printf(" ] ");

        return;
    }
}

void btree_print(struct btree_t* btree) {
    if(btree == NULL) 
        return;
    
    _btree_print(btree->root);
    printf("\n");

    return;
}


static void _dfs(struct btree_t* btree, struct btree_node_t** ret, struct btree_node_t* node) {

    static int count;

    if(node == NULL) return;
    else {
        if(node == btree->root)
            count = 0;

        ret[count] = node;
        count++;

        _dfs(btree, ret, node->left);
        _dfs(btree, ret, node->right);

        return;
    }
}

int8_t btree_dfs(struct btree_t* btree, struct btree_node_t** ret, int size) {

    if(btree == NULL) 
        return -1;

    if(size < btree->size)
        return -1;

    _dfs(btree, ret, btree->root);

    return 0;
}

static void _bfs(struct btree_t* btree, struct btree_node_t** ret, struct btree_node_t** queue, int* start_idx, int* end_idx) {

    static int count;

    if(*start_idx == *end_idx)
        return;

    struct btree_node_t* node = queue[(*start_idx)++];

    if(node == btree->root)
        count = 0;

    ret[count++] = node;

    if(node->left != NULL) 
        queue[(*end_idx)++] = node->left;
    if(node->right != NULL) 
        queue[(*end_idx)++] = node->right;

    _bfs(btree, ret, queue, start_idx, end_idx);
    return;
}

int8_t btree_bfs(struct btree_t* btree, struct btree_node_t** ret, int size) {

    if(btree == NULL)
        return -1;

    if(size < btree->size)
        return -1;

    struct btree_node_t* queue[btree->size];

    int start_idx = 0;
    int end_idx = 0;

    queue[end_idx++] = btree->root;

    _bfs(btree, ret, queue, &start_idx, &end_idx);

    return 0;
}