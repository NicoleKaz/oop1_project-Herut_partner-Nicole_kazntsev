#include "GameControll.h"


GameControll::GameControll()
    :m_window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Mouse&Cat"),
     m_menu(WINDOW_WIDTH, WINDOW_HEIGHT),
     m_board()
{
    loadBackgroundes();
    m_window.setFramerateLimit(60);
}

//this function is the game loop
void GameControll::run()
{
    loadMusic();
    music.play();
    //game loop
    while (m_window.isOpen())
    {
        //display the first window 
        sf::Sprite s1(m_background);
        s1.scale(sf::Vector2f(2.35f, 1.35f));
        m_window.clear(sf::Color::Color(0, 0, 0));
        m_window.draw(s1);
        drawMenu();
        m_window.display();

        //event from user mouse
        if (auto event = sf::Event{}; m_window.waitEvent(event))
        {
            switch (event.type)
            {
            case sf::Event::Closed: //closes the window from the console
                m_window.close();
                break;

            case sf::Event::MouseButtonReleased: //where was preesed
            {
                auto location = m_window.mapPixelToCoords(
                    { event.mouseButton.x, event.mouseButton.y });
                handleClick(location, music,musicEnd);
                break;
            }

            case sf::Event::MouseMoved: //shadow 
            {
                auto location = m_window.mapPixelToCoords(sf::Mouse::getPosition(m_window));
                handleMouseMoved(location, PLAY, EXIT);
            }
            }
        }
        //exit from the window 
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
        {
            m_window.close();
        }
    }
}

//this function handle Mouse Moved
void GameControll::handleMouseMoved(const sf::Vector2f location, const Button first, const Button last)
{
    for (int button = first; button <= last; button++)
    {
        if ((m_menu.getButton((Button)button).getGlobalBounds().contains(location)))
        {
            m_menu.buttonPress((Button)button);
        }
        else
        {
            m_menu.buttonRelease((Button)button);
        }
    }
}

//this function draw the window menu 
void GameControll::drawMenu()
{
    for (int button = PLAY; button <= EXIT; ++button)
    {
        m_window.draw(m_menu.getButton((Button)button));
    }
}

//this function check where the user preesed
void GameControll::handleClick(const sf::Vector2f& location, sf::Music& music, sf::Music& musicEnd)
{
    //if preesed PLAY
    if (m_menu.getButton(PLAY).getGlobalBounds().contains(location))
    {
        music.stop(); //becouse we show project in zoom - so we cant talk with music
        Resources::instance().playSound(CLICK);
        //reset the time of the game so the moving object 
        m_MoveClock.restart();
        m_GameClock.restart();
        //start the game 
        startGame(musicEnd);
    }
    //if preesed HELP
    else if (m_menu.getButton(HELP).getGlobalBounds().contains(location))
    {
       Resources::instance().playSound(CLICK);
       instructionsLoop();
    }
    //if preesed EXIT 
    else if (m_menu.getButton(EXIT).getGlobalBounds().contains(location))
    {
        Resources::instance().playSound(CLICK);
        m_window.close();
    }
}

//this function display the Instructions window
void GameControll::instructionsLoop()
{
    //while the Instructions window is open
    bool exit = false;
    while (!exit)
    {
        m_window.clear(sf::Color::Color(0, 0, 0));
        drawInstructions();
        m_window.display();

        if (auto event = sf::Event{}; m_window.waitEvent(event))
        {
            switch (event.type)
            {
            case sf::Event::Closed: //close
                exit = true;
                m_window.close();
                break;

            case sf::Event::MouseButtonReleased:
            {
                auto location = m_window.mapPixelToCoords(
                    { event.mouseButton.x, event.mouseButton.y });
                handleNextClick(location, exit);
                break;
            }

            case sf::Event::MouseMoved:
            {
                auto location = m_window.mapPixelToCoords(sf::Mouse::getPosition(m_window));
                handleMouseMoved(location, VIDEO_PLAY, BACK);
            }

            }
        }
    }
}

//this function handle the next user click in the Instructions window
void GameControll::handleNextClick(const sf::Vector2f& location, bool& exit)
{
    if (m_menu.getButton(BACK).getGlobalBounds().contains(location))
    {
        Resources::instance().playSound(CLICK);
        exit = true;
    }
    else if (m_menu.getButton(VIDEO_PLAY).getGlobalBounds().contains(location))
    {
        m_menu.displayRules();
    }  
}

