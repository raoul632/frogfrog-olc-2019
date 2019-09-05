#include "pch.h"
#include "Player.h"
#include <iostream>


#define MINSIZESCREEN 0
#define MAXSIZESCREEN 800

void Player::draw(sf::RenderTarget & target, sf::RenderStates state) const
{
	
	target.draw(mSprite);

}

void Player::reload()
{

	mClock.restart();
	mSprite.setPosition({ 40.f + 320.f ,40.f + 880.f });
	eMouvement = Direction::HAUT;
	mPointerToAnimation = 0;
	mAngle = 0;
}

sf::Vector2i Player::getPosition()
{
	
	return sf::Vector2i(mPosition.left + (mPosition.width / 2), mPosition.top + (mPosition.height / 2 ));
}

void Player::MovePlayer(float mvt, bool isForward) //Pour les rondin de bois 
{
	if (isForward)
	{
		if (mSprite.getPosition().x + mvt < MAXSIZESCREEN)
		mSprite.move({ mvt, 0.f });
	}
	else
	{
		if (mSprite.getPosition().x - mvt > MINSIZESCREEN)
		mSprite.move({ mvt , 0.f });
	}
}

void Player::SynchronizeAngleWithDirection()
{
	float rotate = mSprite.getRotation();
	if (eMouvement == Direction::BAS) {
		if (rotate != 0) {
			if (rotate == 180) {
				mSprite.rotate(-180); 
			}
			else if (rotate == 90) {
				mSprite.rotate(-90);
			}
			else if (rotate == 270) {
				mSprite.rotate(-270); 
			}

		}
		//mSprite.setScale(1.0f, -1.0f);
	}
	else if (eMouvement == Direction::HAUT) {
		if (rotate != 180) {
			if (rotate == 0) {
				mSprite.rotate(180);
				 
			}
			else if (rotate == 90) {
				mSprite.rotate(90);
			
			}
			else if (rotate == 270) {
				mSprite.rotate(-90);
				
			}
		}
		//mSprite.setScale(1.0f, -1.0f);
	}
	else if (eMouvement == Direction::GAUCHE) {
		if (rotate != 90) {
			if (rotate == 180) {
				mSprite.rotate(-90);
			}
			else if (rotate == 0) {
				mSprite.rotate(90);
			}
			else if (rotate == 270) {
				mSprite.rotate(-180);
			}
		}
	}
	else if (eMouvement == Direction::DROITE) {
		if (rotate != 270) {
			if (rotate == 180) {
				mSprite.rotate(90);
			}
			else if (rotate == 90) {
				mSprite.rotate(180);
			}
			else if (rotate == 0) {
				mSprite.rotate(270);
			}
		}
	}


}


//la grenouille démarre en fixe a 0,0 
Player::Player(const sf::Sprite& sprite)
{
	mSprite = sprite; 
	eMouvement = Direction::HAUT; 
	mPointerToAnimation = 0;
	mAngle = 0; 
	isMovement = false; 
	isAlive = true; 
	isWining = false; 
	mSprite.setOrigin(27.5f, 18.5f);
	mClock.restart(); 

	mSprite.setPosition({ 40.f + 320.f ,40.f + 880.f });
	
	mAnimation.push_back(sf::IntRect(0, 30, 55, 37));
	mAnimation.push_back(sf::IntRect(55, 30, 57, 42)); 
	mAnimation.push_back(sf::IntRect(113, 20, 58, 51));
	mAnimation.push_back(sf::IntRect(175, 8, 47, 66));
	mAnimation.push_back(sf::IntRect(232, 4, 51, 71));
	mAnimation.push_back(sf::IntRect(284, 20, 58, 52));
	mAnimation.push_back(sf::IntRect(302, 334, 63, 50));

	mSprite.setTextureRect(mAnimation.at(mPointerToAnimation));
}

Player::~Player()
{


}

void Player::Update(Direction dir)
{
	if (isAlive)
	{

		if (dir != Direction::FIXE)
		{
			if (isMovement == false && eMouvement == Direction::FIXE) {

				eMouvement = dir;
				isMovement = true;
				mClock.restart();

			}
		}

		if (eMouvement != Direction::FIXE) {
			if (mClock.getElapsedTime().asMilliseconds() > 48.f)
			{
				if (mPointerToAnimation < 5)
				{
					// décalage relatif à la position actuelle
					mPointerToAnimation++;
					mSprite.setTextureRect(mAnimation.at(mPointerToAnimation));
					sf::Vector2f mvt = { 0.f, 0.f };

					if (eMouvement == HAUT) {

						mvt = { 0.f,-16.f };
					}
					else if (eMouvement == BAS) {
						mvt = { 0.f,16.f };
					}
					else if (eMouvement == DROITE) {
						if (mSprite.getPosition().x + 16.f < MAXSIZESCREEN)
							mvt = { 16.f,0.f };
					}
					else if (eMouvement == GAUCHE) {
						if (mSprite.getPosition().x - 16.f > MINSIZESCREEN)
							mvt = { -16.f,0.f };
					}

					mSprite.move(mvt);
					mClock.restart();
				}
				else {
					mPointerToAnimation = 0;
					eMouvement = FIXE;
					isMovement = false;
					mSprite.setTextureRect(mAnimation.at(mPointerToAnimation));

				}
			}

		}


		mPosition = mSprite.getGlobalBounds();
		SynchronizeAngleWithDirection();
	}
	else {
		mSprite.setOrigin(31.5f, 25.f);
		mSprite.setRotation(360); 
		mSprite.setTextureRect(mAnimation.at(6)) ; 
	}

}
