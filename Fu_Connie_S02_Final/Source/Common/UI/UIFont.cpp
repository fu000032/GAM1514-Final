#include "UIFont.h"

UIFont::UIFont(const char* fontName, float spaceAmount) : 
	m_Font(NULL),
	m_Text(""),
	m_Width(0.0f),
	m_Height(0.0f),
	m_SpaceAmount(spaceAmount)
{
	//create the font object
	m_Font = new OpenGLTexture(fontName);

	//parse font data file json
	parseFontData(fontName);
}

UIFont::~UIFont()
{
	//delete font texture object
	if(m_Font != NULL)
	{
		delete m_Font;
		m_Font = NULL;
	}

	//cycle through and delete all fontframe objects
	for(std::map<std::string, UIFontFrame*>::iterator it = m_FontData.begin(); it!= m_FontData.end(); ++it)
	{
		if(it->second != NULL)
		{
			delete it->second;
			it->second = NULL;
		}
	}

	// clear font data map
	m_FontData.clear();
}

void UIFont::draw(float x, float y)
{
	for(int i = 0;i < m_Text.length(); i++)
	{
		//get character
		std::string character = m_Text.substr(i,1);

		//is character space
		if(character == " ")
		{
			x += m_SpaceAmount;
			continue;
		}

		//get font frame 
		UIFontFrame* fontFrame = getFontFrame(character);
		if(fontFrame != NULL)
		{
			m_Font->setSourceFrame(fontFrame->x, fontFrame->y, fontFrame->width, fontFrame->height);

			//draw font texture
			OpenGLRenderer::getInstance()->drawTexture(m_Font, x, y + (m_Height - fontFrame->height));

			//increment x value
			x += fontFrame->width;
		}
	}
}

void UIFont::setText(const char* text)
{
	//set text string
	m_Text.assign(text);

	//calculate text
	calculateSize();
}

const char* UIFont::getText()
{
	return m_Text.c_str();
}

float UIFont::getWidth()
{
	return m_Width;
}

float UIFont::getHeight()
{
	return m_Height;
}

void UIFont::parseFontData(const char* fontName)
{
	std::string jsonPath = ResourceUtils::getPathForResource(fontName, "json");
	std::ifstream inputStream;
	inputStream.open(jsonPath.c_str());

	//did input stream open
	if(inputStream.is_open() == true)
	{
		Json::Value root;
		Json::Reader reader;
		if(reader.parse(inputStream, root) == true)
		{
			Json::Value frames = root["frames"];
			for(int i = 0; i< frames.size(); i++)
			{
				//get character and frame data
				std::string character = frames[i]["filename"].asString();
				Json::Value frame = frames[i]["frame"];

				//create new uifontframe object
				UIFontFrame* fontFrame = new UIFontFrame();
				fontFrame->x = frame["x"].asUInt();
				fontFrame->y = frame["y"].asUInt();
				fontFrame->width = frame["w"].asUInt();
				fontFrame->height = frame["h"].asUInt();

				//set font data
				m_FontData[character] = fontFrame;
			}
		}
	}

	//close input stream
	inputStream.close();
}

void UIFont::calculateSize()
{
	m_Width = 0.0f;
	m_Height = 0.0f;

	//safety check length of text
	if(m_Text.length() > 0)
	{
		for(int i = 0; i < m_Text.length(); i++)
		{
			//get character
			std::string character = m_Text.substr(i, 1);

			//is character a space
			if(character == " ")
			{
				m_Width += m_SpaceAmount;
				continue;
			}

			//get font frame
			UIFontFrame* fontFrame = getFontFrame(character);
			if(fontFrame != NULL)
			{
				m_Width += fontFrame->width;
				m_Height = fmaxf(m_Height, fontFrame->height);
			}
		}
	}
}

UIFont::UIFontFrame* UIFont::getFontFrame(std::string character)
{
	UIFontFrame* fontFrame = NULL;

	//if font frame is NULL, change case
	if(fontFrame == NULL&& islower(character.at(0)) > 0)
	{
		transform(character.begin(), character.end(), character.begin(), ::toupper);
		fontFrame = m_FontData[character];
	}

	//if font frame is null change to lower case
	if(fontFrame == NULL && isupper(character.at(0))>0)
	{
		transform(character.begin(), character.end(), character.begin(), ::tolower);
		fontFrame = m_FontData[character];
	}

	

	return fontFrame;
}