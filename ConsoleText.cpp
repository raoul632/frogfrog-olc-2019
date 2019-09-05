#include "pch.h"
#include "ConsoleText.h"
#include <iostream>

/*
void messageDeath() {
	if (text != nullptr)
	{
		text->setString("\n");
		text->setCharacterSize(24);
		text->setFillColor(sf::Color::Red);
		text->setPosition({ 400 - 144,400 });
	}
}
*/

void ConsoleText::draw(sf::RenderTarget & target, sf::RenderStates state) const
{
	
	target.draw(mText); 
}

ConsoleText::ConsoleText(const sf::Font & font, unsigned int size, sf::Color color,const  sf::Vector2f pos) : mLimit(size)
{
	mText.setFont(font); 
	mText.setCharacterSize(size);
	mText.setFillColor(color);
	mText.setPosition(pos);

}

void ConsoleText::MessageToShow(std::string text)
{
	
	mEntries.push_back(text); 

	if (mEntries.size() > mLimit)
		mEntries.pop_back(); 

	std::stringstream ss; 
	for (auto &e : mEntries)
		ss << e << "\n";

	mText.setString(ss.str()); 

}

void ConsoleText::MessageToShowUniqu(std::string text)
{
	mText.setString(text); 
}

void ConsoleText::Clear()
{
	mEntries.clear(); 
	mText.setString("");
}


ConsoleText::~ConsoleText()
{
}
