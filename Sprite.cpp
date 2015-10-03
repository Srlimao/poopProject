#pragma once
#include "Sprite.h"

Sprite::Sprite(vector<Image*> v){
	for(Image* i : v){
		images.push_back(i);
	}
}
Sprite::~Sprite(){}


void Sprite::insertImagePos(Image* image, int pos){
	vector<Image*>::iterator iterator = images.begin();
	if (pos > images.size()) {
		images.insert(images.end(), image);
	}
	else {
		images.insert(iterator+pos, image);
	}
}

void Sprite::insertImageLast(Image * image)
{
	images.push_back(image);
}


Image* Sprite::getImage(int pos){
	return images[pos];
}
