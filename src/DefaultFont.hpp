/*
 *	DefaultFont.hpp
 *
 *	by Vinicius Rodrigues
 *	May 21, 2020
 */


#include <SFML/Graphics.hpp>
#include "Singleton.hpp"

#ifndef __DEFAULTFONT_HPP__
#define __DEFAULTFONT_HPP__

// Use g_pDefaultFont to abreviate sentences
#define g_pDefaultFont DefaultFont::Instance()

// To load font only once
class DefaultFont : public Singleton<DefaultFont> {

	sf::Font font;

public:
	DefaultFont() {
		font.loadFromFile("./resources/UbuntuMono-Regular.ttf");
	}

	sf::Font& get() {
		return font;
	}

	~DefaultFont() {
	}
};

#endif
