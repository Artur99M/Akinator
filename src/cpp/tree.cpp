#include "../header/tree.h"
#include "../../DEBUG/def.h"
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

TREE_ERROR TreeAdd (Node* Tree, const elem_t* elem)
{
    if (Tree == nullptr) return TREE_NULLPTR;
    if (elem == nullptr) return TREE_ELEM_NULLPTR;

    Node* new_Tree_elem = nullptr;
    if ((new_Tree_elem = (Node*) calloc (1, sizeof (Node) )) == nullptr)
        return TREE_CALLOC_ERROR;
    new_Tree_elem->value = *elem;

    while (1)
    {
        if (*elem <= Tree->value)
            if (Tree->left == nullptr)
            {
                Tree->left = new_Tree_elem;
                break;
            }
            else
                Tree = Tree->left;

        else
            if (Tree->right == nullptr)
            {
                Tree->right = new_Tree_elem;
                break;
            }
            else
                Tree = Tree->right;
    }

    return TREE_NO_ERROR;
}

TREE_ERROR TreePrint (const Node* Tree)
{
    if (Tree == nullptr)
        return TREE_NULLPTR;

    PRINT_DEBUG ("TreePrint >>> start\n");
    PRINT_DEBUG ("TreePrint >>> Tree->value = %s\n", Tree->value);
    printf ("{\n%s\n", Tree->value);

    if (Tree->left != nullptr)
    {
        PRINT_DEBUG ("TreePrint >>> I go to left\n");
        TreePrint (Tree->left);
    }
    else
    {
        PRINT_DEBUG ("TreePrint >>> left is void\n");
        puts ("*");
    }
    if (Tree->right != nullptr)
    {
        PRINT_DEBUG ("TreePrint >>> Tree->right = %p\n", Tree->right);
        PRINT_DEBUG ("TreePrint >>> I go to right\n");
        TreePrint (Tree->right);
    }
    else
    {
        PRINT_DEBUG ("TreePrint >>> right is void");
        puts ("*");
    }

    puts ("}");
    PRINT_DEBUG ("TreePrint >>> I finish\n");

    return TREE_NO_ERROR;
}

TREE_ERROR TreeCtor (Node* Tree, const elem_t* elem)
{
    if (Tree == nullptr) return TREE_NULLPTR;

    if (elem != nullptr) Tree->value = *elem;
    Tree->left = nullptr;
    Tree->right = nullptr;

    return TREE_NO_ERROR;
}

TREE_ERROR TreeCtor (Node* Tree)
{
    if (Tree == nullptr) return TREE_NULLPTR;

    Tree->left = nullptr;
    Tree->right = nullptr;

    return TREE_NO_ERROR;
}

void TreeDtor (Node* Tree)
{
    if (Tree == nullptr)
        return;

    PRINT_DEBUG ("TreeDtor >>> &Tree = %p, Tree->value = \"%s\", Tree->left = %p, Tree->right = %p\n", Tree, Tree->value, Tree->left, Tree->right);
    if (Tree->left != nullptr)
        TreeDtor (Tree->left);
    if (Tree->right != nullptr)
        TreeDtor (Tree->right);

    free (Tree->left);
    free (Tree->right);
    free (Tree->value);

    Tree->value = nullptr;
    Tree->left  = nullptr;
    Tree->right = nullptr;

    return;
}

