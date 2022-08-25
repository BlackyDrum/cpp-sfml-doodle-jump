#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <time.h>
#include <fstream>

const int pixelLength = 540, pixelHeight = 960;

class Game {
private:
    sf::Sprite player;
    sf::Texture playerModelRight;
    sf::Texture playerModelLeft;
    sf::Texture playerModelShoot;
    sf::IntRect playerRect;

    std::vector<sf::Sprite*> backgroundVector;
    sf::Texture background;
    sf::IntRect backgroundRect;

    sf::Sprite pauseBackground;
    sf::Texture tPauseBackground;

    sf::Sprite menuBackground;
    sf::Texture tmenuBackground;

    sf::Sprite gameOverBackground;
    sf::Texture tGameOverBackground;

    sf::Sprite optionsBackground;
    sf::Texture tOptionsBackground;

    std::vector<sf::Sprite*> tileVector;
    sf::Texture tileModel;
    sf::IntRect tileRect;

    sf::Sprite* shield;
    sf::IntRect shieldRect;
    sf::Sprite* shieldActivated;
    sf::IntRect shieldActivatedRect;
    sf::Texture shieldActivatedModel;

    sf::Sprite* federShoe;
    sf::IntRect federShoeRect;

    std::vector<sf::Sprite*> federVector;
    std::vector<sf::IntRect*> federRectVector;
    
    std::vector<sf::Sprite*> trampolineVector;
    std::vector<sf::IntRect*> trampolineRectVector;

    std::vector<sf::Sprite*> enemyVector;
    sf::IntRect enemyRect;

    std::vector<sf::Sprite*> brokenTileVector;
    std::vector<sf::IntRect*> brokenTileRectVector;
    std::vector<bool> checkBrokenTileVector;

    std::vector<sf::Sprite*> blackHoleVector;
    sf::Texture blackHole;
    sf::IntRect blackHoleRect;

    std::vector<sf::Sprite*> bubbleVector;
    sf::Texture bubble;

    sf::Sprite pauseButton;
    sf::Texture pauseButtonModel;

    sf::Sprite mouseBoundingBox;

    sf::Text score;
    sf::Text scoreForGameOver;
    sf::Text highscore;
    sf::Text displayName;
    sf::Font font;

    sf::Clock clockForTiles,clockForFeder,clockForTrampoline,clockForShield,clockForFederShoe, clockForBackground, clockForEnemy, clockForEnemy2, clockForBlackHole, clockForBubbles, clockForBrokenTiles,clockForBrokenTiles2, clockForBrokenTilesAnimation, clockForPause, clockForGameOver, clockForMenu;

    sf::View view, currentView;

    sf::Mouse mouse;

    sf::SoundBuffer lostBuffer;
    sf::Sound lostSound;
    sf::SoundBuffer jumpBuffer;
    sf::Sound jumpSound;
    sf::SoundBuffer breakBuffer;
    sf::Sound breakSound;
    sf::SoundBuffer shoot1Buffer, shoot2Buffer;
    sf::Sound shootSound;
    sf::SoundBuffer monsterBuffer;
    sf::Sound monsterSound;
    sf::SoundBuffer monsterDeathBuffer;
    sf::Sound monsterDeathSound;
    sf::SoundBuffer federBuffer;
    sf::Sound federSound;
    sf::SoundBuffer trampolineBuffer;
    sf::Sound trampolineSound;
    sf::SoundBuffer shieldBuffer;
    sf::Sound shieldSound;

    sf::Sprite soundOnButton;
    sf::Texture tSoundOnButton;

    sf::Sprite soundOffButton;
    sf::Texture tSoundOffButton;

    sf::Texture soundOnButtonPressed;
    sf::Texture soundOffButtonPressed;


