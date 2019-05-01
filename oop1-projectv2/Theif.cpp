#include "Theif.h"
#include "Keys.h"
#include "Gate.h"
#include "Dwarf.h"


Theif::Theif()
{
}


Theif::~Theif()
{
}

//movement of the character
void Theif::move(const sf::Vector2f &Direction,
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
			if (m_pic.getGlobalBounds().intersects(dwarfs[i]->globalBounds()))
			{
				m_pic.move(-Direction);
			}
		}
		for (size_t i = 0; i < statics.size(); ++i)
		{
			//if the thief reach key, take it, erase the key from the vector, mark it for next use
			if (m_pic.getGlobalBounds().intersects(statics[i]->globalBounds())) {
				if (dynamic_cast<Keys*>(statics[i].get()) != nullptr) {
					if (m_hasKey)
						break;
					else
					{
						statics.erase(statics.begin() + i);
						m_hasKey = true;
						break;
					}
				}
				if (dynamic_cast<Gate*>(statics[i].get()) != nullptr) {
					if (m_hasKey) {
						statics.erase(statics.begin() + i);
						m_hasKey = false;
						break;
					}
				}
				m_pic.move(-Direction);
			}
		}
	}
}

