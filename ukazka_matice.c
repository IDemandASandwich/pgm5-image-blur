#include <stdio.h>
#include <stdlib.h>
#include "matice.h"

int main(void)
{
    GSI *to_blur = gsi_create_by_pgm5("minitel-main.pgm");
    GSI *blurred = gsi_create_by_pgm5("minitel-main.pgm");

    gsi_gauss_blur(to_blur, blurred, 1.5);

    gsi_save_as_pgm5(blurred, "blurred.pgm", "blurred");

    gsi_destroy(blurred);
    gsi_destroy(to_blur);
    
    return 0;
}