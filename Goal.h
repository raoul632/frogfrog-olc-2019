#ifndef GOAL_H
#define GOAL_H
#include "SFML/Graphics.hpp"

class Goal : public sf::Drawable
{
public:
	Goal(const sf::Sprite& sprite);
	~Goal();

	void draw(sf::RenderTarget& target, sf::RenderStates state) const;
	void update(); 
	void reload(); 

	sf::FloatRect mPosition;
	

private : 
	sf::Sprite mSprite;
	sf::IntRect mCoordinateSprite; 

};


#endif // !GOAL_H
