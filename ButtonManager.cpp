#include "ButtonManager.h"
#include <iostream>

std::string stateToString(ButtonState state) {
    switch (state) {
    case ButtonState::Normal: return "Normal";
    case ButtonState::Hovered: return "Hovered";
    case ButtonState::Pressed: return "Pressed";
    default: return "Unknown";
    }
}

Button::Button(const std::string& name, ButtonType type, SDL_Rect srcRect, SDL_Rect dstRect)
    : name(name), type(type), srcBox(srcRect), dstBox(dstRect), state(ButtonState::Normal), visible(true) {}

int Button::render(SDL_Renderer* renderer, SDL_Texture* texture) {

    if (!texture)
        return 1;

    return SDL_RenderCopy(renderer, texture, &srcBox, &dstBox);
}

bool Button::isMouseOver(int mouseX, int mouseY) const {
    return mouseX >= dstBox.x && mouseX <= (dstBox.x + dstBox.w) &&
        mouseY >= dstBox.y && mouseY <= (dstBox.y + dstBox.h);
}

void Button::handleEvent(SDL_Event& event)
{
    // Si la souris est sur le bouton
    if (isMouseOver(event.button.x, event.button.y))
    {
        // Déclencher l'événement de survol
        triggerEvent(ButtonEventType::OnHover);

        // Vérifier si le bouton a été enfoncé
        if (event.button.state == SDL_PRESSED)
        {
            // Gérer les clics de souris
            handleMouseClick(event.button);
        }
    }
    else
    {
        // Réinitialiser l'état du bouton
        state = ButtonState::Normal;
    }
}

void Button::handleMouseClick(const SDL_MouseButtonEvent& event)
{
    // Vérifier le type de clic de souris
    switch (event.button)
    {
    case SDL_BUTTON_LEFT:
        if (event.clicks > 1)
        {
            triggerEvent(ButtonEventType::OnDoubleLeftClick);
        }
        else
        {
            triggerEvent(ButtonEventType::OnLeftClick);
        }
        break;

    case SDL_BUTTON_RIGHT:
        if (event.clicks > 1)
        {
            triggerEvent(ButtonEventType::OnDoubleRightClick);
        }
        else
        {
            triggerEvent(ButtonEventType::OnRightClick);
        }
        break;

    case SDL_BUTTON_MIDDLE:
        triggerEvent(ButtonEventType::OnMiddleClick);
        break;

    default:
        break;
    }

    // Mettre à jour l'état du bouton
    state = ButtonState::Pressed;
}


void ButtonManager::init(SDL_Renderer* renderer, ResourceManager& resourceManager) {
    this->renderer = renderer;
    this->resourceManager = &resourceManager;
}

void ButtonManager::addButton(const std::string& name, ButtonType type, const std::string& pathFile, SDL_Rect srcBox, SDL_Rect dstBox) {
    SDL_Texture* normalButtonTexture = resourceManager->loadTexture(name + stateToString(ButtonState::Normal), pathFile);

    Button button(name, type, srcBox, dstBox);
    buttons.push_back(button);
}

void ButtonManager::renderButtons() {
    for (auto& button : buttons) {
        std::cout << "State : " << static_cast<int>(button.getState()) << std::endl;
        if (!button.render(renderer, resourceManager->getTexture(button.getName() + stateToString(button.getState())))) {
            continue;
        }

        if (button.getState() == ButtonState::Normal) {
            SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Erreur de chargement de la texture normal du bouton '%s' : %s", button.getName().c_str(), SDL_GetError());
        }
        else {
            button.render(renderer, resourceManager->getTexture(button.getName() + stateToString(ButtonState::Normal)));
        }
    }
}

void ButtonManager::handleEvents(SDL_Event& event) {
    int mouseX, mouseY;
    Uint32 mouseState = SDL_GetMouseState(&mouseX, &mouseY);
    bool mousePressed = (mouseState & SDL_BUTTON(SDL_BUTTON_LEFT)) || (mouseState & SDL_BUTTON(SDL_BUTTON_RIGHT));

    for (auto& button : buttons) {
        button.handleEvent(event);
    }
}
