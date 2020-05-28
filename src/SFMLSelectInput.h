/*
 *	SFMLSelectInput.h
 *
 *	May 27, 2020
 *	by Vinicius Rodrigues
 */

#include <string>
#include <vector>
#include <SFML/Graphics.hpp>
#include "SFMLObject.h"
#include "DefaultFont.hpp"

#ifndef __SFMLSELECTINPUT_H__
#define __SFMLSELECTINPUT_H__

struct SELECT_ITEM {
	std::string text;
	int value;
};

class SFMLSelectInput: public SFMLObject {

	sf::Text m_sfmlText;
	std::vector<SELECT_ITEM> m_items;

public:

	SFMLSelectInput();
	SFMLSelectInput(SFMLSelectInput*);

	void setItems(const std::vector<SELECT_ITEM>& items);

	void render(sf::RenderTarget&, sf::RenderStates);
	SFMLObject* copy();

	void handleEvent(sf::Event);

	~SFMLSelectInput();
};

#endif
