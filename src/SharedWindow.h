/*
 *	SharedWindow
 *
 *	by Vinicius Rodrigues
 *	May 20, 2020
 */

#include <SFML/Graphics.hpp>

#ifndef __SHAREDWINDOW_H__
#define __SHAREDWINDOW_H__

// Class to share sf::RenderWindow that is non-copyable
class SharedWindow {

	sf::RenderWindow m_window;

public:

	SharedWindow();
	SharedWindow(sf::VideoMode mode, 
		     const sf::String &title, 
		     sf::Uint32 style=sf::Style::Default, 
		     const sf::ContextSettings &settings=sf::ContextSettings());

	sf::RenderWindow& getSFMLWindow();
	sf::RenderWindow& operator* ();
	sf::RenderWindow* operator-> ();

	~SharedWindow();

};

#endif
