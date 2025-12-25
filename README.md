# Binary Tree (C)

A simple binary search tree implemented in C, featuring insertion, removal, lookup, printing, and traversal (DFS and BFS). This project is minimal and great for learning and experimenting with tree data structures.

## Overview

- Data structures:
  - `btree_node_t`: holds an `int value` and pointers to `left` and `right` children.
  - `btree_t`: holds a `root` node pointer and the current `size`.
- Operations:
  - Initialize and clear the tree
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
```

Example output from the included `main.c`:
```
cheguei aqui
[ 10 : [ 5 : [ 1 : ,  ] ,  ] , [ 15 : , [ 20 : ,  ]  ]  ] 
printado
ret->value 15
[ 10, 5, 1, 15, 20, ]
[ 10, 5, 15, 1, 20, ]
ok
```

## Usage

Minimal example (see `src/main.c`):
```c
#include "btree.h"

int8_t cmp(int a, int b) { return a == b; }

int main() {
    struct btree_t* btree = malloc(sizeof(struct btree_t));

    btree_init(btree);

    // Insert
    btree_add(btree, 10);
    btree_add(btree, 5);
    btree_add(btree, 15);

    // Print
    btree_print(btree);

    // Find
    struct btree_node_t* found = btree_find(btree, cmp, 15);
    if (found) {
        printf("found: %d\n", found->value);
    }

    // DFS traversal
    struct btree_node_t* dfs_list[btree->size];
    btree_dfs(btree, dfs_list, btree->size);

    // BFS traversal
    struct btree_node_t* bfs_list[btree->size];
    btree_bfs(btree, bfs_list, btree->size);

    // Clear and free all
    btree_clear(btree);
    return 0;
}
```

## API

Header: `inc/btree.h`

- `int8_t btree_init(struct btree_t* btree);`
  - Initializes a tree; sets `root` and `size`.
- `void btree_clear(struct btree_t* btree);`
  - Recursively frees all nodes and then frees the `btree` itself.
- `void btree_destroy(struct btree_t* btree);`
  - Resets `root` and `size` to zero (does not free memory).
- `int8_t btree_add(struct btree_t* btree, int value);`
  - Inserts `value` if not already present; enforces BST property.
  - Returns negative value on error; non-negative on success.
- `int8_t btree_remove(struct btree_t* btree, int value);`
  - Removes `value`. Returns negative on error; otherwise an implementation-specific status code.
- `struct btree_node_t* btree_find(struct btree_t* btree, int8_t (*cmp)(int, int), int value);`
  - Finds a node matching `value` according to `cmp`.
- `int8_t btree_dfs(struct btree_t* btree, struct btree_node_t** ret, int size);`
  - Fills `ret` with nodes in DFS (preorder). Requires `size >= btree->size`.
- `int8_t btree_bfs(struct btree_t* btree, struct btree_node_t** ret, int size);`
  - Fills `ret` with nodes in BFS (level-order). Requires `size >= btree->size`.
- `void btree_print(struct btree_t* btree);`
  - Prints the tree recursively in a bracketed form.

## Design Notes & Caveats

- `btree_destroy` frees the `btree` struct itself. If you intend to reuse the same `btree_t` allocation, call `btree_clear` instead or re-`malloc` after clearing.
- `btree_remove` uses a value-pushdown approach (promotes from children) rather than the classic BST delete by predecessor/successor. It works for this sample but differs from standard textbook implementations.
- Traversal functions expect a preallocated array of `struct btree_node_t*` pointers with capacity at least `btree->size`.
- Error codes are minimal; for robust applications, consider standardizing return values and adding input validation.

## Future Improvements

- Implement a hash function to use not just integers, but also any kind of data (void *)
