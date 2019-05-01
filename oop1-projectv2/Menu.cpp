#include "Menu.h"
#include <fstream>
#include <sstream>


Menu::Menu()
{
	m_menu.resize(5);
	std::string s;
	
	m_font.loadFromFile("sansation.ttf");
	
	//set the massage font
	for (int i = 0; i < m_menu.size() - 2; ++i) {
		m_menu[i].setFont(m_font);
		m_menu[i].setCharacterSize(100);
		m_menu[i].setFillColor(sf::Color::Yellow);
	}
	//set win massage
	m_menu[3].setFont(m_font);
	m_menu[3].setCharacterSize(50);
	m_menu[3].setFillColor(sf::Color::Yellow);
	//set lose massage
	m_menu[4].setFont(m_font);
	m_menu[4].setCharacterSize(40);
	m_menu[4].setFillColor(sf::Color::Yellow);
	//set massage title
	s = "START";
	m_menu[0].setString(s);
	s = "HELP";
	m_menu[1].setString(s);
	s = "EXIT";
	m_menu[2].setString(s);
	s = "BACK";
	m_menu[3].setString(s);
	//load instructions
	std::ifstream stream{ R"(instructions.txt)" } ;
	std::string temp;
	s="";
	while (getline(stream, temp)) {
		s += temp;
		s += "\n";
	}
	m_menu[4].setString(s);

}
Menu::~Menu()
{
}
//draw the manu
void Menu::drawMenu(sf::RenderWindow &window)
{
	for (int i = 0; i < m_menu.size() - 2; ++i) {
		window.draw(m_menu[i]);
	}

}
//draw the help section
void Menu::drawHelp(sf::RenderWindow &window)
{
	window.draw(m_menu[3]);
	window.draw(m_menu[4]);
}
//set the postion of the text
void Menu::setPositions(int rows, int cols)
{
	int s = rows / 2,
		t = cols / 2;

	for (int i = 0; i < m_menu.size() - 2; i++) {

		m_menu[i].setPosition(s - 150 , t - 200);
		t += 150;
	}

	m_menu[3].setPosition(rows - 150, cols - 60);
	m_menu[4].setPosition(50, 50);
	
}
//return the text at index i
sf::Text& Menu::at(int i) {
	return m_menu[i];
}
//return true if its time to display the menu
const bool Menu::getDisplayMenue()
{
	return m_displayMenu;
}
//return true if its time to display the help section
const bool Menu::getDisplayHelp()
{
	return m_displayHelp;
}
//set the display menu
void Menu::setDisplayMenu(bool val)
{
	m_displayMenu = val;
}
//set the display help section
void Menu::setDisplayHelp(bool val)
{
	m_displayHelp = val;
}
