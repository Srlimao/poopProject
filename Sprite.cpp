#pragma once
#include "Sprite.h"

Sprite::Sprite(){}
Sprite::~Sprite(){}

/*
void Sprite::setInsertImage(Image* image, int pos){
	if (pos > (images.size)) {
		images.insert(images.end(), image);
	}
	else {
		images.insert(pos, image);
	}
}*/

Image* Sprite::getImage(int pos){
	return images[pos];
}
