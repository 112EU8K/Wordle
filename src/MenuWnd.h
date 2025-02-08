#ifndef MENUWND_H
#define MENUWND_H

#include "WndInterface.h"
#include "Button.h"
#include "WordDatabase.h"
#include <vector>
#include <memory>

class MenuWnd : public WndInterface {
public:
    MenuWnd(const sf::IntRect& bounds, const sf::Font& font, WordDatabase &wordDatabase);

    void update(const float deltaTime) override;
    void draw(sf::RenderWindow& renderWindow) const override;
    void handleMousePress(const sf::Vector2i& mousePosition, bool isLeft) override;
    void handleMouseMove(const sf::Vector2i& mousePosition) override;

    WndResultState getResultState() const override;
    int getSelectedWordLength() const;

private:
    sf::Text _titleText;
    sf::Text _instructionText;
    std::vector<Button> _buttons;
    WndResultState _resultState;
    int _selectedWordLength;
    WordDatabase& _wordDatabase;
};


#endif // MENUWND_H