    float yAccelerationDown, yAccelerationUp;
    bool isJumping, isFalling, isLost, isPause, isMenu,isSettings, isMoving, canMove, looksLeft, looksRight, isShooting, soundOn, playJumpSound;
    bool shieldIsActivated, federShoeIsActivated;
    float xVelocity, bubbleVelocity, enemyVelocity;
    int gapBetweenTiles, scoreInt, highscoreInt;
    
public:
    Game(sf::RenderWindow& win) : yAccelerationDown{ 0 }, xVelocity{ 6 }, enemyVelocity{ 10 }, yAccelerationUp{ 15 }, bubbleVelocity{ 20 }, scoreInt{ 0 }, highscoreInt{ 0 }, gapBetweenTiles{ 60 }, isFalling{ false }, shieldIsActivated{ false }, federShoeIsActivated{ false }, playJumpSound{ true }, soundOn{ true }, isSettings{ false }, isShooting{ false }, canMove{ true }, isJumping{ true }, isLost{ false }, isMenu{ true }, isMoving{ false }, isPause{ false }, looksRight{ true }, looksLeft{ false }, shield{ nullptr }, shieldActivated{ nullptr }, federShoe{ nullptr } {
        playerModelRight.loadFromFile("assets/blue-lik-right.png");
        playerModelRight.setSmooth(true);
        playerModelLeft.loadFromFile("assets/blue-lik-left.png");
        playerModelLeft.setSmooth(true);
        playerModelShoot.loadFromFile("assets/blue-lik-puca.png");
        playerModelShoot.setSmooth(true);

        playerRect.left = 0;
        playerRect.top = 0;
        playerRect.width = 62;
        playerRect.height = 60;
        player.setTexture(playerModelRight);
        player.setTextureRect(playerRect);
        player.setPosition(pixelLength / 2, 0);
        player.setScale(0.7, 0.7);

        currentView = win.getView();

        shieldRect.left = 234;
        shieldRect.top = 305;
        shieldRect.width = 35;
        shieldRect.height = 35;

        shieldActivatedModel.loadFromFile("assets/shield.png");
        shieldActivatedRect.left = 0;
        shieldActivatedRect.top = 0;
        shieldActivatedRect.width = 192;
        shieldActivatedRect.height = 192;

        background.loadFromFile("assets/background.png");
        backgroundRect.left = 0;
        backgroundRect.top = 0;
        backgroundRect.width = pixelLength;
        backgroundRect.height = pixelHeight;

        tileModel.loadFromFile("assets/game-tiles.png");
        tileRect.left = 0; 
        tileRect.top = 0;
        tileRect.width = 58;
        tileRect.height = 16;

        blackHole.loadFromFile("assets/hole.png");
        blackHoleRect.left = 0;
        blackHoleRect.top = 0;
        blackHoleRect.width = 148;
        blackHoleRect.height = 144;

        bubble.loadFromFile("assets/bubble.png");

        view.setCenter(pixelLength / 2, pixelHeight / 2);
        view.setSize(pixelLength, pixelHeight);

        font.loadFromFile("assets/DoodleJump.ttf");
        score.setString(std::to_string(scoreInt));
        score.setFont(font);
        score.setPosition(30, 300);
        score.setCharacterSize(40);
        score.setFillColor(sf::Color::Black);

        scoreForGameOver.setString(std::to_string(scoreInt));
        scoreForGameOver.setFont(font);
        scoreForGameOver.setPosition(400, 100);
        scoreForGameOver.setCharacterSize(40);
        scoreForGameOver.setFillColor(sf::Color::Black);

        highscore.setFont(font);
        highscore.setString(std::to_string(highscoreInt));
        highscore.setPosition(400, 100);
        highscore.setCharacterSize(40);
        highscore.setFillColor(sf::Color::Black);

        displayName.setFont(font);
        displayName.setString("BlackyDrum");
        displayName.setPosition(350, 100);
        displayName.setCharacterSize(40);
        displayName.setFillColor(sf::Color::Black);
        
        pauseButtonModel.loadFromFile("assets/pauseButton.png");
        pauseButton.setTexture(pauseButtonModel);
        pauseButton.setPosition(490, 490);

        tPauseBackground.loadFromFile("assets/pauseBackground v1.2.png");
        pauseBackground.setTexture(tPauseBackground);
        pauseBackground.setPosition(0, 0);

        tmenuBackground.loadFromFile("assets/menuBackground v1.2.png");
        menuBackground.setTexture(tmenuBackground);
        menuBackground.setPosition(0, 0);

        tGameOverBackground.loadFromFile("assets/gameOverBackground v1.1.png");
        gameOverBackground.setTexture(tGameOverBackground);
        gameOverBackground.setPosition(0, 0);

        tOptionsBackground.loadFromFile("assets/optionsBackground.png");
        optionsBackground.setTexture(tOptionsBackground);
        optionsBackground.setPosition(0, 0);

        soundOffButtonPressed.loadFromFile("assets/offButtonPressed.png");
        soundOnButtonPressed.loadFromFile("assets/onButtonPressed.png");

        tSoundOnButton.loadFromFile("assets/onButton.png");
        soundOnButton.setTexture(soundOnButtonPressed);
        soundOnButton.setPosition(240, 470);
        
        tSoundOffButton.loadFromFile("assets/offButton.png");
        soundOffButton.setTexture(tSoundOffButton);
        soundOffButton.setPosition(300, 470);

        lostBuffer.loadFromFile("sounds/lost.wav");
        lostSound.setBuffer(lostBuffer);
        lostSound.setVolume(10);

        jumpBuffer.loadFromFile("sounds/jump.wav");
        jumpSound.setBuffer(jumpBuffer);
        jumpSound.setVolume(10);     

        breakBuffer.loadFromFile("sounds/break.wav");
        breakSound.setBuffer(breakBuffer);
        breakSound.setVolume(10);

        shoot1Buffer.loadFromFile("sounds/shoot1.wav");
        shoot2Buffer.loadFromFile("sounds/shoot2.wav");
        shootSound.setBuffer(shoot1Buffer);
        shootSound.setVolume(10);

        monsterBuffer.loadFromFile("sounds/monster.wav");
        monsterSound.setBuffer(monsterBuffer);
        monsterSound.setVolume(10);

        monsterDeathBuffer.loadFromFile("sounds/monsterdeath.wav");
        monsterDeathSound.setBuffer(monsterDeathBuffer);
        monsterDeathSound.setVolume(10);

        federBuffer.loadFromFile("sounds/feder.wav");
        federSound.setBuffer(federBuffer);
        federSound.setVolume(10);

        trampolineBuffer.loadFromFile("sounds/trampoline.wav");
        trampolineSound.setBuffer(trampolineBuffer);
        trampolineSound.setVolume(10);

        shieldBuffer.loadFromFile("sounds/shield.wav");
        shieldSound.setBuffer(shieldBuffer);
        shieldSound.setVolume(10);
 
    }
    sf::Sprite getPlayer() const { return player; }
    sf::Sprite getPauseButton() const { return pauseButton; }
    sf::Sprite getPauseBackground() const { return pauseBackground; }
    sf::Sprite getMenuBackground() const { return menuBackground; }
    sf::Sprite getGameOverBackground() const { return gameOverBackground; }
    sf::Sprite getOptionsBackground() const { return optionsBackground; }
    sf::Sprite getSoundOnButton() const { return soundOnButton; }
    sf::Sprite getSoundOffButton() const { return soundOffButton; }

    sf::Sprite* getShield() const { return shield; }
    sf::Sprite* getActivatedShield() const { return shieldActivated; }  
    sf::Sprite* getFederShoe() const { return federShoe; }

    std::vector<sf::Sprite*> getTileVector() const { return tileVector; }
    std::vector<sf::Sprite*> getBackgroundVector() const { return backgroundVector; }
    std::vector<sf::Sprite*> getBlackHoleVector() const { return blackHoleVector; }
    std::vector<sf::Sprite*> getBubbleVector() const { return bubbleVector; }
    std::vector<sf::Sprite*> getBrokenTileVector() const { return brokenTileVector; }
    std::vector<sf::Sprite*> getEnemyVector() const { return enemyVector; }
    std::vector<sf::Sprite*> getFederVector() const { return federVector; }
    std::vector<sf::Sprite*> getTrampolineVector() const { return trampolineVector; }

    sf::View getView() const { return view; }
    sf::Text getScore() const { return score; }
    sf::Text getScoreForGameOver() const { return scoreForGameOver; }
    sf::Text getHighScore() const { return highscore; }
    sf::Text getDisplayName() const { return displayName; }

    bool getIsPause() const { return isPause; }
    bool getIsMenu() const { return isMenu; }
    bool getIsLost() const { return isLost; }
    bool getIsSettings() const { return isSettings; }

    ~Game();

