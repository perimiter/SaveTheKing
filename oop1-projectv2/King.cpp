#include "King.h"
#include "Keys.h"
#include "Throne.h"
#include "Dwarf.h"

King::King()
{
}


King::~King()
{
}

//movement of the character
void King::move (const sf::Vector2f & Direction,
	std::vector<std::unique_ptr<DynamicCharacter>>&dynamic,
	std::vector<std::unique_ptr<StaticCharcter>>&statics, std::vector< std::unique_ptr<DynamicCharacter >> &dwarfs)
{
	//move and then check colision with other character, go back if found
	if (m_selected) 
	{
		m_pic.move(Direction);

		for (size_t i = 0; i <dynamic.size(); ++i)
		{
			if (m_pic.getGlobalBounds().intersects(dynamic[i]->globalBounds()) &&
				m_pic.getGlobalBounds()!= dynamic[i]->globalBounds())
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
				if (dynamic_cast<Keys*>(statics[i].get()) != nullptr ) {
					break;
				}
				//if the king reach the throne, flag it, for the next end checking
				if (dynamic_cast<Throne*>(statics[i].get()) != nullptr) {
					m_onThrone = true;
					break;
				}
			m_pic.move(-Direction);
			}
		}
	}
}

const bool King::getOnThrone()
{
	return m_onThrone;
}





