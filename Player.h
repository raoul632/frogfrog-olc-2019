#ifndef PLAYER_H
#define PLAYER_H
#include "SFML/Graphics.hpp"
#include <vector>

enum Direction{HAUT, BAS, DROITE, GAUCHE, FIXE};

class Player : public sf::Drawable
{
public:
	Player(const sf::Sprite& sprite);
	~Player();
	void Update(Direction dir); 
	void draw(sf::RenderTarget& target, sf::RenderStates state) const; 
	void reload(); 

public: 
	int mImageNumber;
	sf::FloatRect mPosition;
	Direction eMouvement; 
	bool isMovement; 
	bool isAlive; 
	bool isWining; 
	float mAngle; 
	sf::Vector2i getPosition(); 
	void MovePlayer(float mvt, bool isForward); 

private : 
	sf::Sprite mSprite;
	sf::Clock mClock; 
	sf::Vector2i vPosition;
	std::vector<sf::IntRect> mAnimation; 
	int mPointerToAnimation; 
	void SynchronizeAngleWithDirection(); 
	
	



};


#endif // !PLAYER_H