    void loadSafetyTiles();
    void updateGameView(sf::RenderWindow&);
    void updateScore();
    void deleteAll();
    void updateMouse(sf::RenderWindow&);
    void updateAssets();
    void pause();
    void menu();
    void gravity();
    void checkIfLost();
    void checkBorderCollision();
    void checkBlackHoleCollision();
    void checkBrokenTileCollision();
    void checkFederCollision();
    void checkTrampolineCollision();
    void checkEnemyCollision();
    void addBackground();
    void deleteBackground();
    void addNewTiles();
    void deleteTiles();
    void addShield();
    void activateShield();
    void deleteActiveShield();
    void activateFederShoe();
    void updateShieldPosition();
    void updateShieldAnimation();
    void addBlackHole();
    void deleteBlackHole();
    void addEnemy();
    void deleteEnemy();
    void moveEnemy();
    void jump();
    void move();
    void shoot();
    void gameOver(sf::RenderWindow&);
    void breakTileAnimation();
    void drawGreenTiles(sf::RenderWindow&);
};
Game::~Game() {
    deleteAll();
}
void Game::deleteAll() {
    for (int i = 0; i < blackHoleVector.size(); i++) {
        delete blackHoleVector[i];
    }
    for (int i = 0; i < backgroundVector.size(); i++) {
        delete backgroundVector[i];
    }
    for (int i = 0; i < tileVector.size(); i++) {
        delete tileVector[i];
    }
    for (int i = 0; i < bubbleVector.size(); i++) {
        delete bubbleVector[i];
    }
    for (int i = 0; i < brokenTileRectVector.size(); i++) {
        delete brokenTileRectVector[i];
    }
    for (int i = 0; i < brokenTileVector.size(); i++) {
        delete brokenTileVector[i];
    }
    for (int i = 0; i < enemyVector.size(); i++) {
        delete enemyVector[i];
    }
    for (int i = 0; i < federVector.size(); i++) {
        delete federVector[i];
    }
    for (int i = 0; i < federRectVector.size(); i++) {
        delete federRectVector[i];
    }
    for (int i = 0; i < trampolineRectVector.size(); i++) {
        delete trampolineRectVector[i];
    }
    for (int i = 0; i < trampolineVector.size(); i++) {
        delete trampolineVector[i];
    }
    if (shield) {
        delete shield;
        shield = nullptr;
    }
    if (shieldIsActivated) {
        delete shieldActivated;
        shieldActivated = nullptr;
    }
    if (federShoe) {
        delete federShoe;
        federShoe = nullptr;
    }

}
void Game::updateAssets() {
    pauseButton.setPosition(currentView.getCenter().x + 230, currentView.getCenter().y - pixelHeight / 2 + 10);
    soundOnButton.setPosition(currentView.getCenter().x - 25, currentView.getCenter().y - 10);
    soundOffButton.setPosition(currentView.getCenter().x + 25, currentView.getCenter().y - 10);
    optionsBackground.setPosition(currentView.getCenter().x - (pixelLength / 2), currentView.getCenter().y - (pixelHeight / 2));
    menuBackground.setPosition(currentView.getCenter().x - (pixelLength / 2), currentView.getCenter().y - (pixelHeight / 2));
    pauseBackground.setPosition(currentView.getCenter().x - (pixelLength / 2), currentView.getCenter().y - (pixelHeight / 2));
    score.setPosition(25, currentView.getCenter().y - (pixelHeight / 2));
    scoreForGameOver.setPosition(currentView.getCenter().x + 110, currentView.getCenter().y - 160);
    highscore.setPosition(currentView.getCenter().x + 110, currentView.getCenter().y - 108);
    displayName.setPosition(currentView.getCenter().x + 78, currentView.getCenter().y - 75);
    gameOverBackground.setPosition(currentView.getCenter().x - (pixelLength / 2), currentView.getCenter().y - (pixelHeight / 2));
}
void Game::drawGreenTiles(sf::RenderWindow& window) {
    float viewY = currentView.getCenter().y - (pixelHeight / 2);
    for (int i = 0; i < tileVector.size(); i++) {
        if (tileVector[i]->getPosition().y > viewY - 100) {
            window.draw(*tileVector[i]);
        }
        else if (tileVector[i]->getPosition().y < viewY - 100)
            break;
    }
}
void Game::updateShieldAnimation() {
    if (!isLost) {
        if (shieldIsActivated) {
            if (shieldActivatedRect.left != 576) {
                shieldActivatedRect.left += 192;
            }
            else {
                shieldActivatedRect.left = 0;
            }
            shieldActivated->setTextureRect(shieldActivatedRect);
        }
    }
}
void Game::addShield() {
    if (clockForShield.getElapsedTime().asSeconds() > 45 && player.getPosition().y < scoreInt - 1 && !shieldIsActivated && !isLost) {
        if (shield)
            return;

        float rShieldPositionX = rand() % 450 + 50;
        sf::Sprite* newShield = new sf::Sprite;

        shield = newShield;
        shield->setTexture(tileModel);
        shield->setTextureRect(shieldRect);
        shield->setPosition(rShieldPositionX, player.getPosition().y - 550);

        for (int i = 0; i < blackHoleVector.size(); i++) {
            if (blackHoleVector[i]->getGlobalBounds().intersects(shield->getGlobalBounds())) {
                delete shield;
                shield = nullptr;
                return;
            }
        }
        clockForShield.restart();
    }
}
void Game::updateShieldPosition() {
    if (shieldActivated && !isLost) {
        shieldActivated->setPosition(player.getPosition().x - 8, player.getPosition().y);
    }
}
void Game::activateShield() {
    if (shield && shield->getGlobalBounds().intersects(player.getGlobalBounds()) && !shieldIsActivated && !isLost) {
        if (soundOn)
            shieldSound.play();
        delete shield;
        shield = nullptr;
        shieldIsActivated = true;

        sf::Sprite* newShieldActivated = new sf::Sprite;

        shieldActivated = newShieldActivated;
        shieldActivated->setTexture(shieldActivatedModel);
        shieldActivated->setTextureRect(shieldActivatedRect);
        shieldActivated->setPosition(player.getPosition().x - 8, player.getPosition().y);
        shieldActivated->setScale(0.3, 0.3);

        clockForShield.restart();
    }
}
void Game::deleteActiveShield() {
    for (int i = 0; i < enemyVector.size(); i++) {
        if (shieldIsActivated && enemyVector[i]->getGlobalBounds().intersects(player.getGlobalBounds())) {
            shieldIsActivated = false;
            delete enemyVector[i];
            enemyVector.erase(enemyVector.begin() + i);

            delete shieldActivated;
            shieldActivated = nullptr;

            monsterDeathSound.play();
            clockForShield.restart();
        }
    }
    if (clockForShield.getElapsedTime().asSeconds() > 30 && shieldIsActivated) {
        delete shieldActivated;
        shieldActivated = nullptr;

        shieldIsActivated = false;
        clockForShield.restart();
    }
}
void Game::addEnemy() {

    if (clockForEnemy.getElapsedTime().asSeconds() > 15 && player.getPosition().y < scoreInt - 1) {
        int rEnemyModel = rand() % 4 + 1;
        float rEnemyPositionX = rand() % 450 + 50;

        sf::Sprite* newEnemy = new sf::Sprite;
        newEnemy->setPosition(rEnemyPositionX, player.getPosition().y - 550);
        newEnemy->setTexture(tileModel);

        switch (rEnemyModel)
        {
        case 1:
            enemyRect.left = 148;
            enemyRect.top = 265;
            enemyRect.height = 36;
            enemyRect.width = 47;
            break;
        case 2:
            enemyRect.left = 336;
            enemyRect.top = 169;
            enemyRect.height = 50;
            enemyRect.width = 56;
            break;
        case 3:
            enemyRect.left = 512;
            enemyRect.top = 69;
            enemyRect.height = 55;
            enemyRect.width = 87;
            break;
        case 4:
            enemyRect.left = 282;
            enemyRect.top = 259;
            enemyRect.height = 81;
            enemyRect.width = 45;
            break;
        }
        newEnemy->setTextureRect(enemyRect);
  
        enemyVector.push_back(newEnemy);
        clockForEnemy.restart();
    }
}
void Game::moveEnemy() {
    for (int i = 0; i < enemyVector.size(); i++) {
        if (clockForEnemy2.getElapsedTime().asSeconds() > 0.2) {
            enemyVector[i]->setPosition(enemyVector[i]->getPosition().x + enemyVelocity, enemyVector[i]->getPosition().y);
            enemyVelocity *= -1;
            clockForEnemy2.restart();
        }
    }
}
void Game::deleteEnemy() {
    for (int i = 0; i < enemyVector.size(); i++) {
        for (int j = 0; j < bubbleVector.size(); j++) {
            if (bubbleVector[j]->getGlobalBounds().intersects(enemyVector[i]->getGlobalBounds())) {
                delete enemyVector[i];
                enemyVector.erase(enemyVector.begin() + i);
                if (soundOn)
                    monsterDeathSound.play();
                break;
            }         
        }
    }
    for (int i = 0; i < enemyVector.size(); i++) {
        if (enemyVector[i]->getPosition().y > player.getPosition().y + 500) {
            delete enemyVector[i];
            enemyVector.erase(enemyVector.begin() + i);
        }
    }  
}
void Game::checkEnemyCollision() {
    for (int i = 0; i < enemyVector.size(); i++) {
        if (enemyVector[i]->getGlobalBounds().intersects(player.getGlobalBounds()) && isFalling) {
            delete enemyVector[i];
            enemyVector.erase(enemyVector.begin() + i);
            yAccelerationUp = 15;
            isFalling = false;
            isJumping = true;
            if (soundOn)
                monsterDeathSound.play();
            break;
        }
        if (player.getGlobalBounds().intersects(enemyVector[i]->getGlobalBounds()) && !shieldIsActivated) {
            isLost = true;
            if (soundOn)
                lostSound.play();
            break;
        }
    }
}
void Game::loadSafetyTiles() {
    for (int i = 0; i < 3; i++) {
        sf::Sprite* newBackground = new sf::Sprite;
        newBackground->setTexture(background);
        newBackground->setTextureRect(backgroundRect);
        if (i == 0) {
            newBackground->setPosition(0, 500);
        }
        else {
            newBackground->setPosition(0, backgroundVector[i - 1]->getPosition().y - 500);
        }

        backgroundVector.push_back(newBackground);
    }

    for (int i = 0; i < 50; i++) {
        float rTilePositionX = rand() % (pixelLength - tileRect.width);

        sf::Sprite* newTile = new sf::Sprite;
        newTile->setTexture(tileModel);
        newTile->setTextureRect(tileRect);

        i != 0 ? newTile->setPosition(rTilePositionX, tileVector[i - 1]->getPosition().y - gapBetweenTiles) : newTile->setPosition(rTilePositionX, 0);

        tileVector.push_back(newTile);
    }
}
void Game::updateMouse(sf::RenderWindow& win) {
    mouseBoundingBox.setPosition(mouse.getPosition(win).x, mouse.getPosition(win).y);
    //std::cout << mouseBoundingBox.getPosition().x << " " << mouseBoundingBox.getPosition().y << std::endl;
}

