#include "Board.h"


Board::Board() : m_ifile("Board.txt"),m_mouse(nullptr)
{
}

//this function reads the new leval
bool Board::ReadNewLevel()
{
	clearMatrix();
	clearVector();
	if (readboard()) // if eof
	{	
		setObjectCheese();
		return true;
	}
	return false;
}

//this function rest the file to the start 
void Board::fileReset()
{
	m_ifile.seekg(0);
}

//this function set the chese counter
void Board::setObjectCheese()
{
	m_MovingObject[m_mouse_idx]->setCheese();
}

//this function cleares the vectores for new game to start
void Board::clearVector()
{
	m_MovingObject.clear();
	m_StaticObject.clear();
	m_cheese = 0;
	m_mouse_idx = 0;
}

//this function cleares the board for new game to start
void Board::clearMatrix()
{
	for (int row = 0; row < m_row; ++row)
	{
		m_matrixVector[row].clear();
	}
	m_matrixVector.clear();
}

//this function reades from the board.txt file 
bool Board::readboard()
{
	if (!m_ifile.eof())
	{
		//reads the row and the col from the file 
		m_ifile >> m_row >> m_col;
		//for the \n
		m_ifile.get();

		//reset the rowes matrix 
		m_matrixVector.clear();
		int rows_size = m_matrixVector.size();
		//reads the lines from the file 
		for (int row = 0; row < m_row; ++row)
		{
			std::string row_string;
			std::getline(m_ifile, row_string);
			m_matrixVector.push_back(row_string);
		}

		//create object board
		sf::Vector2f location;
		sf::Vector2f scaleFactor = calculateFactor();

		//set the location of each object in the board
		for (int row = 0; row < m_matrixVector.size(); row++)
		{
			for (int col = 0; col < m_matrixVector[row].size(); col++)
			{
				//cal the location of each object in the board
				location = sf::Vector2(col * SPRITE_SIZE, row * SPRITE_SIZE );
				location *= scaleFactor.x;
				switch (m_matrixVector[row][col])
				{
				case '#': //wall
				{
					m_StaticObject.push_back(std::make_unique<Wall>(Resources::instance().getTexture(Resources::t_wall), location));
					m_StaticObject.back()->satScale(scaleFactor);
					break;
				}
				case 'D': //door
				{
					m_StaticObject.push_back(std::make_unique<Door>(Resources::instance().getTexture(Resources::t_door), location));
					m_StaticObject.back()->satScale(scaleFactor);
					break;
				}
				case 'F': //key
				{
					m_StaticObject.push_back(std::make_unique<Key>(Resources::instance().getTexture(Resources::t_key), location));
					m_StaticObject.back()->satScale(scaleFactor);
					break;
				}
				case '*': //cheese
				{
					m_cheese++; //counting the cheese at the corrent level
					m_StaticObject.push_back(std::make_unique<Cheese>(Resources::instance().getTexture(Resources::t_cheese), location));
					m_StaticObject.back()->satScale(scaleFactor);
					break;
				}
				case '$': //present
				{
					m_StaticObject.push_back(std::make_unique<Present>(Resources::instance().getTexture(Resources::t_present), location));
					m_StaticObject.back()->satScale(scaleFactor);
					break;
				}
				case 'T': //addtime
				{
					m_StaticObject.push_back(std::make_unique<AddTime>(Resources::instance().getTexture(Resources::t_timeGift), location));
					m_StaticObject.back()->satScale(scaleFactor);
					break;
				}
				case 'L': //addlife
				{
					m_StaticObject.push_back(std::make_unique<AddLife>(Resources::instance().getTexture(Resources::t_lifeGift), location));
					m_StaticObject.back()->satScale(scaleFactor);
					break;
				}
				case 'Z': //freeze
				{
					m_StaticObject.push_back(std::make_unique<Freeze>(Resources::instance().getTexture(Resources::t_freezeGift), location));
					m_StaticObject.back()->satScale(scaleFactor);
					break;
				}
				case '%': //mouse
				{
					m_MovingObject.push_back(std::make_unique<Mouse>(Resources::instance().getTexture(Resources::t_mouse), location, scaleFactor));
					m_MovingObject.back()->satScale(scaleFactor);
					m_MovingObject.back()->setOriginalPos(location);
					//dynamic cast for the mouse 
					m_mouse = dynamic_cast <Mouse*> (m_MovingObject.back().get());
					// Cast failed
					if (m_mouse == nullptr) 
					{
						std::cout << "Failed to cast to Mouse" << std::endl;
					}
					break;
				}
				case '^': //cat
				{
					m_MovingObject.push_back(std::make_unique<Cat>(Resources::instance().getTexture(Resources::t_cat), location));
					m_MovingObject.back()->satScale(scaleFactor);
					m_MovingObject.back()->setOriginalPos(location);
					break;
				}
				default:
					break;
				}
			}
		}
		return true;
	}
	return false;
}

