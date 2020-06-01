/*
 *	SFMLCircle.h
 *
 *	Jun 01, 2020
 *	by Vinicius Rodrigues
 */

#include "SFMLObject.h"

#ifndef __SFMLCIRCLE_H__
#define __SFMLCIRCLE_H__

class SFMLCircle: public SFMLObject {

public:
	SFMLCircle();
	SFMLCircle(SFMLCircle*);

	void render(sf::RenderTarget&, sf::RenderStates);
	SFMLObject* copy();
	
	void handleEvent(sf::Event);

	~SFMLCircle();
};

#endif
