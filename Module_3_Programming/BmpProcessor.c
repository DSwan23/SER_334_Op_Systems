/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

// Include the header file
#include "BmpProcessor.h"

/**
 * read BMP header of a file. Useful for converting files from PPM to BMP.
 *
 * @param  file: A pointer to the file being read or written
 * @param  header: Pointer to the destination BMP header
 */
void readBMPHeader(FILE* file, struct BMP_Header* header)
{
    // Read the signature from the header
    fread(header->signature, sizeof(char)*2, 1, file);
    // Read the size of the BMP file
    fread(header->size, sizeof(int), 1, file);
    // Read the program specific reserved fields
    fread(header->reserved1, sizeof(short), 1, file);
    fread(header->reserved2, sizeof(short), 1, file);
    // Read the offset to the pixel array
    fread(header->offset, sizeof(int), 1, file);
}

/**
 * make BMP header based on width and height. 
 * The purpose of this is to create a new BMPHeader struct using the information 
 * from a PPMHeader when converting from PPM to BMP.
 *
 * @param  header: Pointer to the destination DIB header
 * @param  width: Width of the image that this header is for
 * @param  height: Height of the image that this header is for
 */
void makeBMPHeader(struct BMP_Header* header, int width, int height)
{
    // Assign the default values to the header
    header->signature = "BM";
    header->reserved1 = 0;
    header->reserved2 = 0;
    // Assign the passed values to the header
    header->size = width*height;
}

/**
 * write BMP header of a file. Useful for converting files from PPM to BMP.
 *
 * @param  file: A pointer to the file being read or written
 * @param  header: The header made by makeBMPHeader function
 */
void writeBMPHeader(FILE* file, struct BMP_Header* header)
{
    // Write the BMP header struct to the file
    fwrite(header, sizeof(struct BMP_Header), 1, file);
}
/**
 * read DIB header from a file. Useful for converting files from PPM to BMP.
 *
 * @param  file: A pointer to the file being read or written
 * @param  header: Pointer to the destination DIB header
 */
void readDIBHeader(FILE* file, struct DIB_Header* header)
{
    // Read the number of bytes in the header
    fread(header->size, sizeof(int), 1, file);
    // Read the width in pixels
    fread(header->width, sizeof(int), 1, file);
    // Read the height in pixels
    fread(header->height, sizeof(int), 1, file);
    // Read the number of color planes being used
    fread(header->num_color_planes, sizeof(int), 1, file);
    // Read the number of bits per pixel
    fread(header->num_bits_per_pixel, sizeof(int), 1, file);
    // Read the compression being used
    fread(header->compression, sizeof(short), 1, file);
    // Read the size of the raw bitmap data
    fread(header->size_raw_data, sizeof(short), 1, file);
    // Read the horizontal print resolution
    fread(header->print_res_horizontal, sizeof(int), 1, file);
    // Read the vertical print resolution 
    fread(header->print_res_vertical, sizeof(int), 1, file);
    // Read the number of colors in the palette
    fread(header->palette_color_count, sizeof(int), 1, file);
    // Read the number of important colors
    fread(header->important_colors, sizeof(int), 1, file);
}

/**
 * write DIB header of a file. Useful for converting files from PPM to BMP.
 *
 * @param  file: A pointer to the file being read or written
 * @param  header: The header made by makeDIBHeader function
 */
void writeDIBHeader(FILE* file, struct DIB_Header* header)
{
    // Write the struct to the file
    fwrite(header, sizeof(struct DIB_Header), 1, file);
}

 /**
 * Makes new DIB header based on width and height. Useful for converting files from PPM to BMP.
 *
 * @param  header: Pointer to the destination DIB header
 * @param  width: Width of the image that this header is for
 * @param  height: Height of the image that this header is for
 */
void makeDIBHeader(struct DIB_Header* header, int width, int height)
{
    // Assign default values
    header->num_color_planes = 1;
    header->compression = 0;
    header->print_res_horizontal = 3780;
    header->print_res_vertical = 3780;
    header->num_color_planes = 0;
    header->important_colors = 0;
    // Add the size
    header->size = width * height;
}

