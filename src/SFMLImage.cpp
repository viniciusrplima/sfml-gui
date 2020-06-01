/*
 *	SFMLImage.cpp
 *
 *	May 31, 2020
 *	by Vinicius Rodrigues
 */

#include <iostream>
#include "SFMLImage.h"

SFMLImage::SFMLImage() : SFMLObject(), m_sprite() {
}

SFMLImage::SFMLImage(SFMLImage* obj) : SFMLObject(obj), m_sprite() {
	setImage(obj->m_textureId);
}

void SFMLImage::setImage(TextureId id) {
	m_textureId = id;
	m_sprite.setTexture(g_pSFMLTextureHolder->get(id));
	m_size = sf::Vector2f(g_pSFMLTextureHolder->get(id).getSize());
}

void SFMLImage::render(sf::RenderTarget& target, sf::RenderStates state) {

	auto rect = getRect();

	sf::RenderStates imgState(state);
	imgState.transform.translate(rect.left, rect.top);
	imgState.transform.scale(rect.width / m_size.x, rect.height / m_size.y);

	target.draw(m_sprite, imgState);

	if(m_child != 0) m_child->render(target, state);
	if(m_right != 0) m_right->render(target, state);
}	

SFMLObject* SFMLImage::copy() {
	return new SFMLImage(this);
}

void SFMLImage::handleEvent(sf::Event) {
}

SFMLImage::~SFMLImage() {
}
