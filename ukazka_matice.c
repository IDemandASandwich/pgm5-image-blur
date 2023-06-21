#include <stdio.h>
#include <stdlib.h>
#include "matice.h"

int main(void)
{
    GSI *img = gsi_create_by_pgm5("pic.pgm");

    gsi_destroy(img);
    return 0;
}