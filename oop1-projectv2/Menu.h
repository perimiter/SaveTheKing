#pragma once
#include <vector>
#include <SFML\Graphics.hpp>

class Menu
{
public:
	Menu();
	~Menu();
	void drawMenu(sf::RenderWindow &);
	void drawHelp(sf::RenderWindow & window);
	void setPositions(int, int);
	sf::Text & at(int);
	const bool getDisplayMenue();
	const bool getDisplayHelp();
	void setDisplayMenu(bool);
	void setDisplayHelp(bool);

private:
	sf::Font m_font;
	std::vector<sf::Text> m_menu;
	bool m_displayMenu = true;
	bool m_displayHelp = false;
};

