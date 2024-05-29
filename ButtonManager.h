#pragma once

#include <SDL.h>
#include <functional>
#include <vector>
#include <string>
#include <memory>
#include <unordered_map>

#include "ResourceManager.h"

enum class ButtonType {
    Text,
    Image,
    CustomShape
};

enum class ButtonState {
    Normal,
    Hovered,
    Pressed
};

enum class ButtonEventType{
    OnClick, // 
    OnHover, // Gerer
    WhilePressed, // Gerer
    OnRelease,
    OnRightClick, // Gerer
    OnLeftClick, // Gerer
    OnMiddleClick, // 
    OnDoubleLeftClick, // Gerer
    OnDoubleRightClick // Gerer
};

std::string stateToString(ButtonState state);

class Button {
public:
    Button(const std::string& name, ButtonType type, SDL_Rect srcRect, SDL_Rect dstRect);

    int render(SDL_Renderer* renderer, SDL_Texture* texture);
    bool isMouseOver(int mouseX, int mouseY) const;
    void handleEvent(SDL_Event& event);
    // void updateState(int mouseX, int mouseY, Uint8 mouseState);

    std::string getName() const { return name; }
    ButtonState getState() const { return state; }
    void setState(ButtonState newState) { state = newState; }

private:
    std::string name;
    ButtonType type;
    SDL_Rect srcBox;
    SDL_Rect dstBox;
    std::unordered_map<ButtonEventType, std::function<void()>> eventCallbacks;
    ButtonState state;
    bool visible;

    void handleMouseClick(const SDL_MouseButtonEvent& event);

    bool triggerEvent(ButtonEventType eventType) {
        if (eventCallbacks.find(eventType) != eventCallbacks.end()){
            eventCallbacks[eventType]();
            return true;
        }
        return false;
    }
};

class ButtonManager {
public:
    ButtonManager() : renderer(nullptr), resourceManager(nullptr) {}

    void init(SDL_Renderer* renderer, ResourceManager& resourceManager);
    void addButton(const std::string& name, ButtonType type, const std::string& pathFile, SDL_Rect srcBox, SDL_Rect dstBox);
    void renderButtons();
    void handleEvents(SDL_Event& event);

private:
    SDL_Renderer* renderer;
    std::vector<Button> buttons;
    ResourceManager* resourceManager;
};
