/*
 *	SFMLTextInput.cpp
 *
 *	by Vinicius Rodrigues
 *	May 22, 2020
 */

#include <iostream>
#include <ctime>
#include "SFMLTextInput.h"

SFMLTextInput::SFMLTextInput() : SFMLObject(), m_text(""), m_sfmlText() {
	m_sfmlText.setFont(g_pDefaultFont->get());
	m_sfmlText.setFillColor(sf::Color(0, 0, 0, 255));
	setCharacterSize(18);
	m_enableFocus = true;
	m_color = sf::Color(200, 200, 200, 255);
	m_hoverColor = sf::Color(255, 255, 255, 255);
	m_cursor = 0;
	setDisplayedText(m_text);
}

SFMLTextInput::SFMLTextInput(SFMLTextInput* obj) : SFMLObject(obj), m_text(""), m_sfmlText() {
	m_sfmlText.setFont(g_pDefaultFont->get());
	m_sfmlText.setFillColor(sf::Color(0, 0, 0, 255));
	setCharacterSize(obj->m_size);
	m_enableFocus = obj->m_enableFocus;
	m_color = obj->m_color;
	m_hoverColor = obj->m_hoverColor;
	m_cursor = 0;
	setDisplayedText(m_text);
}

void SFMLTextInput::setText(std::string text) {
	m_text = text;
	setDisplayedText(m_text);
}

std::string SFMLTextInput::getText() {
	return m_text;
}

void SFMLTextInput::setCharacterSize(int size) {
	m_size = size;
	m_sfmlText.setCharacterSize(size);
}

void SFMLTextInput::render(sf::RenderTarget& target, sf::RenderStates state) {

	sf::IntRect rect = getRect();
	sf::RectangleShape box;

	if((m_isHover || m_isFocused) && m_hoverColor != sf::Color::Transparent)
		box.setFillColor(m_hoverColor);
	else
		box.setFillColor(m_color);

	box.setPosition(rect.left, rect.top);
	box.setSize(sf::Vector2f(rect.width, rect.height));

	m_sfmlText.setString(m_displayedText);
	m_sfmlText.setPosition(rect.left, rect.top + rect.height/2 - m_size/2);

	target.draw(box, state);
	target.draw(m_sfmlText, state);

	if((4 * std::clock() / CLOCKS_PER_SEC) % 2 == 0 && m_isFocused) {
		auto textRect = m_sfmlText.getLocalBounds();
		sf::RectangleShape mark;

		mark.setFillColor(sf::Color(0, 0, 0, 255));
		mark.setSize(sf::Vector2f(2, m_size));
		mark.setPosition(rect.left + textRect.width, rect.top + rect.height/2 - m_size/2);
		target.draw(mark, state);
	}

	if(m_child != 0) m_child->render(target, state);
	if(m_right != 0) m_right->render(target, state);
}

SFMLObject* SFMLTextInput::copy() {
	return new SFMLTextInput(this);
}

void SFMLTextInput::handleEvent(sf::Event event) {
	if(event.type == sf::Event::TextEntered) {
		insertChar(event.text.unicode);
	}
}

void SFMLTextInput::insertChar(sf::Uint32 c) {
	if(c == '\b') {
		if(m_text.size() > 0) {
			m_text.pop_back();
			m_cursor--;
		}
	}
	else {
		m_text += c;
		m_cursor++;			
	}

	setDisplayedText(m_text);
}

void SFMLTextInput::setDisplayedText(std::string text) {
	m_displayedText = text;
	m_sfmlText.setString(m_displayedText);
	while(m_sfmlText.getLocalBounds().width > m_rect.width && m_displayedText.size() > 0) {
		m_displayedText = m_displayedText.substr(1, m_displayedText.size()-1);
		m_sfmlText.setString(m_displayedText);
	}
}

SFMLTextInput::~SFMLTextInput() {
}

