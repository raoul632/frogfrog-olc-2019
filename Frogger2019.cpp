// Frogger2019.cpp : Ce fichier contient la fonction 'main'. L'exécution du programme commence et se termine à cet endroit.
//

#include "pch.h"
#include <iostream>
#include <sstream>
#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"
#include "TransportRoutier.h"
#include "TransportFluvial.h"
#include "Ressource.h"
#include "Player.h"
#include "Goal.h"
#include "Vehicle.h"
#include "Wood.h"
#include "Map.h"
#include "ConsoleText.h"
#include "Explosion.h"
#include "SoundManager.h"

Player* frog = nullptr; 
Goal* fly = nullptr; 
TransportRoutier* routeNroUn = nullptr;
TransportRoutier* routeNroDeux= nullptr;
TransportRoutier* routeNroTrois = nullptr;
TransportRoutier* routeNroQuattre = nullptr;
TransportFluvial* voieFluvial = nullptr; 
TransportFluvial* voieFluvialDeux = nullptr;
TransportFluvial* voieFluvialTrois  = nullptr;
sf::Texture* texture = nullptr;
sf::Texture* textureExplosion = nullptr;
Explosion* boom = nullptr;
sf::Clock* counter = nullptr; 

enum GAMESTATE {INTRO, GAME, DEATH, VICTORY, END};

void loadGameRessource() {

	counter = new sf::Clock(); 

	texture = new sf::Texture();
	sf::Sprite sprite; //et oui magique un sprite sur la pile qui pointe toujours sur la texture 
	if (!texture->loadFromFile("images/sprites.png")) {
		return;
	}
	sprite.setTexture(*texture);

	textureExplosion = new sf::Texture(); 
	sf::Sprite spriteExplosion; 
	if (!textureExplosion->loadFromFile("images/nuclearexplosion.png")) {
		return; 
	}
	spriteExplosion.setTexture(*textureExplosion); 
	boom = new Explosion(spriteExplosion); 
	

	frog = new Player(sprite);
	fly = new Goal(sprite);
	//Ressource resus(sprite); //Pour patager avec les Les flot transports 
	routeNroUn = new TransportRoutier(sprite, 8, 6, true, { 20.f, 580.f, -680.f, -1260.f }, 2.2f);
	routeNroDeux = new TransportRoutier(sprite, 7, 5, true, { 60.f,  -380.f, -860.f }, 5.f);
	routeNroTrois = new TransportRoutier(sprite, 5, 5, false, { 60.f,  -380.f, -860.f }, 3.5f);
	routeNroQuattre = new TransportRoutier(sprite, 6, 1, false, { 60.f,  -380.f, -860.f }, 6.5f);
	routeNroUn->init(); 
	routeNroDeux->init(); 
	routeNroTrois->init(); 
	routeNroQuattre->init(); 

	voieFluvial = new TransportFluvial(sprite, 3, 3, true, { 20.f, 480.f, 900.f, -500.f }, 1.3f); //
	voieFluvialDeux = new TransportFluvial(sprite, 2, 3, false, { 68.f, 495.f, -660.f }, 1.8f);
	voieFluvialTrois = new TransportFluvial(sprite, 1, 2, true, { 68.f, 495.f, -660.f }, 2.1f);
	fly->reload();
	counter->restart(); 

}


void deleteGameRessource() {
	delete texture; 
	texture = nullptr; 
	delete frog; 
	frog = nullptr; 
	delete fly; 
	fly = nullptr; 
	delete routeNroUn; 
	routeNroUn = nullptr; 
	delete routeNroDeux; 
	routeNroDeux = nullptr; 
	delete routeNroTrois; 
	routeNroTrois = nullptr; 
	delete voieFluvial; 
	voieFluvial = nullptr; 
	delete voieFluvialDeux;
	voieFluvialDeux = nullptr; 
	delete voieFluvialTrois; 
	voieFluvialTrois = nullptr; 
	delete boom; 
	boom = nullptr; 
	delete routeNroQuattre; 
	routeNroQuattre = nullptr; 
	delete counter; 
	counter = nullptr; 
}


