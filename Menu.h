#ifndef GAME_H_INCLUDED
#define GAME_H_INCLUDED

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Network.hpp>

#include <iostream>
#include <vector>
#include <cstdlib>
#include <random>
#include <ctime>
#include <fstream>

using namespace sf;

//Variables
bool gameOver = false, firstStartGameOver = true, startGame = false, pauseGame = true, Easy = false, Medium = false ;
int dir = 0, score = 0, highScore , P=0, Dir = 0;
int playerYW , heightW , dyw = 0 ;
int playerYB, heightB , dyb = 0 ;
int shootTimer = 0 , killEnemyNum = 0;
bool kamyar1 = true, kamyar2 = true;

int playerX = 250, playerY = 300, height = 350;
float dy = 0;

const int PLAYER_LEFT_BOUNDING_BOX = 20;
const int PLAYER_RIGHT_BOUNDING_BOX = 60;
const int PLAYER_BOTTOM_BOUNDING_BOX = 70;

//Enemy 1
float enemySpawnTimerMax1 = 500.f;
float enemySpawnTimer1 = enemySpawnTimerMax1;
//Enemy 2
float enemySpawnTimerMax2 = 700.f;
float enemySpawnTimer2 = enemySpawnTimerMax2;

int maxEnemies = 1;


//SF
sf::RenderWindow window(sf::VideoMode(500, 700), "Doodle Jump", sf::Style::Close);

sf::Vector2i mousePosWindow;
sf::Vector2f mousePosView;

sf::Texture platTex, backGroundTex, doodleTex;
sf::Sprite plat, backGround, doodle;

sf::SoundBuffer bufferJump,bufferMonster1,bufferMonster2,bufferFall,bufferShoot, bufferWood;
sf::Sound audioJump,audioMonster1,audioMonster2,audioFall,audioShoot, audioWood;

sf::Font font;

sf::Text easyText, mediumText, gameName, gameOverText, scoreText, highScoreText, myName, pause, killEnemy, playAgain;

FILE *fp;
FILE *pf;

sf::Event event;

sf::Texture enemyTex1, enemyTex2;
sf::Sprite enemy1, enemy2;

sf::RectangleShape rect, woodPlat, bluePlat;
sf::CircleShape projectile;

std::vector <CircleShape> projectiles;
std::vector<sf::Sprite> enemies;
std::vector<sf::Sprite> enemies2;

sf::Vector2f platFormPosition[10], woodPlats[3], bluePlats[2];
sf::Vector2f doodleCenter;

void initPictures()
{
    //BackGround
    if(!backGroundTex.loadFromFile("images/background1.png"))
        throw "Could not load background1.png!";
    backGround.setTexture(backGroundTex);
    //Plat
    if(!platTex.loadFromFile("images/platform.png"))
        throw "Could not load platform.png!";
    plat.setTexture(platTex);
    plat.setPosition(60,600);
    //Doodle
    if(!doodleTex.loadFromFile("images/doodle.png"))
        throw "Could not load doodle.png!";
    doodle.setTexture(doodleTex);
    doodle.setPosition(plat.getPosition().x - 10, plat.getPosition().y - doodle.getGlobalBounds().height);
//    doodle.setPosition( 50, 600 - doodle.getGlobalBounds().height);
    //wood plat
    woodPlat.setFillColor(sf::Color(153,76,0));
    woodPlat.setSize(Vector2f(60,12));
    woodPlat.setOutlineColor(sf::Color::Black);
    woodPlat.setOutlineThickness(2);
    //Blue plat
    bluePlat.setFillColor(sf::Color(51,153,255));
    bluePlat.setSize(Vector2f(60,12));
    bluePlat.setOutlineColor(sf::Color::Black);
    bluePlat.setOutlineThickness(2);
    //Projectiles
    projectile.setFillColor(sf::Color::Red);
    projectile.setRadius(5.f);
    projectile.setOutlineColor(sf::Color::Black);
    projectile.setOutlineThickness(3.f);

    projectiles.push_back(CircleShape(projectile));
}

