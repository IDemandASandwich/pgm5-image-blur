#include <stdio.h>
#include <stdlib.h>
#include "matice.h"

int main(void)
{
//    GSI *img = gsi_create_with_geometry_and_color(20, 40, 77);
//    gsi_save_as_pgm5(img, "pic.pgm", "testing");
//    GSI *to_blur = gsi_create_by_pgm5("pic.pgm");

    GSI *to_blur = gsi_create_with_geometry_and_color(50, 50, 74);
    GSI *blurred = gsi_create_with_geometry_and_color(50, 50, 0);

    gsi_gauss_blur(to_blur, blurred, 122.5);

    gsi_save_as_pgm5(blurred, "blurred.pgm", "blurred");

    gsi_destroy(blurred);
    gsi_destroy(to_blur);
    return 0;
}