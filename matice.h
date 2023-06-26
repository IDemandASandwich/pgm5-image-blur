#define BLUR_SUCCESS        1
#define BLUR_FAILURE        2

#define FILE_OPEN_ERROR     3
#define FILE_WRITE_ERROR    4
#define FILE_CLOSE_ERROR    5
#define FILE_SAVE_SUCCESS   6

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

void gsi_destroy(GSI *img);