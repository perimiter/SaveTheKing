#pragma once
#include "DynamicCharacter.h"
class Giant :
	public DynamicCharacter
{
public:
	Giant();
	~Giant();
	//movement of the character
	 void move(const sf::Vector2f&,
		std::vector<std::unique_ptr<DynamicCharacter>>&,
		 std::vector<std::unique_ptr<StaticCharcter>>&, 
		 std::vector< std::unique_ptr<DynamicCharacter >> &);
};

