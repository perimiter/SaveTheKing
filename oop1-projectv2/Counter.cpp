#include "Counter.h"


Counter::Counter()
{
}

Counter::~Counter()
{
}
//get elpased time
int Counter::getTime()
{
	return int(m_clock.getElapsedTime().asSeconds());
}
//get current amount of moves
int Counter::getMoves()
{
	return m_movesCounter;
}
//set the massage of counters
void Counter::countTimeAndMoves()
{
	//convert the moves counter to string and display it
	std::string s = std::to_string(m_movesCounter);
	m_counter.setString("moves counter:" + s);
	//convert the timer to string and display it
	std::string k = std::to_string(int(m_clock.getElapsedTime().asSeconds()));
	m_time.setString("time:" + k);
}
//draw all
void Counter::draw(sf::RenderWindow &window)
{
	window.draw(m_counter);
	window.draw(m_time);
}
//reset the moves counter
void Counter::resetMoveCounter()
{
	m_movesCounter = 0;
}
//restart the clock
void Counter::restartClock()
{
	m_clock.restart();
}
//set the fonts to be displayed
void Counter::setFont(size_t numOfRows, size_t numOfCols)
{
	m_font.loadFromFile("sansation.ttf");
	m_counter.setFont(m_font);
	m_counter.setCharacterSize(40);
	m_counter.setPosition(0, numOfRows);
	m_counter.setFillColor(sf::Color::White);
	m_counter.setString("moves counter: 0");
	//--------------------------------------
	m_time.setFont(m_font);
	m_time.setCharacterSize(40);
	m_time.setPosition(numOfCols - 200, numOfRows);
	m_time.setFillColor(sf::Color::White);
}
//increase the moves counter
void Counter::countMove()
{
	m_movesCounter++;
}
