//#include "Game.h"
//
////private function
//
////void Game::initWindow()
////{
////    this->videoMode.width = 500;
////    this->videoMode.height = 700;
////    this->window = new sf::RenderWindow(this->videoMode,"doodle jump", sf::Style::Close);
////    this->window->setFramerateLimit(50);
////}
//
//void Game::initPictures()
//{
//    //BackGround
//    if(!this->backGroundTex.loadFromFile("images/background1.png"))
//        throw "Could not load background1.png!";
//    this->backGround.setTexture(this->backGroundTex);
//    //Plat
//    if(!this->platTex.loadFromFile("images/platform.png"))
//        throw "Could not load platform.png!";
//    this->plat.setTexture(platTex);
//    this->plat.setPosition(60,600);
//    //Doodle
//    if(!this->doodleTex.loadFromFile("images/doodle.png"))
//        throw "Could not load doodle.png!";
//    this->doodle.setTexture(this->doodleTex);
//    this->doodle.setPosition(this->plat.getPosition().x - 10, this->plat.getPosition().y - this->doodle.getGlobalBounds().height);
//}
//void Game::initAudio()
//{
//    //Audio //Jump
//    if(!this->bufferJump.loadFromFile("audio/jump.wav"))
//    throw "Could not load jump.wav!";
//    this->audioJump.setBuffer(this->bufferJump);
//    //Audio
//    //Monster 1
//    if(!this->bufferMonster1.loadFromFile("audio/monsterblizu.wav"))
//        throw "Could not load monsterblizu.wav";
//    this->audioMonster1.setBuffer(this->bufferMonster1);
//    //Monster 2
//    if(!this->bufferMonster2.loadFromFile("audio/monsterblizu.wav"))
//        throw "Could not load monsterblizu.wav";
//    this->audioMonster2.setBuffer(this->bufferMonster2);
//    //Audio //fall
//    if(!this->bufferFall.loadFromFile("audio/pada.wav"))
//        throw "could not load pada.wav";
//    this->audioFall.setBuffer(this->bufferFall);
//    //Audio  //Shoot
//    if(!this->bufferShoot.loadFromFile("audio/pucanje.wav"))
//        throw "could not load pucanje.wav";
//    this->audioShoot.setBuffer(this->bufferShoot);
//    //Audio  //Wood Broken
//    if(!this->bufferWood.loadFromFile("audio/egg-monster-hit.wav"))
//        throw "could not load egg-monster-hit.wav";
//    this->audioWood.setBuffer(this->bufferWood);
//}
//void Game::initFont()
//{
//    if(!this->font.loadFromFile("font/ARIALNBI.ttf"))
//        throw "Could not load arial.ttf!";
//}
//
//void Game::initText()
//{
//    //PlayText
//    this->playText.setFont(font);
//    this->playText.setCharacterSize(50);
//    this->playText.setFillColor(sf::Color::Black);
//    this->playText.setString("Play");
//    this->playText.setPosition(sf::Vector2f(270,200));
//    //GameName
//    this->gameName.setFont(font);
//    this->gameName.setCharacterSize(60);
//    this->gameName.setFillColor(sf::Color(204,0,0));
//    this->gameName.setString("doodle jump");
//    this->gameName.setPosition(sf::Vector2f(20,60));
//    this->gameName.rotate(-5);
//    //GameOver
//    this->gameOverText.setFont(font);
//    this->gameOverText.setString("Game Over!");
//    this->gameOverText.setCharacterSize(50);
//    this->gameOverText.setFillColor(sf::Color(153,0,0));
//    this->gameOverText.rotate(-5);
//    this->gameOverText.setPosition(sf::Vector2f(125,200));
//    //ScoreText
//    this->scoreText.setFont(font);
//    this->scoreText.setCharacterSize(50);
//    this->scoreText.setFillColor(sf::Color::Black);
//    //High ScoreText
//    this->highScoreText.setFont(font);
//    this->highScoreText.setCharacterSize(50);
//    this->highScoreText.setFillColor(sf::Color::Black);
//    //My Name
//    this->myName.setFont(font);
//    this->myName.setString("Mohammad Kamyar Sabouri Dodaran");
//    this->myName.setCharacterSize(20);
//    this->myName.setFillColor(sf::Color::Black);
//    this->myName.setPosition(sf::Vector2f(100,650));
//    //Pause
//    this->pause.setFont(font);
//    this->pause.setString("P");
//    this->pause.setFillColor(sf::Color::Black);
//    this->pause.setCharacterSize(50);
//    this->pause.setPosition(sf::Vector2f(460,0));
//}
//
//void Game::initHighScore()
//{
//    if ((this->fp = fopen("HighScore.txt", "r"))==NULL )
//        fprintf(stderr,"Error opening file HighScore.txt.");
//
//    fscanf(fp,"%d", &this->highScore);
//    this->highScoreText.setString("high Score: " + std::to_string(this->highScore));
//    this->highScoreText.setPosition(sf::Vector2f(160,300));
//    fclose(this->fp);
//}
//
//Game::Game()
//{
//    this->initWindow();
//    this->initPictures();
//    this->initAudio();
//    this->initFont();
//    this->initText();
//    this->initHighScore();
//}
////--------------------------------------
////const bool Game::running() const
////{
////    return this->window->isOpen();
////}
//////--------------------------------------- Updates
////void Game::pollEvents()
////{
////    while(this->window->pollEvent(this->event))
////    {
////        switch(this->event.type)
////        {
////        case sf::Event::Closed:
////            this->window->close();
////            break;
////        case sf::Event::KeyPressed:
////            if(this->event.key.code == sf::Keyboard::Escape)
////                this->window->close();
////            break;
////        }
////    }
////}
////
////void Game::updateMousePositionMenu()
////{
////    this->mousePosWindow = sf::Mouse::getPosition(*this->window);
////    this->mousePosView = this->window->mapPixelToCoords(this->mousePosWindow);
////
////    if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
////    {
////        if( this->playText.getGlobalBounds().contains(this->mousePosView) )
////        {
////            this->startGame = true;
////        }
////    }
////}
//
//void Game::upDownDoodle()
//{
//    //doodle
//    if(this->doodle.getPosition().y <= 350)
//        this->Dir = 1;
//    else if(this->doodle.getPosition().y + 80 >= this->plat.getPosition().y)
//        this->Dir = 0;
//    if( this->doodle.getPosition().y + 80 == this->plat.getPosition().y )
//        this->audioJump.play();
//
//    if( this->Dir == 0 )
//        this->doodle.move( 0 , -5.f );
//    else if  ( this->Dir == 1 )
//        this->doodle.move( 0 , 5.f );
//}
//
//void Game::update()
//{
////    this->pollEvents();
////    this->updateMousePosition();
//    this->upDownDoodle();
//}
//
//void Game::renderBackGround(sf::RenderTarget& target)
//{
//    target.draw(this->backGround);
//}
//void Game::renderPlayText(sf::RenderTarget& target)
//{
//    target.draw(this->playText);
//}
//void Game::renderPlat(sf::RenderTarget& target)
//{
//    target.draw(this->plat);
//}
//void Game::renderDoodle(sf::RenderTarget& target)
//{
//    target.draw(this->doodle);
//}
//void Game::renderGameName(sf::RenderTarget& target)
//{
//    target.draw(this->gameName);
//}
//void Game::renderHighScoreText(sf::RenderTarget& target)
//{
//    target.draw(this->highScoreText);
//}
//void Game::renderMyName(sf::RenderTarget& target)
//{
//    target.draw(this->myName);
//}
//
//void Game::render()
//{
//    this->window->clear();
//
//    this->renderBackGround(*this->window);
//    this->renderPlayText(*this->window);
//    this->renderPlat(*this->window);
//    this->renderDoodle(*this->window);
//    this->renderGameName(*this->window);
//    this->renderHighScoreText(*this->window);
//    this->renderMyName(*this->window);
//
//    this->window->display();
//}

