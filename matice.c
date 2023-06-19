#include <stdlib.h>
#include <unistd.h>
#include "matice.h"

GSI *gsi_create_empty(void){
    GSI *ptr = (GSI*)malloc(sizeof(GSI));
    if(ptr == NULL)
    {
        return NULL;
    }

    ptr->width = 0;
    ptr->height = 0;
    ptr->px = NULL;

    return ptr;
}

GSI *gsi_create_with_geometry(unsigned int m, unsigned int n){
    GSI *ptr = gsi_create_empty();

    ptr->px = (unsigned char*)malloc(m * n * sizeof(unsigned char));
    if(ptr->px == NULL)
    {
        free(ptr);
        return NULL;
    }

    ptr->width = m;
    ptr->height = n;

    return ptr;
}