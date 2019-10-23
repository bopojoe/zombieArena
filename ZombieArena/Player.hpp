//
//  Player.hpp
//  ZombieArena
//
//  Created by 20074556 on 16/10/2018.
//  Copyright © 2018 20074556. All rights reserved.
//

#ifndef Player_hpp
#define Player_hpp
#include <math.h> /*atan2*/
#include <SFML/Graphics.hpp>

using namespace sf;

class Player{
private:
    const float START_SPEED = 200;
    const float START_HEALTH = 100;
    
    //where is the player
    Vector2f m_Position;
    
    //player sprite
    Sprite m_Sprite;
    
    //player texture
    Texture m_Texture;
    
    //what is sceen res
    Vector2f m_Resolution;
    
    //how big is current areana
    IntRect m_Arena;
    
    //how big is each tile
    int m_TileSize;
    
    //which direction is the player currently moving
    bool m_UpPressed,m_DownPressed,m_LeftPressed,m_RightPressed;
    
    //how much health has the player
    int m_Health;
    
    //what isthe player max Health
    int m_MaxHealth;
    
    //when was the palyer last hit
    
    Time m_LastHit;
    
    //speed in pixels per second
    float m_Speed;
    
public:
    Player();
    
    void spawn(IntRect arena, Vector2f resolution, int tileSize);
    
    
    
    //called at the end of the game
    void resetPlayerStats();
    
    //Handle teh player getting hit
    bool hit(Time timeHit);
    
    //how long since player was hit
    Time getLastHitTime();
    
    //Where is the player?
    FloatRect getPosition();
    
    //Where is the center of the player?
    Vector2f getCenter();
    
    //which angle is the player facing
    float getRotation();
    
    //send copy of sprite to main
    Sprite getSprite();
    
    //how much health has the player currentlt got
    int getHealth();
    
    //move the player
    void moveLeft();
    void moveRight();
    void moveUp();
    void moveDown();
    
    //stop player moving in direction
    void stopLeft();
    void stopRight();
    void stopUp();
    void stopDown();
    
    //called every frame
    void update(float elapsedTime, Vector2i mousePosition);
    
    
    //give spped boost
    void upgradeSpeed();
    
    //give player some health
    void upgradeHealth();
    
    //increase max Health
    void increaseHealthLevel(int amount);
    
    

    
    

};


#endif /* Player_hpp */
