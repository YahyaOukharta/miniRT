#include <fcntl.h>

typedef struct  s_image
{
    BITMAP_FILE_HEADER file_info;
    BITMAP_INFO_HEADER bitmap_info;
    byte *data;
}               t_image;
 
and
 
// BMP File header
typedef struct s_bmp_file_header {
    byte bfType[2];    
    dword bfSize;
    word bfReserved1;    
    word bfReserved2;
    dword bfOffBits;
} t_bmp_file_header;
 
// BMP Image header
typedef struct s_bmp_info_header {
    dword biSize;
    dword biWidth;
    dword biHeight;
    word biPlanes;                   
    word biBitCount;
    dword biCompression;       
    dword biSizeImage;
    dword biXPelsPerMeter;     
    dword biYPelsPerMeter;
    dword biClrUsed;               
    dword biClrImportant;
} t_bmp_info_header;