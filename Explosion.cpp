#include "pch.h"
#include "Explosion.h"


void Explosion::reload()
{
	isStarted = false;
	mPointerToAnimation = 0;
}

Explosion::Explosion(const sf::Sprite & sprite)
{

	mSprite = sprite;
	mPointerToAnimation = 0;
	mClock.restart();
	isStarted = false; 
	isEnding = false; 

	mSprite.setPosition({ 350.f ,550.f });
	mSprite.setScale(2, 2);

	mAnimation.push_back(sf::IntRect(132, 202, 9, 9));
	mAnimation.push_back(sf::IntRect(451, 197, 30, 23));
	mAnimation.push_back(sf::IntRect(772, 192, 30, 30));
	mAnimation.push_back(sf::IntRect(1080, 179, 55, 42));
	mAnimation.push_back(sf::IntRect(1395, 168, 76, 52));

	mAnimation.push_back(sf::IntRect(99, 379, 101, 75));
	mAnimation.push_back(sf::IntRect(413, 369, 117, 85));
	mAnimation.push_back(sf::IntRect(721, 367, 134, 85));
	mAnimation.push_back(sf::IntRect(1035, 349, 145, 102));
	mAnimation.push_back(sf::IntRect(1350, 339, 155, 110));

	mAnimation.push_back(sf::IntRect(61, 565, 178, 114));
	mAnimation.push_back(sf::IntRect(368, 559, 207, 130));
	mAnimation.push_back(sf::IntRect(692, 546, 198, 138));
	mAnimation.push_back(sf::IntRect(993, 532, 226, 154));
	mAnimation.push_back(sf::IntRect(1319, 512, 241, 176));

	mAnimation.push_back(sf::IntRect(38, 738, 238, 177));
	mAnimation.push_back(sf::IntRect(347, 731, 254, 185));
	mAnimation.push_back(sf::IntRect(666, 721, 259, 193));
	mAnimation.push_back(sf::IntRect(976, 713, 277, 197));
	mAnimation.push_back(sf::IntRect(1305, 715, 280, 195));

	mAnimation.push_back(sf::IntRect(27, 947, 286, 185));
	mAnimation.push_back(sf::IntRect(344, 954, 283, 193));
	mAnimation.push_back(sf::IntRect(661, 960, 288, 182));
	mAnimation.push_back(sf::IntRect(985, 950, 288, 186));
	mSprite.setTextureRect(mAnimation.at(mPointerToAnimation));
}

void Explosion::fire()
{
	isStarted = true; 
}

void Explosion::Update()
{
	if (!isStarted)
	{
			mClock.restart();	
	}

	if (isStarted) {
		if (mClock.getElapsedTime().asMilliseconds() > 48.f)
		{
			if (mPointerToAnimation <= mAnimation.size() -2)
			{
				// décalage relatif à la position actuelle
				
				mPointerToAnimation++;
				sf::IntRect rec = mAnimation.at(mPointerToAnimation);
				mSprite.setOrigin(rec.width / 2, rec.height / 2);

				mSprite.setTextureRect(mAnimation.at(mPointerToAnimation));
				mClock.restart();
			}
			else {
				reload(); 
				isEnding = true; 

			}
		}

	}

}

bool Explosion::ending()
{
	return isEnding; 
}



void Explosion::draw(sf::RenderTarget & target, sf::RenderStates state) const
{
	target.draw(mSprite);
}

Explosion::~Explosion()
{
}
