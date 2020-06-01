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

public:
	enum Layout {
		Vertical, 
		Horizontal
	};

private:

	sf::Text m_sfmlText;
	std::vector<SELECT_ITEM> m_items;
	int m_offset;
	int m_target;
	int m_spacing;
	Layout m_layout;
	sf::Color m_markColor;

public:

	SFMLSelectInput();
	SFMLSelectInput(SFMLSelectInput*);

	void setItems(const std::vector<SELECT_ITEM>& items);
	void addItem(SELECT_ITEM& item);
	void addItem(int value, SFMLObject* obj);
	void setTarget(int target);
	int getValue();
	void setLayout(Layout);
	Layout getLayout();
	void setSpacing(int);
	void setMarkColor(sf::Color);

	void drawVerticalItems(sf::RenderTarget&, sf::IntRect);
	void drawHorizontalItems(sf::RenderTarget&, sf::IntRect);

	void render(sf::RenderTarget&, sf::RenderStates);
	SFMLObject* copy();

	void handleEvent(sf::Event);

	~SFMLSelectInput();
private:

	void calcOffset();
};

#endif
