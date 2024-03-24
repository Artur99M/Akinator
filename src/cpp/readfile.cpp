#include "../header/readfile.h"
#include "../Onegin/header/readtext.h"
// #include "../Onegin/header/txtdtor.h"
#include "../Onegin/header/outtext.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#define LEAF '*'
#define IN_BRANCH '{'
#define OUT_BRANCH '}'

TREE_ERROR TreeRead (Node* pNode, text* txt, size_t* nline, Node* array);


TREE_ERROR readfile (Node** Tree, char* file)
{
    if (Tree == nullptr)
        return TREE_NULLPTR;

    text txt;
    readtext (&txt, file);
    outtext (&txt, "outtext.txt");
    size_t nline = 0;
    Node* array = (Node*) calloc (txt.numlines / 3, sizeof (Node));
    *Tree = array;
    TREE_ERROR ERROR = TreeRead (*Tree, &txt, &nline, array);
    printf ("readfile >>> finish\n");

    // txtDtor (&txt);

    return ERROR;
}

TREE_ERROR TreeRead (Node* pNode, text* txt, size_t* nline, Node* array)
{
    // usleep (1000);
    if (pNode == nullptr || txt == nullptr || nline == nullptr || array == nullptr)
        return TREE_NULLPTR;


    char c = '\0';
    printf ("TreeRead >>> *nline = %lu\n", *nline);
    printf ("TreeRead >>> I start sscanf\n");
    printf ("TreeRead >>> pNode = %p\n", pNode);
    printf ("TreeRead >>> txt->line[*nline].str = \"%s\"\n", txt->line[*nline].str);
    sscanf (txt->line[*nline].str, "%c", &c);
    printf ("TreeRead >>> first sscanf: c = %c\n", c);
    (*nline)++;
    printf ("TreeRead >>> *nline = %lu\n", *nline);

    if (c == '{')
    {
        printf ("TreeRead >>> func start do it smth\n");
        // sscanf (txt->line[*nline].str, "%s", pNode->value);
        pNode->value = txt->line[*nline].str;
        printf ("TreeRead >>> *nline = %lu\n", *nline);
        (*nline)++;
        printf ("TreeRead >>> *nline = %lu\n", *nline);
        printf ("TreeRead >>> value = %s\n", pNode->value);
        printf ("TreeRead >>> find memmory for left\n");
        printf ("TreeRead >>> &(pNode->left) = %p\n", &(pNode->left));
        pNode->left = array + (*nline);
        printf ("TreeRead >>> start see left\n");
        printf ("TreeRead >>> pNode->left = %p\n", pNode->left);
        printf ("TreeRead >>> *nline = %lu\n", *nline);
        if (TreeRead (pNode->left, txt, nline, array) == TREE_VOID)
            pNode->left = nullptr;
        printf ("TreeRead >>> *nline = %lu\n", *nline);
        printf ("TreeRead >>> finish see left\n");
        printf ("TreeRead >>> pNode->left = %p\n", pNode->left);
        printf ("TreeRead >>> find memmory for right\n");
        printf ("TreeRead >>> &(pNode->right) = %p\n", &(pNode->right));
        pNode->right = array + (*nline);
        printf ("TreeRead >>> pNode->right = %p\n", pNode->right);
        printf ("TreeRead >>> start see right\n");
        if (TreeRead (pNode->right, txt, nline, array) == TREE_VOID)
            pNode->right = nullptr;
        printf ("TreeRead >>> *nline = %lu\n", *nline);
        printf ("TreeRead >>> finish see right\n");
        printf ("TreeRead >>> pNode->right = %p\n", pNode->right);
        sscanf (txt->line[*nline].str, "%c", &c);
        printf ("TreeRead >>> third sscanf: c = %c\n", c);
        if (c != '}')
            return TREE_HZ_ERROR;
        (*nline)++;
        printf ("TreeRead >>> *nline = %lu\n", *nline);
    }
    else if (c == '*')
    {
        printf ("TreeRead >>> free memory\n");
        return TREE_VOID;
    }
    else
    {
        printf ("TreeRead >>> Strange ERROR\n");
        return TREE_HZ_ERROR;
    }

    return TREE_NO_ERROR;
}
