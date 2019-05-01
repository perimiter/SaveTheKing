#pragma once
#include "DynamicCharacter.h"
class Theif :
	public DynamicCharacter
{
public:
	Theif();
	~Theif();
	//movement of the character
	 void move(const sf::Vector2f&,
		std::vector<std::unique_ptr<DynamicCharacter>>&,
		 std::vector<std::unique_ptr<StaticCharcter>>&,
		 std::vector< std::unique_ptr<DynamicCharacter >> &);
protected:
	//if thief has key
	bool m_hasKey = false;
};

