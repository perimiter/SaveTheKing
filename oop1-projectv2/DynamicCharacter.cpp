#include "DynamicCharacter.h"



DynamicCharacter::DynamicCharacter()
{
}


DynamicCharacter::~DynamicCharacter()
{
}

//set current selected character
void DynamicCharacter::setSelect()
{
	m_selected = true;
	m_pic.setColor(sf::Color::Red);
}

//relese last selected character
void DynamicCharacter::resetSelect()
{
	m_selected = false;
	m_pic.setColor(sf::Color::White);
}
