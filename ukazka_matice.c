#include <stdio.h>
#include <stdlib.h>
#include "matice.h"

int main(void)
{
    GSI *ptr = gsi_create_with_geometry_and_color(25,25, 250);

    gsi_save_as_pgm5(ptr, "pic.pgm", "testing");

    free(ptr);
    free(ptr->px);
    return 0;
}