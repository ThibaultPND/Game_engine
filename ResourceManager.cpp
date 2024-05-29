#include "ResourceManager.h"

ResourceManager::ResourceManager() {
    renderer = nullptr;
}

ResourceManager::~ResourceManager() {
    cleanUp();
}
void ResourceManager::init(SDL_Renderer* renderer) {
    this->renderer = renderer;
}

SDL_Texture* ResourceManager::loadTexture(const std::string& textureName, const std::string& filePath) {
    SDL_Texture* texture = IMG_LoadTexture(renderer, filePath.c_str());
    if (texture) {
        textures[textureName] = texture;
        return texture;
    }
    else {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Chargement de la texture '%s' : %s", filePath.c_str(), SDL_GetError());
        return nullptr;
    }
}

bool ResourceManager::textureExist(const std::string& textureName) {
    auto it = textures.find(textureName);
    if (it != textures.end())
        return true;

    return false;
}

void ResourceManager::unloadTexture(const std::string& textureName) {
    auto it = textures.find(textureName);
    if (it != textures.end()) {
        SDL_DestroyTexture(it->second);
        textures.erase(it);
    }
}


SDL_Texture* ResourceManager::getTexture(const std::string& textureName) {
    auto it = textures.find(textureName);
    if (it != textures.end()) {
        return it->second;
    }
    return nullptr;
}


TTF_Font* ResourceManager::loadFont(const std::string& filePath, int size) {
    std::string originFilePath = "assets/fonts/" + filePath;
    auto it = fonts.find(filePath);
    if (it != fonts.end()) {
        auto fontIt = it->second.find(size);
        if (fontIt != it->second.end())
        {
            return fontIt->second;
        }
        else {
            TTF_Font* font = TTF_OpenFont(originFilePath.c_str(), size);
            if (font)
            {
                it->second[size] = font;
                return font;
            }
            else {
                SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "< %d > Impossible de chargé la font '%s' : %s",__LINE__ , filePath.c_str(), SDL_GetError());
                return nullptr;
            }
        }
    }
    else {
        TTF_Font* font = TTF_OpenFont(originFilePath.c_str(), size);
        if (font)
        {
            fonts[filePath][size] = font;
            return font;
        }
        else {
            SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "<%d> Impossible de chargé la font '%s' : %s", __LINE__, filePath.c_str(), SDL_GetError());
            return nullptr;
        }
    }
}
TTF_Font* ResourceManager::getFont(const std::string& fontName, int size){
    auto it = fonts.find(fontName);
    if (it != fonts.end())
    {
        auto fontIt = it->second.find(size);
        if (fontIt != it->second.end()) {
            return fontIt->second;
        }
    }
    // Tente de charger la police avant de retourner nullptr.
    return loadFont(fontName, size);
}
void ResourceManager::unloadFont(const std::string fontName) {
    auto it = fonts.find(fontName);
    if (it != fonts.end()) {
        for (auto& pair : it->second) {
            TTF_CloseFont(pair.second);
        }
        fonts.erase(it);
    }
}

void ResourceManager::cleanUp() {
    for (auto& pair : textures) {
        SDL_DestroyTexture(pair.second);
    }
    textures.clear();
}