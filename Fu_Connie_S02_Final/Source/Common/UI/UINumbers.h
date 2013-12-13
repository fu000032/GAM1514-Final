#ifndef UINUMBERS_H
#define UINUMBERS_H

#include "../OpenGL/OpenGL.h"

class UINumbers
{
public:
	UINumbers();
	~UINumbers();

	void draw(int number, float x, float y);
	
private:
	OpenGLTexture* m_Numbers[10];
};

#endif