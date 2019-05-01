#include "Mage.h"
#include "Keys.h"
#include "Fire.h"
#include "Dwarf.h"

Mage::Mage()
{
}


Mage::~Mage()
{
}

//movement of the character
void Mage::move(const sf::Vector2f &Direction, 
	std::vector<std::unique_ptr<DynamicCharacter>>&dynamic
	, std::vector<std::unique_ptr<StaticCharcter>>&statics, 
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
			if (m_pic.getGlobalBounds().intersects(dwarfs[i]->globalBounds()))
			{
				m_pic.move(-Direction);
			}
		}
		for (size_t i = 0; i < statics.size(); ++i)
		{
			if (m_pic.getGlobalBounds().intersects(statics[i]->globalBounds())) {
				if (dynamic_cast<Fire*>(statics[i].get()) != nullptr) {
					statics.erase(statics.begin()+i);
					break;
				}
				if (dynamic_cast<Keys*>(statics[i].get()) != nullptr)
					break;
				m_pic.move(-Direction);
			}
		}
	}
}


