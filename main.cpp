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
#include "src/SFMLImage.h"
#include "src/SFMLSelectInput.h"
#include "src/SFMLTextureHolder.h"
#include "src/SFMLCircle.h"

int main() {
	
	SharedWindow window(sf::VideoMode(600, 480), "SFMLGui Test");
	SFMLGui gui(&window);

	TextureId texture = g_pSFMLTextureHolder->loadTexture("./resources/bomb.png");
	SFMLImage* image = new SFMLImage();
	image->setImage(texture);
	image->setSize(100, 100);
	image->setHorizontalAlign(SFMLObject::Center);
	image->setVerticalAlign(SFMLObject::Center);

	SFMLObject* popup = DOMFactory::createPopup(300, 150);
	popup->addChildren(image);
	popup->setHorizontalAlign(SFMLObject::Start);
	popup->setVerticalAlign(SFMLObject::Start);
	popup->setColor(sf::Color(220, 220, 220, 255));
	popup->setMargin(20, 20);

	SFMLSelectInput* select = new SFMLSelectInput();
	select->setSize(250, 400);
	select->setMargin(10, 10);
	select->setColor(sf::Color(230, 230, 230, 255));
	select->setHorizontalAlign(SFMLObject::Stretch);
	select->setVerticalAlign(SFMLObject::Center);
	select->setFocusColor(sf::Color(255, 255, 255, 255));
	select->setLayout(SFMLSelectInput::Horizontal);

	select->addItem(0, new SFMLCaption("Mapa do Castelo"));
	select->addItem(0, new SFMLCaption("Mapa do Porao"));

	SFMLImage* image2 = new SFMLImage(image);
	image2->setMargin(0, 0);
	select->addItem(0, image2);

	select->addItem(0, new SFMLCaption("Campo de Batalha"));
	select->addItem(0, new SFMLCaption("Citadela"));
	select->addItem(0, new SFMLCaption("Mapa do Castelo"));
	select->addItem(0, new SFMLCaption("Mapa do Porao"));
	select->addItem(5, image2->copy());
	select->addItem(0, new SFMLCaption("Campo de Batalha"));
	select->addItem(0, new SFMLCaption("Citadela"));

	SFMLCircle* circle = new SFMLCircle();
	circle->setSize(100, 20);
	circle->setColor(sf::Color::Red);
	select->addItem(6, circle);

	select->addItem(0, new SFMLCaption("Mapa do Castelo"));
	select->addItem(0, new SFMLCaption("Mapa do Castelo"));
	select->addItem(0, new SFMLCaption("Campo de Batalha"));
	select->addItem(0, new SFMLCaption("Citadela"));
	select->addItem(0, new SFMLCaption("Mapa do Porao"));
	select->addItem(0, new SFMLCaption("Campo de Batalha"));
	select->addItem(0, new SFMLCaption("Citadela"));

	gui.addChildren(popup);
	gui.addChildren(select);

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
