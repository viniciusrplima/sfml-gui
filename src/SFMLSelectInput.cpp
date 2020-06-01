/*
 *	SFMLSelectInput.cpp
 *
 *	May 27, 2020
 *	by Vinicius Rodrigues
 */

#include "SFMLSelectInput.h"

SFMLSelectInput::SFMLSelectInput() 
	: SFMLObject(), 
	  m_sfmlText() {
	
	m_sfmlText.setFont(g_pDefaultFont->get());
	m_enableFocus = true;
	m_offset = 0;
	m_target = 0;
	m_spacing = 5;
	m_markColor = sf::Color(230, 230, 230, 255);
}

SFMLSelectInput::SFMLSelectInput(SFMLSelectInput* obj) 
	: SFMLObject(obj), 
	  m_sfmlText() {

	setItems(obj->m_items);
	m_sfmlText.setFont(g_pDefaultFont->get());
	m_enableFocus = true;
	m_offset = 0;
	m_target = 0;
	m_spacing = 5;
	m_markColor = sf::Color(230, 230, 230, 255);
}

void SFMLSelectInput::setItems(const std::vector<SELECT_ITEM>& items) {
	m_items = std::vector<SELECT_ITEM>();

	for(int i = 0; i < items.size(); i++) {
		SELECT_ITEM item;
		item.value = items[i].value;
		item.object = item.object->copy();

		m_items.push_back(item);
	}
}

void SFMLSelectInput::addItem(SELECT_ITEM& item) {
	m_items.push_back(item);
}

void SFMLSelectInput::addItem(int value, SFMLObject* obj) {
	SELECT_ITEM item;
	item.value = value;
	item.object = obj;

	addItem(item);
}

void SFMLSelectInput::setTarget(int target) {
	m_target = target % m_items.size();
	calcOffset();
}

void SFMLSelectInput::setLayout(SFMLSelectInput::Layout layout) {
	m_layout = layout;
}

SFMLSelectInput::Layout SFMLSelectInput::getLayout() {
	return m_layout;
}

void SFMLSelectInput::setSpacing(int spacing) {
	m_spacing = spacing;
}

void SFMLSelectInput::setMarkColor(sf::Color markColor) {
	m_markColor = markColor;
}

void SFMLSelectInput::calcOffset() {
	int offset = 0;
	auto rect = getRect();

	if(m_layout == SFMLSelectInput::Vertical) {
		for(int i = 0; i <= m_target; i++) {
			auto size = m_items[i].object->getSize();
			offset += size.y + m_spacing;
		}

		if(offset - m_offset > rect.height || 
				offset - m_offset < 0) {
			m_offset += offset - m_offset - rect.height;
		}

		if(m_target == 0) 
			m_offset = 0;
	}

	if(m_layout == SFMLSelectInput::Horizontal) {
		for(int i = 0; i <= m_target; i++) {
			auto size = m_items[i].object->getSize();
			offset += size.x + m_spacing;
		}

		if(offset - m_offset > rect.width || 
		   offset - m_offset < 0) {
			m_offset += offset - m_offset - rect.width;
		}

		if(m_target == 0) 
			m_offset = 0;
	}
}

int SFMLSelectInput::getValue() {
	return m_items[m_target].value;
}

void SFMLSelectInput::render(sf::RenderTarget& target, sf::RenderStates state) {

	auto rect = getRect();

	sf::RenderTexture mask;
	mask.create(rect.width, rect.height, 24);

	sf::Color bgColor;
	if(m_enableFocus && m_isFocused)
		bgColor = m_focusColor;
	else
		bgColor = m_color;

	mask.clear(bgColor);
	mask.display();
	
	if(m_layout == SFMLSelectInput::Vertical)
		drawVerticalItems(mask, rect);
	if(m_layout == SFMLSelectInput::Horizontal)
		drawHorizontalItems(mask, rect);

	sf::RenderStates allState(state);
	allState.transform.translate(rect.left, rect.top);
	sf::Sprite sprite(mask.getTexture());
	target.draw(sprite, allState);

	if(m_child != 0) m_child->render(target, state);
	if(m_right != 0) m_right->render(target, state);
}

void SFMLSelectInput::drawVerticalItems(sf::RenderTarget& mask, sf::IntRect rect) {
	// draw items
	sf::RenderStates itemState;
	itemState.transform.translate(0, -m_offset);
		
	int top = 0;

	for(int i = 0; i < m_items.size(); i++) {
		itemState.transform.translate(0, top);
		
		if(m_items[i].object != 0) {
			auto rc = m_items[i].object->getRect();
			top = rc.height + m_spacing;
	
			if(i == m_target) {
				sf::RectangleShape shape;
				shape.setFillColor(m_markColor);
				shape.setSize(sf::Vector2f(rect.width, rc.height));
				mask.draw(shape, itemState);
			}

			m_items[i].object->render(mask, itemState);
		}
	}
}

void SFMLSelectInput::drawHorizontalItems(sf::RenderTarget& mask, sf::IntRect rect) {
	// draw items
	sf::RenderStates itemState;
	itemState.transform.translate(-m_offset, 0);
		
	int left = 0;

	for(int i = 0; i < m_items.size(); i++) {
		itemState.transform.translate(left, 0);
		
		if(m_items[i].object != 0) {
			auto rc = m_items[i].object->getRect();
			left = rc.width + m_spacing;
	
			if(i == m_target) {
				sf::RectangleShape shape;
				shape.setFillColor(m_markColor);
				shape.setSize(sf::Vector2f(rc.width, rect.height));
				mask.draw(shape, itemState);
			}

			m_items[i].object->render(mask, itemState);
		}
	}
}

SFMLObject* SFMLSelectInput::copy() {
	return new SFMLSelectInput(this);
}

void SFMLSelectInput::handleEvent(sf::Event event) {
	
	if(event.type == sf::Event::KeyPressed) {
		if(m_layout == SFMLSelectInput::Vertical) {
			if(event.key.code == sf::Keyboard::Down)
				setTarget(m_target+1);
			else if(event.key.code == sf::Keyboard::Up)
				setTarget(m_target-1);
		}

		if(m_layout == SFMLSelectInput::Horizontal) {
			if(event.key.code == sf::Keyboard::Right)
				setTarget(m_target+1);
			else if(event.key.code == sf::Keyboard::Left)
				setTarget(m_target-1);
		}
	}
}

SFMLSelectInput::~SFMLSelectInput() {
}
