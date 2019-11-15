#ifndef BMP_PROCESSOR_H
#define BMP_PROCESSOR_H
struct BMP_Header {
    char signature[2];  // ID Field
    int size;           // Size of the BMP File
    int offset;         // Offset where the pixel array can be found
    short reserved1;    // Program specific
    short reserved2;    // Program specific 2
};

struct DIB_Header{
    int size;                       // Number of bytes in the DIB header
    int img_width;                  // The width of the bitmap (in pixels)
    int img_height;                 // The height of the bitmap (in pixels)
    short num_color_planes;         // The number of color planes being used
    short num_bits_per_pixel;       // The number of bits per pixel
    int compression;                // The compression mode being used
    int size_img_data;              // The size of the raw bitmap data
    int pixels_per_meter_x;         // The numbers of pixels in a meter, x 
    int pixels_per_meter_y;         // The numbers of pixels in a meter, y
    int palette_color_count;        // The number of colors in the palette
    int color_table_color_count;    // The number of colors in the color table
    int important_colors;           // The number of important colors used, typically 0
};

struct DIB_Header{
    int size;               // Number of bytes in the DIB header
    int width;              // The width of the bitmap (in pixels)
    int height;             // The height of the bitmap (in pixels)
    int num_color_planes;   // The number of color planes being used
    int num_bits_per_pixel; // The number of bits per pixel
    short compression;        // The compression mode being used
    short size_raw_data;      // The size of the raw bitmap data
    int print_res_horizontal;// The resolution of the image should it be printed
    int print_res_vertical;
    int palette_color_count;// The number of colors in the palette
    int important_colors;   // The number of important colors used, typically 0
};

/**
 * read BMP header of a file. Useful for converting files from PPM to BMP.
 *
 * @param  file: A pointer to the file being read or written
 * @param  header: Pointer to the destination BMP header
 */
void readBMPHeader(FILE* file, struct BMP_Header* header);

/**
 * write BMP header of a file. Useful for converting files from PPM to BMP.
 *
 * @param  file: A pointer to the file being read or written
 * @param  header: The header made by makeBMPHeader function
 */
void writeBMPHeader(FILE* file, struct BMP_Header* header);

/**
 * read DIB header from a file. Useful for converting files from PPM to BMP.
 *
 * @param  file: A pointer to the file being read or written
 * @param  header: Pointer to the destination DIB header
 */
void readDIBHeader(FILE* file, struct DIB_Header* header);

/**
 * write DIB header of a file. Useful for converting files from PPM to BMP.
 *
 * @param  file: A pointer to the file being read or written
 * @param  header: The header made by makeDIBHeader function
 */
void writeDIBHeader(FILE* file, struct DIB_Header* header);

/**
 * make BMP header based on width and height. 
 * The purpose of this is to create a new BMPHeader struct using the information 
 * from a PPMHeader when converting from PPM to BMP.
 *
 * @param  header: Pointer to the destination DIB header
 * @param  width: Width of the image that this header is for
 * @param  height: Height of the image that this header is for
 */
void makeBMPHeader(struct BMP_Header* header, int width, int height);


 /**
 * Makes new DIB header based on width and height. Useful for converting files from PPM to BMP.
 *
 * @param  header: Pointer to the destination DIB header
 * @param  width: Width of the image that this header is for
 * @param  height: Height of the image that this header is for
 */
void makeDIBHeader(struct DIB_Header* header, int width, int height);


/**
 * read Pixels from BMP file based on width and height.
 *
 * @param  file: A pointer to the file being read or written
 * @param  pArr: Pixel array of the image that this header is for
 * @param  width: Width of the image that this header is for
 * @param  height: Height of the image that this header is for
 */
void readPixelsBMP(FILE* file, struct Pixel** pArr, int width, int height);


/**
 * write Pixels from BMP file based on width and height.
 *
 * @param  file: A pointer to the file being read or written
 * @param  pArr: Pixel array of the image that this header is for
 * @param  width: Width of the image that this header is for
 * @param  height: Height of the image that this header is for
 */
void writePixelsBMP(FILE* file, struct Pixel** pArr, int width, int height);

#endif BMP_PROCESSOR_H