#ifndef MAP_H
#define MAP_H

#include "SFML/Graphics.hpp"
#include <vector>

class Map : public sf::Drawable, public sf::Transformable
{
public:
	Map();


	void draw(sf::RenderTarget& target, sf::RenderStates state) const;
	bool load(const std::string& tleset, sf::Vector2u tileSize, const int* tiles, unsigned int width, unsigned int height); 
	int getTile(sf::Vector2i coord); 


	~Map();

public: 
	sf::VertexArray mVertices;
	sf::Texture mTileset;
	std::vector<sf::IntRect> mTextureCoordinate; 
private: 
	unsigned int mWidth; 
	unsigned int mHeight; 
	const int * mTiles; 
};


#endif // !MAP_H

