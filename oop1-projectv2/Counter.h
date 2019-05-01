#pragma once
#include <SFML\Graphics.hpp>

class Counter
{
public:
	Counter();
	~Counter();
	int getTime();
	int getMoves();
	void countMove();
	//for show movment and time
	void countTimeAndMoves();
	//draw counters on window
	void draw(sf::RenderWindow &);
	//for initializing level
	void resetMoveCounter();
	void restartClock();
	//locate counters position on window
	void setFont(size_t, size_t);
	
	
private:
	sf::Clock m_clock;
	int m_movesCounter = 0;
	sf::Text m_counter;
	sf::Text m_time;
	sf::Font m_font;
};

