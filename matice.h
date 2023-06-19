#define PIX(im, x, y) ( (im)->px[(y) * (im)->width + (x)] )

typedef struct{
    unsigned int    width;
    unsigned int    height;
    unsigned char   *px;
}GSI;

GSI *gsi_create_empty(void);

GSI *gsi_create_with_geometry(unsigned int m, unsigned int n);