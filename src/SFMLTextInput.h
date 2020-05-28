/*
 *	SFMLTextInput.h
 *
 *	by Vinicius Rodrigues
 *	May 22, 2020
 */

#include <SFML/Graphics.hpp>
#include "SFMLObject.h"
#include "DefaultFont.hpp"

#ifndef __SFMLTEXTINPUT_H__
#define __SFMLTEXTINPUT_H__

class SFMLTextInput : public SFMLObject {

	sf::Text m_sfmlText;
	std::string m_text;
	std::string m_displayedText;
	int m_size;
	int m_cursor;

public:

	SFMLTextInput();
	SFMLTextInput(SFMLTextInput*);

	void setText(std::string);
	std::string getText();
	void setCharacterSize(int);

	void render(sf::RenderTarget&, sf::RenderStates);
	SFMLObject* copy();

	void handleEvent(sf::Event);

	~SFMLTextInput();

private:

	void insertChar(sf::Uint32 c);
	void setDisplayedText(std::string);
};

#endif