void initAudio()
{
    //Audio //Jump
    if(!bufferJump.loadFromFile("audio/jump.wav"))
    throw "Could not load jump.wav!";
    audioJump.setBuffer(bufferJump);
    //Audio
    //Monster 1
    if(!bufferMonster1.loadFromFile("audio/monsterblizu.wav"))
        throw "Could not load monsterblizu.wav";
    audioMonster1.setBuffer(bufferMonster1);
    //Monster 2
    if(!bufferMonster2.loadFromFile("audio/monsterblizu.wav"))
        throw "Could not load monsterblizu.wav";
    audioMonster2.setBuffer(bufferMonster2);
    //Audio //fall
    if(!bufferFall.loadFromFile("audio/pada.wav"))
        throw "could not load pada.wav";
    audioFall.setBuffer(bufferFall);
    //Audio  //Shoot
    if(!bufferShoot.loadFromFile("audio/pucanje.wav"))
        throw "could not load pucanje.wav";
    audioShoot.setBuffer(bufferShoot);
    //Audio  //Wood Broken
    if(!bufferWood.loadFromFile("audio/egg-monster-hit.wav"))
        throw "could not load egg-monster-hit.wav";
    audioWood.setBuffer(bufferWood);
}

void initText()
{
    //easyText
    if(!font.loadFromFile("font/ARIALNBI.ttf"))
        throw "Could not load arial.ttf!";
    easyText.setFont(font);
    easyText.setCharacterSize(50);
    easyText.setFillColor(sf::Color::Black);
    easyText.setString("Easy");
    easyText.setPosition(Vector2f(270,150));
    //HardText
    mediumText.setFont(font);
    mediumText.setCharacterSize(50);
    mediumText.setFillColor(sf::Color::Black);
    mediumText.setString("Pro");
    mediumText.setPosition(Vector2f(280,250));
    //GameName
    gameName.setFont(font);
    gameName.setCharacterSize(60);
    gameName.setFillColor(sf::Color(204,0,0));
    gameName.setString("doodle jump");
    gameName.setPosition(Vector2f(20,60));
    gameName.rotate(-5);
    //GameOver
    gameOverText.setFont(font);
    gameOverText.setString("Game Over!");
    gameOverText.setCharacterSize(60);
    gameOverText.setFillColor(sf::Color(153,0,0));
    gameOverText.rotate(-5);
    gameOverText.setPosition(Vector2f(105,150));
    //ScoreText
    scoreText.setFont(font);
    scoreText.setCharacterSize(50);
    scoreText.setFillColor(sf::Color::Black);
//    if(gameOver)
//        scoreText.setPosition(110,400);
    //High ScoreText
    highScoreText.setFont(font);
    highScoreText.setCharacterSize(50);
    highScoreText.setFillColor(sf::Color::Black);
    //My Name Text
    myName.setFont(font);
    myName.setString("Name: Mohammad Kamyar Sabouri Dodaran\nID: 9932193");
    myName.setCharacterSize(20);
    myName.setFillColor(sf::Color::Black);
    myName.setPosition(Vector2f(5,650));
    //Pause Text
    pause.setFont(font);
    pause.setString("P/S");
    pause.setFillColor(sf::Color::Black);
    pause.setCharacterSize(50);
    pause.setPosition(Vector2f(420,0));
    //kill Enemy Numbers
    killEnemy.setFont(font);
    killEnemy.setCharacterSize(50);
    killEnemy.setFillColor(sf::Color::Black);
    killEnemy.setPosition(sf::Vector2f(110,560));
    //Play Again
    playAgain.setFont(font);
    playAgain.setCharacterSize(50);
    playAgain.setFillColor(sf::Color::Black);
    playAgain.setPosition(sf::Vector2f(110,280));
    playAgain.setString("Play Again\n--------------");
}

void doodleUpDown()
{
//    plat.setPosition(60,600);
//    doodle.setPosition(plat.getPosition().x - 10, plat.getPosition().y - doodle.getGlobalBounds().height);
    if(doodle.getPosition().y <= 350)
        Dir = 1;
    else if(doodle.getPosition().y + 80 >= plat.getPosition().y)
        Dir = 0;
    if( doodle.getPosition().y + 80 == plat.getPosition().y )
        audioJump.play();

    if( Dir == 0 )
        doodle.move( 0 , -5.f );
    else if  ( Dir == 1 )
        doodle.move( 0 , 5.f );
}

