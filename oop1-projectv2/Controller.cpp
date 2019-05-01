#ifdef _DEBUG
#pragma comment(lib, "sfml-main-d.lib")
#pragma comment(lib, "sfml-system-d.lib")
#pragma comment(lib, "sfml-window-d.lib")
#pragma comment(lib, "sfml-graphics-d.lib")
#pragma comment(lib, "sfml-audio-d.lib")
#elif defined(NDEBUG)
#pragma comment(lib, "sfml-main.lib")
#pragma comment(lib, "sfml-system.lib")
#pragma comment(lib, "sfml-window.lib")
#pragma comment(lib, "sfml-graphics.lib")
#pragma comment(lib, "sfml-audio-d.lib")
#else
#error "Unrecognized configuration!"
#endif

#include <string>
#include "Fire.h"
#include "Dwarf.h"
#include "Gate.h"
#include "Giant.h"
#include "Keys.h"
#include "Mage.h"
#include "Theif.h"
#include "Throne.h"
#include "Wall.h"
#include "king.h"
#include "Controller.h"
#include <SFML/Audio.hpp>

	const float movmentSpeed = 5.f ;
int main() {
	srand(time(NULL));
	Controller game;
	sf::Music music;
	if (!music.openFromFile("sound.wav"))
		exit(EXIT_FAILURE);
	//play msuic 
	music.play();
	music.setLoop(true);
	//start the game
	game.play();
}
//start next level 
void Controller::restartLevel()
{
	//dont continue if the player lost
	if (m_mainend.getLose())
		return;
	//rows and cols for the window
	m_numOfCols = 0;
	m_numOfRows = 0;
	//clear all the old data stored 
	m_dynamic.clear();
	m_static.clear();
	m_dwarfs.clear();
	//load new data from file
	loadFromFile();
	//leave if the ga,e is won 
	if (m_mainend.getWin())
		return;
	//set the font for the moves counter  
	m_mainCounter.setFont(m_numOfRows, m_numOfCols);
	//make new window
	m_window.create(sf::VideoMode(m_numOfCols, m_numOfRows + 50), "save the king");
	m_window.setVerticalSyncEnabled(true);
	setBackground();
	//reset all counters and clocks
	m_currentSelection = -1;
	m_mainCounter.resetMoveCounter();
	m_cycle = 0;
	m_mainCounter.restartClock();
	//select by what condition should the player lose
	m_mainend.endConditions();
}
//play the game
void Controller::play()
{
	restartLevel();

	while (m_window.isOpen() && !m_mainend.getWin() && !m_mainend.getLose())
	{
		//display menu
		if (!m_isPlay) {
			m_window.draw(m_background);
			m_menu.setPositions(m_numOfCols, m_numOfRows + 50);
			m_menu.drawMenu(m_window);
		}

		for (sf::Event event; m_window.pollEvent(event);)
		{
			if (event.key.code == sf::Keyboard::Escape)
			{
				m_window.close();
				exit(EXIT_SUCCESS);
			}
			switch (event.type)
			{
			case sf::Event::Closed:
				m_window.close();
				exit(EXIT_SUCCESS);

			case sf::Event::MouseButtonReleased:
				sf::Vector2f  mouseCoords = m_window.mapPixelToCoords
					({ event.mouseButton.x, event.mouseButton.y });
				//help button
				if (m_menu.at(1).getGlobalBounds().contains(mouseCoords))
				{
					m_menu.setDisplayHelp(true);
					m_menu.setDisplayMenu(false);
				}
				//back button
				if (m_menu.at(3).getGlobalBounds().contains(mouseCoords))
				{
					m_menu.setDisplayHelp(false);
					m_menu.setDisplayMenu(true);
				}
				//exit button
				if (m_menu.at(2).getGlobalBounds().contains(mouseCoords))
				{
					exit(EXIT_SUCCESS);
				}
				//play button
				if (m_menu.at(0).getGlobalBounds().contains(mouseCoords))
				{
					m_menu.setDisplayHelp(false);
					m_menu.setDisplayMenu(false);
					m_isPlay = true;
				}

				//index of presed charecter
				size_t index = findContain(mouseCoords);
				//change selection
				if (index < m_dynamic.size())
				{
					//change to new selection and remove the old one
					m_lastSelection = m_currentSelection;
					m_currentSelection = index;
					m_dynamic[m_currentSelection]->setSelect();
					//reset old selection
					if (m_lastSelection != -1 && m_lastSelection != m_currentSelection) {
						m_dynamic[m_lastSelection]->resetSelect();
					}
				}
				break;
			}
		}
		//display help
		if (m_menu.getDisplayHelp()) {
			m_window.clear();
			m_window.draw(m_background);
			m_menu.drawHelp(m_window);
		}
		//display manu
		if (m_menu.getDisplayMenue()) {
			m_window.clear();
			m_window.draw(m_background);
			m_menu.drawMenu(m_window);
		}

		if (m_isPlay) {
			moveAll();
			//end a level
			if(m_mainend.endLevel(m_dynamic, m_currentSelection, m_mainCounter))
			{
				m_window.close();
				restartLevel();
			}
			m_mainCounter.countTimeAndMoves();
				drwaAll();
		}
		m_window.display();
	}
	//end the game
	setBackground();
	m_mainend.endGame(m_window);
}

