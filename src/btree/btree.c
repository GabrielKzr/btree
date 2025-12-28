#include "btree.h"

int8_t btree_init(struct btree_t* btree) {

    if(btree == NULL)
        return -1;

    btree->root = 0;
    btree->size = 0;

    return 0;
}

static void _btree_clear(struct btree_t* btree, struct btree_node_t** node, uint8_t flag) {
    if(*node == NULL) return;
    else 
    {
        _btree_clear(btree, &(*node)->left, flag);
        _btree_clear(btree, &(*node)->right, flag);
    
        // free
        if(flag)
            free((*node)->data);    

        free(*node);
        *node = NULL;
        btree->size--;
    }
}

void btree_clear(struct btree_t* btree) {

    if(btree == NULL) 
        return;

    _btree_clear(btree, &btree->root, 1); 
    free(btree); 
}

void btree_destroy(struct btree_t* btree) {
    if(btree == NULL) 
        return;

    _btree_clear(btree, &btree->root, 0);  
    free(btree);
}

static int8_t _btree_add(struct btree_t* btree, int weight, void* data, struct btree_node_t** node) {

    if(*node == NULL) {

        *node = malloc(sizeof(struct btree_node_t));

        (*node)->weight = weight;
        (*node)->data = data;
        btree->size++;
        
        return btree->size;

    } else {

        if(weight == (*node)->weight) 
            return -1;
        else if(weight < (*node)->weight)
            return _btree_add(btree, weight, data, &(*node)->left);
        else
            return _btree_add(btree, weight, data, &(*node)->right);
    }
}

int8_t btree_add(struct btree_t* btree, int weight, void *data) {

    if(btree == NULL || data == NULL) 
        return -1;

    return _btree_add(btree, weight, data, &btree->root);
}

static void* _btree_remove(struct btree_t* btree, int weight, struct btree_node_t** node) {
    if(*node == NULL) return NULL;
    else
    {   
        if((*node)->weight == weight) {

            if((*node)->right != NULL) { // rigth first (is bigger) to keep tree rule
                (*node)->weight = (*node)->right->weight; // here is "removing" the weight
                void* temp = (*node)->data; // important to free the data that is removed ('cause the node is not removed)
                (*node)->data = (*node)->right->data;
                _btree_remove(btree, (*node)->weight, &(*node)->right);
                return temp;
            
            } else if((*node)->left != NULL) {
                (*node)->weight = (*node)->left->weight; // here is "removing" the weight
                void* temp = (*node)->data; // important to free the data that is removed ('cause the node is not removed)
                (*node)->data = (*node)->right->data;
                _btree_remove(btree, (*node)->weight, &(*node)->left);
                return temp;

            } else { // case is leaf
                free(*node);
                *node = NULL;
                btree->size--;
                return NULL;            
            }
        } 
        else {
            if(weight < (*node)->weight) 
                return _btree_remove(btree, weight, &(*node)->left);
            else 
                return _btree_remove(btree, weight, &(*node)->right);     
        }
        
    }
}

int8_t btree_remove(struct btree_t* btree, int weight) {
    if(btree == NULL) 
        return -1;

    void* temp = _btree_remove(btree, weight, &btree->root);
        
    if(temp != NULL) {
        free(temp);
        return 1;
    }
    
    return -1;
}

static struct btree_node_t* _btree_find(int8_t (*cmp)(void *, void *), void *data, struct btree_node_t* node) {
    if(node == NULL) return NULL;
    else {
        if(cmp(data, node->data)) 
            return node;

        struct btree_node_t* ret = _btree_find(cmp, data, node->left);

        if(ret != NULL)
            return ret;

        ret = _btree_find(cmp, data, node->right);

        return ret;
    }
}

struct btree_node_t* btree_find(struct btree_t* btree, int8_t (*cmp)(void *, void *), void* cmp_val) {

    if(btree == NULL || cmp_val == NULL || cmp == NULL)
        return NULL;

    return _btree_find(cmp, cmp_val, btree->root);
}

static void _btree_print(struct btree_node_t* node) {
    if(node == NULL) return;
    else {
        printf("[ %d : ", node->weight);       
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