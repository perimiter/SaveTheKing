#pragma once
#include "DynamicCharacter.h"
#include "StaticCharcter.h"

class King :
	public DynamicCharacter
{
public:
	King();
	~King();
	//movement of the character
	 void move(const sf::Vector2f &,
		std::vector<std::unique_ptr<DynamicCharacter>>&, 
		 std::vector<std::unique_ptr<StaticCharcter>>&, 
		 std::vector< std::unique_ptr<DynamicCharacter >> &) ;
	 const bool getOnThrone();
protected:
	//if king on throne
	bool m_onThrone = false;

};

