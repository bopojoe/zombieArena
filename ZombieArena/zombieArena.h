//
//  zombieArena.h
//  ZombieArena
//
//  Created by 20074556 on 06/11/2018.
//  Copyright © 2018 20074556. All rights reserved.
//


#ifndef zombieArena_h
#define zombieArena_h
#include "zombie.hpp"
using namespace sf;
int createBackground(VertexArray& rVA, IntRect arena);

Zombie* createHorde(int numZombies, IntRect arena);

#endif /* zombieArena_h */
