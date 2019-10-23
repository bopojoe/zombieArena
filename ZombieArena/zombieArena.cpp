#include <SFML/Graphics.hpp>
#include "Player.hpp"
#include "zombieArena.h"
#include "textureHolder.hpp"
#include "bullet.hpp"
#include "zombie.hpp"
#include "pickup.hpp"
using namespace sf;

int main()
{
    TextureHolder holder;
    //the game will always be in one state
    enum class State {PAUSED, LEVELING_UP, GAME_OVER, PLAYING};
    
    //start with the game over state
    State state = State::GAME_OVER;
    
    //get the screen res and create window
    Vector2f resolution;
    resolution.x = VideoMode::getDesktopMode().width;
    resolution.y = VideoMode::getDesktopMode().height;
    RenderWindow window(VideoMode(resolution.x,resolution.y), "Zombie Arena", Style::Fullscreen);
    
    //create a an sfml view for the main action
    View mainView(sf::FloatRect(0,0,resolution.x,resolution.y));
    
    //clock to tine everything
    Clock clock;
    
    //how long has the playing been active
    Time gameTimeTotal;
    
    //where is the mouse in relation to world coordinates
    Vector2f mouseWorldPosition;
    
    //where is the mouse in relation to scereen coordinates
    Vector2i mouseScreenPosition;
    
    //creates player
    Player player;
    
    //the boundries of the arena
    IntRect arena;
    
    //create the background
    VertexArray background;
    
    //load the texture
    Texture textureBackground;
    textureBackground.loadFromFile("../Resources/graphics/background_sheet.png");
    
    //prepare for a horde of zombies
    int numZombies = 0;
    int numZombiesAlive = 0;
    Zombie* zombies = nullptr;
    
    //100 bullets should do
    Bullet bullets[100];
    int currentBullet = 0;
    int bulletsSpare = 24;
    int bulletsInClip = 6;
    int clipSize = 6;
    float fireRate =  1;
    //when was the fire button last pressed
    Time lastPressed;
    
    //hide and replace the mouse pointer
    window.setMouseCursorVisible(false);
    Sprite spriteCrosshair;
    Texture textureCrosshair = TextureHolder::GetTexture("../Resources/graphics/crosshair.png");
    spriteCrosshair.setTexture(textureCrosshair);
    spriteCrosshair.setOrigin(25, 25);
    //Pickups
    Pickup healthPickup(1);
    Pickup ammoPickup(2);
    
    
    
    /**********************************
     ********************************
     ********************************/
    
    //the main game loop
    /**************************
     **************************
     ************************/
    while(window.isOpen()){
        
        /*
         ***************
         
         Handle input
         
         ***************/
        //handle events
        
        Event event;
        
        while(window.pollEvent(event)){
            if(event.type==Event::KeyPressed){
                //pause the game while playing
                if (event.key.code == Keyboard::Return && state==State::PLAYING) {
                    state = State::PAUSED;
                }else if (event.key.code==Keyboard::Return && state==State::PAUSED){
                    state =State::PLAYING;
                    
                    //reset the clock no frame jumps
                    clock.restart();
                    //start new game while in game over state
                }else if (event.key.code==Keyboard::Return && state==State::GAME_OVER){
                    state = State::LEVELING_UP;
                }
                
                if (state == State::PLAYING) {
                    //reloading
                    if (event.key.code == Keyboard::R) {
                        if (bulletsSpare>=clipSize) {
                            //plenty of bullets. reload
                            bulletsInClip = clipSize;
                            bulletsSpare-=clipSize;
                        }
                    }else if(bulletsSpare>0){
                        //only a few left
                        bulletsInClip = bulletsSpare;
                        bulletsSpare = 0;
                        
                    }else{
                        //more here later
                    }
                }
                
            }//end  if(event.type==Event::KeyPressed)
        }//end pollEvent
        
        //Handle the player Quitting
        if (Keyboard::isKeyPressed(Keyboard::Escape)) {
            window.close();
        }
        
        /***********************************
         **  Handle input while playing  ***
         ***********************************/
        if (state == State::PLAYING) {
            
            //handle the wasd keys
            if (Keyboard::isKeyPressed(Keyboard::W)) {
                player.moveUp();
            }else{
                player.stopUp();
            }
            
            if (Keyboard::isKeyPressed(Keyboard::S)) {
                player.moveDown();
            }else{
                player.stopDown();
            }
            
            if (Keyboard::isKeyPressed(Keyboard::A)) {
                player.moveLeft();
            }else{
                player.stopLeft();
            }
            
            
            if (Keyboard::isKeyPressed(Keyboard::D)) {
                player.moveRight();
            }else{
                player.stopRight();
            }
            
            if(sf::Mouse::isButtonPressed(sf::Mouse::Left)){
                if (gameTimeTotal.asMilliseconds()-lastPressed.asMilliseconds()>1000/fireRate&&bulletsInClip>0) {
                    //get center of char and crosshair
                    
                    bullets[currentBullet].shoot(player.getCenter().x, player.getCenter().y, mouseWorldPosition.x, mouseWorldPosition.y - resolution.y);
                    currentBullet++;
                    if (currentBullet>99) {
                        currentBullet = 0;
                    }
                    lastPressed=gameTimeTotal;
                    bulletsInClip--;
                }
            }//end of fire a bullet
            
        
            
        
        }// end wasd while playing
        
        /***********************************************
         **        Levelling up State              **
         ***********************************************/
        
        if (state == State::LEVELING_UP) {
            
            //handle the player leveling up
            if (event.key.code == Keyboard::Num1) {
                state = State::PLAYING;
            }
            
            if (event.key.code == Keyboard::Num2) {
                state = State::PLAYING;
            }
            if (event.key.code == Keyboard::Num3) {
                state = State::PLAYING;
            }
            if (event.key.code == Keyboard::Num4) {
                state = State::PLAYING;
            }
            if (event.key.code == Keyboard::Num5) {
                state = State::PLAYING;
            }
            if (event.key.code == Keyboard::Num6) {
                state = State::PLAYING;
            }
            
            if (state == State::PLAYING) {
                //Prepare the level -- updated later
                arena.width = 500;
                arena.height = 500;
                arena.left = 0;
                arena.top = 0;
                
                //int tileSize = 50; //updated later
                
                int tileSize = createBackground(background, arena);
                
                //Spawn teh player in the middle of the arena
                player.spawn(arena, resolution, tileSize);
                
                healthPickup.setArena(arena);
                ammoPickup.setArena(arena);
                
                
                //create a horde of zombies
                numZombies = 10;
                //Delete the previous allocated memory(if it exists)
                delete [] zombies;
                zombies = createHorde(numZombies, arena);
                numZombiesAlive = numZombies;
                
                
                //reset the clock so no frame jump
                clock.restart();
            }
            
        }//end leveling up
        
        /*************************************************
         *****      update the frame /scene       *******
         ***********************************************/
        
        if (state == State::PLAYING) {
            //update the dt Clock
            Time dt = clock.restart();
            //update the total game time
            gameTimeTotal += dt;
            //Make a decimal fraction of 1 from the delta time
            float dtAsSeconds = dt.asSeconds();
            
            //find the mouse pointer
            mouseScreenPosition = Mouse::getPosition(window);
            
            //convert the mouse pos toworld coords
            mouseWorldPosition = window.mapPixelToCoords(Mouse::getPosition(), mainView);
            spriteCrosshair.setPosition(mouseWorldPosition.x, mouseWorldPosition.y-resolution.y);
            
            //update the player
            player.update(dtAsSeconds, Mouse::getPosition());
            
            //make a note of teh players new pos
            Vector2f playerPosition(player.getCenter());
            
            //make the view center around the player
            
            mainView.setCenter(player.getCenter());
            
            //loop through each Zombie and update them if alive
            for (int i  = 0; i<numZombies; i++) {
                if (zombies[i].isAlive()) {
                    zombies[i].update(dt.asSeconds(), playerPosition);
                }
            }
            
            for(int i  =0; i<100; i++){
                if (bullets[i].isInFlight()) {
                    bullets[i].update(dtAsSeconds);
                }
            }
            healthPickup.update(dtAsSeconds);
            ammoPickup.update(dtAsSeconds);
            
        }//end update scene
        
        
        /***********************************************
         ****            Draw the Scene             ****
         *************************************************/
        
        if (state == State::PLAYING) {
            window.clear();
            
            //set the mainview to be disabled
            //and draw everything related
            window.setView(mainView);
            
            window.draw(background,&textureBackground);
            
            for (int i = 0; i<numZombies; i++) {
                window.draw(zombies[i].getSprite());
            }
            
            for (int i = 0; i<100; i++) {
                if (bullets[i].isInFlight()) {
                    window.draw(bullets[i].getShape());
                }
            }
            window.draw(spriteCrosshair);
            
            //Draw the Pick-ups, ifcurrently spawned
            if(ammoPickup.isSpawned()){
                window.draw(ammoPickup.getSprite());
            }

            //draw the player
            window.draw(player.getSprite());
            
            
        }
        
        if (state == State::LEVELING_UP) {
            
        }
        
        if (state == State::LEVELING_UP) {
           
        }
        
        if (state == State::PAUSED) {
            
        }
        
        if (state == State::GAME_OVER) {
            
        }
        
        window.display();
 
         }
    
    
    delete[] zombies;
    return 0;
    
}