void findHighScore()
{
    if ((fp = fopen("HighScore.txt", "r"))==NULL )
        fprintf(stderr,"Error opening file HighScore.txt.");

    fscanf(fp,"%d", &highScore);
    highScoreText.setString("High Score: " + std::to_string(highScore));
    highScoreText.setPosition(Vector2f(160,350));
    fclose(fp);
}

void RectangleShapeUp(bool Medium)
{
    //RectangleShapeUp
    if (Medium)
        rect.setFillColor(sf::Color(204,0,0));
    else
        rect.setFillColor(sf::Color(204,229,255));
    rect.setSize(Vector2f(500, 60));
    rect.setOutlineColor(sf::Color::Black);
    rect.setOutlineThickness(2);
}

void initPlatsGreen(Vector2f platFormPosition[10])
{
    platFormPosition[0].y = 30;
    platFormPosition[1].y = 90;
    platFormPosition[2].y = 120;
    platFormPosition[3].y = 170;
    platFormPosition[4].y = 270;
    platFormPosition[5].y = 300;
    platFormPosition[6].y = 380;
    platFormPosition[7].y = 490;
    platFormPosition[8].y = 550;
    platFormPosition[9].y = 680;

    for ( size_t i=0 ; i<10 ; i++ )
        platFormPosition[i].x = rand()% 432;
}

void initWoodPlats(Vector2f woodPlats[3])
{
    woodPlats[0].y = 70;
    woodPlats[1].y = 240;
//    woodPlats[2].y = 330;
    woodPlats[2].y = 520;

    for ( size_t i=0 ; i<3 ; i++ )
        woodPlats[i].x = rand()% 432;
}

void initbluePlats(Vector2f bluePlats[2])
{
    bluePlats[0].y = 220;
    bluePlats[1].y = 615;

    for (size_t i=0 ; i<2 ; i++)
        bluePlats[i].x = rand()% 432;
}

void EnemiesPicture()
{
    //Enemy 1
    if(!enemyTex1.loadFromFile("images/big_blue_monster.png"))
        throw "Could not load big_blue_monster.png!";
    enemy1.setTexture(enemyTex1);

    //Enemy 2
    if(!enemyTex2.loadFromFile("images/green_flying_monster_1.png"))
        throw "Could not load green_flying_monster_1.png!";
    enemy2.setTexture(enemyTex2);
}
//--------------------------------------------------score------------------------------------------
void Score(int playerY, int height , sf::Text& scoreText)
{
    scoreText.setPosition(0,0);
    if(playerY == height )
    {
        score +=1;
        scoreText.setString("score: " + std::to_string(score));
    }
}

