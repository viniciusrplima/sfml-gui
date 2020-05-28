/*
 *	DOMFactory.h
 *
 *	by Vinicius Rodrigues
 *	May 22, 2020
 */

#include <string>
#include <functional>
#include <vector>
#include <SFML/Graphics.hpp>
#include "SFMLObject.h"
#include "SFMLBox.h"
#include "SFMLCaption.h"

#ifndef __DOMFACTORY_H__
#define __DOMFACTORY_H__

class DOMFactory {


public:
	static SFMLObject* createButton(int, int, std::string);
	static SFMLObject* createPopup(int, int);
};

#endif
