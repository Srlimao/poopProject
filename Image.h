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
	int posX, posY;		//posição horizental e vertical da imagem no portview

public:
	Image(int width, int height, int posX, int posY);
	~Image(void);

	void setRGB(int x, int y, int rgb);
	void setPosX(int x);
	void setPosY(int y);
	void Image::clearAndResize(int w, int h);

	int getRGB(int x, int y);
	int getWidth();
	int getHeight();
	int getPosX();
	int getPosY();
	int* getPixels();

	
};
