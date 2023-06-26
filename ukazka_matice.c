#include <stdio.h>
#include <stdlib.h>
#include "matice.h"

int main(void)
{
    GSI *to_blur = gsi_create_with_geometry_and_color(150, 150, 100);
    GSI *blurred = gsi_create_with_geometry_and_color(150, 150, 0);

    gsi_gauss_blur(to_blur, blurred, 150.0);

    gsi_save_as_pgm5(blurred, "blurred.pgm", "blurred");

    gsi_destroy(blurred);
    gsi_destroy(to_blur);
    return 0;
}