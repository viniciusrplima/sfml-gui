/*
 *	SFMLBox.cpp
 *
 *	by Vinicius Rodrigues
 *	May 20, 2020
 */

#include <iostream>
#include "SFMLBox.h"

SFMLBox::SFMLBox() : SFMLObject() {
}

SFMLBox::SFMLBox(SFMLBox* box) : SFMLObject(box) {
}

void SFMLBox::render(sf::RenderTarget& target, sf::RenderStates state) {
	sf::IntRect rect = getRect();
	sf::RectangleShape box;

	box.setSize(sf::Vector2f(rect.width, rect.height));

	if(m_isFocused && m_focusColor != sf::Color::Transparent) 
		box.setFillColor(m_focusColor);
	else if(m_isHover && m_hoverColor != sf::Color::Transparent)
		box.setFillColor(m_hoverColor);
	else
		box.setFillColor(m_color);
	box.setPosition(rect.left, rect.top);

	target.draw(box, state);

	if(m_child != 0) m_child->render(target, state);
	if(m_right != 0) m_right->render(target, state);
}

SFMLObject* SFMLBox::copy() {
	return new SFMLBox(this);
}

void SFMLBox::handleEvent(sf::Event) {
}

SFMLBox::~SFMLBox() {
}
