#ifndef EXPLOSITION_H
#define EXPLOSITION_H
#include "SFML/Graphics.hpp"

class Explosion : public sf::Drawable
{
private:
	sf::Sprite mSprite;
	sf::Clock mClock;
	sf::Vector2i vPosition;
	std::vector<sf::IntRect> mAnimation;
	int mPointerToAnimation;
	bool isStarted; 
	bool isEnding; 

public:
	void reload(); 
	Explosion(const sf::Sprite& sprite);
	void fire(); 
	void Update();
	bool ending(); 
	void draw(sf::RenderTarget& target, sf::RenderStates state) const;
	~Explosion();
};


#endif // !EXPLOSITION_H

