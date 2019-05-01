#include "BaseCharacter.h"



BaseCharacter::BaseCharacter()
{
}


BaseCharacter::~BaseCharacter()
{
}

void BaseCharacter::setLocation(int x,int y)
{
	m_pic.setPosition(x*40,y*41);
}

void BaseCharacter::setImage(sf::Texture* img)
{
	m_pic.setTexture(*img);
}

void BaseCharacter::draw(sf::RenderWindow &window)
{
	window.draw(m_pic);
}

sf::FloatRect BaseCharacter::globalBounds()
{
	return m_pic.getGlobalBounds();
}
void BaseCharacter::setSpriteColor(sf::Color color)
{
	m_pic.setColor(color);
}
