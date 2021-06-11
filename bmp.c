#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <windows.h>
#define WIN32_MEAN_AND_LEAN
#include "bmp.h"

void read(const char* file_in, const char *file_out) {
	
	BITMAPFILEHEADER file_header;
	BITMAPINFOHEADER info_header;
	FILE *input, *output;

	
	input = fopen("file_in.bmp", "rb");
	output = fopen("file_out.bmp", "wb");

	if (!input) {
		printf("File bmp not found\n");
		system("pause");
		return;
	}

	fread(&file_header, sizeof(BITMAPFILEHEADER), 1, input);
	fread(&info_header, sizeof(BITMAPINFOHEADER), 1, input);

	if (info_header.biCompression != 0 || info_header.biBitCount != 24 || info_header.biPlanes != 1) {
		printf("File not a BMP24\n");
		system("pause");
		return;
	}
	out(file_header, info_header, input, output);
}

void out(BITMAPFILEHEADER file_header, BITMAPINFOHEADER info_header, FILE* input, FILE* output) {
	RGBTRIPLE pixel;
	int Width = info_header.biWidth;
	int Height = info_header.biHeight;

	unsigned char padding = 0;
	if ((Width * 3) % 4)
		padding = 4 - (Width * 3) % 4;

	RGBTRIPLE **img = malloc(Height*sizeof(RGBTRIPLE));
	for (size_t i = 0; i < Height; i++)
		img[i] = malloc(Width * sizeof(RGBTRIPLE));

	for (int i = 0; i < Height; i++) {
		for (int j = 0; j < Width; j++) {
			fread(&pixel, sizeof(RGBTRIPLE), 1, input);
			img[i][j] = pixel;
		}
		fseek(input, padding, SEEK_CUR); 
	}
	fclose(input);

	info_header.biHeight = Width;
	info_header.biWidth = Height;
	fwrite(&file_header, sizeof(BITMAPFILEHEADER), 1, output);
	fwrite(&info_header, sizeof(BITMAPINFOHEADER), 1, output);

	padding = 0;
	if ((Height * 3) % 4)
		padding = 4 - (Height * 3) % 4;

	for (int j = Width - 1; j >= 0; j--) {
		for (int i = 0; i < Height; i++)
			fwrite(&img[i][j], sizeof(RGBTRIPLE), 1, output);

		if (padding != 0) {
			BYTE filler = 0;
			fwrite(&filler, sizeof(BYTE), padding, output);
		}
	}

}