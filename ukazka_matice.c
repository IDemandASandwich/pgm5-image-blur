#include <stdio.h>
#include <stdlib.h>
#include "matice.h"

int main(void)
{
    GSI *ptr = gsi_create_with_geometry(5,5);

    free(ptr);
    free(ptr->px);
    return 0;
}