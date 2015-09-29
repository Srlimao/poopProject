#pragma once
#include "Image.h"
#include <windows.h>	
#include <GL\GL.h>
#include <GL\GLU.h>
#include <GL\glut.h>

using namespace std;

Image::Image(int width, int height, int posX, int posY){
	this->width = width;
	this->height = height;
	this->posX = posX;
	this->posY = posY;
	pixels = new int[width*height];
}

Image::~Image(){
	delete[] pixels;
}



void Image::setRGB(int x, int y, int rgb) 
{
	pixels[x + y * width] = rgb;
}

void Image::setPosX(int x)
{
	this->posX = x;
}

void Image::setPosY(int y)
{
	this->posY = y;
}

void Image::clearAndResize(int width, int height){
	delete[] pixels;
	pixels = new int[width*height];
	this->width = width;
	this->height = height;
}


int Image::getRGB(int x, int y) { return pixels[x + y * width]; }
int Image::getWidth() { return width; }
int Image::getHeight() { return height; }
int* Image::getPixels() { return pixels; }
int Image::getPosX() { return posX; }		//posição horizontal da imagem
int Image::getPosY() { return posY; }		//posição vertical da imagem




