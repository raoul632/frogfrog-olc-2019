#ifndef CONSOLETEXT_H
#define CONSOLETEXT_H
#include "SFML/Graphics.hpp"
#include <list>
#include <string>
#include <sstream>


class ConsoleText : public sf::Drawable
{
private : 
	sf::Font* mFont; 
	sf::Text mText; 
	unsigned int mLimit; 
	std::list<std::string> mEntries;

public:
		void draw(sf::RenderTarget& target, sf::RenderStates state) const;
		ConsoleText(const sf::Font & font, unsigned int limit, sf::Color color, const  sf::Vector2f pos);
		void MessageToShow(std::string text); 
		void MessageToShowUniqu(std::string text); 
		void Clear(); 


		~ConsoleText();
};


#endif // !CONSOLETEXT_H
