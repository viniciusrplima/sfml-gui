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
	int value;
	SFMLObject* object;
};

class SFMLSelectInput: public SFMLObject {

	sf::Text m_sfmlText;
	std::vector<SELECT_ITEM> m_items;
	int m_offset;
	int m_target;

public:

	SFMLSelectInput();
	SFMLSelectInput(SFMLSelectInput*);

	void setItems(const std::vector<SELECT_ITEM>& items);
	void addItem(SELECT_ITEM& item);
	void addItem(int value, SFMLObject* obj);
	void setTarget(int target);

	void render(sf::RenderTarget&, sf::RenderStates);
	SFMLObject* copy();

	void handleEvent(sf::Event);

	~SFMLSelectInput();
};

#endif
