#include "UINumbers.h"

UINumbers::UINumbers()
{
	char* NumberChars[10] = {"0", "1", "2", "3", "4", "5", "6", "7", "8", "9"};

	for(int i = 0; i < 10; i++)
	{
		m_Numbers[i] = new OpenGLTexture("BitmapNumbers", NumberChars[i]); 
	}
}

UINumbers::~UINumbers()
{
	for(int i = 0; i < 10; i++)
	{
		delete m_Numbers[i];
		m_Numbers[i] = NULL;
	}
}

void UINumbers::draw(int number, float x, float y)
{
	int digitToDraw = number%10;

	OpenGLTexture *digit = m_Numbers[digitToDraw];

	OpenGLRenderer::getInstance()->drawTexture(digit,x-(digit->getSourceWidth()), y,digit->getSourceWidth(), digit->getSourceHeight());
	if (number >= 10)
	{
		draw(number/10, x-(digit->getSourceWidth())-2,y);
	}
}