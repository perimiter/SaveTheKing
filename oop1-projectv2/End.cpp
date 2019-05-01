#include "End.h"
#include "King.h"


End::End()
{
	m_font.loadFromFile("sansation.ttf");
	m_winFont.setFont(m_font);
	m_winFont.setCharacterSize(120);
	m_winFont.setString("Congratulations!\n you Win!\n Press esc to exit");
	m_winFont.setPosition(0, 0);
	m_winFont.setFillColor(sf::Color::Yellow);
	//----------------------------------
	m_loseFont.setFont(m_font);
	m_loseFont.setCharacterSize(120);
	m_loseFont.setString("looser! you lose\nPress esc to exit");
	m_loseFont.setPosition(0, 0);
	m_loseFont.setFillColor(sf::Color::Yellow);
}


End::~End()
{
}
/*
in case we are on the throne we end the level or if the time run out
or in case the moves limit run out
currentselection: current selected charecter index in vector
*/
bool End::endLevel(std::vector < std::unique_ptr<DynamicCharacter>> &dynamic,
	size_t currentSelection,
	Counter &counter)
{
	//if the king has stepped on the throne
	if (currentSelection >= 0 && currentSelection < dynamic.size()) {
		King *kptr = dynamic_cast<King*>(dynamic[currentSelection].get());
		if (kptr)
		{
			return kptr->getOnThrone();
		}
	}
	//if the time run out
	if (m_endconditions == times && counter.getTime() >= 500) {
		m_loseGame = true;
		return true;
	}
	//if the moves limit run out
	if (m_endconditions == moves && counter.getMoves() >= 500) {
		m_loseGame = true;
		return true;
	}

	return false;
}
//select the condition should the player lose at
void End::endConditions()
{
	int random = rand() % 2;
	switch (random) {
	case 0:
		m_endconditions = times;
		break;
	case 1:
		m_endconditions = moves;
		break;
	}
}
//get the status of the game
const bool End::getLose()
{
	return m_loseGame;
}
//get the status of the game
const bool End::getWin()
{
	return m_winGame;
}
//set the status if the player lost or not
void End::setLose(bool val)
{
	m_loseGame = val;
}
//set the status if the player win or not
void End::setWin(bool val)
{
	m_winGame = val;
}
//draw all
void End::draw(sf::RenderWindow &window)
{
	if (m_winGame) {
		window.draw(m_winFont);
	}
	if(m_loseGame) {
		window.draw(m_loseFont);
	}
}
//end game massage 
void End::endGame(sf::RenderWindow &window)
{
	window.create(sf::VideoMode(1000, 400), "save the king");
	window.setVerticalSyncEnabled(true);
	draw(window);	
	window.display();

	while (window.isOpen())
	{
		for (sf::Event event; window.waitEvent(event);)
		{
			if (event.type == sf::Event::TextEntered)
			{
				window.close();
			}
			switch (event.type)
			{
			case sf::Event::Closed:
				window.close();
				break;
			}
		}
	}
}

