#include "LabelManager.h"

LabelManager::LabelManager() {}

LabelManager::~LabelManager() {
    for (auto& pair : labels) {
        Label& label = pair.second;
        SDL_DestroyTexture(label.texture);
    }
}

void LabelManager::createLabel(const std::string& name, const std::string& text, TTF_Font* font, const SDL_Color& color, int x, int y) {
    auto it = labels.find(name);
    if (it != labels.end()) {
        SDL_LogWarn(0, "Il y a déja un label avec ce nom qui existe.");
        return;
    }

    Label label;
    label.name = name;
    label.text = text;
    label.font = font;
    label.color = color;
    label.x = x;
    label.y = y;
    label.texture = nullptr; // La texture sera rendue au besoin
    labels[name] = label;
    label.visible = true;
}

void LabelManager::updateLabel(const std::string& name, const std::string& text, TTF_Font* font, const SDL_Color& color) {
    if (!font)
        return;

    auto it = labels.find(name);
    if (it != labels.end()) {
        Label& label = it->second;
        label.text = text;
        label.font = font;
        label.color = color;
    }
}

void LabelManager::updateLabelText(const std::string& name, const std::string& newText) {
    auto it = labels.find(name);
    if (it != labels.end()) {
        it->second.text = newText;
    }
}

void LabelManager::setPosition(const std::string name, int x, int y) {
    auto it = labels.find(name);
    if (it != labels.end()) {
        it->second.x = x;
        it->second.y = y;
    }
}

void LabelManager::renderLabels(SDL_Renderer* renderer) {
    for (auto& pair : labels) {
        if (!pair.second.visible) continue;

        Label& label = pair.second;
        if (!label.texture) {
            SDL_Surface* surface = TTF_RenderText_Solid(label.font, label.text.c_str(), label.color);
            if (surface) {
                label.texture = SDL_CreateTextureFromSurface(renderer, surface);
                SDL_FreeSurface(surface);
            }
        }
        if (label.texture) {
            SDL_Rect destRect = { label.x, label.y, 0, 0 }; // Position du texte

            SDL_QueryTexture(label.texture, nullptr, nullptr, &destRect.w, &destRect.h);
            SDL_RenderCopy(renderer, label.texture, nullptr, &destRect);
        }
    }
}

void LabelManager::show(const std::string& name) {
    auto it = labels.find(name);
    if (it != labels.end()) {
        it->second.visible = true;
    }
}
void LabelManager::hide(const std::string& name) {
    auto it = labels.find(name);
    if (it != labels.end()) {
        it->second.visible = false;
    }
}