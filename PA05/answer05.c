#include<stdio.h>
#include<stdlib.h>
#include<libgen.h>
#include<string.h>

#include "answer05.h"
#define TRUE 1
#define FALSE 0

Image * Image_load(const char * filename)
{
	ImageHeader header;
	size_t read;
	Image *tmp_im = NULL;;
	//Image *im = NULL;	

	//OPEN FILE	
	FILE * fp = fopen(filename, "rb");
	int err = fp == NULL;
	if (err) fprintf(stderr, "unable to open file %s!\n", filename);
	

	//READ THE HEADER	
	if(!err)
	{
		read = fread(&header, sizeof(ImageHeader), 1, fp);
		err = read != 1 ||
			header.magic_number != ECE264_IMAGE_MAGIC_NUMBER ||
			header.width == 0 ||
			header.height == 0 ||
			header.comment_len == 0;
		if(err) fprintf(stderr, "corrupt header\n");	
	}
	
	//ALLOCATE MEMORY
	if(!err)
	{
	tmp_im = malloc(sizeof(Image));
	err = tmp_im == NULL;
	if(err) fprintf(stderr, "unable to allocate memory\n");	
	}

	//ALLOCATE MEMORY FOR THE COMMENTS AND PIXELS
	if(!err)
	{
	tmp_im->width = header.width;
	tmp_im->height = header.height;
	tmp_im->comment = malloc(sizeof(char) * header.comment_len);	
	tmp_im->data = malloc(sizeof(char) * header.width * header.height);
	err = (tmp_im->comment == NULL) || (tmp_im->data == NULL);
	if(err) fprintf(stderr, "Unable to allocate memory\n");
	}

	//READ THE COMMENT
 	if(!err)
	{
	read = fread(tmp_im->comment, sizeof(char), header.comment_len, fp);
	err = read != header.comment_len || tmp_im->comment[header.comment_len - 1] != '\0';
	if(err) fprintf(stderr, "NOT ENOUGH COMMENTS\n");
	}

	//READ THE PIXELS
	if(!err)
	{
	read = fread(tmp_im->data,sizeof(char), header.width * header.height, fp);
	err = read != header.width * header.height;
	if(err) fprintf(stderr, "Unable to Read Pixels\n");
	}
	
	//MAKE SURE END OF FILE
	if(!err)
	{
	fgetc(fp);
	err = !feof(fp);
	if(err) fprintf(stderr, "Not end of file\n");
	}
	//CLOSE THE FILE	
	if(fp != NULL)
	{
		fclose(fp);
	}
	return tmp_im;
}
int Image_save(const char * filename, Image * image)
{
    FILE * fp = NULL;

    // Attempt to open file for writing
        fp = fopen(filename, "wb");
        if(fp == NULL) 
	{ 
           return FALSE; 
        }
	fclose(fp);
         return TRUE;                      

}
void Image_free(Image * image)
{
	if(image != NULL)
	{
	free (image->data);
	free (image->comment);
	free (image);

	}
}
void linearNormalization(int width, int height, uint8_t * intensity)
{
	int i = 0;
	uint8_t min = intensity[i];
	uint8_t max = intensity[i];

	for(i = 1; i < (width * height); i++)
	{
	if(intensity[i] < min)
	{
		min = intensity[i];
	}

	if(intensity[i] > max)
	{
		max = intensity[i];
	}
	}

	for(i = 0; i < (width * height); i++)
	{
	intensity[i] = (intensity[i] - min) * 255.0 / (max - min);
	}
}
