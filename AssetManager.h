#pragma once

#include <map>
#include <string>
#include "texturemanager.hpp"
#include <SDL.h>
#include "Vector2D.h"
#include "ECS/ECS.hpp"
#include "gameloop.h"
using namespace std;


class AssetManager 
{
public:
    AssetManager(Manager* man);
    ~AssetManager();

    void AddTexture(string id, const char* file);
    SDL_Texture* GetTexture(string id);

private:
Manager* manager;
    map<string, SDL_Texture*> textures;

};