/*
 *	SFMLTextureHolder.h
 *
 *	May 31, 2020
 *	by Vinicius Rodrigues
 */

#include <SFML/Graphics.hpp>
#include <string>
#include <memory>
#include <map>
#include "Singleton.hpp"

#ifndef __SFMLTEXTUREHOLDER_H__
#define __SFMLTEXTUREHOLDER_H__

#define g_pSFMLTextureHolder SFMLTextureHolder::Instance()

typedef unsigned int TextureId;

class SFMLTextureHolder: public Singleton<SFMLTextureHolder> {

	std::map<TextureId, std::unique_ptr<sf::Texture>> m_textures;
	TextureId m_lastId;

public:
	SFMLTextureHolder();

	TextureId loadTexture(const std::string&);
	sf::Texture& get(TextureId);

	~SFMLTextureHolder();
};

#endif
