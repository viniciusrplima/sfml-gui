/*
 *	SFMLTextureHolder.cpp
 *
 *	May 31, 2020
 *	by Vinicius Rodrigues
 */

#include "SFMLTextureHolder.h"

SFMLTextureHolder::SFMLTextureHolder() {
	m_lastId = 0;
}

TextureId SFMLTextureHolder::loadTexture(const std::string& filename) {
	std::unique_ptr<sf::Texture> texture(new sf::Texture());
	texture->loadFromFile(filename);

	m_lastId++;
	m_textures.insert(std::make_pair(m_lastId, std::move(texture)));
	return m_lastId;
}

sf::Texture& SFMLTextureHolder::get(TextureId id) {
	auto found = m_textures.find(id);
	return *found->second;
}

SFMLTextureHolder::~SFMLTextureHolder() {
}
