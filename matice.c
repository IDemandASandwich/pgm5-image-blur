#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <math.h>
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

    snprintf(header, sizeof(header), "P5\n#%s\n%d %d 255\n", comment, img->width, img->height);

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

GSI *gsi_create_by_pgm5(char *file_name){
    GSI* img = gsi_create_empty();

    unsigned int val = 0, i = 0;
    unsigned char temp[3], c = 0;

    int fd = open(file_name, O_RDONLY);
    if (fd < 0) {
        gsi_destroy(img);
        return NULL;
    }

    //obsahuje P5 ?
    val = read(fd, temp, 2);
    if(val != 2 || temp[0] != 80 || temp[1] != 53){
        gsi_destroy(img);
        close(fd);
        return NULL;
    }

    if(lseek(fd, 1, SEEK_CUR) == -1){
        gsi_destroy(img);
        close(fd);
        return NULL;
    }

    //comment
    while (read(fd, &c, 1) == 1 && c != '\n');

    //sirka
    temp[0] = temp[1] = temp[2] = 0;
    i = 0;

    while(read(fd, &c, 1) == 1 && c != ' '){
        temp[i] = c;
        i++;
    }

    img->width = atoi(temp);

    //vyska
    temp[0] = temp[1] = temp[2] = 0;
    i = 0;

    while(read(fd, &c, 1) == 1 && c != ' '){
        temp[i] = c;
        i++;
    }
    
    img->height = atoi(temp);

    //najvyssia hodnota (preskocime kedze ju netreba)
    while(read(fd, &c, 1) == 1 && c != '\n');

    //citanie samotneho obrazku
    img->px = (unsigned char*)malloc(img->width * img->height * sizeof(unsigned char));

    val = read(fd, img->px, img->width * img->height * sizeof(unsigned char));
    if(val != img->width * img->height){        
        gsi_destroy(img);
        close(fd);
        return NULL;
    }

    if(close(fd) == -1){
        gsi_destroy(img);
        return NULL;
    }
    return img;
}

char gsi_gauss_blur(GSI *to_blur, GSI *blurred, float sigsq){
    unsigned int y = 0, x = 0;

    if (to_blur == NULL || blurred == NULL || to_blur->px == NULL || blurred->px == NULL ||
        to_blur->width != blurred->width || to_blur->height != blurred->height) {
        return BLUR_FAILURE; 
    }

    // Vypocitaj velkost kernelu podla sigsq
    int kernel_size = ceil(sqrt(2.0 * sigsq) * 3.0) * 2 + 1;
    int kernel_radius = kernel_size / 2;

    // vytvor a vypln gauss kernel
    float *kernel = (float *)malloc(kernel_size * sizeof(float));
    if(kernel == NULL){
        return BLUR_FAILURE;
    }

    float sum = 0.0;

    for (int i = 0; i < kernel_size; i++) {
        int x = i - kernel_radius;
        kernel[i] = exp(-x * x / (2.0 * sigsq));
        sum += kernel[i];
    }

    for (int i = 0; i < kernel_size; i++) {
        kernel[i] /= sum; // Normalizuj kernel aby sucet bol 1.0
    }

    // Apply
    for (y = 0; y < to_blur->height; y++) {
        for (x = 0; x < to_blur->width; x++) {
            float blurred_value = 0.0;
            for (int i = 0; i < kernel_size; i++) {
                int px = x + i - kernel_radius;
                if (px < 0 || px >= to_blur->width) {
                    continue; // preskoc pixely mimo obrazku
                }
                blurred_value += PIX(to_blur, px, y) * kernel[i];
            }
            PIX(blurred, x, y) = (unsigned char)blurred_value;
        }
    }

    for (y = 0; y < to_blur->height; y++) {
        for (x = 0; x < to_blur->width; x++) {
            float blurred_value = 0.0;
            for (int i = 0; i < kernel_size; i++) {
                int py = y + i - kernel_radius;
                if (py < 0 || py >= to_blur->height) {
                    continue; // preskoc pixely mimo obrazku
                }
                blurred_value += PIX(blurred, x, py) * kernel[i];
            }

        PIX(blurred, x, y) = (unsigned char)blurred_value;
        }
    }

    free(kernel);

    return BLUR_SUCCESS;
}

void gsi_destroy(GSI *img){
    free(img->px);
    free(img);
}