/*
 *	SFMLObject.cpp
 *
 *	by Vinicius Rodrigues
 *	May 20, 2020
 */

#include <iostream>
#include "SFMLObject.h"

SFMLObject::SFMLObject() {
	m_parent = 0;
	m_child = 0;
	m_left = 0;
	m_right = 0;
	m_id = "";
	m_hide = false;
	m_rect = sf::IntRect(0, 0, 0, 0);
	m_hoverColor = sf::Color::Transparent;
	m_focusColor = sf::Color::Transparent;
	m_isHover = false;
	m_isFocused = false;
	m_onClick = 0;
	m_enableFocus = false;
}

SFMLObject::SFMLObject(SFMLObject* object) {
	m_parent = 0;
	m_left = 0;
	m_right = 0;
	m_child = 0;
	m_id = "";
	m_hide = object->m_hide;
	m_rect = sf::IntRect(object->m_rect);
	m_color = object->m_color;
	m_hoverColor = object->m_hoverColor;
	m_focusColor = object->m_focusColor;
	m_verticalAlign = object->m_verticalAlign;
	m_horizontalAlign = object->m_horizontalAlign;
	m_positioning = object->m_positioning;
	m_isHover = false;
	m_isFocused = false;
	m_enableFocus = false;
	m_onClick = object->m_onClick;

	SFMLObject* nextChild = object->m_child;
	while(nextChild != 0) {
		addChildren(nextChild->copy());
		nextChild = nextChild->m_right;
	}
}

void SFMLObject::addChildren(SFMLObject* child) {
	child->setParent(this);

	if(m_child == 0) 
		m_child = child;
	else
		m_child->addRight(child);
}

void SFMLObject::removeChildren(SFMLObject* child) {
	SFMLObject* nextChild = m_child;
	while(nextChild != 0) {
		if(nextChild == child) {
			// child is not the first child
			if(nextChild->m_left != 0) {
				nextChild->m_left->m_right = nextChild->m_right;
			}
			// child is the first child
			else {
				if(nextChild->m_right != 0)
					nextChild->m_right->m_left = 0;
				m_child = nextChild->m_right;
			}

			// child is not the last
			if(nextChild->m_right != 0) {
				nextChild->m_right->m_left = nextChild->m_left;
			}
			// child is the last
			else {
				if(nextChild->m_left != 0)
					nextChild->m_left->m_right = 0;
			}

			return;
		}
		nextChild = nextChild->m_right;
	}
}

void SFMLObject::removeThis() {
	if(m_parent != 0) {
		m_parent->removeChildren(this);
		delete this;
	}
}

SFMLObject* SFMLObject::getParent() {
	return m_parent;
}

bool SFMLObject::handleMouseMove(sf::Vector2f pos) {
	m_isHover = false;

	if(m_child == 0 || !m_child->handleMouseMove(pos)) {
		sf::IntRect rect = getRect();

		if(m_hoverColor != sf::Color::Transparent &&
		   pos.x >= rect.left && pos.x <= rect.left + rect.width &&
		   pos.y >= rect.top && pos.y <= rect.top + rect.height)
			m_isHover = true;
		else if(m_right != 0)
			return m_right->handleMouseMove(pos);
	}

	return m_isHover;
}

bool SFMLObject::handleMouseClick(sf::Vector2f pos) {

	if(m_child == 0 || !m_child->handleMouseClick(pos)) {
		sf::IntRect rect = getRect();

		if(m_onClick != 0 &&
		   pos.x >= rect.left && pos.x <= rect.left + rect.width &&
		   pos.y >= rect.top && pos.y <= rect.top + rect.height) {
			m_onClick(this);
			return true;
		}
		else if(m_right != 0)
			return m_right->handleMouseClick(pos);
	}

	return false;
}

SFMLObject* SFMLObject::handleFocus(sf::Vector2f pos) {
	m_isFocused = false;

	if(m_right != 0) {
		auto focused = m_right->handleFocus(pos);
		if(focused != 0) return focused;
	}

	if(m_child != 0) {
		auto focused = m_child->handleFocus(pos);
		if(focused != 0) return focused;
	}

	sf::IntRect rect = getRect();
	if(m_enableFocus &&
	   pos.x >= rect.left && pos.x <= rect.left + rect.width &&
	   pos.y >= rect.top && pos.y <= rect.top + rect.height) {
		m_isFocused = true;
		return this;
	}

	return 0;
}

void SFMLObject::setColor(sf::Color color) {
	m_color = color;
}

