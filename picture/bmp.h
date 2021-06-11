#define _CRT_SECURE_NO_WARNINGS
#pragma once
#include <stdio.h>
#include <windows.h>
#define WIN32_MEAN_AND_LEAN

void read(const char *file_in, const char *file_out);
void out(BITMAPFILEHEADER file_header, BITMAPINFOHEADER info_header, FILE *input, FILE *output);