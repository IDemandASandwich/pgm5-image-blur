#include <stdio.h>
#include <stdlib.h>
#include "matice.h"

int main(void)
{
    GSI *img = gsi_create_by_pgm5("pic.pgm");

//    GSI *img = gsi_create_with_geometry_and_color(25, 25, 255);
//    gsi_save_as_pgm5(img, "pic.pgm", "testing");

    gsi_destroy(img);
    return 0;
}