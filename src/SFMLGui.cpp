/*
 *	SFMLGui.cpp
 *
 *	by Vinicius Rodrigues
 *	May 20, 2020
 */

#include <iostream>
#include "SFMLGui.h"
#include "SFMLBox.h"

SFMLGui::SFMLGui(SharedWindow* window) : m_window(window), m_resizeScale(1.0f, 1.0f) {
	m_objectRoot = new SFMLBox();
	auto size = (*window)->getSize();
	m_initialWindowSize = sf::Vector2f(size);
	m_objectRoot->setColor(sf::Color(127, 50, 255, 255));
	m_objectRoot->setSize(size.x, size.y);
	m_objectFocused = m_objectRoot;
}

void SFMLGui::render() {

	sf::Transform transform;
	transform.scale(m_resizeScale);

	if(m_objectRoot != 0)
		m_objectRoot->render(m_window->getSFMLWindow(), transform);
}

void SFMLGui::handleEvent(sf::Event event) {

	if(event.type == sf::Event::Resized) {
		m_resizeScale.x = m_initialWindowSize.x / event.size.width;
		m_resizeScale.y = m_initialWindowSize.y / event.size.height;
		m_windowSize = sf::Vector2f(event.size.width, event.size.height);
		m_objectRoot->setSize(m_windowSize.x, m_windowSize.y);
	}

	if(event.type == sf::Event::MouseMoved) {
		sf::Vector2f mousePos(event.mouseMove.x, event.mouseMove.y);
		m_objectRoot->handleMouseMove(mousePos);
	}

	if(event.type == sf::Event::MouseButtonPressed) {
		sf::Vector2f mousePos(event.mouseButton.x, event.mouseButton.y);
		m_objectFocused = m_objectRoot->handleFocus(mousePos);
		m_objectRoot->handleMouseClick(mousePos);
	}

	if(event.type == sf::Event::TextEntered ||
	   event.type == sf::Event::KeyPressed) {
		if(m_objectFocused != 0)
			m_objectFocused->handleEvent(event);
	}
}

void SFMLGui::addChildren(SFMLObject* object) {
	m_objectRoot->addChildren(object);
}

void SFMLGui::removeChildren(SFMLObject* object) {
	m_objectRoot->removeChildren(object);
}

void SFMLGui::setWindow(SharedWindow* window) {
	m_window = window;
}

SharedWindow* SFMLGui::getWindow() {
	return m_window;
}

SFMLGui::~SFMLGui() {
	m_window = 0;
}