void HighScore(int highScore, int score, sf::Text& highScoreText, FILE *pf)
{
    if ( highScore > score )
        highScoreText.setString("High Score: " + std::to_string(highScore));
    else
    {
        highScoreText.setString("High Score: " + std::to_string(score));
        if ((pf = fopen("HighScore.txt", "w"))==NULL)
            fprintf(stderr,"Error opening file HighScore.txt.");
        fprintf(pf,"%d", score);
        fclose(pf);
    }
}
//----------------------------------------------Doodle , Plats-----------------------------------------------
void updatePlat()
{
    if(playerY < height)
    {
        for (size_t i=0 ; i < 10 ; i++)
        {
            playerY = height;
            platFormPosition[i].y -= dy;
            if ( platFormPosition[i].y > 700)
            {
                platFormPosition[i].y = 0;
                platFormPosition[i].x = rand()%432;
            }
        }
    }

    for (size_t i=0; i<10 ; i++)
    {
        if((playerX + PLAYER_RIGHT_BOUNDING_BOX > platFormPosition[i].x) && (playerX + PLAYER_LEFT_BOUNDING_BOX < platFormPosition[i].x + platTex.getSize().x )
            && (playerY + PLAYER_BOTTOM_BOUNDING_BOX > platFormPosition[i].y) && (playerY + PLAYER_BOTTOM_BOUNDING_BOX < platFormPosition[i].y + platTex.getSize().y) && (dy > 0))
        {
            audioJump.play();
            dy = -9;
        }
    }
    doodle.setPosition(playerX,playerY);

}
// ------------------------------------------------WoodPlat---------------------------------------------------
void updateWoodPlat()
{
    if(playerYW < heightW)
    {
        for ( size_t i=0 ; i<3 ; i++)
        {
            playerYW = heightW;
            woodPlats[i].y -= dy;
            if ( woodPlats[i].y > 700 )
            {
                woodPlats[i].y = -rand()%400;
                woodPlats[i].x = rand()%432;
            }
        }
    }

    for (size_t i=0; i<3 ; i++)
    {
        if((playerX + PLAYER_RIGHT_BOUNDING_BOX > woodPlats[i].x) && (playerX + PLAYER_LEFT_BOUNDING_BOX < woodPlats[i].x + woodPlat.getSize().x )
            && (playerYW + PLAYER_BOTTOM_BOUNDING_BOX > woodPlats[i].y) && (playerYW + PLAYER_BOTTOM_BOUNDING_BOX < woodPlats[i].y + woodPlat.getSize().y) && (dyw > 0))
        {
            woodPlats[i].y = -rand()%100;
            woodPlats[i].x = rand()%432;
            audioWood.play();
        }
    }
}
//--------------------------------------------------bluePlat--------------------------------------------------
void updateBluePlat()
{
    if(playerYB < heightB)
    {
        for ( size_t i=0 ; i<2 ; i++)
        {
            playerYB = heightB;
            bluePlats[i].y -= dy;
            if ( bluePlats[i].y > 700 )
            {
                bluePlats[i].y = 0;
                bluePlats[i].x = 0;
            }
            if ( bluePlats[i].x <= 0 )
                dir = 1;
            else if ( bluePlats[i].x + 60 >= 500 )
                dir = 0;

            if ( dir == 0 )
                bluePlats[i].x -= 2;
            else
                bluePlats[i].x += 2;
        }
    }

    for (size_t i=0; i<2 ; i++)
    {
        if((playerX + PLAYER_RIGHT_BOUNDING_BOX > bluePlats[i].x) && (playerX + PLAYER_LEFT_BOUNDING_BOX < bluePlats[i].x + bluePlat.getSize().x )
            && (playerYB + PLAYER_BOTTOM_BOUNDING_BOX > bluePlats[i].y) && (playerYB + PLAYER_BOTTOM_BOUNDING_BOX < bluePlats[i].y + bluePlat.getSize().y) && (dy > 0))
        {
            audioJump.play();
            dy = -9;
        }
    }
}
//-----------------------------------------------Projectiles-------------------------------------------------
void updateProjectiles()
{
    doodleCenter = Vector2f(doodle.getPosition().x + doodle.getGlobalBounds().width/2 , doodle.getPosition().y );

    if ( shootTimer < 5 )
        shootTimer++;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && shootTimer>=5)
    {
        projectile.setPosition(doodleCenter);
        projectiles.push_back(CircleShape(projectile));
        audioShoot.play();
        shootTimer = 0;
    }
    for (size_t i=0 ; i<projectiles.size() ; i++)
    {
        projectiles[i].move(0.f , -10.f);

        if (projectiles[i].getPosition().y <= 0 || (projectiles[i].getPosition().x + projectiles[i].getGlobalBounds().width >= window.getSize().x))
            projectiles.erase(projectiles.begin() + i);
    }
}
//---------------------------------------------Enemies------------------------------------------------
//Enemy 1
void updateEnemy1()
{
    if ( enemies.size() < maxEnemies )
    {
        if ( enemySpawnTimer1 >= enemySpawnTimerMax1 )
        {
            enemy1.setPosition((rand()% int(window.getSize().x - enemy1.getGlobalBounds().width)), -300);

            enemies.push_back(enemy1);
            audioMonster1.play();
            enemySpawnTimer1 = 0.f;
        }
        else
            enemySpawnTimer1 += 1.f;
    }
    //moving and updating enemies
    for ( size_t i=0 ; i < enemies.size() ; i++ )
    {
        enemies[i].move(0.f,2.f);

        if (enemies[i].getPosition().y > window.getSize().y)
        {
            enemies.erase(enemies.begin() + i);
        }
    }
}
//----------------------------------------------------Collision1-----------------------------------------------
void CollisionEnemy1WithDoodleAndPro()
{
    //Collision between projectiles and enemies
    for ( size_t i=0 ; i < projectiles.size() ; i++ )
    {
        for ( size_t k=0 ; k<enemies.size() ; k++ )
        {
            if( projectiles[i].getGlobalBounds().intersects(enemies[k].getGlobalBounds()))
            {
                projectiles.erase(projectiles.begin() + i);
                enemies.erase(enemies.begin() + k);
                audioMonster1.stop();
                killEnemyNum += 1;
                break;
            }
        }
    }
    //Collision between doodle and enemies
    for ( size_t i=0 ; i<enemies.size() ; i++ )
    {
        if ( doodle.getGlobalBounds().intersects(enemies[i].getGlobalBounds()))
        {
            gameOver = true;
            audioMonster1.stop();
        }

    }
}
//---------------------------------------------------Enemy 2---------------------------------------------
void updateEnemy2()
{
    if ( enemies2.size() < maxEnemies )
    {
        if ( enemySpawnTimer2 >= enemySpawnTimerMax2 )
        {
            enemy2.setPosition((rand()% int(window.getSize().x - enemy2.getGlobalBounds().width)), -360);

            enemies2.push_back(enemy2);
            audioMonster2.play();
            enemySpawnTimer2 = 0.f;
        }
        else
            enemySpawnTimer2 += 1.f;
    }
        //moving and updating enemies
    for ( size_t i=0 ; i < enemies2.size() ; i++ )
    {
        enemies2[i].move(0.f,3.f);

        if (enemies2[i].getPosition().y > window.getSize().y)
        {
            enemies2.erase(enemies2.begin() + i);
        }
    }
}
//--------------------------------------------------Collision2------------------------------------------------
void CollisionEnemy2WithDoodleAndPro()
{
    //Collision between projectiles and enemies
    for ( size_t i=0 ; i < projectiles.size() ; i++ )
    {
        for ( size_t k=0 ; k<enemies2.size() ; k++ )
        {
            if( projectiles[i].getGlobalBounds().intersects(enemies2[k].getGlobalBounds()))
            {
                projectiles.erase(projectiles.begin() + i);
                enemies2.erase(enemies2.begin() + k);
                audioMonster2.stop();
                killEnemyNum += 1;
                break;
            }
        }
    }
    //Collision between doodle and enemies
    for ( size_t i=0 ; i<enemies2.size() ; i++ )
    {
        if ( doodle.getGlobalBounds().intersects(enemies2[i].getGlobalBounds()))
        {
            gameOver = true;
            audioMonster2.stop();
        }
    }
}


