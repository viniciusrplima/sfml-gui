/*
 *	SFMLImage.h
 *
 *	May 31, 2020
 *	by Vinicius Rodrigues
 */


#include <SFML/Graphics.hpp>
#include "SFMLObject.h"
#include "SFMLTextureHolder.h"

#ifndef __SFMLIMAGE_H__
#define __SFMLIMAGE_H__

class SFMLImage: public SFMLObject {

	sf::Sprite m_sprite;
	sf::Vector2f m_size;
	TextureId m_textureId;

public:

	SFMLImage();
	SFMLImage(SFMLImage*);

	void setImage(TextureId);

	void render(sf::RenderTarget&, sf::RenderStates);
	SFMLObject* copy();
	void handleEvent(sf::Event);

	~SFMLImage();
};

#endif
