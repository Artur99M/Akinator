#ifndef TREE_H
#define TREE_H
#define  LEFT_NODE 1
#define RIGHT_NODE 2
#include <stdio.h>
typedef struct elem_t
{
    size_t line;
    char* str;
} elem_t;

typedef struct Node
{
    elem_t value;
    Node* left;
    Node* right;
} Node;

enum TREE_ERROR
{
    TREE_NO_ERROR = 0,
    TREE_NULLPTR = 1,
    TREE_ELEM_NULLPTR = 2,
    TREE_CALLOC_ERROR = 4,
    TREE_NO_ELEM = 8,
    TREE_ADD_ERROR = 16,
    ELEM_IS_VALUE_OF_NODE_OF_TREE = 32,
    TREE_FILE_NULLPTR = 64,
    TREE_INFILE_NULLPTR = 128,
    TREE_HZ_ERROR = 256,
    TREE_VOID = 512
};

TREE_ERROR TreeAdd (Node*, const elem_t*);
TREE_ERROR TreePrint (const Node*);
TREE_ERROR TreeCtor (Node*, const elem_t*);
TREE_ERROR TreeCtor (Node*);
TREE_ERROR TreeDtor (Node*);
TREE_ERROR TreeAddNode (Node*, Node*);
TREE_ERROR TreeDelete (Node*, const elem_t*);
#endif
