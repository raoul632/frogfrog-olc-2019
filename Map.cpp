#include "pch.h"
#include "Map.h"




//0.Herbe 1.eau 2.asphalte 3.bosquet 4.bosquet-nenuphare 5.nenuphare
Map::Map()
{
	mTextureCoordinate.push_back( { 135, 158, 80, 80 }); 
}

void Map::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	// on applique la transformation
	states.transform *= getTransform();

	// on applique la texture du tileset
	states.texture = &mTileset;

	// et on dessine enfin le tableau de vertex
	target.draw(mVertices, states);

}

bool Map::load(const std::string & tileset, sf::Vector2u tileSize, const int * tiles, unsigned int width, unsigned int height)
{
	mTiles = tiles; 
	mWidth = width; 
	mHeight = height; 

	// on charge la texture du tileset
	if (!mTileset.loadFromFile(tileset))
		return false;

	// on redimensionne le tableau de vertex pour qu'il puisse contenir tout le niveau
	mVertices.setPrimitiveType(sf::Quads);
	mVertices.resize(width * height * 4);

	// on remplit le tableau de vertex, avec un quad par tuile
	for (unsigned int i = 0; i < width; ++i)
		for (unsigned int j = 0; j < height; ++j)
		{
			// on récupère le numéro de tuile courant
			int tileNumber = tiles[i + j * width];

			// on en déduit sa position dans la texture du tileset
			int tu = tileNumber % (mTileset.getSize().x / tileSize.x);
			int tv = tileNumber / (mTileset.getSize().x / tileSize.x);

			// on récupère un pointeur vers le quad à définir dans le tableau de vertex
			sf::Vertex* quad = &mVertices[(i + j * width) * 4];

			// on définit ses quatre coins
			quad[0].position = sf::Vector2f(i * tileSize.x, j * tileSize.y);
			quad[1].position = sf::Vector2f((i + 1) * tileSize.x, j * tileSize.y);
			quad[2].position = sf::Vector2f((i + 1) * tileSize.x, (j + 1) * tileSize.y);
			quad[3].position = sf::Vector2f(i * tileSize.x, (j + 1) * tileSize.y);

			// on définit ses quatre coordonnées de texture
			quad[0].texCoords = sf::Vector2f(tu * tileSize.x, tv * tileSize.y);
			quad[1].texCoords = sf::Vector2f((tu + 1) * tileSize.x, tv * tileSize.y);
			quad[2].texCoords = sf::Vector2f((tu + 1) * tileSize.x, (tv + 1) * tileSize.y);
			quad[3].texCoords = sf::Vector2f(tu * tileSize.x, (tv + 1) * tileSize.y);
		}

	return true;

}

int Map::getTile(sf::Vector2i coord)
{
	int largeur = coord.x / 80; 
	int hauteur = coord.y / 80; 
	int tileNumber = mTiles[largeur + hauteur * mWidth];
	
	return tileNumber;
}

Map::~Map()
{
}