//this function manages all options after starting the game
//win and loss conditions
void GameControll::startGame(sf::Music& musicEnd)
{
    //rest the leval clock 
    m_GameClock.restart();

    if (m_board.readboard())
    {   
        while (m_window.isOpen())
        {
            sf::Sprite s2(m_backgroundplay);
            s2.scale(sf::Vector2f(2.35f, 1.35f));
            m_window.clear(sf::Color::Color(0, 102, 102));
            m_window.draw(s2);
            m_board.drawBoard(m_window);
            drawToolBar();
            m_window.display();

            for (auto event = sf::Event{}; m_window.pollEvent(event); )
            {
                //close the game window
                switch (event.type)
                {
                case sf::Event::Closed:
                    m_window.close();
                    break;
                }
            }
            //reset the move clock for the moving objectes
            auto delta_Time = m_MoveClock.restart();
            //update moving directions
            m_board.updateGame(delta_Time);
            //the toolbar update
            updateData();
            
            //exit the game from the keyboard
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
            {
                m_window.close();
            }
            if (m_board.wasAddTime())
            {
                was = false;
            }
            //if the player loset 
            if (m_board.returnMouseLife() == 0)
            {
                m_board.returnMouseLifeStart();
                //singleton - A static function with global access to an object from 
                //anywhere in the code without the need to create a new instance every time.
                Resources::instance().playSound(GAME_OVER);
                //reset all the data
                m_level = 0;
                m_board.clearMatrix();
                m_board.clearVector();
                //reset the file to the first leval
                m_board.fileReset();
                break;
            }
            // if the player won the leval by collecting all the cheese
            else if (m_board.getCheese() - m_board.getEattenCheese() == 0) 
            {
                if (m_board.ReadNewLevel())
                {
                    //saves the previous life and score
                    m_board.setMouseData(m_toolbar.GetLife(), m_toolbar.GetScore());
                    m_level++;
                    //restart the leval time 
                    m_GameClock.restart();
                }
                //if the player won the game 
                else 
                {
                    //rest the game 
                    m_level = 0;
                    Resources::instance().playSound(WIN);
                    //you win announcement
                    sf::Sprite s3(m_playerWon);
                    s3.scale(sf::Vector2f(2.35f, 1.35f));
                    m_window.clear(sf::Color::Color(0, 102, 102));
                    m_window.draw(s3);
                    m_window.display();
                    //so we could see the you win announcement
                    std::this_thread::sleep_for(std::chrono::seconds(5));
                    break;
                }
            }
            //if the time of this leval is over
            else if (m_GameClock.getElapsedTime().asSeconds() > 40 + m_board.getAddTime()) 
            {
                m_board.returnMouseLifeStart();
                Resources::instance().playSound(GAME_OVER);
                m_level = 0;
                m_board.clearMatrix();
                m_board.clearVector();
                m_board.fileReset();
                break;
            }
            if (!was && m_GameClock.getElapsedTime().asSeconds() > 35 + m_board.getAddTime())
            {
                // If received a gift of additional time
                musicEnd.play(); //counting down.
                was = true;
            }
        }
    }
 }

//this function display the tool bar
void GameControll::drawToolBar()
{
    for (int word = LIFE; word <= KEYCOUNTER; word++)
    {
        //display the string
        m_window.draw(m_toolbar.GetText(word));
        //display the data
        m_window.draw(m_toolbar.GetNum(word));
    }
}

//this function uptates the tool ber data
void GameControll::updateData()
{
    //update the toolbar data
    m_toolbar.setLife(m_board.returnMouseLife());
    m_toolbar.SetScore(m_board.returnMouseScore());
    m_toolbar.SetLevel(m_level);
    m_toolbar.SetKeys(m_board.returnMouseKeys());
    m_toolbar.SetTime(m_GameClock.getElapsedTime().asSeconds()- m_board.getAddTime());
}

//this function display the instructions buttons
void GameControll::drawInstructions()
{
    for (int object = 0; object <= 0; ++object)
    {
        m_window.draw(m_menu.getInstructions((Instructions)object));
    }
    for (int object = VIDEO_PLAY; object <= BACK; ++object)
    {
        m_window.draw(m_menu.getButton((Button)object));
    }
}

//this function loades the long pieces of music
void GameControll::loadMusic()
{
    music.openFromFile("Song.wav");
    music.setVolume(100);

    musicEnd.openFromFile("5_second_end.wav");
    musicEnd.setVolume(100);
}

//this function loads the Backgroundes of the game
void GameControll::loadBackgroundes()
{
    m_background.loadFromFile("background.png");
    m_backgroundplay.loadFromFile("backgroundplay.png");
    m_playerWon.loadFromFile("youWin.png");
    m_background.setSmooth(true);
    m_backgroundplay.setSmooth(true);
    m_playerWon.setSmooth(true);
}


