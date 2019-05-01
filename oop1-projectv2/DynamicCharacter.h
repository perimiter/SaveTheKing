#pragma once
#include<SFML\Graphics.hpp>
#include "BaseCharacter.h"
#include <memory>

class StaticCharcter;

class DynamicCharacter :
	public BaseCharacter
{
public:
	DynamicCharacter();
	virtual~DynamicCharacter();
	//virtual func of movement of the character, over ride in each character
	virtual void move(const sf::Vector2f&,
		std::vector<std::unique_ptr<DynamicCharacter>>&,
		std::vector<std::unique_ptr<StaticCharcter>>&, 
		std::vector< std::unique_ptr<DynamicCharacter >> &)=0;
	//set current selected character
	void setSelect();
	//relese last selected character
	void resetSelect();
protected:
	bool m_selected=false;
};

