#include <stdio.h>
#include <stdlib.h>
#include "../header/tree.h"
#include "../header/readfile.h"
#include "../header/Akinator.h"
#include "../Onegin/header/readtext.h"

int main()
{
    Node* Tree = (Node*) calloc (1, sizeof (Node));

    text txt;
    readfile (&Tree, "data/data.txt");
    TreePrint (Tree);
}
