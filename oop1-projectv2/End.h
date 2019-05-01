#pragma once
#include <SFML\Graphics.hpp>
#include <memory>
#include "DynamicCharacter.h"
#include "Counter.h"

enum  endconditions { times, moves };


class End
{
public:
	//check if king on thrown/ time end/ movement end
	bool endLevel(std::vector < std::unique_ptr<DynamicCharacter>> &dynamic, 
		size_t currentSelection,
		Counter &);
	//set end level under time or movement
	void endConditions();
	const bool getLose();
	const bool getWin();
	void setLose(bool);
	void setWin(bool);
	//drwa end messege
	void draw(sf::RenderWindow &);
	//end the game, show match end messege
	void endGame(sf::RenderWindow &);
	End();
	~End();

private:
	//set end level under time or movement
	enum  endconditions m_endconditions;
	bool m_winGame = false;
	bool m_loseGame = false;
	sf::Text m_winFont;
	sf::Text m_loseFont;
	sf::Font m_font;
};

