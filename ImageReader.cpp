#pragma once
#include "Image.h"
#include "ImageReader.h"
#include <iostream>
#include <fstream>
#include <regex>

/*
#include <windows.h>
#include <GL\GL.h>
#include <GL\GLU.h>
#include <GL\glut.h>
*/

using namespace std;

Image * ImageReader::loadImageFile(string path) {
	Image * image;
	ifstream file;
	file.open(path, ios::in);
	string type; getline(file, type);
	string line; getline(file, line);
	int w, h;
	const char * str = line.c_str();
	char * pch;
	char * next_tk;
	pch = strtok_s((char *)str, " ", &next_tk);
	while (pch != NULL) {
		w = atoi(pch);
		pch = strtok_s(NULL, " ", &next_tk);
		h = atoi(pch);
		pch = strtok_s(NULL, " ", &next_tk);
	}
	getline(file, line);
	int max = stoi(line);
	image = new Image(w, h);

	int i = 0;		//width
	int j = h - 1;	//height

	while (getline(file, line)) {
		const char * str = line.c_str();
		char * pch;
		char *next_tk;
		pch = strtok_s((char *)str, " ", &next_tk);
		while (pch != NULL) {
			int a = atoi(pch);
			pch = strtok_s(NULL, " ", &next_tk);
			int b = atoi(pch);
			pch = strtok_s(NULL, " ", &next_tk);
			int g = atoi(pch);
			pch = strtok_s(NULL, " ", &next_tk);
			int r = atoi(pch);
			pch = strtok_s(NULL, " ", &next_tk);
			if (i == w) {
				i = 0;
				j--;
			}
			int rgba = (((int)a) << 24) | (((int)r) << 16) | (((int)g) << 8) | (int)b;
			image->setRGB(i++, j, rgba);
		}
	}
	file.close();
	return image;
}


Image* ImageReader::subImage(int width, int height, Image* image, int posx, int posy) {

	Image* im = new Image(width, height);
	for (int i = 0; i < width; i++) {
		for (int j = 0; j < height; j++) {
			im->setRGB(i, i, 0);
		}
	}

	int xx = 0;
	int yy = 0;

	if (posx < 0) {
		xx = -(posx);
	}
	if (posy < 0) {
		yy = -(posy);
	}
	

	for (int x = xx; x < width && x < image->getWidth(); x++) {			//changed || to &&
		for (int y = yy; y < height && y < image->getHeight(); y++) {	//changed || to &&
			im->setRGB(posx + x, posy + y ,image->getRGB(x, y));
		}
	}
	return im;

}