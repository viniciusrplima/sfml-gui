/*
 *	SFMLCaption.cpp
 *
 *	by Vinicius Rodrigues
 *	May 21, 2020
 */

#include "SFMLCaption.h"

SFMLCaption::SFMLCaption() : SFMLObject(), m_text(""), m_sfmlText() {
	m_sfmlText.setFont(g_pDefaultFont->get());
	setSize(18);
}

SFMLCaption::SFMLCaption(SFMLCaption* caption) : SFMLObject(caption), m_text(""), m_sfmlText()  {
	m_sfmlText.setFont(g_pDefaultFont->get());
	setSize(caption->m_size);
	setText(caption->m_text);
}

SFMLCaption::SFMLCaption(std::string text) : SFMLCaption() {
	setText(text);
}

void SFMLCaption::setText(std::string text) {
	m_text = text;
	m_sfmlText.setString(m_text);
	auto rect = m_sfmlText.getLocalBounds();
	m_rect.width = rect.width;
}

std::string SFMLCaption::getText() {
	return m_text;
}

void SFMLCaption::setSize(int size) {
	m_size = size;
	m_rect.height = size;
	m_sfmlText.setCharacterSize(size);
	auto rect = m_sfmlText.getLocalBounds();
	m_rect.width = rect.width;
}

int SFMLCaption::getSize() {
	return m_size;
}

void SFMLCaption::render(sf::RenderTarget& target, sf::RenderStates state) {

	sf::IntRect rect = getRect();
	m_sfmlText.setPosition(rect.left, rect.top);
	m_sfmlText.setFillColor(m_color);

	target.draw(m_sfmlText, state);
	
	if(m_child != 0) m_child->render(target, state);
	if(m_right != 0) m_right->render(target, state);
}

SFMLObject* SFMLCaption::copy() {
	return new SFMLCaption(this);
}

void SFMLCaption::handleEvent(sf::Event) {
}

SFMLCaption::~SFMLCaption() {
}
