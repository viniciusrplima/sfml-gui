/*
 *	SFMLCaption.h
 *
 *	by Vinicius Rodrigues
 *	May 21, 2020
 */

#include <string>
#include "SFMLObject.h"
#include "DefaultFont.hpp"

#ifndef __SFMLCAPTION_HPP__
#define __SFMLCAPTION_HPP__

class SFMLCaption : public SFMLObject {

	sf::Text m_sfmlText;
	std::string m_text;
	int m_size;

public:

	SFMLCaption();
	SFMLCaption(SFMLCaption*);
	SFMLCaption(std::string);

	void setText(std::string);
	std::string getText();
	void setSize(int);
	int getSize();

	void render(sf::RenderTarget&, sf::RenderStates);
	SFMLObject* copy();

	void handleEvent(sf::Event);

	~SFMLCaption();
};

#endif
