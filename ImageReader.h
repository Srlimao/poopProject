#pragma once
#include "Image.h"
#include <string>
#include "Layer.h"

using namespace std;

class ImageReader
{
private:

public:

	Image * loadImageFile(string path);
	Image* subImage(int width, int height, Image* image, int posx, int posy);
	
};