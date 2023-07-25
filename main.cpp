#include "Menu.h"

int main()
{
    window.setFramerateLimit(50);

    initPictures();
    initAudio();
    initText();

    //Menu Start
    while(window.isOpen())
    {
        //File
        findHighScore();

        while(window.pollEvent(event))
        {
            if(event.type == sf::Event::Closed)
                window.close();
            if(event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
                window.close();
        }
        mousePosWindow = sf::Mouse::getPosition(window);
        mousePosView = window.mapPixelToCoords(mousePosWindow);

        if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
        {
            if( easyText.getGlobalBounds().contains(mousePosView) )
            {
                startGame = true;
                kamyar1 = true;
            }
        }
        if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
        {
            if( mediumText.getGlobalBounds().contains(mousePosView) )
            {
                startGame = true;
                kamyar1 = true;
                Medium = true;
            }
        }

        //doodle
        doodleUpDown();

        window.clear();

        window.draw(backGround);
        window.draw(easyText);
        window.draw(mediumText);
        window.draw(plat);
        window.draw(doodle);
        window.draw(gameName);
        window.draw(highScoreText);
        window.draw(myName);

        window.display();
if(kamyar1 == true)
{
//{
//----------------------------------------------Doodle Jump Game----------------------------------------------
if ( startGame )
{
    //RectangleShapeUp
    RectangleShapeUp(Medium);
    //-------------------------------------------------Plat-----------------------------------------------------
    //initPlatsGreen
    initPlatsGreen(platFormPosition);
    //initWoodPlats
    initWoodPlats(woodPlats);
    //initbluePlats
    initbluePlats(bluePlats);
    //EnemiesPicture
    EnemiesPicture();

    //--------------------------------------------------GAME LOOP----------------------------------------------------
    while (window.isOpen() && kamyar1 == true)
    {
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
                window.close();
        }

    //----------------------------------------------------Pause----------------------------------------------------
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::P))
        {
                pauseGame = false;
                audioMonster1.pause();
                audioMonster2.pause();
        }
        else if(sf::Keyboard::isKeyPressed(sf::Keyboard::S))
            pauseGame = true;

        //-------------------------------------------Update--------------------------------------------

        //----------------------------------------Doodle , Plats---------------------------------------
    if(pauseGame)
    {
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
            playerX -= 4;
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
            playerX += 4;

        if(playerX > 500)
            playerX = 0;
        if(playerX < -80)
            playerX = window.getSize().x - doodleTex.getSize().x;

        //--------------------------------------------------score------------------------------------------
        Score(playerY, height , scoreText);

        HighScore(highScore,score,highScoreText,pf);
        //-----------------------------------------------------------------------------------------------
        dy += 0.2;
        playerY += dy;
        playerYW = playerY, heightW = height, dyw = dy;
        playerYB = playerY, heightB = height, dyb = dy;

        updatePlat();
        // ------------------------------------------------WoodPlat---------------------------------------------------
        //Collision betwwen doodle and woodPlat
    if(Medium)
    {
        updateWoodPlat();
    }
    //--------------------------------------------------bluePlat--------------------------------------------------
    if(Medium)
    {
        updateBluePlat();
    }
        //-----------------------------------------------Projectiles-------------------------------------------------
        updateProjectiles();
    }
        //---------------------------------------------Enemies------------------------------------------------
        //Enemy 1
        //updating the timer for enemy spawning
     if(pauseGame)
     {
         updateEnemy1();
     }
        //Collision
        CollisionEnemy1WithDoodleAndPro();
        //---------------------------
        //Enemy 2
        //updating the timer for enemy spawning
if(pauseGame)
{
    if(Medium)
    {
        updateEnemy2();
    }
        //Collision
        CollisionEnemy2WithDoodleAndPro();
}
        //----------------------------------------------------------------------------------------------------------
        //Game Over
        if(playerY > 700)
        {
            gameOver = true;
            kamyar2 = true;
            audioMonster1.pause();
            audioMonster2.pause();
        }

        //------------------------------------------------Draw-------------------------------------------------
        window.clear();

        window.draw(backGround);

        for( size_t i=0 ; i < 10 ; i++ )
        {
            plat.setPosition(platFormPosition[i].x, platFormPosition[i].y);
            window.draw(plat);
        }
if(Medium)
{
        for ( size_t i=0 ; i<3 ; i++ )
        {
            woodPlat.setPosition(woodPlats[i].x, woodPlats[i].y);
            window.draw(woodPlat);
        }
        for ( size_t i=0 ; i<2 ; i++ )
        {
            bluePlat.setPosition(bluePlats[i].x, bluePlats[i].y);
            window.draw(bluePlat);
        }
}
        window.draw(doodle);

        for ( size_t i=0 ; i<enemies.size() ; i++ )
            window.draw(enemies[i]);
if(Medium)
{
        for ( size_t i=0 ; i<enemies2.size() ; i++ )
            window.draw(enemies2[i]);
}
        for( size_t i=0 ; i<projectiles.size() ; i++ )
            window.draw(projectiles[i]);

        window.draw(rect);
        window.draw(scoreText);
        window.draw(pause);

        window.display();
    if(kamyar2 == true)
    {
        //-------------------------------------------Game Over----------------------------------------------
        if(gameOver)
        {
            while( window.isOpen() && kamyar2 == true)
            {
                scoreText.setPosition(110,400);
                highScoreText.setPosition(110,480);
                killEnemy.setString("Kill Monster: " + std::to_string(killEnemyNum));
                //sf::Event event;
                while( window.pollEvent(event))
                {
                    if( event.type == sf::Event::Closed )
                        window.close();
                    if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
                    window.close();
                }

                if( firstStartGameOver )
                {
                    doodle.setPosition(sf::Mouse::getPosition(window).x - doodle.getGlobalBounds().width/2, 0 );
                    audioFall.play();
                    firstStartGameOver = false;
                }
                else
                    doodle.setPosition(sf::Mouse::getPosition(window).x - doodle.getGlobalBounds().width/2, doodle.getPosition().y );

                if(doodle.getPosition().x > window.getSize().x - doodle.getGlobalBounds().width)
                    doodle.setPosition(window.getSize().x - doodle.getGlobalBounds().width , doodle.getPosition().y);

                if(doodle.getPosition().x < 0)
                    doodle.setPosition( 0, doodle.getPosition().y);

                if( doodle.getPosition().y == 700 )
                    doodle.setPosition(window.getSize().x/2 , window.getSize().y + 80);


                doodle.move(0.f,8.f);

                mousePosWindow = sf::Mouse::getPosition(window);
                mousePosView = window.mapPixelToCoords(mousePosWindow);

                if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
                {
                    if( playAgain.getGlobalBounds().contains(mousePosView) )
                    {
                        //gameOver = false;
                        kamyar1 = false;
                        kamyar2 = false;
                    }
                    doodle.setPosition( 50, 600 - doodle.getGlobalBounds().height);
                    plat.setPosition(60,600);
                    highScoreText.setPosition(Vector2f(160,350));
                }

                window.clear();

                window.draw(backGround);
                window.draw(gameOverText);
                window.draw(doodle);
                window.draw(scoreText);
                window.draw(highScoreText);
                window.draw(killEnemy);
                window.draw(playAgain);

                window.display();


            }

        }
    }
    }
    }
}
}

    return 0;
}

