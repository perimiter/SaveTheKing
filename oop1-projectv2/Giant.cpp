#include "Giant.h"
#include "Keys.h"
#include "Dwarf.h"

Giant::Giant()
{
}


Giant::~Giant()
{
}

//movement of the character
void Giant::move(const sf::Vector2f &Direction, 
	std::vector<std::unique_ptr<DynamicCharacter>>&dynamic,
	std::vector<std::unique_ptr<StaticCharcter>>&statics, 
	std::vector< std::unique_ptr<DynamicCharacter >> &dwarfs)
{
	if (m_selected)
	{
		m_pic.move(Direction);
		//move and then check colision with other character, go back if found
		for (size_t i = 0; i < dynamic.size(); ++i)
		{
			if (m_pic.getGlobalBounds().intersects(dynamic[i]->globalBounds()) &&
				m_pic.getGlobalBounds() != dynamic[i]->globalBounds())
			{
				m_pic.move(-Direction);
			}
		}
		for (size_t i = 0; i < dwarfs.size(); ++i)
		{
			//if the giant reach dwarf, he is force him to go back to the start point
			if (m_pic.getGlobalBounds().intersects(dwarfs[i]->globalBounds()))
			{
				Dwarf *p = static_cast<Dwarf*>(dwarfs[i].get()); 
				p->resetLocation(dynamic, dwarfs, i);
				break;
			}
		}
		for (size_t i = 0; i < statics.size(); ++i)
		{
			if (m_pic.getGlobalBounds().intersects(statics[i]->globalBounds())) {
				if (dynamic_cast<Keys*>(statics[i].get()) != nullptr) {
					break;
				}
				m_pic.move(-Direction);
			}
		}
	}
}


