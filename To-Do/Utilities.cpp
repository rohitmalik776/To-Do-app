#include <iostream>
#include <SFML/Graphics.hpp>


class partitionMaker {

public:

	sf::RectangleShape space;

	int posX = 0, posY = 0;
	float height = 0, width = 0;


	partitionMaker(int positionX, int positionY, float sizeX, float sizeY) {

		posX = positionX;
		posY = positionY;
		height = sizeY;
		width = sizeX;
		space.setPosition(positionX, positionY);
		space.setSize(sf::Vector2f(sizeX, sizeY));

		space.setFillColor(sf::Color(173, 239, 209));

	}


	bool inRange(int mouseX, int mouseY) {

		if (mouseX <= posX + width && mouseX >= posX && mouseY <= posY + height && mouseY >= posY) {

			return true;

		}

		return false;

	}

	void unHovered() {
		
		space.setFillColor(sf::Color(173, 239, 209));

		return;
	
	}

	void hovered() {
	
		space.setFillColor(sf::Color(255, 255, 255));
		
		
		return;

	}



};




class textMaker {

public:

	int textSize = 24;
	sf::Text text;

	textMaker(int posX, int posY) {
	
		//text.setString("Trial");
		text.setCharacterSize(textSize);
		text.setFillColor(sf::Color(256,256,256));
		text.setPosition(posX, posY);
	
	}


};