#include "Dwarf.h"
#include "Keys.h"


Dwarf::Dwarf(int i, int j)
	:m_startLocation(i*40, j*41)
{
}


Dwarf::~Dwarf()
{
}



//dwarfs movment chosen random
void Dwarf::move(const sf::Vector2f &directon , 
	std::vector<std::unique_ptr<DynamicCharacter>>&dynamic,
	std::vector<std::unique_ptr<StaticCharcter>>&statics, 
	std::vector< std::unique_ptr<DynamicCharacter >> &dwarfs)
{
	const float speed = 3.f; //movement speed
	m_cycles++;				//cycle counter to make signification movement
	int random = rand() % 4;	//add random factor to the direction
	if (m_cycles == 40) {
		switch (random)
		{
		case 0:
			direction = { 0, -speed };
			break;
		case 1:
			direction = { 0,speed };
			break;
		case 2:
			direction = { -speed ,0 };
			break;
		case 3:
			direction = { speed , 0 };
			break;
		}
		m_cycles = 0;
	}

	m_pic.move(direction);

	//check colision with all other character, go back if found
	for (size_t i = 0; i < dynamic.size(); ++i)
	{
		if (m_pic.getGlobalBounds().intersects(dynamic[i]->globalBounds()))
		{
			m_pic.move(-direction);		
			return;
		}
	}

	for (size_t i = 0; i < statics.size(); ++i)
	{
		if (m_pic.getGlobalBounds().intersects(statics[i]->globalBounds())) {
			if (dynamic_cast<Keys*>(statics[i].get()) != nullptr) {
				break;
			}
			m_pic.move(-direction);
			return;
		}
	}

	for (size_t i = 0; i < dwarfs.size(); ++i) {
		if (m_pic.getGlobalBounds().intersects(dwarfs[i]->globalBounds()) &&
			 m_pic.getGlobalBounds() != dwarfs[i]->globalBounds())
		{
			m_pic.move(-direction);
			return;
		}
	}
}

//reset location of dwarf if the giant touch him 
void Dwarf::resetLocation(std::vector<std::unique_ptr<DynamicCharacter>>&dynamic,
	std::vector<std::unique_ptr<DynamicCharacter>>&dwarfs, size_t me)
{
	
	float x = m_startLocation.x;
	float y = m_startLocation.y;
	m_pic.setPosition(x, y);

	for (size_t i = 0; i < dynamic.size(); ++i)
	{
		//check if any other character standing on the start point, erase yourself if found
		//to prevent const colision
		if (m_pic.getGlobalBounds().intersects(dynamic[i]->globalBounds()))
		{
			dwarfs.erase(dwarfs.begin() + me);
			return;
		}
	}
	for (size_t i = 0; i < dwarfs.size(); ++i)
	{
		if (m_pic.getGlobalBounds().intersects(dwarfs[i]->globalBounds()) &&
			m_pic.getGlobalBounds() != dwarfs[i]->globalBounds())
		{
			dwarfs.erase(dwarfs.begin() + me);
			return;
		}
	}
}




