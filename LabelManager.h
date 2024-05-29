#pragma once

#include "SDL.h"
#include "SDL_ttf.h"

#include <iostream>
#include <map>
#include <string>

struct Label {
    std::string name;
    std::string text;
    TTF_Font* font;
    SDL_Color color;
    int x, y;
    SDL_Texture* texture; // Texture pré-rendue du texte
    bool visible;
};

class LabelManager {
public:
    LabelManager();
    ~LabelManager();

    void createLabel(const std::string& name, const std::string& text, TTF_Font* font, const SDL_Color& color, int x, int y);
    void updateLabelText(const std::string& name, const std::string& newText);
    void updateLabel(const std::string& name, const std::string& text, TTF_Font* font, const SDL_Color& color);
    void renderLabels(SDL_Renderer *renderer);
    void setPosition(const std::string name, int x, int y);
    void show(const std::string& name);
    void hide(const std::string& name);

private:
    std::map<std::string,Label> labels;
};
