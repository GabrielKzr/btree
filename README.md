# Binary Tree (C)

A simple binary search tree implemented in C. Each node stores an integer weight (used for ordering) and a generic `void* data` payload. The library supports insertion, removal, lookup, printing, and traversal (DFS and BFS).

## Overview

- Data structures:
  - `btree_node_t`: holds an `int weight`, a `void* data` payload, and pointers to `left` and `right` children.
  - `btree_t`: holds a `root` node pointer and the current `size`.
- Operations:
  - Initialize and clear/destroy the tree
  - Insert unique values (BST property)
  - Remove values
  - Find values with a custom comparison function
  - Print the tree recursively
  - Depth-first and breadth-first traversals (return node lists)

## Project Structure

```
main
Makefile
bin/
  btree/
inc/
  btree.h
src/
  main.c
  btree/
    btree.c
```

## Build

Requirements: `gcc`, `make` (Linux/macOS; tested on Linux).

```zsh
make
```
- Compiles all `*.c` files under `src/`.
- Places object files under `bin/` and links to a `main` executable.

Clean build artifacts:
```zsh
make clean
```

## Run

```zsh
./main
#or
make run
```

Example output from the included `main.c`:
```
abc... 0
abc... 1
abc... 2
abc... 3
abc... 4
[ 10 : [ 5 : [ 1 : ,  ] ,  ] , [ 15 : , [ 20 : ,  ]  ]  ] 
[ 15 : [ 5 : [ 1 : ,  ] ,  ] , [ 20 : ,  ]  ] 
ret->weight 15
ret->data abc... 2
[ 15, 5, 1, 20, ]
[ 15, 5, 20, 1, ]
ok
all working
ending...
```

## Usage

Minimal example (see `src/main.c`):
```c
#include "btree.h"
#include <string.h>

// Comparator now compares payloads (`void* data`), not weights
int8_t cmp(void *a, void *b) {
  return strcmp((const char*)a, (const char*)b) == 0;
}

int main() {
    struct btree_t* btree = malloc(sizeof(struct btree_t));

  const char *hello = "hello";
  const char *world = "world";

  btree_init(btree);

  // Insert weight/payload pairs
  btree_add(btree, 10, (void*)hello);
  btree_add(btree, 5,  (void*)world);

  // Print
  btree_print(btree);

  // Find by payload using the comparator
  struct btree_node_t* found = btree_find(btree, cmp, (void*)world);
  if (found) {
    printf("found weight: %d, data: %s\n", found->weight, (char*)found->data);
  }

  // DFS traversal
  struct btree_node_t* dfs_list[btree->size];
  btree_dfs(btree, dfs_list, btree->size);

  // BFS traversal
  struct btree_node_t* bfs_list[btree->size];
  btree_bfs(btree, bfs_list, btree->size);

  // Clear all nodes AND free stored payloads; frees the tree struct too
  btree_clear(btree);
  btree = NULL; // now invalid
  return 0;
}
```

## API

Header: `inc/btree.h`

- `int8_t btree_init(struct btree_t* btree);`
  - Initializes a tree; sets `root` and `size`.
- `void btree_clear(struct btree_t* btree);`
  - Recursively frees all nodes, frees each node's `data`, resets `size`, and frees the `btree` struct itself.
- `void btree_destroy(struct btree_t* btree);`
  - Clears nodes (does **not** free stored `data`) and then frees the `btree` struct itself.
- `int8_t btree_add(struct btree_t* btree, int weight, void *data);`
  - Inserts a unique `weight` with associated payload `data`; enforces BST property.
  - Returns negative value on error; non-negative on success.
- `int8_t btree_remove(struct btree_t* btree, int weight);`
  - Removes `btree_node_t` with matching `weight`and frees `data`. Returns negative on error; non-negative on success.
- `struct btree_node_t* btree_find(struct btree_t* btree, int8_t (*cmp)(int, int), void* cmp_val);`
  - Finds a node matching `cmp_val` according to `cmp`.
- `int8_t btree_dfs(struct btree_t* btree, struct btree_node_t** ret, int size);`
  - Fills `ret` with nodes in DFS (preorder). Requires `size >= btree->size`.
- `int8_t btree_bfs(struct btree_t* btree, struct btree_node_t** ret, int size);`
  - Fills `ret` with nodes in BFS (level-order). Requires `size >= btree->size`.
- `void btree_print(struct btree_t* btree);`
  - Prints the tree recursively in a bracketed form.

## Design Notes

- `btree_remove` uses a value-pushdown approach (promotes from children) rather than the classic BST delete by predecessor/successor.
- Traversal functions expect a preallocated array of `struct btree_node_t*` pointers with capacity at least `btree->size`.
- Error codes are minimal; for robust applications, consider standardizing return values and adding input validation.