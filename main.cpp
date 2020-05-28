/*
 *	SFMLGui
 *
 *	by Vinicius Rodrigues
 *	May 20, 2020
 */

#include <iostream>
#include <SFML/Graphics.hpp>
#include "src/SFMLGui.h"
#include "src/SharedWindow.h"
#include "src/DOMFactory.h"
#include "src/SFMLBox.h"
#include "src/SFMLCaption.h"
#include "src/SFMLTextInput.h"

int main() {
	
	SharedWindow window(sf::VideoMode(600, 480), "SFMLGui Test");
	SFMLGui gui(&window);

	SFMLBox* hud = new SFMLBox();
	hud->setColor(sf::Color(50, 50, 200, 255));
	hud->setMargin(10, 10);
	hud->setSize(0, 150);
	hud->setVerticalAlign(SFMLObject::End);
	hud->setHorizontalAlign(SFMLObject::Stretch);
	gui.addChildren(hud);

	SFMLObject* popup = DOMFactory::createPopup(300, 150);
	SFMLTextInput* textInput = new SFMLTextInput();
	textInput->setSize(250, 30);
	textInput->setHorizontalAlign(SFMLObject::Center);
	textInput->setVerticalAlign(SFMLObject::Center);
	popup->addChildren(textInput);
	popup->setVerticalAlign(SFMLObject::Center);
	popup->setHorizontalAlign(SFMLObject::Center);
	gui.addChildren(popup);

	while(window->isOpen()) {
		
		sf::Event event;
		while(window->pollEvent(event)) {
			if(event.type == sf::Event::Closed) {
				window->close();
			}

			gui.handleEvent(event);
		}

		window->clear();

		gui.render();
		
		window->display();
	}
}
