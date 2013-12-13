#include "Game.h"
#include "GameObject.h"
#include "Level.h"
#include "../OpenGL/OpenGL.h"
#include "../Constants/Constants.h"
#include "../Utils/Utils.h"
#include "../Screen Manager/ScreenManager.h"


Game::Game() :
	m_Lives(15),
	m_Score(0000)
{
	//Create the level object
	m_Level = new Level();

	m_FontLives = new UIFont("BitmapFont");
	m_FontLives->setText("lives");

	m_FontScore = new UIFont("BitmapFont");
	m_FontScore->setText("score");

	m_NumberLives = new UINumbers();
	m_NumberScore = new UINumbers();
	//m_NumberTime  = new UINumbers();
	//m_TimeColon	  = new OpenGLTexture("Colon");
	
	m_GameInfo = new OpenGLTexture("UIBox");

	m_PauseButton = new UIButton("ButtonPause");
	m_PauseButton->setCenterPosition(843.5f, 681.5f);
	m_PauseButton -> setListener(this);

	//Reset everything
	reset();
}

Game::~Game()
{
	//Delete the level object
	if(m_Level != NULL)
	{
		delete m_Level;
		m_Level = NULL;
	}
	if(m_PauseButton != NULL)
	{
		delete m_PauseButton;
		m_PauseButton = NULL;
	}
	if(m_FontLives != NULL)
	{
		delete m_FontLives;
		m_FontLives = NULL;
	}
	if(m_FontScore != NULL)
	{
		delete m_FontScore;
		m_FontScore = NULL;
	}
	if(m_NumberLives != NULL)
	{
		delete m_NumberLives;
		m_NumberLives = NULL;
	}
	/*if(m_NumberTime != NULL)
	{
		delete m_NumberTime;
		m_NumberTime = NULL;
	}*/
	if(m_NumberScore != NULL)
	{
		delete m_NumberScore;
		m_NumberScore = NULL;
	}
	if(m_GameInfo != NULL)
	{
		delete m_GameInfo;
		m_GameInfo = NULL;
	}
}

void Game::update(double delta)
{
	if(m_Level != NULL)
	{
		m_Level->update(delta);
	}
}

void Game::paint()
{
	if(m_Level != NULL)
	{
		m_Level->paint();
	}
	if(m_PauseButton != NULL)
	{
		m_PauseButton->paint();
	}

	OpenGLRenderer::getInstance()->drawTexture(m_GameInfo, 14.0f, 610.0f);
	if(m_FontLives != NULL)
	{
		m_FontLives->draw(55.0f, 700.0f);
	}
	if(m_FontScore != NULL)
	{
		m_FontScore->draw(230.0f, 715.0f);
	}
	if(m_NumberLives != NULL)
	{
		m_NumberLives->draw(m_Lives, 135.0f, 670.0f);
	}
	if(m_NumberScore != NULL)
	{
		m_NumberScore->draw(m_Score, 600.0f, 715.0f);
	}
	/*if(m_NumberTime != NULL)
	{
		m_NumberTime->draw(1234567890, 1000.0f, 100.0f);
	}*/
}

void Game::reset()
{
	if(m_Level != NULL)
	{
		m_Level->reset();
	}
}

const char* Game::getName()
{
	return GAME_SCREEN_NAME;
}

Level* Game::getLevel()
{
	return m_Level;
}

void Game::mouseLeftClickUpEvent(float positionX, float positionY)
{
	if(m_Level != NULL)
	{
		m_Level->mouseLeftClickUpEvent(positionX, positionY);
	}
	if(m_PauseButton != NULL)
	{
		m_PauseButton->mouseLeftClickUpEvent(positionX, positionY);
	}
}

void Game::mouseMovementEvent(float deltaX, float deltaY, float positionX, float positionY)
{
	if(m_PauseButton != NULL)
	{
		m_PauseButton->mouseMovementEvent(positionX, positionY);
	}
}

void Game::keyUpEvent(int keyCode)
{
	if(m_Level != NULL)
	{
		m_Level->keyUpEvent(keyCode);
	}  
	if(keyCode == KEYCODE_ESCAPE)
	{
		ScreenManager::getInstance()->switchScreen(PAUSE_MENU_SCREEN_NAME);
	}
	if(keyCode == KEYCODE_P)
	{
		ScreenManager::getInstance()->switchScreen(PAUSE_MENU_SCREEN_NAME);
	}
}

void Game::buttonAction(UIButton* button)
{
	if(button == m_PauseButton)
	{
		ScreenManager::getInstance()->switchScreen(PAUSE_MENU_SCREEN_NAME);
	}
}

void Game::buttonIsSelected(UIButton* button)
{
	if(button == m_PauseButton)
	{
		m_PauseButton->setIsSelected(true);
	}
}