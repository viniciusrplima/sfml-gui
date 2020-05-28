/*
 *	SFMLBox.h
 *
 *	by Vinicius Rodrigues
 *	May 20, 2020
 */

#include <SFML/Graphics.hpp>
#include "SFMLObject.h"

#ifndef __SFMLBOX_H__
#define __SFMLBOX_H__

class SFMLBox : public SFMLObject {

public:

	SFMLBox();
	SFMLBox(SFMLBox*);

	void render(sf::RenderTarget& target, sf::RenderStates);
	SFMLObject* copy();

	void handleEvent(sf::Event);

	~SFMLBox();
};

#endif
