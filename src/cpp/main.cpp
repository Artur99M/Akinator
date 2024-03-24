#include <stdio.h>
#include <stdlib.h>
#include "../header/tree.h"
// #include "../header/readfile.h"
#include "../header/Akinator.h"

int main()
{
    Node* Tree = (Node*) calloc (1, sizeof (Node));

    AkinatorRead (&Tree, "data/data.txt", "data/str.txt");

    // for(;;) Akinator (Tree);

}