sf::Color SFMLObject::getColor() {
	return m_color;
}

void SFMLObject::setHoverColor(sf::Color color) {
	m_hoverColor = color;
}

void SFMLObject::setOnClick(void (*func)(SFMLObject*)) {
	m_onClick = func;
}

sf::Color SFMLObject::getHoverColor() {
	return m_hoverColor;
}

void SFMLObject::setFocusColor(sf::Color color) {
	m_focusColor = color;
}

sf::Color SFMLObject::getFocusColor() {
	return m_focusColor;
}

sf::IntRect SFMLObject::getRect() {
	sf::IntRect rect(m_rect);

	// Alignment with parent
	if(m_parent != 0) {
		sf::IntRect parentRect = m_parent->getRect();

		switch(m_verticalAlign) {
		
			case SFMLObject::End: 
				rect.top = parentRect.top + parentRect.height - rect.height - rect.top;
				break;
			case SFMLObject::Center:
				// Position don't work
				rect.top = parentRect.top + parentRect.height/2 - rect.height/2;
				break;
			case SFMLObject::Stretch:
				rect.top = parentRect.top + rect.top;
				rect.height = parentRect.height - 2 * rect.top;
				break;
			case SFMLObject::Start:
			default:
				rect.top += parentRect.top;
		}

		switch(m_horizontalAlign) {
			case SFMLObject::End:
				rect.left = parentRect.left + parentRect.width - rect.width - rect.left;
				break;
			case SFMLObject::Center:
				rect.left = parentRect.left + parentRect.width/2 - rect.width/2;
				break;
			case SFMLObject::Stretch:
				rect.left = parentRect.left + rect.left;
				rect.width = parentRect.width - 2 * rect.left;
				break;
			case SFMLObject::Start:
			default:
				rect.left += parentRect.left;
		}
	}

	if(m_left != 0 && m_positioning != SFMLObject::Static) {

		sf::IntRect leftRect = m_left->getRect();

		if(m_positioning == SFMLObject::HorizontallyRelative) {
			if(m_horizontalAlign != SFMLObject::End) {
				rect.left += leftRect.left + leftRect.width;
			}
			else {
				rect.left -= leftRect.left + leftRect.width;
			}
		}
		else if(m_positioning == SFMLObject::VerticallyRelative) {
			if(m_verticalAlign != SFMLObject::End) {
				rect.top += leftRect.top + leftRect.height;
			}
			else {
				rect.top -= leftRect.top + leftRect.height;
			}
		}
	}

	return rect;
}

void SFMLObject::setSize(int width, int height) {
	m_rect.width = width;
	m_rect.height = height;
}

void SFMLObject::setMargin(int horizontal, int vertical) {
	m_rect.left = horizontal;
	m_rect.top = vertical;
}

void SFMLObject::setVerticalAlign(SFMLObject::Align verticalAlign) {
	m_verticalAlign = verticalAlign;
}

SFMLObject::Align SFMLObject::getVerticalAlign() {
	return m_verticalAlign;
}

void SFMLObject::setHorizontalAlign(SFMLObject::Align horizontalAlign) {
	m_horizontalAlign = horizontalAlign;
}

SFMLObject::Align SFMLObject::getHorizontalAlign() {
	return m_horizontalAlign;
}

void SFMLObject::setPositioning(SFMLObject::Positioning positioning) {
	m_positioning = positioning;
}

SFMLObject::Positioning SFMLObject::getPositioning() {
	return m_positioning;
}

void SFMLObject::setId(std::string id) {
	m_id = id;
}

SFMLObject* SFMLObject::getChild(std::string id) {
	auto nextChild = m_right;
	while(nextChild != 0) {
		if(nextChild->m_id == id)
			return nextChild;
		nextChild = nextChild->m_right;
	}
	return 0;
}

void SFMLObject::setHide(bool hide) {
	m_hide = hide;
}

void SFMLObject::setParent(SFMLObject* parent) {
	m_parent = parent;
}

void SFMLObject::addRight(SFMLObject* right) {
	if(m_right == 0) {
		right->setLeft(this);
		m_right = right;
	}
	else
		m_right->addRight(right);
}

void SFMLObject::setLeft(SFMLObject* left) {
	m_left = left;
}

SFMLObject::~SFMLObject() {	
	SFMLObject* nextChild = m_child;
	while(nextChild != 0) {
		auto childRight = nextChild->m_right;
		delete nextChild;
		nextChild = childRight;
	}
}