TREE_ERROR TreeDelete (Node* Tree, const elem_t* elem)
{
    if (Tree == nullptr) return TREE_NULLPTR;
    if (elem == nullptr) return TREE_ELEM_NULLPTR;
    Node* prevNode = nullptr;

    int Tree_left_or_right = 0;

    if (Tree->value == *elem)
    {
        return ELEM_IS_VALUE_OF_NODE_OF_TREE;
    }

    while (Tree->value != *elem)
        if (*elem <= Tree->value)
        {
            if (Tree->left == nullptr)
                return TREE_NO_ELEM;

            prevNode = Tree;
            Tree = Tree->left;
            Tree_left_or_right = 1;
        }

        else
            if (Tree->right != nullptr)
            {
                prevNode = Tree;
                Tree = Tree->right;
                Tree_left_or_right = 0;
            }
            else return TREE_NO_ELEM;

    if (Tree->left != nullptr && Tree->right != nullptr)
    {
        TreeAddNode (Tree->left, Tree->right);
        switch (Tree_left_or_right)
        {
            case 0:
                prevNode->right = Tree->left;
                break;
            case 1:
                prevNode->left = Tree->left;
                break;
        }
    }

    else if (Tree->left != nullptr)
        switch (Tree_left_or_right)
        {
            case 0:
                prevNode->right = Tree->left;
                break;
            case 1:
                prevNode->left = Tree->left;
                break;
        }

    else if (Tree->right != nullptr)
        switch (Tree_left_or_right)
        {
            case 0:
                prevNode->right = Tree->right;
                break;
            case 1:
                prevNode->left = Tree->right;
                break;
        }

    else
        switch (Tree_left_or_right)
        {
            case 0:
                prevNode->right = nullptr;
                break;
            case 1:
                prevNode->left = nullptr;
                break;
        }

    free (Tree);

    return TREE_NO_ERROR;
}

TREE_ERROR TreeAddNode (Node* Tree, Node* NodeAdd)
{
    if (Tree == nullptr) return TREE_NULLPTR;
    if (NodeAdd == nullptr) return TREE_NULLPTR;

    while (1)
    {
        if (NodeAdd->value <= Tree->value)
            if (Tree->left == nullptr)
            {
                Tree->left = NodeAdd;
                break;
            }
            else
                Tree = Tree->left;

        else
            if (Tree->right == nullptr)
            {
                Tree->right = NodeAdd;
                break;
            }
            else
                Tree = Tree->right;
    }

    return TREE_NO_ERROR;
}

TREE_ERROR TREE_FPRINT (Node* Tree, FILE* outfile)
{
    if (Tree == nullptr)
        return TREE_NULLPTR;
    if (outfile == nullptr)
        return TREE_FILE_NULLPTR;

    PRINT_DEBUG ("TREE_FPRINT >>> Tree = %p, Tree->value = \"%s\"\n", Tree, Tree->value);
    fputs ("{\n", outfile);
    // fprintf (outfile, "{\n%s\n", Tree->value);
    fputs (Tree->value, outfile);
    PRINT_DEBUG ("TREE_FPRINT start putc (\'\\n\', outfile)\n");
    putc ('\n', outfile);
    PRINT_DEBUG ("TREE_FPRINT finish putc (\'\\n\', outfile)\n");
    // return TREE_NO_ERROR;

    if (Tree->left != nullptr)
    {
        PRINT_DEBUG ("TREE_FPRINT >>> Start see left: Tree->left = %p\n", Tree->left);
        TREE_FPRINT (Tree->left, outfile);
    }
    else fputs ("*\n", outfile);
    PRINT_DEBUG ("TREE_FPRINT >>> finish see left\n")
    if (Tree->right != nullptr)
    {
        PRINT_DEBUG ("TREE_FPRINT >>> Start see right: Tree->right = %p\n", Tree->right);
        TREE_FPRINT (Tree->right, outfile);
    }
    else fputs ("*\n", outfile);
    PRINT_DEBUG ("TREE_FPRINT >>> finish see right\n");

    fputs ("}\n", outfile);

    return TREE_NO_ERROR;

}
TREE_ERROR TreeFPrint (Node* Tree, char* file)
{
    if (Tree == nullptr || file == nullptr)
        return TREE_NULLPTR;

    PRINT_DEBUG ("TreeFPrint start\n");

    FILE* outfile = fopen (file, "w");
    if (outfile == nullptr)
        return TREE_FILE_NULLPTR;

    TREE_ERROR ERROR = TREE_FPRINT (Tree, outfile);
    // fputs ("\n\n\n\n\n", outfile);
    return ERROR;
}
