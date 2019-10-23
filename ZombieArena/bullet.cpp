//
//  bullet.cpp
//  ZombieArena
//
//  Created by 20074556 on 27/11/2018.
//  Copyright © 2018 20074556. All rights reserved.
//

//#include "stdafx.h" <- Visual Studio only
#include "bullet.hpp"

// The constructor
Bullet::Bullet()
{
    m_BulletShape.setSize(Vector2f(2, 2));
}

void Bullet::shoot(float startX, float startY,
                   float targetX, float targetY)
{
    
    // TO BE COMPLETED IN THIS CLASS
    //keep track of the bullet
    m_InFlight = true;
    m_Position.x = startX;
    m_Position.y = startY;
    
    // Calculate the gradient of the flight path
    float gradient = (startX -targetX)/ (startY - targetY);
    
    //any gradient less than zero needs to be positive
    if(gradient<0){
        gradient *= -1;
    }
    
    //Calculate teh ratio between x and y
    float ratioXY = m_BulletSpeed/(1+gradient);
    
    //set the speed hor and ver
    m_BulletDistanceY = ratioXY;
    m_BulletDistanceX = ratioXY *gradient;
    
    // Point the bullet in the right dir
    if (targetX<startX) {
        m_BulletDistanceX *= -1;
    }
    
    if (targetY<startY) {
        m_BulletDistanceY*=-1;
    }
    
    //set max range of 1000 pix
    float range = 1000;
    m_MinX = startX-range;
    m_MaxX = startX+range;
    m_MinY = startY-range;
    m_MaxY = startY+range;
    
    //position the bullet ready to be drawn
    m_BulletShape.setPosition(m_Position);
    
    
    
}

void Bullet::stop()
{
    m_InFlight = false;
}

bool Bullet::isInFlight()
{
    return m_InFlight;
}

FloatRect Bullet::getPosition()
{
    return m_BulletShape.getGlobalBounds();
}

RectangleShape Bullet::getShape()
{
    return m_BulletShape;
}


void Bullet::update(float elapsedTime)
{
    
    // TO BE COMPLETED IN THIS CLASS
    //update the bullet position vars
    m_Position.x += m_BulletDistanceX * elapsedTime;
    m_Position.y += m_BulletDistanceY * elapsedTime;
    
    //move te bullet
    m_BulletShape.setPosition(m_Position);
    
    //has the bullet gone out of range
    if (m_Position.x< m_MinX ||m_Position.x>m_MaxX||m_Position.y< m_MinY ||m_Position.y>m_MaxY) {
        m_InFlight = false;
    }
    
    
    
}
