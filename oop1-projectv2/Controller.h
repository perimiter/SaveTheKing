#pragma once
#include "BaseCharacter.h"
#include "StaticCharcter.h"
#include <SFML/Graphics.hpp>
#include <memory>
#include <vector>
#include <fstream>
#include "Pictures.h"
#include "Menu.h"
#include "Counter.h"
#include "End.h"


class Controller
{
public:
	//main game function 
	void play();
	Controller();
	~Controller()=default;
	//initializing level
	void restartLevel();
private:
	//move all dynamic objects
	void moveAll();
	//drwa all objects
	void drwaAll();
	//set backgraund pictures
	void setBackground();
	//read level from file
	void loadFromFile();
	//vector of pictures
	Pictures m_pictures;
	//find selected dynamic character choosen by player
	size_t findContain(sf::Vector2f mouseCoords);
	//control all end situation in game
	End m_mainend;
	//controll of counting time and movement
	Counter m_mainCounter;
	//controll the menu
	Menu m_menu;
	sf::RenderWindow m_window;
	sf::RectangleShape m_background;
	//all the dynamic objects exclude dwarfs
	std::vector < std::unique_ptr<DynamicCharacter>> m_dynamic;
	//all static objects
	std::vector < std::unique_ptr<StaticCharcter>> m_static;
	//all dwarfs
	std::vector< std::unique_ptr<DynamicCharacter >>  m_dwarfs;
	//to read the level
	std::ifstream m_stage{ R"(level1.txt)" };
	//window size
	size_t m_numOfRows=0;
	size_t m_numOfCols=0;
	//selected character
	size_t m_currentSelection = -1,
		m_lastSelection = -1;
	//dwarfs movement cycle
	int m_cycle = 0;
	//flag for end menu start game
	bool m_isPlay = false;
};

