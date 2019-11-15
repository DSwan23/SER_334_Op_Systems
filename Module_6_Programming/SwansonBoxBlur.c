////////////////////////////////////////////////////////////////////////////////
//INCLUDES
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <math.h>

////////////////////////////////////////////////////////////////////////////////
//MACRO DEFINITIONS

#pragma warning(disable: 4996)

//problem assumptions
#define BMP_HEADER_SIZE_BYTES 14
#define BMP_DIB_HEADER_SIZE_BYTES 40
#define MAXIMUM_IMAGE_SIZE 256

typedef unsigned char uint8_t;
//bmp compression methods
//none:
#define BI_RGB 0
#define THREAD_COUNT 1

//TODO: finish me


////////////////////////////////////////////////////////////////////////////////
//DATA STRUCTURES

struct BMP_Header {
    char signature[2];      //ID field
    int size;               //Size of the BMP file
    short reserved1;        //Application specific
    short reserved2;        //Application specific
    int offset_pixel_array; //Offset where the pixel array (bitmap data) can be found
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

struct pixel{
    uint8_t red; // Red value
    uint8_t green; // Green Value
    uint8_t blue; // Blue value
};


////////////////////////////////////////////////////////////////////////////////
//SUPPORTING FUNCTIONS

int blur_value(int inputVals[])
{
    // Create a sum variable
    int sum = 0, count = 0, total = 0;
    // Walk through and add all of the input values together
    for(int i = 0; i < sizeof(inputVals)/sizeof(inputVals[0]) ; i ++)
    {
        sum = sum + inputVals[i];
        count++;
    }
    // Calculate the value
    total = sum / count;
    // Return the total
    return total;
}


////////////////////////////////////////////////////////////////////////////////
//MAIN PROGRAM CODE
void main(int argc, char* argv[]) {

	// Get input and output from command line
    char *input_file, *output_file;
    if(argc > 0)
    {
        input_file = argv[0];
        output_file = argv[1];
    }
    else
    {
        input_file = "test1wonderbread.bmp";
        output_file ="test1_output.bmp";
    }


	//sample code to read first 14 bytes of BMP file format
	FILE* file = fopen(input_file, "rb");
	struct BMP_Header header;
        struct DIB_Header d_header;

	//read bitmap file header (14 bytes)
	fread(&header.signature, sizeof(char)*2, 1, file);
	fread(&header.size, sizeof(int), 1, file);
	fread(&header.reserved1, sizeof(short), 1, file);
	fread(&header.reserved2, sizeof(short), 1, file);
	fread(&header.offset_pixel_array, sizeof(int), 1, file);
        
        // Debugging statements
        printf("----------- File Header -----------\n");
	printf("signature: %c%c\n", header.signature[0], header.signature[1]);
	printf("size: %d\n", header.size);
	printf("reserved1: %d\n", header.reserved1);
	printf("reserved2: %d\n", header.reserved2);
	printf("offset_pixel_array: %d\n\n", header.offset_pixel_array);
        
        //Read in the DIB header
        fread(&d_header.size , sizeof(int), 1, file);
        fread(&d_header.img_width , sizeof(int), 1, file);
        fread(&d_header.img_height , sizeof(int), 1, file);
        fread(&d_header.num_color_planes , sizeof(short), 1, file);
        fread(&d_header.num_bits_per_pixel , sizeof(short), 1, file);
        fread(&d_header.compression , sizeof(int), 1, file);
        fread(&d_header.size_img_data , sizeof(int), 1, file);
        fread(&d_header.pixels_per_meter_x , sizeof(int), 1, file);
        fread(&d_header.pixels_per_meter_y , sizeof(int), 1, file);
        fread(&d_header.color_table_color_count , sizeof(int), 1, file);
        fread(&d_header.important_colors , sizeof(int), 1, file);
        
        // Debugging statements
        printf("----------- DIB Header -----------\n");
        printf("size: %d\n", d_header.size);
        printf("image width: %d\n", d_header.img_width);
        printf("image height : %d\n", d_header.img_height);
        printf("color planes: %d\n", d_header.num_color_planes);
        printf("bits per pixel: %d\n", d_header.num_bits_per_pixel);
        printf("compression method: %d\n", d_header.compression);
        printf("image size: %d\n", d_header.size_img_data);
        printf("pixels per meter (x): %d\n", d_header.pixels_per_meter_y);
        printf("pixels per meter (y): %d\n", d_header.pixels_per_meter_x);
        printf("colors in color table: %d\n", d_header.color_table_color_count);
        printf("number of important colors: %d\n\n", d_header.important_colors);
        
        // Calculate row size
        int rowsize = (int) ceil((double)((d_header.num_bits_per_pixel * d_header.img_width)/32)) * 4;
                
        // Calculate padding
        int padding = rowsize % 4;
        
        // Debuggin statements
        printf("----------- DIB Header -----------\n");
        printf("row size: %d\n", rowsize);
        printf("row padding: %d\n", padding);
        printf("start address: %d\n", header.offset_pixel_array);
        // Create bitmap matrix
        struct pixel pixel_array [d_header.img_width][d_header.img_height];
        
        // Go to the beginning of the pixel array in the file, from the begging of the file
        fseek(file, header.offset_pixel_array, 1);
        
        // Load in the bitmap image into the matrix
        int rowidx, colidx;        
        for(colidx = d_header.img_height - 1; colidx >= 0; colidx--)
        {
            for(rowidx = 0; rowidx < d_header.img_width; rowidx++)
            {
                // Create a new pixel struct
                struct pixel pixel_val;
                // Get RGB values value
                fread(&pixel_val.blue, sizeof(uint8_t), 1, file);
                fread(&pixel_val.green, sizeof(uint8_t), 1, file);
                fread(&pixel_val.red, sizeof(uint8_t), 1, file);
                // Store the pixel in the array
                pixel_array[rowidx][colidx].red = pixel_val.red;
                pixel_array[rowidx][colidx].blue = pixel_val.blue;
                pixel_array[rowidx][colidx].green = pixel_val.green;
            }
            // move the file pointer to account for padding
            if(padding != 0)
                fseek(file, padding, 2);
        }    
        
        // Close the file
	fclose(file);
        
        // walk through the pixel array and blur the image
        for(colidx = 0; colidx < d_header.img_height; colidx++)
        {
            for(rowidx = 0; rowidx < d_header.img_width; rowidx++)
            {
                // Should be on seperate threads, pulled from the thread pool.
                
                // start row and column
                int startRow, startCol, width = 3, height = 3, values = 9;
                // Set the start row
                if(rowidx > 0 && rowidx < d_header.img_height)
                {
                    startRow = rowidx - 1;
                }
                else if(rowidx == 0 || rowidx == d_header.img_height -1)
                {
                    startRow = rowidx;
                    values = values -3;
                }
                // set the start column
                if(colidx > 0 && colidx < d_header.img_width)
                {
                    startCol = colidx - 1;
                }
                else if(colidx == 0 ||colidx == d_header.img_width - 1)
                {
                    startCol = colidx;
                    values = values - 3;
                }
                else if((colidx == 0 && rowidx == 0) || 
                        (colidx == d_header.img_width - 1 &&  rowidx == d_header.img_height -1 ) ||
                        (colidx == 0 && rowidx == d_header.img_height -1) || 
                        (colidx == d_header.img_width - 1 &&  rowidx == 0 )
                        )
                {
                    startCol = colidx;
                    values = values - 3;
                }
                int redVals[values], greenVals[values], blueVals[values];
                // Gather the values
                for(int w = 0; w < width; w++ )
                {
                    for(int h = 0; h < height; h++ )
                    {
                        // Check to see if the next index is valid
                        
                        // Add the value to the array
                    }
                }
                // Compute the new RGB value for the pixel in question
                
                // Store the new values in the pixel
            }
        } 
        
        
        // Open the output file
        file = fopen(output_file, "wb");
        // Write bitmap file header (14 bytes)
	fwrite(&header.signature, sizeof(char)*2, 1, file);
	fwrite(&header.size, sizeof(int), 1, file);
	fwrite(&header.reserved1, sizeof(short), 1, file);
	fwrite(&header.reserved2, sizeof(short), 1, file);
	fwrite(&header.offset_pixel_array, sizeof(int), 1, file);
        // Write the dib header
        fwrite(&d_header.size , sizeof(int), 1, file);
        fwrite(&d_header.img_width , sizeof(int), 1, file);
        fwrite(&d_header.img_height , sizeof(int), 1, file);
        fwrite(&d_header.num_color_planes , sizeof(short), 1, file);
        fwrite(&d_header.num_bits_per_pixel , sizeof(short), 1, file);
        fwrite(&d_header.compression , sizeof(int), 1, file);
        fwrite(&d_header.size_img_data , sizeof(int), 1, file);
        fwrite(&d_header.pixels_per_meter_x , sizeof(int), 1, file);
        fwrite(&d_header.pixels_per_meter_y , sizeof(int), 1, file);
        fwrite(&d_header.color_table_color_count , sizeof(int), 1, file);
        fwrite(&d_header.important_colors , sizeof(int), 1, file);
        // iterate over the array and write to the file
        for(colidx = d_header.img_height - 1; colidx >= 0; colidx--)
        {
            for(rowidx = 0; rowidx < d_header.img_width; rowidx++)
            {
                // Create a new pixel struct
                struct pixel pixel_val = pixel_array[rowidx][colidx];
                // Get RGB values value
                fwrite(&pixel_val.blue, sizeof(uint8_t), 1, file);
                fwrite(&pixel_val.green, sizeof(uint8_t), 1, file);
                fwrite(&pixel_val.red, sizeof(uint8_t), 1, file);
            }
            // move the file pointer to account for padding
            if(padding != 0)
            {
                uint8_t zero = 0;
                for(int i = 0; i< padding; i++)
                    fwrite(&zero, sizeof(uint8_t),1,file);
            }
        }
        
        
}