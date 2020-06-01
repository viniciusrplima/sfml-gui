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
	m_enableFocus = true;
	m_offset = 0;
	m_target = 0;
}

SFMLSelectInput::SFMLSelectInput(SFMLSelectInput* obj) 
	: SFMLObject(obj), 
	  m_sfmlText() {

	setItems(obj->m_items);
	m_sfmlText.setFont(g_pDefaultFont->get());
	m_enableFocus = true;
	m_offset = 0;
	m_target = 0;
}

void SFMLSelectInput::setItems(const std::vector<SELECT_ITEM>& items) {
	m_items = std::vector<SELECT_ITEM>();

	for(int i = 0; i < items.size(); i++) {
		SELECT_ITEM item;
		item.value = items[i].value;
		item.object = item.object->copy();

		m_items.push_back(item);
	}
}

void SFMLSelectInput::addItem(SELECT_ITEM& item) {
	m_items.push_back(item);
}

void SFMLSelectInput::addItem(int value, SFMLObject* obj) {
	SELECT_ITEM item;
	item.value = value;
	item.object = obj;

	addItem(item);
}

void SFMLSelectInput::setTarget(int target) {
	m_target = target % m_items.size();
}

void SFMLSelectInput::render(sf::RenderTarget& target, sf::RenderStates state) {

	auto rect = getRect();

	sf::RectangleShape bg;
	if(m_enableFocus && m_isFocused)
		bg.setFillColor(m_focusColor);
	else
		bg.setFillColor(m_color);
	bg.setSize(sf::Vector2f(rect.width, rect.height));
	bg.setPosition(rect.left, rect.top);

	target.draw(bg, state);

	// draw items
	sf::RenderStates itemState(state);
	itemState.transform.translate(rect.left, rect.top);
	int top = 0;
	for(int i = 0; i < m_items.size(); i++) {
		itemState.transform.translate(0, top);
		
		if(m_items[i].object != 0) {
			auto rc = m_items[i].object->getRect();
			top = rc.height + 5;
	
			if(i == m_target) {
				sf::RectangleShape shape;
				shape.setFillColor(sf::Color(255, 127, 50, 255));
				shape.setSize(sf::Vector2f(rect.width, rc.height));
				target.draw(shape, itemState);
			}

			m_items[i].object->render(target, itemState);
		}
	}

	if(m_child != 0) m_child->render(target, state);
	if(m_right != 0) m_right->render(target, state);
}

SFMLObject* SFMLSelectInput::copy() {
	return new SFMLSelectInput(this);
}

void SFMLSelectInput::handleEvent(sf::Event event) {
	
	if(event.type == sf::Event::KeyPressed) {
		if(event.key.code == sf::Keyboard::Down) {
			setTarget(m_target+1);
		}
		else if(event.key.code == sf::Keyboard::Up) {
			setTarget(m_target-1);
		}
	}
}

SFMLSelectInput::~SFMLSelectInput() {
}
