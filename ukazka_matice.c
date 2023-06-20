#include <stdio.h>
#include <stdlib.h>
#include "matice.h"

int main(void)
{
    char* name = "ahoj.pgm";

    GSI *ptr = gsi_create_with_geometry_and_color(5,5, 27);

    printf("%d", gsi_save_as_pgm5(ptr, name, NULL));

    free(ptr);
    free(ptr->px);
    return 0;
}