void Controller::moveAll()
{
	//move dwarfs
	for (size_t i = 0; i < m_dwarfs.size(); ++i)
	{
		m_dwarfs[i]->move(sf::Vector2f{ 0,-movmentSpeed },m_dynamic, m_static,m_dwarfs);
	}
	//----------arrow key selection
	//move up
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && m_currentSelection != -1)
	{

		m_dynamic[m_currentSelection]->move(sf::Vector2f{ 0,-movmentSpeed },
			m_dynamic, m_static, m_dwarfs);
		m_cycle++;
		//limit movment to 10 per cycle
		if (m_cycle == 10) {
			m_mainCounter.countMove();
			m_cycle = 0;
		}

	}
	//move down
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && m_currentSelection != -1)
	{
		m_dynamic[m_currentSelection]->move(sf::Vector2f{ 0,movmentSpeed },
			m_dynamic, m_static, m_dwarfs);
		m_cycle++;
		//limit movment to 10 per cycle
		if (m_cycle == 10) {
			m_mainCounter.countMove();
			m_cycle = 0;
		}
	}
	//move left
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && m_currentSelection != -1)
	{
		m_dynamic[m_currentSelection]->move(sf::Vector2f{ -movmentSpeed,0 },
			m_dynamic, m_static, m_dwarfs);
		m_cycle++;
		//limit movment to 10 per cycle
		if (m_cycle == 10) {
			m_mainCounter.countMove();
			m_cycle = 0;
		}
	}
	//move right
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && m_currentSelection != -1)
	{
		m_dynamic[m_currentSelection]->move(sf::Vector2f{ movmentSpeed, 0 },
			m_dynamic, m_static, m_dwarfs);
		m_cycle++;
		//limit movment to 10 per cycle
		if (m_cycle == 10) {
			m_mainCounter.countMove();
			m_cycle = 0;
		}
	}
}
//draw all the charecters
void Controller::drwaAll()
{
	m_window.clear();
	m_window.draw(m_background);
	m_mainCounter.draw(m_window);

	for (int i = 0; i<m_static.size(); i++)
	{
		m_static[i]->draw(m_window);
	}
	for (int i = 0; i<m_dynamic.size(); i++)
	{
		m_dynamic[i]->draw(m_window);
	}
	for (int i = 0; i < m_dwarfs.size(); i++)
	{
		m_dwarfs[i]->draw(m_window);
	}

}
//defualt constructor
Controller::Controller()
{
}
//load data from file
void Controller::loadFromFile()
{
	std::string line;
	//----------read to board------
	std::vector<std::string> map;
	while (getline(m_stage, line)) {
		if (line == "$")
			break;
		if (line == "$$") {
			m_mainend.setWin(true);
			return;
		}
		map.push_back(line);
	}
	//the size of the largest row
	for (int i = 0; i < map.size(); i++)
	{
		if (map[i].size() > m_numOfCols)
			m_numOfCols = map[i].size();
	}
	//set the rows and calles of the board
	m_numOfRows = map.size()*41;
	m_numOfCols *= 40;
	//create the objects
	for (size_t j = 0; j < map.size(); j++) {
		for (size_t i = 0; i < map[j].size(); i++) {
			int random = rand() % 3;
			switch (map[j][i])
			{
			case 'k':
				m_dynamic.push_back(std::make_unique<King>());
				m_dynamic.back()->setLocation(i,j);
				m_dynamic.back()->setImage(&m_pictures.at(0));
				
				break;
			case 'm':
				m_dynamic.push_back(std::make_unique<Mage>());
				m_dynamic.back()->setLocation(i, j);
				m_dynamic.back()->setImage(&m_pictures.at(1));
				break;
			case 't':
				m_dynamic.push_back(std::make_unique<Theif>());
				m_dynamic.back()->setLocation(i, j);
				m_dynamic.back()->setImage(&m_pictures.at(3));
				break;
			case 'g':
				m_dynamic.push_back(std::make_unique<Giant>());
				m_dynamic.back()->setLocation(i, j);
				m_dynamic.back()->setImage(&m_pictures.at(2));
				break;
			case '^':
				m_dwarfs.push_back(std::make_unique<Dwarf>( i,j ));
				m_dwarfs.back()->setLocation(i, j);
				m_dwarfs.back()->setImage(&m_pictures.at(4));
				break;
			case '@':
				m_static.push_back(std::make_unique<Throne>());
				m_static.back()->setLocation(i, j);
				m_static.back()->setImage(&m_pictures.at(11));
				break;
			case 'F':
				m_static.push_back(std::make_unique<Keys>());
				m_static.back()->setLocation(i, j);
				m_static.back()->setImage(&m_pictures.at(6));
				break;
			case '=':
				m_static.push_back(std::make_unique<Wall>());
				m_static.back()->setLocation(i, j);
				m_static.back()->setImage(&m_pictures.at(10));
				//random wall color
				switch (random) {
				case 0:
					m_static.back()->setImage(&m_pictures.at(8));
					break;
				case 1:
					m_static.back()->setImage(&m_pictures.at(9));
					break;
				case 2:
					m_static.back()->setImage(&m_pictures.at(10));
					break;
				}
				break;
			case '#':
				m_static.push_back(std::make_unique<Gate>());
				m_static.back()->setLocation(i, j);
				m_static.back()->setImage(&m_pictures.at(7));
				break;
			case '*':
				m_static.push_back(std::make_unique<Fire>());
				m_static.back()->setLocation(i, j);
				m_static.back()->setImage(&m_pictures.at(5));
				break;

			}
		}
	}
	//---------------------------
}
/*
find a charecter was pressed ,if so return its index
mouseCoords: the coardinets of the mouse press
i: index of the pressed charecter in vector
*/
size_t Controller::findContain(sf::Vector2f mouseCoords){
	size_t i;
	for (i = 0; i<m_dynamic.size(); ++i)
	{
		if (m_dynamic[i]->globalBounds().contains(mouseCoords))
		{
			break;
		}
	}
	return i;
}
//set the beckround photo
void Controller::setBackground()
{
	m_background.setPosition(0, 0);
	m_background.setSize(sf::Vector2f{ float(m_numOfCols),float(m_numOfRows + 50) });
	m_background.setTexture(&m_pictures.at(12));
}

