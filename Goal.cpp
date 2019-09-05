#include "pch.h"
#include "Goal.h"
#include "Utils.h"


Goal::Goal(const sf::Sprite& sprite)
{
	mSprite = sprite; 
	mCoordinateSprite = {82,171,40,49}; 
	mSprite.setTextureRect(mCoordinateSprite); 
	mSprite.setColor(sf::Color(255, 255, 0)); 

}


Goal::~Goal()
{


}

void Goal::draw(sf::RenderTarget & target, sf::RenderStates state) const
{
	target.draw(mSprite); 

}

void Goal::update()
{
	mPosition = mSprite.getGlobalBounds(); 

}

//on va chargé le sprite dans un ou deux endroits différents 
void Goal::reload()
{
	int res = Generate(); 
	mSprite.setPosition(0.f, 0.f); 
	if (res == 1) 
		mSprite.move(180, 20);
	if (res == 2)
		mSprite.move(580, 20); 




}
