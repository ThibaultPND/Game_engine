#pragma once

#include "SDL.h"
#include "SDL_image.h"
#include "SDL_ttf.h"

#include <map>
#include <string>

class ResourceManager {
public:
    ResourceManager();
    ~ResourceManager();

    void init(SDL_Renderer* renderer);

    SDL_Texture* loadTexture(const std::string& textureName, const std::string& filePath);
    bool textureExist(const std::string& textureName);
    SDL_Texture* getTexture(const std::string& textureName);
    void unloadTexture(const std::string& textureName);

    TTF_Font* loadFont(const std::string& filePath, int size);
    TTF_Font* getFont(const std::string& fontName, int size);
    void unloadFont(const std::string fontName);

private:
    SDL_Renderer *renderer;
    std::map<std::string, SDL_Texture*> textures;
    std::map<std::string, std::map<int,TTF_Font*>> fonts;

    void cleanUp();
};