void Game::menu() {
    if (isMenu && mouse.isButtonPressed(sf::Mouse::Left) && mouseBoundingBox.getPosition().x > 75 && mouseBoundingBox.getPosition().x < 300 && mouseBoundingBox.getPosition().y > 220 && mouseBoundingBox.getPosition().y < 300) {
        isMenu = false;
        canMove = true;
    }
    else if (isMenu && clockForMenu.getElapsedTime().asSeconds() > 0.5 && mouse.isButtonPressed(sf::Mouse::Left) && mouseBoundingBox.getPosition().x > 430 && mouseBoundingBox.getPosition().x < 500 && mouseBoundingBox.getPosition().y > 715 && mouseBoundingBox.getPosition().y < 790) {
        isSettings = true;
    }
    else if (isSettings && isMenu && mouse.isButtonPressed(sf::Mouse::Left) && mouseBoundingBox.getPosition().x > 280 && mouseBoundingBox.getPosition().x < 515 && mouseBoundingBox.getPosition().y > 815 && mouseBoundingBox.getPosition().y < 900) {
        isSettings = false;
    }
    if (isSettings) {
        if (mouse.isButtonPressed(sf::Mouse::Left) && mouseBoundingBox.getPosition().x > 240 && mouseBoundingBox.getPosition().x < 280 && mouseBoundingBox.getPosition().y > 450 && mouseBoundingBox.getPosition().y < 490) {
            soundOn = true;
            soundOnButton.setTexture(soundOnButtonPressed);
            soundOffButton.setTexture(tSoundOffButton);
        }
        else if (mouse.isButtonPressed(sf::Mouse::Left) && mouseBoundingBox.getPosition().x > 300 && mouseBoundingBox.getPosition().x < 360 && mouseBoundingBox.getPosition().y > 465 && mouseBoundingBox.getPosition().y < 500) {
            soundOn = false;
            soundOnButton.setTexture(tSoundOnButton);
            soundOffButton.setTexture(soundOffButtonPressed);
        }
    }
}
void Game::pause() {
    if (!isLost && mouse.isButtonPressed(sf::Mouse::Left) && mouseBoundingBox.getPosition().x > 490 && mouseBoundingBox.getPosition().x < 530 && mouseBoundingBox.getPosition().y > 5 && mouseBoundingBox.getPosition().y < 40 && clockForPause.getElapsedTime().asSeconds() > 0.2) {
        isPause = true;     
        clockForPause.restart();       
    }
    else if (mouse.isButtonPressed(sf::Mouse::Left) && isPause && clockForPause.getElapsedTime().asSeconds() > 0.2 && mouseBoundingBox.getPosition().x > 220 && mouseBoundingBox.getPosition().x < 450 && mouseBoundingBox.getPosition().y > 780 && mouseBoundingBox.getPosition().y < 870) {
        isPause = false;
        clockForPause.restart();
    }
}
void Game::updateScore() {
    if (scoreInt > player.getPosition().y) {
        scoreInt = player.getPosition().y;
    }
    score.setString(std::to_string(scoreInt * -1));
    highscore.setString(std::to_string(highscoreInt));
    scoreForGameOver.setString(std::to_string(scoreInt * -1));

    if (isLost) {
        std::ifstream highscoreFileRead("game/highscore.txt");
        std::string tmp = "", tmp2 = "0";
        if (highscoreFileRead.is_open()) {
            while (std::getline(highscoreFileRead, tmp)) {
                tmp2 = tmp;
            }
            highscoreFileRead.close();
        }
        std::ofstream highscoreFileWrite("game/highscore.txt");
        if (std::stoi(tmp2) < scoreInt * -1) {         
            highscoreFileWrite << scoreInt * -1 << std::endl;
            highscoreInt = scoreInt * -1;
        }
        else {
            highscoreFileWrite << std::stoi(tmp2);
            highscoreInt = std::stoi(tmp2);
        }
    }
}
void Game::breakTileAnimation() {
    for (int i = 0; i < checkBrokenTileVector.size(); i++) {
        if (!isLost && checkBrokenTileVector[i] && clockForBrokenTilesAnimation.getElapsedTime().asSeconds() > 0.1 && brokenTileRectVector[i]->top < 144 ) {
            brokenTileRectVector[i]->top += 8;
            
            switch (brokenTileRectVector[i]->top)
            {
            case 88:
                brokenTileRectVector[i]->height = 24;
                brokenTileVector[i]->setTextureRect(*(brokenTileRectVector[i]));
                clockForBrokenTilesAnimation.restart();
                break;
            case 112:
                brokenTileRectVector[i]->height = 34;
                brokenTileVector[i]->setTextureRect(*(brokenTileRectVector[i]));
                clockForBrokenTilesAnimation.restart();
                break;
            }      
        }
        if (!isLost && checkBrokenTileVector[i] ) {
            brokenTileVector[i]->setPosition(brokenTileVector[i]->getPosition().x, brokenTileVector[i]->getPosition().y + 5);
        }
    }
}
void Game::checkBrokenTileCollision() {
    for (int i = 0; i < brokenTileVector.size(); i++) {
        if (!isLost && player.getGlobalBounds().intersects(brokenTileVector[i]->getGlobalBounds()) && !isJumping ) {
            checkBrokenTileVector[i] = true;
            if (clockForBrokenTiles2.getElapsedTime().asSeconds() > 0.5 && soundOn) {
                breakSound.play();
                clockForBrokenTiles2.restart();
            }          
        }
    }
}
void Game::shoot() {
    if (!isLost && sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space) && clockForBubbles.getElapsedTime().asSeconds() > 0.1) {
        sf::Sprite* newBubble = new sf::Sprite;
        newBubble->setTexture(bubble);
        newBubble->setPosition(player.getPosition().x + 12, player.getPosition().y);

        bubbleVector.push_back(newBubble);
        player.setTexture(playerModelShoot);
        isShooting = true;
        int rShootingSound = rand() % 2 + 1;
        switch (rShootingSound)
        {
        case 1:
            shootSound.setBuffer(shoot1Buffer);
            break;
        case 2:
            shootSound.setBuffer(shoot2Buffer);
            break;  
        }
        if (soundOn)
            shootSound.play();
        clockForBubbles.restart();
    }
    else if (!isLost && clockForBubbles.getElapsedTime().asSeconds() > 0.3) {
        isShooting = false;
        if (looksLeft) {
            player.setTexture(playerModelLeft);
        }
        else {
            player.setTexture(playerModelRight);
        }
    }
    for (int i = 0; i < bubbleVector.size(); i++) {
        bubbleVector[i]->setPosition(bubbleVector[i]->getPosition().x, bubbleVector[i]->getPosition().y - bubbleVelocity);
    }
    for (int i = 0; i < bubbleVector.size(); i++) {
        if (bubbleVector[i]->getPosition().y + 500 < player.getPosition().y) {
            delete bubbleVector[i];
            bubbleVector.erase(bubbleVector.begin() + i);
        }
    }
}
void Game::gameOver(sf::RenderWindow& win) {

    if (isLost) {
        canMove = false; 
        if (shield) {
            delete shield;
            shield = nullptr;
        }
        if (shieldIsActivated) {
            delete shieldActivated;
            shieldActivated = nullptr;
        }
        if (federShoe) {
            delete federShoe;
            federShoe = nullptr;
        }
        if (mouse.isButtonPressed(sf::Mouse::Left) && mouseBoundingBox.getPosition().x > 190 && mouseBoundingBox.getPosition().x < 450 && mouseBoundingBox.getPosition().y > 560 && mouseBoundingBox.getPosition().y < 640 && clockForGameOver.getElapsedTime().asSeconds() > 1) {
            isLost = false;
            isMenu = false;
            canMove = true;
            player.setPosition(pixelLength / 2, 0);
            yAccelerationUp = 15;
            yAccelerationDown = 0;
            isJumping = true;
            shieldIsActivated = false;
            federShoeIsActivated = false;
            scoreInt = 0;
            
            deleteAll();
            lostSound.stop();
            
            blackHoleVector.resize(0);
            backgroundVector.resize(0);
            tileVector.resize(0);
            bubbleVector.resize(0);
            brokenTileRectVector.resize(0);
            brokenTileVector.resize(0);
            checkBrokenTileVector.resize(0);
            enemyVector.resize(0);
            federVector.resize(0);
            federRectVector.resize(0);
            trampolineRectVector.resize(0);
            trampolineVector.resize(0);

            clockForBlackHole.restart();
            clockForEnemy.restart();
            clockForTrampoline.restart();
            clockForShield.restart();
            clockForFederShoe.restart();
            

            loadSafetyTiles();
            clockForGameOver.restart();

        }
        else if (mouse.isButtonPressed(sf::Mouse::Left) && mouseBoundingBox.getPosition().x > 300 && mouseBoundingBox.getPosition().x < 530 && mouseBoundingBox.getPosition().y > 680 && mouseBoundingBox.getPosition().y < 770) {
            isLost = false;
            isMenu = true;
            clockForMenu.restart();
            canMove = false;
            player.setPosition(pixelLength / 2, 0);
            yAccelerationUp = 15;
            yAccelerationDown = 0;
            isJumping = true;
            shieldIsActivated = false;
            federShoeIsActivated = false;
            scoreInt = 0;

            deleteAll();
            lostSound.stop();

            blackHoleVector.resize(0);
            backgroundVector.resize(0);
            tileVector.resize(0);
            bubbleVector.resize(0);
            brokenTileRectVector.resize(0);
            brokenTileVector.resize(0);
            checkBrokenTileVector.resize(0);
            enemyVector.resize(0);
            federVector.resize(0);
            federRectVector.resize(0);
            trampolineRectVector.resize(0);
            trampolineVector.resize(0);

            clockForBlackHole.restart();
            clockForEnemy.restart();
            clockForTrampoline.restart();
            clockForShield.restart();
            clockForFederShoe.restart();

            loadSafetyTiles();
        }
    }
    
}
void Game::checkBlackHoleCollision() {
    for (int i = 0; i < blackHoleVector.size(); i++) {
        if (player.getGlobalBounds().intersects(blackHoleVector[i]->getGlobalBounds()) && !isLost && !shieldIsActivated) {
            isLost = true;
            if (soundOn)
                lostSound.play();
        }
    }
}
void Game::addBlackHole() {
    if (!isLost && clockForBlackHole.getElapsedTime().asSeconds() > 50 ) {
        int rBlackHolePositionX = rand() % (pixelLength - tileRect.width);
        sf::Sprite* newBlackHole = new sf::Sprite;

        newBlackHole->setTexture(blackHole);
        newBlackHole->setTextureRect(blackHoleRect);
        newBlackHole->setPosition(rBlackHolePositionX, player.getPosition().y - 800);

        for (int i = 0; i < tileVector.size(); i++) {
            if (newBlackHole->getGlobalBounds().intersects(tileVector[i]->getGlobalBounds())) {
                delete newBlackHole;
                return;
            }
        }
        blackHoleVector.push_back(newBlackHole);
        clockForBlackHole.restart();
    }
}
void Game::deleteBlackHole() {
    for (int i = 0; i < blackHoleVector.size(); i++) {
        if (!isLost && player.getPosition().y < blackHoleVector[i]->getPosition().y - 600) {
            delete blackHoleVector[i];
            blackHoleVector.erase(blackHoleVector.begin() + i);
        }
    }
}
void Game::checkBorderCollision() {
    if (player.getPosition().x < -playerRect.width && !isLost) {
        player.setPosition(pixelLength, player.getPosition().y);
    }
    if (player.getPosition().x > pixelLength && !isLost) {
        player.setPosition(-playerRect.width, player.getPosition().y);
    }
}
void Game::deleteBackground() {
    for (int i = 0; i < backgroundVector.size(); i++) {
        if (!isLost && player.getPosition().y < backgroundVector[i]->getPosition().y - 500 ) {
            delete backgroundVector[i];
            backgroundVector.erase(backgroundVector.begin() + i);
        }
    }
}
void Game::addBackground() {
    if (!isLost && player.getPosition().y < backgroundVector[backgroundVector.size() - 1]->getPosition().y + 800 && clockForBackground.getElapsedTime().asSeconds() > 0.2 ) {
        sf::Sprite* newBackground = new sf::Sprite;
        newBackground->setTexture(background);
        newBackground->setTextureRect(backgroundRect);
        newBackground->setPosition(0, backgroundVector[backgroundVector.size() - 1]->getPosition().y - 500);

        backgroundVector.push_back(newBackground);
        clockForBackground.restart();
    }
    
}
void Game::deleteTiles() {   
    for (int i = 0; i < tileVector.size(); i++ ) {
        if (!isLost && player.getPosition().y < tileVector[i]->getPosition().y - 500 ) {
            delete tileVector[i];
            tileVector.erase(tileVector.begin() + i);
        }
    }
    for (int i = 0; i < brokenTileVector.size(); i++) {
        if (!isLost && player.getPosition().y < brokenTileVector[i]->getPosition().y - 500) {
            delete brokenTileVector[i];
            delete brokenTileRectVector[i];
            brokenTileVector.erase(brokenTileVector.begin() + i);
            brokenTileRectVector.erase(brokenTileRectVector.begin() + i);
            checkBrokenTileVector.erase(checkBrokenTileVector.begin() + i);
        }
    }
    for (int i = 0; i < federVector.size(); i++) {
        if (!isLost && player.getPosition().y < federVector[i]->getPosition().y - 500) {
            delete federVector[i];
            delete federRectVector[i];
            federVector.erase(federVector.begin() + i);
            federRectVector.erase(federRectVector.begin() + i);
        }
    }
    for (int i = 0; i < trampolineVector.size(); i++) {
        if (!isLost && player.getPosition().y < trampolineVector[i]->getPosition().y - 500) {
            delete trampolineVector[i];
            delete trampolineRectVector[i];
            trampolineVector.erase(trampolineVector.begin() + i);
            trampolineRectVector.erase(trampolineRectVector.begin() + i);
        }
    }
    if (!isLost && shield && player.getPosition().y < shield->getPosition().y - 500) {
        delete shield;
        shield = nullptr;
    }
    if (!isLost && federShoe && player.getPosition().y < federShoe->getPosition().y - 500) {
        delete federShoe;
        federShoe = nullptr;
    }
}
void Game::checkIfLost() {
    if (player.getPosition().y > tileVector[0]->getPosition().y + 200 && !isLost) {
        isLost = true;
        if (soundOn)
            lostSound.play();
    }
}
void Game::updateGameView(sf::RenderWindow& win) {
    if (!isLost)
        view.setCenter(pixelLength / 2, player.getPosition().y);
    currentView = win.getView();
}
void Game::move() {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A) && canMove) {
        player.setPosition(player.getPosition().x - xVelocity, player.getPosition().y);
        isMoving = true;
        looksLeft = true;
        looksRight = false;
        if (!isShooting)
            player.setTexture(playerModelLeft);
    }
    else isMoving = false;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D) && canMove) {
        player.setPosition(player.getPosition().x + xVelocity, player.getPosition().y);
        isMoving = true;
        looksLeft = false;
        looksRight = true;
        if (!isShooting)
            player.setTexture(playerModelRight);
    }
    else isMoving = false;
}
void Game::jump() {
    if (isJumping && !isLost) {
        player.setPosition(player.getPosition().x, player.getPosition().y - yAccelerationUp);
        yAccelerationUp -= 0.5;    
        
        if (yAccelerationUp <= 0) {
            isJumping = false;
            isFalling = true;
            playJumpSound = true;
            if (!federShoeIsActivated)
            yAccelerationUp = 15;
        }
    }
}
void Game::checkFederCollision() {
    for (int i = 0; i < federVector.size(); i++) {
        if (!isJumping && !federShoeIsActivated && federVector[i]->getGlobalBounds().intersects(player.getGlobalBounds())) {
            federRectVector[i]->top = 114;
            federRectVector[i]->height = 29;
            federVector[i]->setTextureRect(*(federRectVector[i]));
            federVector[i]->setPosition(federVector[i]->getPosition().x, federVector[i]->getPosition().y - 5);
            if (soundOn)
                federSound.play();
            yAccelerationUp = 25;
        }
    }
}
void Game::checkTrampolineCollision() {
    for (int i = 0; i < trampolineVector.size(); i++) {
        if (!isJumping && !federShoeIsActivated && player.getGlobalBounds().intersects(trampolineVector[i]->getGlobalBounds())) {
            trampolineRectVector[i]->left = 148;
            trampolineRectVector[i]->top = 93;
            trampolineRectVector[i]->height = 19;
            trampolineVector[i]->setTextureRect(*(trampolineRectVector[i]));
            if (soundOn)
                trampolineSound.play();
            yAccelerationUp = 30;
        }
    }
}
void Game::activateFederShoe() {
    if (!isLost && federShoe && player.getGlobalBounds().intersects(federShoe->getGlobalBounds()) && !federShoeIsActivated) {
        federShoeIsActivated = true;
        federShoe->setScale(0.8, 0.8);
        clockForFederShoe.restart();
    }
    if (!isLost && federShoeIsActivated && clockForFederShoe.getElapsedTime().asSeconds() < 15) {
        federShoe->setPosition(player.getPosition().x + 10, player.getPosition().y + 30);
        for (int i = 0; i < tileVector.size(); i++) {
            if (!isJumping && federShoe&& tileVector[i]->getGlobalBounds().intersects(player.getGlobalBounds())) {
                yAccelerationUp = 25;
                if (soundOn)
                    federSound.play();
                break;
            }
        }
    }
    else if (federShoeIsActivated && federShoe && !isLost) {
        delete federShoe;
        federShoe = nullptr;
        federShoeIsActivated = false;
    }
}
void Game::addNewTiles() {
    if (!isLost && clockForTiles.getElapsedTime().asSeconds() > 0.1 && player.getPosition().y < scoreInt + 10) {
        float rTilePositionX = rand() % (pixelLength - tileRect.width);

        sf::Sprite* newTile = new sf::Sprite;
        newTile->setTexture(tileModel);
        newTile->setTextureRect(tileRect);
        newTile->setPosition(rTilePositionX, tileVector[tileVector.size() - 1]->getPosition().y - gapBetweenTiles);

        tileVector.push_back(newTile);

        if (clockForFeder.getElapsedTime().asSeconds() > 2) {
            sf::Sprite* newFeder = new sf::Sprite;
            sf::IntRect* newRect = new sf::IntRect;

            newRect->left = 403;
            newRect->top = 98;
            newRect->width = 18;
            newRect->height = 13;

            newFeder->setPosition(newTile->getPosition().x + 16, newTile->getPosition().y - 12);
            newFeder->setTextureRect(*newRect);
            newFeder->setTexture(tileModel);

            federVector.push_back(newFeder);
            federRectVector.push_back(newRect);
            clockForFeder.restart();
        }
        if (clockForFederShoe.getElapsedTime().asSeconds() > 30 && !federShoeIsActivated && !federShoe) {
            sf::Sprite* newFederShoe = new sf::Sprite;

            federShoeRect.left = 300;
            federShoeRect.top = 204;
            federShoeRect.height = 22;
            federShoeRect.width = 29;
            federShoe = newFederShoe;

            federShoe->setTexture(tileModel);
            federShoe->setTextureRect(federShoeRect);
            federShoe->setPosition(newTile->getPosition().x + 16, newTile->getPosition().y - 17);

            for (int i = 0; i < federVector.size(); i++) {
                if (federShoe && federVector[i]->getGlobalBounds().intersects(federShoe->getGlobalBounds())) {
                    delete federShoe;
                    federShoe = nullptr;
                    break;
                }

            }
            clockForFederShoe.restart();
        }
        if (clockForTrampoline.getElapsedTime().asSeconds() > 15) {
            sf::Sprite* newTrampoline = new sf::Sprite;
            sf::IntRect* newRect = new sf::IntRect;

            newRect->left = 187;
            newRect->top = 97;
            newRect->width = 37;
            newRect->height = 15;

            newTrampoline->setPosition(newTile->getPosition().x + 12, newTile->getPosition().y - 13);
            newTrampoline->setTextureRect(*newRect);
            newTrampoline->setTexture(tileModel);

            bool tmp = true;
            for (int i = 0; i < federVector.size(); i++) {
                if (federVector[i]->getGlobalBounds().intersects(newTrampoline->getGlobalBounds())) {
                    delete newRect;
                    delete newTrampoline;
                    tmp = false;
                }
            }
            if (federShoe && tmp && newTrampoline->getGlobalBounds().intersects(federShoe->getGlobalBounds())) {
                delete newTrampoline;
                delete newRect;
                tmp = false;
            }
            
            if (tmp) {
                trampolineRectVector.push_back(newRect);
                trampolineVector.push_back(newTrampoline);
                clockForTrampoline.restart();
            }
            
        }
        clockForTiles.restart();
    }
    if (!isLost && clockForBrokenTiles.getElapsedTime().asSeconds() > 1.5  && player.getPosition().y < scoreInt - 1) {
        float rTilePositionX = rand() % (pixelLength - tileRect.width);
        int rTilePositionY = rand() % 200 + 700;

        sf::Sprite* newBrokenTile = new sf::Sprite;
        sf::IntRect* newBrokenTileRect = new sf::IntRect;
          
        newBrokenTileRect->left = 0;
        newBrokenTileRect->width = 61;
        newBrokenTileRect->height = 16;
        newBrokenTileRect->top = 72;

        newBrokenTile->setTexture(tileModel);
        newBrokenTile->setTextureRect(*newBrokenTileRect);
        newBrokenTile->setPosition(rTilePositionX, player.getPosition().y - rTilePositionY);

        for (int i = 0; i < tileVector.size(); i++) {
            if (tileVector[i]->getGlobalBounds().intersects(newBrokenTile->getGlobalBounds())) {
                delete newBrokenTile;
                delete newBrokenTileRect;
                return;
            }
        }
        for (int i = 0; i < blackHoleVector.size(); i++) {
            if (blackHoleVector[i]->getGlobalBounds().intersects(newBrokenTile->getGlobalBounds())) {
                delete newBrokenTile;
                delete newBrokenTileRect;
                return;
            }
        }
        brokenTileVector.push_back(newBrokenTile);
        brokenTileRectVector.push_back(newBrokenTileRect);
        checkBrokenTileVector.push_back(false);

        clockForBrokenTiles.restart();
    }

}
void Game::gravity() {
    for (int i = 0; i < tileVector.size(); i++) {
        if (isLost || !tileVector[i]->getGlobalBounds().intersects(player.getGlobalBounds()) && !isJumping) {
            player.setPosition(player.getPosition().x, player.getPosition().y + yAccelerationDown);
            yAccelerationDown += 0.55;
            isFalling = true;
            break;
        }
        else if (!isLost) {
            yAccelerationDown = 0;
            isFalling = false;
            isJumping = true;
            if (playJumpSound && soundOn && !federShoeIsActivated) {
                jumpSound.play();
                playJumpSound = false;
            }
        }

    }
    for (int i = 0; i < tileVector.size(); i++) {
        if (!isLost && tileVector[i]->getGlobalBounds().intersects(player.getGlobalBounds())) {
            yAccelerationDown = 0;
            isFalling = false;
            isJumping = true;
            break;
        }
    }
}

