/*
 *	SFMLGui.h
 *
 *	by Vinicius Rodrigues
 *	May 20, 2020
 */

#include <SFML/Graphics.hpp>

#ifndef __SFMLOBJECT_H__
#define __SFMLOBJECT_H__

// Base class for SFMLGui objects
// Use Decorator Pattern
class SFMLObject {

public:
	enum Positioning {
		Static, 
		HorizontallyRelative, 
		VerticallyRelative
	};

	enum Align {
		Start, 
		End, 
		Center, 
		Stretch
	};

protected: 

	// Objects to comunicate with others objects
	SFMLObject* m_parent;
	SFMLObject* m_child;
	SFMLObject* m_left;
	SFMLObject* m_right;

	std::string m_id;
	bool m_isHover;
	bool m_isFocused;
	bool m_enableFocus;
	bool m_hide;
	void (*m_onClick)(SFMLObject*);

	sf::IntRect m_rect;
	sf::Color m_color;
	sf::Color m_hoverColor;
	sf::Color m_focusColor;
	Align m_verticalAlign;
	Align m_horizontalAlign;
	Positioning m_positioning;

public:

	SFMLObject();
	SFMLObject(SFMLObject*);

	// Virtual function for render
	// Must also render children and objects on right
	virtual void render(sf::RenderTarget&, sf::RenderStates) = 0;

	// Build a object with another object
	virtual SFMLObject* copy() = 0;

	// Add children for object
	// Dont add same object twice
	void addChildren(SFMLObject* child);
	
	void removeChildren(SFMLObject* child);
	void removeThis();

	SFMLObject* getParent();

	bool handleMouseMove(sf::Vector2f);
	bool handleMouseClick(sf::Vector2f);

	// return Focused Object
	SFMLObject* handleFocus(sf::Vector2f);

	virtual void handleEvent(sf::Event) = 0;

	// Calculate rect based in parent rect and aligning
	sf::IntRect getRect();
	
	// Set the size for the object
	void setSize(int width, int height);

	void setMargin(int horizontal, int vertical);

	// Tiny Getters and Setters for Object's States
	void setColor(sf::Color color);
	sf::Color getColor();
	void setHoverColor(sf::Color color);
	sf::Color getHoverColor();
	void setFocusColor(sf::Color color);
	sf::Color getFocusColor();
	void setVerticalAlign(Align);
	Align getVerticalAlign();
	void setHorizontalAlign(Align);
	Align getHorizontalAlign();
	void setPositioning(Positioning);
	Positioning getPositioning();
	void setId(std::string);
	SFMLObject* getChild(std::string);
	void setHide(bool);

	void setOnClick(void (*func)(SFMLObject*));


	~SFMLObject();

private:

	// Set the parent, used only by function addChildren
	void setParent(SFMLObject* parent);

	// Set the right, to make a linked list
	void addRight(SFMLObject* right);

	void setLeft(SFMLObject* left);
};

#endif
