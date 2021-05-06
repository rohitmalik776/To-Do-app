#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>
#include "Utilities.cpp"



int main() {

	int taskIterator = 0;


	//Adding the tasks

	//The tasks array
	std::vector <std::string> tasks;

//	tasks.push_back("This is the Task 1");
//	tasks.push_back("This is the Task 2");
//	tasks.push_back("This is the Task 3");

	//Creating the main Window
	int width = 450, height = 600;
	sf::RenderWindow mainWin(sf::VideoMode(width, height), "Basic To-Do app");
	mainWin.setFramerateLimit(20);

	//Adding the top rectangular bar using a rectangle
	sf::RectangleShape topBar;
	topBar.setPosition(0,0);
	topBar.setSize(sf::Vector2f(width, height/4));
	topBar.setFillColor(sf::Color(0, 32, 63));

	//Adding "To-Do" text
	
	//Importing font files
	sf::Font openSansBold;
	if (!openSansBold.loadFromFile("Resources/OpenSans-Bold.ttf")) {
		std::cout << "Error Reading Bold Fonts file\n";
	}

	sf::Font openSansRegular;
	if (!openSansRegular.loadFromFile("Resources/OpenSans-Regular.ttf")) {
		std::cout << "Error Reading Regular Fonts file\n";
	}
	
	//Making sf::Text
	int textSize = 100;
	sf::Text heading("To-Do", openSansBold, textSize);
	heading.setFillColor(sf::Color(255,255,255));
	heading.setPosition((width+100)/6, 0);



	// Adding spaces for the tasks

	partitionMaker first(0, height/4 + 1, width, height / 5 - 1);

	partitionMaker second(0, height / 4 + height/5 + 1, width, height / 5 - 1);

	partitionMaker third(0, height / 4 + 2 * (height / 5) + 1, width, height / 5 - 1);
	

	//Making space for "Add Task"

	partitionMaker newTask(0, height / 4 + 3 * (height / 5) + 1, width, 90);


	//Making text for partitions

	int subTextSize = 50;

	textMaker firstText(6, first.posY + (first.height - 24)/2);
	firstText.text.setFont(openSansRegular);
	//firstText.text.setString("First Task");

	textMaker secText(6, second.posY + (second.height - 24) / 2);
	secText.text.setFont(openSansRegular);
	//secText.text.setString("Second Task");

	textMaker terText(6, third.posY + (third.height - 24)/2);
	terText.text.setFont(openSansRegular);
	//terText.text.setString("Third Task");

	textMaker newText(6, newTask.posY + (newTask.height - 24)/2);
	newText.text.setFont(openSansRegular);
	newText.text.setString("Add a new task");

	//Declaring text variable to add a new task
	textMaker addText(0, 0);
	addText.text.setFillColor(sf::Color(0, 0, 0));

	//Taking the "New Task" as input
	sf::String newString;
	sf::Event textEvent;

	//Tracking mouse pos
	sf::Vector2i mousePos = sf::Mouse::getPosition();


	//The main event loop
	sf::Event mainEvent;
	
	while (mainWin.isOpen()) {


		if (tasks.size() >= 3 + taskIterator) {
		
			firstText.text.setString(tasks[taskIterator]);
			secText.text.setString(tasks[taskIterator + 1]);
			terText.text.setString(tasks[taskIterator + 2]);

		}
		else if (tasks.size() == 1 + taskIterator) {
		
			firstText.text.setString(tasks[taskIterator]);
		
		}
		else if (tasks.size() == 2 + taskIterator) {
		
			firstText.text.setString(tasks[taskIterator]);
			secText.text.setString(tasks[taskIterator + 1]);

		}


		//Resetting newTask text
		newText.text.setFillColor(sf::Color(256, 256, 256));
		newText.text.setPosition(6, newTask.posY + (newTask.height - 24) / 2);


		mainWin.clear(sf::Color(255,255,255));


		//Drawing things to the main window
		mainWin.draw(topBar);
		mainWin.draw(heading);
		mainWin.draw(first.space);
		//mainWin.draw(sepLine);
		mainWin.draw(second.space);
		mainWin.draw(third.space);
		mainWin.draw(newTask.space);
		mainWin.draw(firstText.text);
		mainWin.draw(secText.text);
		mainWin.draw(terText.text);
		mainWin.draw(newText.text);




		mainWin.display();

	
		while (mainWin.pollEvent(mainEvent))
		{


			switch (mainEvent.type) {

				case (sf::Event::Closed):
					mainWin.close();
					break;

				//Tracking the click position

				case (sf::Event::MouseButtonPressed):
					if (mainEvent.mouseButton.button == sf::Mouse::Left) {
					
						if (first.inRange(mousePos.x, mousePos.y)) {

						
							

						}

					}
					if (mainEvent.mouseButton.button == sf::Mouse::Left) {

						if (second.inRange(mousePos.x, mousePos.y)) {

						


						}

					}
					if (mainEvent.mouseButton.button == sf::Mouse::Left) {
					
						if (third.inRange(mousePos.x, mousePos.y)) {
						
						
						
						}
					
					}
					if (mainEvent.mouseButton.button == sf::Mouse::Left) {
					
						if (newTask.inRange(mousePos.x, mousePos.y)) {

							
							//Declaring Text Input Window
							sf::RenderWindow newTaskWin(sf::VideoMode(400, 400), "Add New Task");
							newTaskWin.setFramerateLimit(20);

							//Display the text entered
							
							addText.text.setPosition(0, 0);
							addText.text.setFillColor(sf::Color(0, 0, 0));
							int iterator = -1;

							while(newTaskWin.isOpen()){

								newTaskWin.clear(sf::Color(255, 255, 255));
								newTaskWin.draw(addText.text);

								newTaskWin.display();

								while (newTaskWin.pollEvent(textEvent)) {

									if (textEvent.type == sf::Event::Closed) {

										newTaskWin.close();


									}

									if (textEvent.type == sf::Event::TextEntered) {

										if (textEvent.text.unicode == 27) {

											tasks.push_back(newString);

											newTaskWin.close();
										
										}

										else if (!newString.isEmpty() && textEvent.text.unicode == 8) {
										
											newString.erase(iterator,1);
											iterator--;
											addText.text.setString(newString);
											
										}

										else if (textEvent.text.unicode < 128 && textEvent.text.unicode != 8) {

											iterator++;
											newString += static_cast<char>(textEvent.text.unicode);
											addText.text.setString(newString);
											
										}


									}

								}
							}

						} 

							
						}



				//Tracking position of mouse cursor


				case (sf::Event::MouseMoved) :

					mousePos = sf::Mouse::getPosition(mainWin);
					
					if (first.inRange(mousePos.x, mousePos.y)) {

						first.hovered();

					}
					else first.unHovered();

					if (second.inRange(mousePos.x, mousePos.y)) {

						second.hovered();

					}
					else second.unHovered();

					if (third.inRange(mousePos.x, mousePos.y)) {

						third.hovered();

					}
					else third.unHovered();

					if (newTask.inRange(mousePos.x, mousePos.y)) {

						newTask.hovered();

					}
					else newTask.unHovered();

					break;


			}
		}
	
	}

	return 0;

}