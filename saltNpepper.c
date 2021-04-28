#include<stdio.h>
#include<stdlib.h>
#include<time.h>

int main()
{
	clock_t start, stop;
	start=clock();
	FILE* fp = fopen("lena.bmp", "rb");   //read the file//

	unsigned char *imageData; // to store the image information
	unsigned char *newimageData; // to store the new image information, i.e. the negative image
        unsigned char imageHeader[54]; // to get the image header
        unsigned char colorTable[1024]; // to get the colortable

	int i,j; // loop counter variables

	fread(imageHeader, sizeof(unsigned char), 54, fp); // read the 54-byte from fp to imageHeader


	// extract image height and width from imageHeader
        int width = *(int*)&imageHeader[18];
        int height = *(int*)&imageHeader[22];
	int bitDepth = *(int*)&imageHeader[28];

        int imgDataSize = width * height; // calculate image size

        imageData = (unsigned char*)malloc (imgDataSize * sizeof(unsigned char)); // allocate the block of memory as big as the image size
        newimageData = (unsigned char*)malloc (imgDataSize * sizeof(unsigned char));

	if(bitDepth <= 8)	// COLOR TABLE Present
		fread(colorTable, sizeof(unsigned char), 1024, fp); // read the 1024-byte from fp to colorTable


	fread( imageData, sizeof(unsigned char), imgDataSize, fp);

	printf("%d w: %d\n",height,width);
	//Calculate the mean of the image
	for(i = 0; i < height; i++){
	      for(j = 0; j < width; j++){
		    newimageData[i*width + j] =imageData[i*width + j];
		 }
	}
	for(i = 0; i < height; i+=rand()%10){
	      for(j = 0; j < width; j=j+rand()%50){
		    newimageData[i*width + j] =0;
		 }
	}
	for(i = 0; i < height; i+=rand()%10){
	      for(j = 0; j < width; j=j+rand()%50){
		    newimageData[i*width + j] =255;
		 }
	}

	FILE *fo = fopen("images/salted_lena.bmp", "wb");// Name of output file

        fwrite(imageHeader, sizeof(unsigned char), 54, fo); // write the header back.

	if(bitDepth <= 8)	// COLOR TABLE Present
        	fwrite(colorTable, sizeof(unsigned char), 1024, fo); // write the color table back

        fwrite( newimageData, sizeof(unsigned char), imgDataSize, fo); // write the values of the negative image.

        fclose(fo);
	fclose(fp);
        stop = clock();
	double d = (double)(stop - start) * 1000.0 / CLOCKS_PER_SEC;
        printf("%lf\n",d);

}
