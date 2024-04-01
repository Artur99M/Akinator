#include "../header/Akinator.h"
#include "../header/readfile.h"
#include "../Onegin/header/readtext.h"
#include "../../DEBUG/def.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define YES(x) (strcmp (x, "yes") == 0)
#define NO(x)  (strcmp (x, "no")  == 0)
#define GREEN "\x1b[32m"
#define ALL "\x1b[0m"

char* mygets (char* s, size_t max_size);

bool YESorNO ()
{
    char str[5] = "";
    while (scanf ("%s", str) == 0);
    str[4] = '\0';
    for (int i = 0; str[i]; str[i] = tolower (str[i]), i++);
    if (!YES(str) && !NO(str))
    {
        puts ("print yes or no");
        return YESorNO ();
    }
    return YES(str);
}
TREE_ERROR Akinator(Node* Tree)
{
    if (Tree == nullptr)
        return TREE_NULLPTR;

    TREE_ERROR ERROR = TREE_NO_ERROR;

    while (Tree->left != nullptr && Tree->right != nullptr)
    {
        printf ("%s?\n", Tree->value);

        if (YESorNO())
            Tree = Tree->left;
        else Tree = Tree->right;

        if (strlen(Tree->value) < 2)
        {
            puts ("Who is he/she?");
            scanf ("%s", Tree->value);
        }
    }
    printf ("It\'s %s?\n", Tree->value);

    if (YESorNO())
    {
        puts ("I guess?");
        if (YESorNO())
        {
            printf (GREEN "\nI knew\n\n" ALL);
            return TREE_NO_ERROR;
        }
        else return AkinatorAddSign (Tree);

        return TREE_NO_ERROR;
    }
    else return AkinatorAdd (Tree);

}


TREE_ERROR AkinatorAdd (Node* Tree)
{
    if (Tree == nullptr) return TREE_NULLPTR;

    PRINT_DEBUG ("AkinatorAdd >>> start\n");
    PRINT_DEBUG ("AkinatorAdd >>> Tree->value = \"%s\", Tree->left = %p, Tree->right = %p\n", Tree->value, Tree->left, Tree->right);
    if ((Tree->left   = (Node*) calloc (1, sizeof (Node))) == nullptr) return TREE_CALLOC_ERROR;
    PRINT_DEBUG ("AkinatorAdd >>> Tree->left  = %p\n", Tree->left);
    if ((Tree->right  = (Node*) calloc (1, sizeof (Node))) == nullptr) return TREE_CALLOC_ERROR;
    PRINT_DEBUG ("AkinatorAdd >>> Tree->right = %p\n", Tree->right);
    PRINT_DEBUG ("AkinatorAdd >>> Tree->value = \"%s\", Tree->left = %p, Tree->right = %p\n", Tree->value, Tree->left, Tree->right);


    Tree->right->value = Tree->value;
    PRINT_DEBUG ("AkinatorAdd >>> Tree->right->value = \"%s\"\n", Tree->right->value);

    puts ("Who is he/she?");
    char s[MAX_STR_SIZE] = "";
    PRINT_DEBUG ("AkinatorAdd >>> mygets start\n");
    // mygets (s, MAX_STR_SIZE);
    while (getchar() != '\n');
    mygets (s, MAX_STR_SIZE);
    PRINT_DEBUG ("AkinatorAdd >>> mygets finish\n");
    PRINT_DEBUG ("%s\n", s);
    if ((Tree->left->value = (char*) calloc (strlen(s), sizeof (char))) == nullptr) return TREE_CALLOC_ERROR;
    strcpy (Tree->left->value, s);
    printf ("How is %s different from %s?\n", Tree->left->value, Tree->right->value);
    char c[MAX_STR_SIZE] = "";
    PRINT_DEBUG ("AkinatorAdd >>> mygets start\n");
    mygets (c, MAX_STR_SIZE);
    PRINT_DEBUG ("AkinatorAdd >>> mygets finish\n");
    PRINT_DEBUG ("%s\n", c);
    if ((Tree->value = (char*) calloc (strlen(c), sizeof (char))) == nullptr) return TREE_CALLOC_ERROR;
    strcpy (Tree->value, c);

    // Tree->left->left   = nullptr;
    // Tree->left->right  = nullptr;
    // Tree->right->left  = nullptr;
    // Tree->right->right = nullptr;
    PRINT_DEBUG ("AkinatorAdd >>> Tree->value = \"%s\", Tree->left = %p, Tree->right = %p\n", Tree->value, Tree->left, Tree->right);
    PRINT_DEBUG ("AkinatorAdd >>> Tree->left->value = \"%s\", Tree->left->left = %p, Tree->left->right = %p\n", Tree->left->value, Tree->left->left, Tree->left->right);
    PRINT_DEBUG ("AkinatorAdd >>> Tree->right->value = \"%s\", Tree->right->left = %p, Tree->right->right = %p\n", Tree->right->value, Tree->right->left, Tree->right->right);
    return TREE_NO_ERROR;
}

