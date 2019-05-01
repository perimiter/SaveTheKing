#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
class Pictures
{
public:
	Pictures();
	~Pictures();
	//for match texture to character
	sf::Texture &at(int) ;
private:
	//vector of all images
	std::vector<sf::Texture> m_images;
};

