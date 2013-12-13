#ifndef GAME_H
#define GAME_H

#include <vector>
#include "../Screen Manager/Screen.h"
#include "../UI/UIButton.h"
#include "../UI/UIFont.h"
#include "../UI/UINumbers.h"

class GameObject;
class Level;
class UIFont;

class Game : public Screen, public UIButtonListener
{
public:
	Game();
	~Game();

	//Game lifecycle methods
	void update(double delta);
	void paint();
	void reset();

	//Screen name, must be implemented, it's a pure
	//virtual method in the Screen class
	const char* getName();

	Level* getLevel();

private:
	//Mouse Events
	void mouseLeftClickUpEvent(float positionX, float positionY);
	void mouseMovementEvent(float deltaX, float deltaY, float positionX, float positionY);

	void keyUpEvent(int keyCode);

	//Level pointer
	Level* m_Level;

	//UI Button variables
	UIButton* m_PauseButton;

	//Button events
	void buttonAction(UIButton* button);
	void buttonIsSelected(UIButton* button);
	bool buttonShouldBeDeselectedOnExit(UIButton* button) { return true; }

	UIFont* m_FontLives;
	UIFont* m_FontScore;
	
	UINumbers* m_NumberLives;
	UINumbers* m_NumberScore;
	UINumbers* m_NumberTime;
	OpenGLTexture* m_TimeColon;

	OpenGLTexture* m_GameInfo;

	int m_Lives;
	int m_Score;
};

#endif