#ifndef AKINATOR_H
#define AKINATOR_H
#include "tree.h"

TREE_ERROR Akinator (Node* Tree);
TREE_ERROR AkinatorAdd (Node* Tree);
TREE_ERROR AkinatorAddSign (Node* Tree);
TREE_ERROR AkinatorRead (Node** ppNode, char* data, char* str);
#endif
