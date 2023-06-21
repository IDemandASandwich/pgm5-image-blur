#define FILE_OPEN_ERROR     10
#define FILE_WRITE_ERROR    11
#define FILE_CLOSE_ERROR    12
#define FILE_SAVE_SUCCESS   13

#define PIX(im, x, y) ( (im)->px[(y) * (im)->width + (x)] )

typedef struct{
    unsigned int    width;
    unsigned int    height;
    unsigned char   *px;
}GSI;

GSI *gsi_create_empty(void);

GSI *gsi_create_with_geometry_and_color(unsigned int m, unsigned int n, unsigned char color);

char gsi_save_as_pgm5(GSI *img, char *file_name, char *comment);

GSI *gsi_create_by_pgm5(char *file_name);

char gsi_gauss_blur(GSI *to_blur, GSI *blurred, float sigsq);

GSI *gsi_read_header_pgm5(char *file_name);

void gsi_destroy(GSI *img);