//this function disply the board
void Board::drawBoard(sf::RenderWindow& m_window)
{
	for (auto& staticc : m_StaticObject)
	{
		staticc->drawObject(m_window);
	}
	for (auto& moving : m_MovingObject)
	{
		moving->drawObject(m_window);
	}
}

//this function calculate the factor of the current board
sf::Vector2f Board::calculateFactor()
{
	sf::Vector2f scaleFactor;
	//define the width and heigt
	float heigt = 800;
	float width = 1200;
	// Calculate the minimum scale according to the new width and height
	scaleFactor.x = std::min((heigt / (m_row * SPRITE_SIZE)), (width / (m_col * SPRITE_SIZE)));
	scaleFactor.y = scaleFactor.x;
	return scaleFactor;
}

//this function update each object direction 
void Board::updateGame(const sf::Time delta_Time)
{
	//update moving object direction 
	for (auto& moving : m_MovingObject)
	{
		//if the moving obj is the mouse and he took a freeze present then move only the mouse
		if ((m_isFreeze && moving->getChar() == '%') || (!m_isFreeze))
		{
			//polymorphism
			moving->moveObject(delta_Time, m_MovingObject);
		}
		moving->checkCollition(m_MovingObject, m_StaticObject);
		//check if we need to delete any obj from the board
		std::erase_if(m_StaticObject, [](const auto& game_object) {return game_object->getIsCollide(); });
	}
	//if the moving obj is the mouse and he took a remove cat present 
	if (m_mouse->getIsDeleteCat())
	{
		//delete the last cat in the moving vector
		auto cat = (std::find_if(m_MovingObject.begin(), m_MovingObject.end(), [](const auto& game_object) {return game_object->getChar() == '^'; }));
		if (cat != m_MovingObject.end())
		{
			m_MovingObject.erase(cat);
			m_mouse->setIsDeleteCat();
		}	
	}
	//handel the freeze present 
	if (m_mouse->getIsFreeze())
	{
		m_isFreeze = true;
		m_freezeTimer.restart();
		m_mouse->setIsFreeze();
	}
	//set the time for the cats freeze
	if (m_freezeTimer.getElapsedTime().asSeconds() > 5.f) //wait 5 se
	{
		m_isFreeze = false;
	}
}

//this function returnes the moving obj sprite
sf::Sprite Board::getGameObjectMoving(const int index)
{
	return m_MovingObject[index]->getSprite();
}

//this function return the mouse life
int Board::returnMouseLife() const
{
	return m_MovingObject[m_mouse_idx]->getLife();
}

//this function set the mouse life to 3
int Board::returnMouseLifeStart()
{
	return m_MovingObject[m_mouse_idx]->setLifeStart();
}

//this function set the mouse data
void Board::setMouseData(int life, int score)
{
	//sets mouse data for next levels
	m_MovingObject[m_mouse_idx]->setLife(life);
	m_MovingObject[m_mouse_idx]->setScore(score);
}

//this function return the time that the mouse collected 
int Board::returnMouseTime() const
{
	return m_MovingObject[m_mouse_idx]->getTime();
}

//this function return the score that the mouse collected 
int Board::returnMouseScore() const
{
	return m_MovingObject[m_mouse_idx]->getScore();
}

//this function return the number of keyes that the mouse collected 
int Board::returnMouseKeys() const
{
	return m_MovingObject[m_mouse_idx]->getKeys();
}

//get the cheese counter
int Board::getCheese() const
{
	return m_cheese;
}

//get how many cheese the mouse collected
int Board::getEattenCheese() const
{
	return m_MovingObject[m_mouse_idx]->getEatten();
}