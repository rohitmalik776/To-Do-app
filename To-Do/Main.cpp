#include <iostream>
#include <fstream>
#include <vector>
#include <SFML/Graphics.hpp>
#include "Utilities.cpp"



//Function to edit tasks
sf::String* taskEditor(std::string, sf::Font*);

//Funciton to import data
void import( std::vector<std::string>* );

//Function to export data
void eksport( std::vector<std::string>* );



int main() {

	int taskIterator = 0;


	//Adding the tasks

	//The tasks array
	std::vector <std::string> tasks;

	//Importing the tasks from database file
	import(&tasks);


	//Creating the main Window
	int width = 450, height = 600;
	sf::RenderWindow mainWin(sf::VideoMode(width, height), "Basic To-Do app", sf::Style::Close);
	mainWin.setFramerateLimit(20);

	//Adding the top rectangular bar using a rectangle
	sf::RectangleShape topBar;
	topBar.setPosition(0,0);
	topBar.setSize(sf::Vector2f(width, height/4));
	topBar.setFillColor(sf::Color(0, 32, 63));

	//Adding "To-Do" text

	//Importing png files

	//Importing title icon
	sf::Image titleIcon;
	if (!titleIcon.loadFromFile("Resources/title_icon.png")) {
	
		std::cout << "Error loading title_icon.png\n";
		system("pause");
		return 0;

	}


	sf::Image editIconImg;
	if (!editIconImg.loadFromFile("Resources/edit_icon.png")) {
	
		std::cout << "Failed to load Resources/edit_icon.png\n";
		system("pause");
		return 0;

	}
	sf::Texture editIcon;
	editIcon.loadFromImage(editIconImg);

	//Setting title icon
	mainWin.setIcon(titleIcon.getSize().x, titleIcon.getSize().y, titleIcon.getPixelsPtr());
	
	//First Edit Icon
	sf::Sprite firstEditIcon;
	firstEditIcon.setTexture(editIcon);
	firstEditIcon.setPosition(width - 80 + 18, height / 4 + 6);
	firstEditIcon.setScale(sf::Vector2f(0.05,0.05));

	//Second Edit Icon
	sf::Sprite secEditIcon;
	secEditIcon.setTexture(editIcon);
	secEditIcon.setPosition(width - 80 + 18, height / 4 + 6 + (height / 5 - 1));
	secEditIcon.setScale(sf::Vector2f(0.05, 0.05));

	//Thired Edit Icon
	sf::Sprite terEditIcon;
	terEditIcon.setTexture(editIcon);
	terEditIcon.setPosition(width - 80 + 18, height / 4 + 6 + 2*(height / 5 - 1));
	terEditIcon.setScale(sf::Vector2f(0.05, 0.05));

	//Importing Delete Image
	sf::Image delIconImg;
	if (!delIconImg.loadFromFile("Resources/delete_icon.png")) {
	
		std::cout << "Error loading Resources/delete_icon.png\n";
		return 0;

	}

	sf::Texture delIcon;
	delIcon.loadFromImage(delIconImg);

	//Making sprites of Delete Icons
	sf::Sprite firstDelIcon;
	firstDelIcon.setTexture(delIcon);
	firstDelIcon.setPosition(width - 80 + 18 - 8, height / 4 + 6 - 5 + (height / 5 - 1) / 2);
	firstDelIcon.setScale(0.03, 0.03);

	sf::Sprite secDelIcon;
	secDelIcon = firstDelIcon;
	secDelIcon.setPosition(width - 80 + 18 - 8, height / 4 + 6 - 5 + 3*(height / 5 - 1) / 2);

	sf::Sprite terDelIcon;
	terDelIcon = firstDelIcon;
	terDelIcon.setPosition(width - 80 + 18 - 8, height / 4 + 6 - 5 + 5 * (height / 5 - 1) / 2);


	
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

	partitionMaker first(0, height/4 + 1, width - 80, height / 5 - 1);

	partitionMaker second(0, height / 4 + height/5 + 1, width - 80, height / 5 - 1);

	partitionMaker third(0, height / 4 + 2 * (height / 5) + 1, width - 80, height / 5 - 1);
	

	//Adding Operations Space to the tasks space

	partitionMaker firstOptionEdit( width - 79, height/4 + 1, 79, (height / 5 -1)/2);
	partitionMaker firstOptionDelete(width - 79, height / 4 + 2 + (height / 5 - 1) / 2, 79, (height / 5 - 1)/2 );

	partitionMaker secOptionEdit(width - 79, height / 4 + height / 5 + 1, 79, (height / 5 - 1) / 2);
	partitionMaker secOptionDelete(width - 79, height / 4 + height / 5 + 2 + (height / 5 - 1) / 2, 79, (height / 5 - 1) / 2);

	partitionMaker terOptionEdit(width - 79, height / 4 + 2 * (height / 5) + 1, 79, (height / 5 - 1) / 2);
	partitionMaker terOptionDelete(width - 79, height / 4 + 2 * (height / 5) + 2 + (height / 5 - 1) / 2, 79, (height / 5 - 1) / 2);
	
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
	addText.text.setFont(openSansRegular);
	addText.text.setString("Enter the task here");

	//Taking the "New Task" as input
	
	sf::Event textEvent;

	//Tracking mouse pos
	sf::Vector2i mousePos = sf::Mouse::getPosition();


	//The main event loop
	sf::Event mainEvent;

	
	//Adding number of tasks and page number on top right
	sf::Text taskIndicator;
	taskIndicator.setFont(openSansBold);
	taskIndicator.setFillColor(sf::Color(255,255,255));
	taskIndicator.setCharacterSize(20);
	taskIndicator.setPosition(5, height / 4 - 25);
	sf::String taskIndicatorString;
	taskIndicator.setString(taskIndicatorString);
	taskIndicatorString += "Tasks: 0";
	unsigned int taskSize;

	//Adding page number on top right
	sf::Text pageIndicator;
	pageIndicator.setFont(openSansBold);
	pageIndicator.setFillColor(sf::Color(255, 255, 255));
	pageIndicator.setCharacterSize(20);
	pageIndicator.setPosition(width - 95, height / 4 - 25);
	sf::String pageIndicatorString;
	pageIndicator.setString(taskIndicatorString);
	pageIndicatorString += "Page: 0";
	unsigned int pageIndicatorSize, finalPageInd = 0;

	
	while (mainWin.isOpen()) {



		//Updating Task Indicator text
		taskSize = tasks.size() / 10;
		taskIndicatorString.erase(7, 2);
		taskIndicatorString += ((taskSize % 10) + '0');
		taskIndicatorString += ((tasks.size() % 10) + '0');
		taskIndicator.setString(taskIndicatorString);

		//Updating Page Indicator text
		finalPageInd = taskIterator / 3 + 1;
		pageIndicatorSize = finalPageInd / 10;
		pageIndicatorString.erase(6, 2);

		pageIndicatorString += ((pageIndicatorSize % 10) + '0');
		pageIndicatorString += ((finalPageInd % 10)+'0');
		
		pageIndicator.setString(pageIndicatorString);




		if (tasks.size() >= 3 + taskIterator) {
		
			firstText.text.setString(tasks[taskIterator]);
			secText.text.setString(tasks[taskIterator + 1]);
			terText.text.setString(tasks[taskIterator + 2]);

		}
		else if (tasks.size() == 1 + taskIterator) {
		
			firstText.text.setString(tasks[taskIterator]);
			secText.text.setString(" ");
			terText.text.setString(" ");
		
		}
		else if (tasks.size() == 2 + taskIterator) {
		
			firstText.text.setString(tasks[taskIterator]);
			secText.text.setString(tasks[taskIterator + 1]);
			terText.text.setString(" ");

		}
		else {
		
			firstText.text.setString(" ");
			secText.text.setString(" ");
			terText.text.setString(" ");
		
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

		//Drawing Options space
		mainWin.draw(firstOptionDelete.space);
		mainWin.draw(firstOptionEdit.space);

		mainWin.draw(secOptionDelete.space);
		mainWin.draw(secOptionEdit.space);

		mainWin.draw(terOptionDelete.space);
		mainWin.draw(terOptionEdit.space);


		//Drawing Sprites

		//Edit Icons
		mainWin.draw(firstEditIcon);
		mainWin.draw(secEditIcon);
		mainWin.draw(terEditIcon);

		//Delete Icons
		mainWin.draw(firstDelIcon);
		mainWin.draw(secDelIcon);
		mainWin.draw(terDelIcon);


		//Drawing task Indicator
		mainWin.draw(taskIndicator);
		mainWin.draw(pageIndicator);


		mainWin.display();

	
		while (mainWin.pollEvent(mainEvent))
		{


			switch (mainEvent.type) {

				case (sf::Event::Closed):
					eksport(&tasks);
					mainWin.close();
					break;


				//Tracking Keyboard key presses

				case (sf::Event::KeyPressed): 
					
					if (mainEvent.key.code == 72) {
					
						taskIterator += 3;

						if (taskIterator >= tasks.size())
							taskIterator -= 3;
					
					}
					if (mainEvent.key.code == 71) {
					
						taskIterator -= 3;
						
						if (taskIterator < 0)
							taskIterator += 3;
					
					}



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

					//Checking for Edit Icon clicks
					if (mainEvent.mouseButton.button == sf::Mouse::Left) {

						if (firstOptionEdit.inRange(mousePos.x, mousePos.y)) {

							if (tasks.size() >= taskIterator + 1) {
								tasks.insert(tasks.begin(), *taskEditor(tasks[taskIterator], &openSansRegular));
								tasks.erase(tasks.begin() + 1);
							}
						}

					}

					if (mainEvent.mouseButton.button == sf::Mouse::Left) {

						if (secOptionEdit.inRange(mousePos.x, mousePos.y)) {

							
							if (tasks.size() >= taskIterator + 2) {
								tasks.insert(tasks.begin() + 1, *taskEditor(tasks[taskIterator + 1], &openSansRegular));
								tasks.erase(tasks.begin() + 2);
							}
						}

					}

					if (mainEvent.mouseButton.button == sf::Mouse::Left) {

						if (terOptionEdit.inRange(mousePos.x, mousePos.y)) {

							
							if (tasks.size() >= taskIterator + 3) {
								tasks.insert(tasks.begin() + 2, *taskEditor(tasks[taskIterator + 2], &openSansRegular));
								tasks.erase(tasks.begin() + 3);
							}

						}

					}

					//Checking for Delete Icon clicks
					if (mainEvent.mouseButton.button == sf::Mouse::Left) {

						if (firstOptionDelete.inRange(mousePos.x, mousePos.y)) {

							if (tasks.size() >= taskIterator + 1) {
								tasks.erase(tasks.begin() + taskIterator);
							}

						}

					}

					if (mainEvent.mouseButton.button == sf::Mouse::Left) {

						if (secOptionDelete.inRange(mousePos.x, mousePos.y)) {

							if (tasks.size() >= taskIterator + 2) {
								tasks.erase(tasks.begin() + taskIterator + 1);
							}

						}

					}

					if (mainEvent.mouseButton.button == sf::Mouse::Left) {

						if (terOptionDelete.inRange(mousePos.x, mousePos.y)) {

							if (tasks.size() >= taskIterator + 3) {
								tasks.erase(tasks.begin() + taskIterator + 2);
							}

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

							//String to store entered data
							sf::String newString;

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

					if (firstOptionDelete.inRange(mousePos.x, mousePos.y)) {

						firstOptionDelete.hovered();

					}

					else firstOptionDelete.unHovered();

					if (secOptionDelete.inRange(mousePos.x, mousePos.y)) {

						secOptionDelete.hovered();

					}
					
					else secOptionDelete.unHovered();

					if (terOptionDelete.inRange(mousePos.x, mousePos.y)) {

						terOptionDelete.hovered();

					}

					else terOptionDelete.unHovered();
					

					//Edit options
					if (firstOptionEdit.inRange(mousePos.x, mousePos.y)) {

						firstOptionEdit.hovered();

					}

					else firstOptionEdit.unHovered();

					if (secOptionEdit.inRange(mousePos.x, mousePos.y)) {

						secOptionEdit.hovered();

					}

					else secOptionEdit.unHovered();

					if (terOptionEdit.inRange(mousePos.x, mousePos.y)) {

						terOptionEdit.hovered();

					}

					else terOptionEdit.unHovered();


					break;


			}
		}
	
	}

	return 0;

}



//Function to edit tasks

sf::String* taskEditor(std::string str, sf::Font* openSansRegular) {

	sf::RenderWindow editorWin(sf::VideoMode(450, 300), "Edit task");
	editorWin.setFramerateLimit(20);

	sf::Event editorEvent;
	sf::Text editorText;
	editorText.setFont(*openSansRegular);
//	editorText.setCharacterSize(40);
	editorText.setFillColor(sf::Color(0, 0, 0));

	sf::String* strin = new sf::String;
	int iterator = 0;


	for (int i = 0; i < str.size(); i++) {

		*strin += (str[i]);
		iterator = i;

	}


	while (editorWin.isOpen()) {

		editorText.setString(*strin);


		editorWin.clear(sf::Color(255, 255, 255));
		editorWin.draw(editorText);
		editorWin.display();

		while (editorWin.pollEvent(editorEvent)) {

			if (editorEvent.type == sf::Event::Closed) {

				editorWin.close();
				return strin;

			}

			else if (editorEvent.type == sf::Event::KeyPressed) {

				if (editorEvent.key.code == sf::Keyboard::Escape) {

					editorWin.close();
					return strin;

				}

				else if (editorEvent.key.code == sf::Keyboard::BackSpace && (iterator >= 0)) {

					(*strin).erase(iterator, 1);
					iterator--;
					editorText.setString(*strin);

				}

			}


			else if (editorEvent.type == sf::Event::TextEntered) {

				if (editorEvent.text.unicode < 128 && editorEvent.text.unicode != 8) {
					*strin += static_cast<char>(editorEvent.text.unicode);
					iterator++;
					editorText.setString(*strin);
				}

			}



		}


	}



}


//Defining the export function
void eksport(std::vector <std::string>* tasks) {

	std::string temp;
	std::ofstream output;
	output.open("Resources/dataBase.txt");

	for (int i = 0; i < tasks->size(); i++) {

		output << (*tasks)[i];
		if (!(i == tasks->size() - 1))
			output << '`';

	}

}

//Defining the import function
void import(std::vector<std::string>* tasks) {

	std::string temp;
	std::ifstream input;
	input.open("Resources/dataBase.txt");

	while (!input.eof()) {
	
		if (!input.eof()) {
			std::getline(input, temp, '`');
//			std::cout << "Temp is: " << (int) temp[0] << std::endl;
			if ( (temp[0] != 0) )
				(*tasks).push_back(temp);
		}

	}


}