TREE_ERROR AkinatorAddSign (Node* Tree)
{
    PRINT_DEBUG ("AkinatorAddSign >>> start\n");
    if (Tree == nullptr) return TREE_NULLPTR;

    if (!(Tree->left  = (Node*) calloc (1, sizeof (Node)))) return TREE_CALLOC_ERROR;
    if (!(Tree->right = (Node*) calloc (1, sizeof (Node)))) return TREE_CALLOC_ERROR;
    PRINT_DEBUG ("AkinatorAddSign >>> Tree->left = %p, Tree->right = %p\n", Tree->left, Tree->right);

    if (!(Tree->left->value  = (char*) calloc (1, MAX_STR_SIZE))) return TREE_CALLOC_ERROR;
    if (!(Tree->right->value = (char*) calloc (1, MAX_STR_SIZE))) return TREE_CALLOC_ERROR;
    PRINT_DEBUG ("AkinatorAddSign >>> Tree->left->value = %p, Tree->right->value = %p\n", Tree->left->value, Tree->right->value);

    puts ("Who is he/she?");
    char s[MAX_STR_SIZE] = "";
    while (getchar() != '\n');
    mygets (s, MAX_STR_SIZE);
    PRINT_DEBUG ("%s\n", s);
    if ((Tree->left->value = (char*) calloc (strlen(s), sizeof (char))) == nullptr) return TREE_CALLOC_ERROR;
    strcpy (Tree->left->value, s);
    printf ("Who is hasn\'t this characteristics \"%s\"?\n", Tree->value);
    char c[MAX_STR_SIZE] = "";
    mygets (c, MAX_STR_SIZE);
    PRINT_DEBUG ("%s\n", c);
    if ((Tree->right->value = (char*) calloc (strlen(c), sizeof (char))) == nullptr) return TREE_CALLOC_ERROR;
    strcpy (Tree->right->value, c);
    PRINT_DEBUG ("AkinatorAdd >>> Tree->value = \"%s\", Tree->left = %p, Tree->right = %p\n", Tree->value, Tree->left, Tree->right);
    PRINT_DEBUG ("AkinatorAdd >>> Tree->left->value = \"%s\", Tree->left->left = %p, Tree->left->right = %p\n", Tree->left->value, Tree->left->left, Tree->left->right);
    PRINT_DEBUG ("AkinatorAdd >>> Tree->right->value = \"%s\", Tree->right->left = %p, Tree->right->right = %p\n", Tree->right->value, Tree->right->left, Tree->right->right);


    return TREE_NO_ERROR;
}

char* mygets (char* s, size_t max_size)
{
    if (s == nullptr) return nullptr;
    char c = '\0';
    for (size_t i = 0; i < max_size && c != '\n'; i++)
    {
        c = getchar();
        if (c != '\n')
            s[i] = c;
    }

    return s;
}
