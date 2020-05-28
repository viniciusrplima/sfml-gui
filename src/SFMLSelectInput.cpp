/*
 *	SFMLSelectInput.cpp
 *
 *	May 27, 2020
 *	by Vinicius Rodrigues
 */

#include "SFMLSelectInput.h"

SFMLSelectInput::SFMLSelectInput() 
	: SFMLObject(), 
	  m_sfmlText() {
	
	m_sfmlText.setFont(g_pDefaultFont->get());
}

SFMLSelectInput::SFMLSelectInput(SFMLSelectInput* obj) 
	: SFMLObject(obj), 
	  m_sfmlText() {

	setItems(obj->m_items);
	m_sfmlText.setFont(g_pDefaultFont->get());
}

void SFMLSelectInput::setItems(const std::vector<SELECT_ITEM>& items) {
	m_items = std::vector<SELECT_ITEM>();

	for(int i = 0; i < items.size(); i++) {
		SELECT_ITEM item;
		item.text = items[i].text;
		item.value = items[i].value;

		m_items.push_back(item);
	}
}

void SFMLSelectInput::render(sf::RenderTarget& target, sf::RenderStates state) {


	if(m_child != 0) m_child->render(target, state);
	if(m_right != 0) m_right->render(target, state);
}

SFMLObject* SFMLSelectInput::copy() {
	return new SFMLSelectInput(this);
}

void SFMLSelectInput::handleEvent(sf::Event) {
	
}

SFMLSelectInput::~SFMLSelectInput() {
}
