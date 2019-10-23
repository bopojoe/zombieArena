//
//  textureHolder.cpp
//  ZombieArena
//
//  Created by 20074556 on 13/11/2018.
//  Copyright © 2018 20074556. All rights reserved.
//

#include "textureHolder.hpp"
#include <assert.h>

using namespace sf;
using namespace std;

TextureHolder* TextureHolder:: m_s_Instance=nullptr;

TextureHolder::TextureHolder(){
    assert(m_s_Instance == nullptr);
    m_s_Instance = this;
}

sf::Texture& TextureHolder::GetTexture(const std::string &filename){
    //get a reference to the map m_Textures using m_s_Instance
    auto& m = m_s_Instance	-> m_Textures;
    
    //creates an iterator and search m for the passed in filename
    auto keyValuePair = m.find(filename);
    
    if(keyValuePair != m.end()){
        //if found return the texture
        return keyValuePair->second;
    }
    else{
        // Create a new key value pair using the filename
        auto& texture = m[filename];
        
        //load texture from file into map beside the filename
        texture.loadFromFile(filename);
        
        return texture;
    }
}
