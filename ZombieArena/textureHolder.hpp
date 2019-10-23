//
//  textureHolder.cpp
//  ZombieArena
//
//  Created by 20074556 on 13/11/2018.
//  Copyright © 2018 20074556. All rights reserved.
//

#ifndef textureHolder_hpp
#define textureHolder_hpp
#include <SFML/Graphics.hpp>
#include<map>

using namespace sf;

#endif

class TextureHolder{
public:
    TextureHolder();
    static Texture& GetTexture(std::string const& filename);
    
private:
    //a map holding pairs of String and texture
    std::map<std::string, sf::Texture> m_Textures;
    
    static TextureHolder* m_s_Instance;
};