#endif // GAME_H_INCLUDED


//class Game
//{
//private:
//    //variables
//    //window
//    sf::RenderWindow* window;
//    sf::VideoMode videoMode;
//    sf::Event event;
//
//    //Mouse Position
//    sf::Vector2i mousePosWindow;
//    sf::Vector2f mousePosView;
//    //Picture
//    sf::Texture platTex, backGroundTex, doodleTex;
//    sf::Sprite plat, backGround, doodle;
//    //Audio
//    sf::SoundBuffer bufferJump,bufferMonster1,bufferMonster2,bufferFall,bufferShoot, bufferWood;
//    sf::Sound audioJump,audioMonster1,audioMonster2,audioFall,audioShoot, audioWood;
//    //Font
//    sf::Font font;
//    //Text
//    sf::Text playText, gameName, gameOverText, scoreText, highScoreText, myName, pause;
//    //File
//    FILE *fp;
//    FILE *pf;
//    //game logic
//    bool firstStart = true , gameOver = false, firstStartGameOver = true,movePlats,click = false,startGame = false;
//    int dir, score = 0, highScore, Dir = 0;
//
//    //private function
//    void initWindow();
//    void initPictures();
//    void initAudio();
//    void initFont();
//    void initText();
//    void initHighScore();
//
//public:
//    Game();
//    virtual ~Game();
//
////    const bool running() const;
//
//    //functions
////    void pollEvents();
////    void updateMousePositionMenu();
//    void upDownDoodle();
//    void update();
//
//    void renderBackGround(sf::RenderTarget& window);
//    void renderPlayText(sf::RenderTarget& target);
//    void renderPlat(sf::RenderTarget& target);
//    void renderDoodle(sf::RenderTarget& target);
//    void renderGameName(sf::RenderTarget& target);
//    void renderHighScoreText(sf::RenderTarget& target);
//    void renderMyName(sf::RenderTarget& target);
//    void render();
//};
