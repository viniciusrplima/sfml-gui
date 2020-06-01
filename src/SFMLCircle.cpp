/*
 *	SFMLCircle.cpp
 *
 *	Jun 01, 2020
 *	by Vinicius Rodrigues
 */

#include "SFMLCircle.h"

SFMLCircle::SFMLCircle() : SFMLObject() {
}

SFMLCircle::SFMLCircle(SFMLCircle* obj) : SFMLObject(obj) {
}

void SFMLCircle::render(sf::RenderTarget& target, sf::RenderStates state) {
	
	auto rect = getRect();

	sf::CircleShape circle(std::min(rect.width, rect.height)/2, 30);
	circle.setFillColor(m_color);
	circle.setPosition(rect.left, rect.top);

	target.draw(circle, state);


	if(m_child != 0) m_child->render(target, state);
	if(m_right != 0) m_right-> render(target, state);
}

SFMLObject* SFMLCircle::copy() {
	return new SFMLCircle(this);
}

void SFMLCircle::handleEvent(sf::Event) {
}

SFMLCircle::~SFMLCircle() {
}
