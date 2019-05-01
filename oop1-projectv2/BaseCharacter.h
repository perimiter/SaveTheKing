#pragma once
#include <SFML/Graphics.hpp>
class BaseCharacter
{
public:
	BaseCharacter();
	virtual ~BaseCharacter();
	//set location of pic on window
	void setLocation(int,int);
	//match pic to character
	void setImage(sf::Texture*);
	//draw character on window
	void draw(sf::RenderWindow &);
	//get bounds for prevent colision
	sf::FloatRect globalBounds();
	//for flag of selected character
	void setSpriteColor(sf::Color color);
	
protected:
	sf::Sprite m_pic;
};

