#pragma once
#include <SFML\Graphics.hpp>
#include "DynamicCharacter.h"


class Dwarf :
	public DynamicCharacter
{
public:
	Dwarf(int, int);
	~Dwarf();
	//movement of the character
	void move(const sf::Vector2f & Direction,
		std::vector<std::unique_ptr<DynamicCharacter>>&,
		std::vector<std::unique_ptr<StaticCharcter>>&,
		std::vector< std::unique_ptr<DynamicCharacter >> &) ;
	//get back the dwarf to start point
	void resetLocation(std::vector<std::unique_ptr<DynamicCharacter>>&dynamic,
		 std::vector<std::unique_ptr<DynamicCharacter>>&dwarfs, size_t);
private:
	sf::Vector2i m_startLocation;
	//movement direction 
	sf::Vector2f direction;
	//movement cycle
	int m_cycles = 0;
};

