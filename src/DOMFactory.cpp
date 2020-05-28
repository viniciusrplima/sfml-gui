/*
 *	DOMFactory.cpp
 *
 *	by Vinicius Rodrigues
 *	May 20, 2020
 */

#include <iostream>
#include "DOMFactory.h"

SFMLObject* DOMFactory::createButton(int width, int height, std::string title) {
	SFMLCaption* caption = new SFMLCaption();
	caption->setText(title);
	caption->setSize(16);
	caption->setVerticalAlign(SFMLObject::Center);
	caption->setHorizontalAlign(SFMLObject::Center);
	caption->setColor(sf::Color(255, 255, 255, 255));

	SFMLBox* button = new SFMLBox();
	button->setSize(width, height);
	button->setColor(sf::Color(70, 70, 70, 255));
	button->setHoverColor(sf::Color(127, 127, 127, 255));
	button->addChildren(caption);

	return button;
}

SFMLObject* DOMFactory::createPopup(int width, int height) {
	SFMLObject* cancelButton = DOMFactory::createButton(18, 18, "x");
	cancelButton->setHoverColor(sf::Color(255, 127, 127, 255));
	cancelButton->setHorizontalAlign(SFMLObject::End);
	cancelButton->setMargin(5, 5);

	SFMLBox* popup = new SFMLBox();
	popup->setSize(width, height);
	popup->setColor(sf::Color(30, 30, 127, 255));
	popup->addChildren(cancelButton);

	cancelButton->setOnClick([](SFMLObject* obj){
		obj->getParent()->removeThis();
	});

	return popup;
}

