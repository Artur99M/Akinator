#include "../header/Akinator.h"
#include "../header/readfile.h"
#include "../Onegin/header/readtext.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define YES(x) (strcmp (x, "yes") == 0)
#define NO(x)  (strcmp (x, "no")  == 0)
#define GREEN "\x1b[32m"
#define ALL "\x1b[0m"

// TREE_ERROR Akinator(Node* Tree)
// {
//     if (Tree == nullptr) return TREE_NULLPTR;
//
//     char str[5] = "";
//     while (Tree->left != nullptr && Tree->right != nullptr)
//     {
//         printf ("%s?\n", Tree->value);
//         qwerty:
//         while (scanf ("%s", str) == 0);
//         str[4] = '\0';
//         for (int i = 0; str[i]; str[i] = tolower (str[i]), i++);
//         if (!YES(str) && !NO(str))
//         {
//             puts ("print yes or no");
//             goto qwerty;
//         }
//
//         if (YES(str))
//             Tree = Tree->left;
//         else Tree = Tree->right;
//
//         if (strlen(Tree->value) < 2)
//         {
//             puts ("Who is he/she?");
//             scanf ("%s", Tree->value);
//         }
//     }
//     printf ("It\'s %s?\n", Tree->value);
//
//     second_qwerty:
//     while (scanf ("%s", str) == 0) puts ("print yes or no");
//     str[4] = '\0';
//     for (int i = 0; str[i]; str[i] = tolower (str[i]), i++);
//     if (!YES(str) && !NO(str)) goto second_qwerty;
//
//     if (YES(str))
//     {
//         puts ("I guess?");
//         third_qwerty:
//         while (scanf ("%s", str) == 0) puts ("print yes or no");
//         str[4] = '\0';
//         for (int i = 0; str[i]; str[i] = tolower (str[i]), i++);
//         if (!YES(str) && !NO(str)) goto third_qwerty;
//
//         if (YES(str))
//         {
//             printf (GREEN "\nI knew\n\n" ALL);
//
//             return TREE_NO_ERROR;
//         }
//         else return AkinatorAddSign (Tree);
//
//         return TREE_NO_ERROR;
//     }
//     else return AkinatorAdd (Tree);
//
// }
//
//
// TREE_ERROR AkinatorAdd (Node* Tree)
// {
//     if (Tree == nullptr) return TREE_NULLPTR;
//
//     if (!(Tree->left  = (Node*) calloc (1, sizeof (Node*)))) return TREE_CALLOC_ERROR;
//     if (!(Tree->right = (Node*) calloc (1, sizeof (Node*)))) return TREE_CALLOC_ERROR;
//
//     Tree->right->value     = Tree->value;
//     if (!(Tree->left->value  = (char*) calloc (1, MAX_STR_SIZE))) return TREE_CALLOC_ERROR;
//     if (!(Tree->value        = (char*) calloc (1, MAX_STR_SIZE))) return TREE_CALLOC_ERROR;
//
//     puts ("Who is he/she?");
//     while (scanf("%s[^\n]", Tree->left->value) != 1);
//     printf ("How is %s different from %s?\n", Tree->left->value, Tree->right->value);
//
//     scanf ("%s", Tree->value);
//     return TREE_NO_ERROR;
// }
//
// TREE_ERROR AkinatorAddSign (Node* Tree)
// {
//     if (Tree == nullptr) return TREE_NULLPTR;
//
//     if (!(Tree->left  = (Node*) calloc (1, sizeof (Node*)))) return TREE_CALLOC_ERROR;
//     if (!(Tree->right = (Node*) calloc (1, sizeof (Node*)))) return TREE_CALLOC_ERROR;
//
//     if (!(Tree->left->value  = (char*) calloc (1, MAX_STR_SIZE))) return TREE_CALLOC_ERROR;
//     if (!(Tree->right->value = (char*) calloc (1, MAX_STR_SIZE))) return TREE_CALLOC_ERROR;
//
//     puts ("Who is he/she?");
//     while (scanf("%s[^\n]", Tree->left->value) != 1);
//
//     return TREE_NO_ERROR;
// }

TREE_ERROR AkinatorAddStr (Node* pNode, text* txt)
{
    if (pNode == nullptr || txt == nullptr)
        return TREE_NULLPTR;

    pNode->value.str = txt->line[pNode->value.line].str;

    if (pNode->left != nullptr)
        AkinatorAddStr (pNode->left, txt);
    if (pNode->right != nullptr)
        AkinatorAddStr (pNode->right, txt);

    return TREE_NO_ERROR;
}

TREE_ERROR AkinatorRead (Node** ppNode, char* data, char* str)
{
    if (ppNode == nullptr || data == nullptr || str == nullptr)
        return TREE_NULLPTR;

    puts ("bark");
    TREE_ERROR ERROR = TREE_NO_ERROR;
    if ((ERROR = readfile (ppNode, data)) != TREE_NO_ERROR)
        return ERROR;
    puts ("bark");
    text txt;
    readtext (&txt, str);
    if ((ERROR = AkinatorAddStr (*ppNode, &txt)) != TREE_NO_ERROR)
        return ERROR;

    return TREE_NO_ERROR;
}

