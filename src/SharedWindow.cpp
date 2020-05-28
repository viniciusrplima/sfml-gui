/*
 *	SharedWindow
 *
 *	by Vinicius Rodrigues
 *	May 20, 2020
 */

#include "SharedWindow.h"

SharedWindow::SharedWindow() : m_window() {}

SharedWindow::SharedWindow(sf::VideoMode mode, 
			   const sf::String &title, 
			   sf::Uint32 style, 
			   const sf::ContextSettings &settings) :
	m_window(mode, title, style, settings) {}


sf::RenderWindow&
SharedWindow::getSFMLWindow() {
	return m_window;
}

sf::RenderWindow& 
SharedWindow::operator* () {
	return m_window;
}

sf::RenderWindow*
SharedWindow::operator-> () {
	return &m_window;
}

SharedWindow::~SharedWindow() {
	m_window.close();
}

