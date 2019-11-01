/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

// Include the header file
#include "PpmProcessor.h"

/**
 * read PPM header of a file. Useful for converting files from BMP to PPM.
 *
 * @param  file: A pointer to the file being read or written
 * @param  header: Pointer to the destination PPM header
 */
void readPPMHeader(FILE* file, struct PPM_Header* header)
{
    // Read the magic number in
    fread(header->magic_number, sizeof(char)*2, 1, file);
    // Read in a white space
    fread(header->whitespace, sizeof(char), 1, file);
    // Read in the width
    fread(header->width, sizeof(int), 1, file);
    // Read in a white space
    fread(header->whitespace, sizeof(char), 1, file);
    // Read in the height
    fread(header->height, sizeof(int), 1, file);
    // Read in a white space
    fread(header->whitespace, sizeof(char), 1, file);
    // Read in the maximum color
    fread(header->maximum_color, sizeof(int), 1, file);
}