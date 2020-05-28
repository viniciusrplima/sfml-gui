/*
 *	SFMLGui.h
 *
 *	by Vinicius Rodrigues
 *	May 20, 2020
 */

#include <SFML/Graphics.hpp>
#include "SharedWindow.h"
#include "SFMLObject.h"

#ifndef __SFMLGUI_H__
#define __SFMLGUI_H__

class SFMLGui {

	SharedWindow* m_window;
	SFMLObject* m_objectRoot;
	SFMLObject* m_objectFocused;
	sf::Vector2f m_initialWindowSize;
	sf::Vector2f m_windowSize;
	sf::Vector2f m_resizeScale;

public: 

	SFMLGui(SharedWindow* window);

	void render();
	void handleEvent(sf::Event);

	void addChildren(SFMLObject* object);
	void removeChildren(SFMLObject* object);

	void setWindow(SharedWindow* window);
	SharedWindow* getWindow();

	~SFMLGui();
};

#endif
