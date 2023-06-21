#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <sys/stat.h>
#include "matice.h"

#include <stdio.h>

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

GSI *gsi_create_with_geometry_and_color(unsigned int m, unsigned int n, unsigned char color){

    GSI *ptr = gsi_create_empty();
    if(ptr == NULL){
        return NULL;
    }

    ptr->px = (unsigned char*)malloc(m * n * sizeof(unsigned char));
    if(ptr->px == NULL){
        free(ptr);
        return NULL;
    }

    (unsigned char*)memset(ptr->px, color, m*n);
    ptr->width = m;
    ptr->height = n;

    return ptr;
}

char gsi_save_as_pgm5(GSI *img, char *file_name, char *comment){
    int fd, write_b;
    char header[50];
    
    fd = open(file_name, O_CREAT | O_WRONLY, S_IRUSR | S_IWUSR);
    if(fd < 0){
        return FILE_OPEN_ERROR;
    }

    snprintf(header, sizeof(header), "P5\n#%s\n%d %d\n255\n", comment, img->width, img->height);

    write_b = write(fd, header, strlen(header));
    if (write_b < 0) {
        close(fd);
        return FILE_WRITE_ERROR;
    }

    write_b = write(fd, img->px, img->height * img->width);
    if(write_b < 0){
        return FILE_WRITE_ERROR;
    }

    write_b = close(fd);
    if(write_b == -1){
        return FILE_CLOSE_ERROR;
    }

    return FILE_SAVE_SUCCESS;
}

GSI *gsi_create_by_pgm5(char *file_name) {
    int width, height, max_val, ptr, c;
    char temp[3];

    int fd = open(file_name, O_RDONLY);
    if (fd < 0) {
        return NULL;
    }

    ptr = read(fd, temp, 2);
    if(ptr != 2 || temp[0] != 80 || temp[1] != 53){
        return NULL;
    }

    if(lseek(fd, 1, SEEK_CUR) == -1){
        return NULL;
    }

    while (read(fd, &c, 1) == 1 && c != '\n');

    ptr = read(fd, &width, sizeof(int));
    if(ptr != sizeof(int)){
        return NULL;
    }

    if(lseek(fd, 1, SEEK_CUR) == -1){
        return NULL;
    }

    ptr = read(fd, &height, sizeof(int));
    if(ptr != sizeof(int)){
        return NULL;
    }

    printf("%d\n",width);
    printf("%d\n",height);

    GSI* img = gsi_create_empty();
    img->width = width;
    img->height = height;
    img->px = (unsigned char*)malloc(width * height * sizeof(unsigned char));

    return img;
}

void gsi_destroy(GSI *img){
    free(img->px);
    free(img);
}