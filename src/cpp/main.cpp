#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "../header/tree.h"
#include "../header/readfile.h"
#include "../header/Akinator.h"
#include "../../DEBUG/def.h"

int main()
{
    Node* Tree = (Node*) calloc (1, sizeof (Node));

    readfile (&Tree, "data/data.txt");
    #ifdef DEBUG
    TreePrint (Tree);
    #endif

    for(;;)
    {
        Akinator (Tree);
        puts ("Do you want end game?");
        if (YESorNO())
            break;
    }
    // PRINT_DEBUG ("\n\nbark");
    // TreePrint (Tree);
    // PRINT_DEBUG ("bark\n\n");
    // TreePrint (Tree);
    TreeFPrint (Tree, "data/data.txt");
    // sleep (1);
    TreeDtor (Tree);

}
