#pragma once
#include <Windows.h>
#include <gl/GL.h>
#include <gl/glut.h>
#include <gl/GLU.h>
#include <string>
#include "Image.h"


class Layer
{
private:
	float taxaX, taxaY;	//Taxa de movimento da camada, controlado pela camada mais alta
	int posX, posY;		//Posição pra alguma coisa? 
	Image * image;		//Imagem
	bool status;
	float cursorY;

public:
	Layer(Image* image);
	Layer(Image* image, float taxaX, float taxaY);
	~Layer(void);

	bool isActive();
	Image* getImage();
	int getPosX();
	int getPosY();
	void setPosX(int posX);
	void setPosY(int posY);
	void setCursorY(float y);
	float getTaxaX();
	float getTaxaY();
	float getCursorY();

};
