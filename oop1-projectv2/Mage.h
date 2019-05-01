#pragma once
#include "DynamicCharacter.h"
class Mage :
	public DynamicCharacter
{
public:
	Mage();
	~Mage();
	//movement of the character
	virtual void move(const sf::Vector2f&,
		std::vector<std::unique_ptr<DynamicCharacter>>&,  
		std::vector<std::unique_ptr<StaticCharcter>>&, 
		std::vector< std::unique_ptr<DynamicCharacter >> &) ;
};