int main()
{

    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

    sf::RenderWindow window(sf::VideoMode(540, 960), "Doodle Jump!");
    window.setFramerateLimit(60);
    srand(time(NULL));
    Game game(window);
    game.loadSafetyTiles();

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        game.updateMouse(window);
        game.menu();
        game.pause();
        game.gameOver(window);

        if (!game.getIsPause() && !game.getIsMenu() ) {

            window.setView(game.getView());
            game.updateGameView(window);
            game.checkIfLost();
            game.checkBlackHoleCollision();
            
            game.checkEnemyCollision();
            game.checkBorderCollision();
            game.checkBrokenTileCollision();
            
            game.checkTrampolineCollision();
            game.addEnemy();
            game.addNewTiles();
            game.addShield();
            game.activateShield();
            game.updateShieldAnimation();
            game.deleteActiveShield();
            
            
            game.updateScore();
            game.updateAssets();

            game.addEnemy();
            game.deleteEnemy();
            game.breakTileAnimation();
            game.addBackground();
            game.deleteBackground();
            
            game.deleteTiles();
            game.addBlackHole();
            game.deleteBlackHole();
            game.gravity();
            game.moveEnemy();
            game.jump();
            game.shoot();
            game.move();
            game.checkFederCollision();
            game.updateShieldPosition();
            game.activateFederShoe();

        }
        window.clear();

        std::vector<sf::Sprite*> tileVector = game.getTileVector();
        std::vector<sf::Sprite*> backgroundVector = game.getBackgroundVector();
        std::vector<sf::Sprite*> blackHoleVector = game.getBlackHoleVector();
        std::vector<sf::Sprite*> bubbleVector = game.getBubbleVector();
        std::vector<sf::Sprite*> brokenTileVector = game.getBrokenTileVector();
        std::vector<sf::Sprite*> enemyVector = game.getEnemyVector();
        std::vector<sf::Sprite*> federVector = game.getFederVector();
        std::vector<sf::Sprite*> trampolineVector = game.getTrampolineVector();

        for (int i = 0; i < backgroundVector.size(); i++) {
            window.draw((*backgroundVector[i]));
        }
        for (int i = 0; i < blackHoleVector.size(); i++) {
            window.draw((*blackHoleVector[i]));
        }
        for (int i = 0; i < federVector.size(); i++) {
            window.draw(*(federVector[i]));
        }
        /*for (int i = 0; i < tileVector.size(); i++) {
            window.draw(*(tileVector[i]));
        } */     
        game.drawGreenTiles(window);
        for (int i = 0; i < trampolineVector.size(); i++) {
            window.draw(*(trampolineVector[i]));
        }
        for (int i = 0; i < brokenTileVector.size(); i++) {
            window.draw(*(brokenTileVector[i]));
        }
        for (int i = 0; i < bubbleVector.size(); i++) {
            window.draw((*bubbleVector[i]));
        }
        for (int i = 0; i < enemyVector.size(); i++) {
            window.draw(*(enemyVector[i]));
        }
        window.draw(game.getPauseButton());
        window.draw(game.getScore());
        
        if (game.getIsLost()) {
            window.draw(game.getGameOverBackground());
            window.draw(game.getHighScore());
            window.draw(game.getScoreForGameOver());
            window.draw(game.getDisplayName());
        }
       
        window.draw(game.getPlayer());

        if (game.getShield())
            window.draw(*(game.getShield()));
        if (game.getActivatedShield())
            window.draw(*(game.getActivatedShield()));
        if (game.getFederShoe()) {
            window.draw(*(game.getFederShoe()));
        }

        if (game.getIsPause()) {
            window.draw(game.getPauseBackground());
        }
        
        if (game.getIsMenu() && !game.getIsSettings()) {
            window.draw(game.getMenuBackground());
        }
        if (game.getIsMenu() && game.getIsSettings()) {
            window.draw(game.getOptionsBackground());
            window.draw(game.getSoundOffButton());
            window.draw(game.getSoundOnButton());
        }
               
        window.display();

    }

    return 0;
}