int main()
{
	//on va changer d'état avec cette enum
	GAMESTATE currentState = GAMESTATE::INTRO; 

	sf::RenderWindow window(sf::VideoMode(800, 880), "Frogger 2019"); 
	const int level[] = {
						 3,3,4,3,3,3,3,4,3,3,
						 1,1,1,1,1,1,1,1,1,1,
						 1,1,1,1,1,1,1,1,1,1,
						 1,1,1,1,1,1,1,1,1,1,
					     2,2,2,2,2,2,2,2,2,2,
						 2,2,2,2,2,2,2,2,2,2,
						 2,2,2,2,2,2,2,2,2,2,
						 2,2,2,2,2,2,2,2,2,2,
						 2,2,2,2,2,2,2,2,2,2,
		                 0,0,0,0,0,0,0,0,0,0,
						 0,0,0,0,0,0,0,0,0,0,					 
						 }; 

	sf::Clock clock; 
	std::string counterSVG = ""; 
	sf::RectangleShape introShape; 
	introShape.setFillColor(sf::Color::Color(0x92,0x3c,0xc4,0xff)); 
	introShape.setPosition(100, 100); 
	introShape.setSize({ 600.f,600.f }); 
	
	//on charge les ressource !! sisi sf::RectangleShape
	loadGameRessource(); 

	sf::Font* font = new sf::Font(); 
	if (!font->loadFromFile("Font/zerovelo.ttf"))
	{
		return -1;
	}

	ConsoleText introMessage(*font, 32, sf::Color::Black,{100,200 });//sf::Color::Color(0x4c,0x60,0x46,0xff)
	introMessage.MessageToShow("OLC CODEJAM 2019");
	introMessage.MessageToShow("");
	introMessage.MessageToShow("The wise elder toad RamusRamus ");
	introMessage.MessageToShow("give you this mission :"); 
	introMessage.MessageToShow("you are the choosen frog ");
	introMessage.MessageToShow("find the super fly and eat them"); 
	introMessage.MessageToShow("the alchemy made by flyfly ");
	introMessage.MessageToShow(" give you superpower ");
	introMessage.MessageToShow("the power to save the world");
	introMessage.MessageToShow(" and humankind from destruction");
	introMessage.MessageToShow("");
	introMessage.MessageToShow("Press Space Bar to Start");

	ConsoleText deathMessage(*font, 32, sf::Color::Red, { 100,400 });
	deathMessage.MessageToShow("You are Dead" );
	deathMessage.MessageToShow(" ");
	deathMessage.MessageToShow("Press Space Bar to reload");

	ConsoleText endMessage(*font, 32, sf::Color::Red, { 100,400 });
	endMessage.MessageToShow("NEVER TRUST A TOAD ");
	endMessage.MessageToShow(" ");
	endMessage.MessageToShow("Press Space Bar to reload");

	ConsoleText counterMessage(*font, 28, sf::Color::Red, { 680, 0 });
	counterMessage.MessageToShowUniqu("0"); 

	SoundManager sm; 
	sm.loadMusic("Audio/GameMusic.wav");
	sm.loadSound("Audio/omeawe.wav"); 
	sm.playMusic(); 
	//la carte est fixe
	Map map; 
	map.load("images/sprites2.png", sf::Vector2u(80, 80), level, 10, 11); 
	
	
	while (window.isOpen()) {
		//GAME
		sf::Event event; 

		Direction directionGrenouille = FIXE; 

		while (window.pollEvent(event))
		{

			switch (event.type) {
				case sf::Event::Closed:
					window.close(); 
					break; 
				case sf::Event::KeyPressed:
					if (event.key.code == sf::Keyboard::Down) {
						directionGrenouille = BAS; 
					}
					if (event.key.code == sf::Keyboard::Up) {
						directionGrenouille = HAUT;
					}
					if (event.key.code == sf::Keyboard::Right) {
						directionGrenouille = DROITE;
					}
					if (event.key.code == sf::Keyboard::Left) {
						directionGrenouille = GAUCHE;
					}
					if (event.key.code == sf::Keyboard::Space && ((currentState == GAMESTATE::DEATH)) || (currentState == GAMESTATE::INTRO) || (currentState == GAMESTATE::END)) {
						loadGameRessource();
						currentState = GAMESTATE::GAME;
					}
					

					break; 
				default:
					break; 

			}
			



		}

		bool isPlayerOnWood = false;
		bool isPLayerTouchCar = false; 
		//Update 
		if (currentState == GAMESTATE::GAME || currentState == GAMESTATE::DEATH || currentState == GAMESTATE::VICTORY)
		{
			frog->Update(directionGrenouille);
			fly->update();

			routeNroUn->update();
			routeNroDeux->update();
			routeNroTrois->update();
			routeNroQuattre->update(); 

			voieFluvial->update();
			voieFluvialDeux->update();
			voieFluvialTrois->update();

			for (const auto& vec : routeNroUn->mListVehicle) {
				if (frog->mPosition.intersects(vec->getPositionRect())) {
					isPLayerTouchCar = true;
				}
			}
			for (const auto& vec : routeNroDeux->mListVehicle) {
				if (frog->mPosition.intersects(vec->getPositionRect())) {
					isPLayerTouchCar = true;
				}
			}
			for (const auto& vec : routeNroTrois->mListVehicle) {
				if (frog->mPosition.intersects(vec->getPositionRect())) {
					isPLayerTouchCar = true;
				}
			}

			for (const auto& vec : routeNroQuattre->mListVehicle) {
				if (frog->mPosition.intersects(vec->getPositionRect())) {
					isPLayerTouchCar = true;
				}
			}

			//check si le player est sur du bois
			for (const auto& vec : voieFluvial->mListWood) {
				if (frog->mPosition.intersects(vec->getPositionRect())) {
					frog->MovePlayer(voieFluvial->mVitesse, voieFluvial->isForward);
					isPlayerOnWood = true;
				}
			}

			for (const auto& vec : voieFluvialDeux->mListWood) {
				if (frog->mPosition.intersects(vec->getPositionRect())) {
					frog->MovePlayer(voieFluvialDeux->mVitesse, voieFluvialDeux->isForward);
					isPlayerOnWood = true;
				}
			}

			for (const auto& vec : voieFluvialTrois->mListWood) {
				if (frog->mPosition.intersects(vec->getPositionRect())) {
					frog->MovePlayer(voieFluvialTrois->mVitesse, voieFluvialTrois->isForward);
					isPlayerOnWood = true;
				}
			}
		}
		
		if (currentState == GAMESTATE::GAME)
		{
			sf::Time elapsed = counter->getElapsedTime(); 
			counterSVG = std::to_string(elapsed.asSeconds());
			
			counterMessage.MessageToShowUniqu(counterSVG);
		}

		if (currentState == GAMESTATE::VICTORY)
		{
			sm.playSound(); 
			boom->Update();
			if (boom->ending())
			{
				currentState = GAMESTATE::END; 
			}
		}

 

		//Collision gestion du niveau 

		if (frog->mPosition.intersects(fly->mPosition) && !frog->isWining ) {
			currentState = GAMESTATE::VICTORY; 
			frog->isWining = true; 
			frog->reload(); 
			fly->reload(); 
			boom->fire(); 
			
		}
		if ((map.getTile(frog->getPosition()) == 1) && !isPlayerOnWood) {
			
			frog->isAlive = false; 
			currentState = GAMESTATE::DEATH; 
		}
		if (isPLayerTouchCar) {
			frog->isAlive = false;
			currentState = GAMESTATE::DEATH;
		}

		
	    //Draw		
		window.clear(sf::Color::Black); 
		window.draw(map);
		window.draw(*fly);
	
		//dessin des transport routier 		
		for (const auto& vec : routeNroUn->mListVehicle) {
			window.draw(*vec); 
		}
		for (const auto& vec : routeNroDeux->mListVehicle) {
			window.draw(*vec);
		}
		for (const auto& vec : routeNroTrois->mListVehicle) {
			window.draw(*vec);
		}

		for (const auto& vec : routeNroQuattre->mListVehicle) {
			window.draw(*vec);
		}

		//dessin des transports fluvial
		for (const auto& vec : voieFluvial->mListWood) {
			window.draw(*vec); 
		}

		for (const auto& vec : voieFluvialDeux->mListWood) {
			window.draw(*vec);
		}

		for (const auto& vec : voieFluvialTrois->mListWood) {
			window.draw(*vec);
		}

	
		//la grenouille est dessiné a la fin bien sur 
		window.draw(*frog);

		if (currentState == GAMESTATE::GAME) {
			window.draw(counterMessage); 
		}

		if (currentState == GAMESTATE::INTRO) {
			window.draw(introShape); 
			window.draw(introMessage); 
		}

		if (currentState == GAMESTATE::VICTORY)
		{
			window.draw(counterMessage);
			window.draw(*boom);
		}
		//GAME

		//TEXT
		if (currentState == GAMESTATE::DEATH)
		{
			window.draw(counterMessage);
			window.draw(deathMessage);
		}

		if (currentState == GAMESTATE::END) {
			window.draw(endMessage); 
		}
		
		window.display(); 
		//fin draw

		//on bloque le temps a 16 milliseconds
		if (clock.getElapsedTime().asMilliseconds() < 16)
		{
			sf::sleep(sf::milliseconds(16 - clock.getElapsedTime().asMilliseconds())); 
		}
		
		clock.restart();
	

	}

	deleteGameRessource(); 
	return 0; 
}


// Exécuter le programme : Ctrl+F5 ou menu Déboguer > Exécuter sans débogage
// Déboguer le programme : F5 ou menu Déboguer > Démarrer le débogage

// Conseils pour bien démarrer : 
//   1. Utilisez la fenêtre Explorateur de solutions pour ajouter des fichiers et les gérer.
//   2. Utilisez la fenêtre Team Explorer pour vous connecter au contrôle de code source.
//   3. Utilisez la fenêtre Sortie pour voir la sortie de la génération et d'autres messages.
//   4. Utilisez la fenêtre Liste d'erreurs pour voir les erreurs.
//   5. Accédez à Projet > Ajouter un nouvel élément pour créer des fichiers de code, ou à Projet > Ajouter un élément existant pour ajouter des fichiers de code existants au projet.
//   6. Pour rouvrir ce projet plus tard, accédez à Fichier > Ouvrir > Projet et sélectionnez le fichier .sln.

