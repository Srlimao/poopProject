#pragma once
#include <Windows.h>
#include <gl/GL.h>
#include <gl/glut.h>
#include <gl/GLU.h>
#include <string>

class Image 
{
private:
	int width, height;
	int *pixels;

public:
	Image(int width, int height);
	~Image(void);

	void setRGB(int x, int y, int rgb);
	void Image::clearAndResize(int w, int h);

	int getRGB(int x, int y);
	int getWidth();
	int getHeight();
	int* getPixels();

	
};
