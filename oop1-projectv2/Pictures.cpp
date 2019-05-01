#include "Pictures.h"



Pictures::Pictures()
{
	//--------------load imeges
	m_images.resize(20);

	m_images[0].loadFromFile("king.png");
	m_images[1].loadFromFile("mage.png");
	m_images[2].loadFromFile("giant.png");
	m_images[3].loadFromFile("theif.png");
	m_images[4].loadFromFile("dwarf.png");
	m_images[5].loadFromFile("fire.png", sf::IntRect(0, 0, 20, 40));
	m_images[6].loadFromFile("keytemp.png", sf::IntRect(0, 0, 20, 45));
	m_images[7].loadFromFile("gate.png");
	m_images[8].loadFromFile("wallbrown.png");
	m_images[9].loadFromFile("wall1.png");
	m_images[10].loadFromFile("wall2.png");
	m_images[11].loadFromFile("throne.png");
	m_images[12].loadFromFile("savetheking.jpg" );
}


Pictures::~Pictures()
{
}

sf::Texture & Pictures::at(int i) 
{
	return m_images[i];
}
