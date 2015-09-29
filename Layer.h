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
	int taxaX, taxaY;	//Taxa de movimento da camada, controlado pela camada mais alta
	int posX, posY;		//Posição pra alguma coisa? 
	Image * image;		//Imagem
	bool status;

public:
	Layer(Image* image);
	~Layer(void);

	bool isActive();
	Image* getImage();
	int getPosX();
	int getPosY();
	void setPosX(int posX);
	void setPosY(int posY);
	int getTaxaX();
	int getTaxaY();

};
