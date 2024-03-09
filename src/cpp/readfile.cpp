#include <stdio.h>
#include <sys/stat.h>
#include <string.h>
#include <stdlib.h>
#include "../header/tree.h"
#include "../header/readfile.h"
#include "../Onegin/header/readtext.h"


TREE_ERROR readfile (Node* Tree, char* file)
{
    if (Tree == nullptr)   return TREE_NULLPTR;
    FILE* infile = fopen (file, "r");
    if (infile == nullptr) return TREE_INFILE_NULLPTR;

    TREE_ERROR ERROR = AkinatorTreeCtor (Tree, infile);
    return ERROR;
}

TREE_ERROR AkinatorTreeCtor (Node* Tree, FILE* infile)
{
    char c = getc (infile);
    if (c == EOF || c == '}') return TREE_NO_ERROR;
    char* str_left = (char*) calloc (1, MAX_STR_SIZE);
    if (c == '{')
    {
        if (strlen (fgets(str_left, MAX_STR_SIZE, infile)) > 2)
        {
            Tree->left = (Node*) calloc (1, sizeof (Node));
            Tree->left->value = str_left;
            AkinatorTreeCtor (Tree->left, infile);
        }
    }

    c = getc (infile);
    if (c == EOF) return TREE_NO_ERROR;
    char* str_right = (char*) calloc (1, MAX_STR_SIZE);
    if (c == '\\' && getc (infile) == '{')
    {
        if (strlen (fgets(str_right, MAX_STR_SIZE, infile)) > 2)
        {
            Tree->right = (Node*) calloc (1, sizeof (Node));
            Tree->right->value = str_right;
            AkinatorTreeCtor (Tree->right, infile);
        }
    }
    return TREE_NO_ERROR;
}
