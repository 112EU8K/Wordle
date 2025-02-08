#ifndef PAUSEWND_H
#define PAUSEWND_H

#include "WndInterface.h"
#include "Button.h"
#include <memory>
#include <vector>

class PauseWnd : public WndInterface {
public:
    PauseWnd(const sf::IntRect& bounds, const sf::Font& font);

    void update(const float deltaTime) override;
    void draw(sf::RenderWindow& renderWindow) const override;
    void handleMousePress(const sf::Vector2i& mousePosition, bool isLeft) override;
    void handleMouseMove(const sf::Vector2i& mousePosition) override;
    WndResultState getResultState() const override;
    int getSelectedWordLength() const;
    void setCurrentWordLength(int length);

private:
    void initializeWordLengthButtons(const sf::Font& font);

    std::unique_ptr<sf::RectangleShape> _fullScreenBackground;
    std::unique_ptr<sf::RectangleShape> _background;
    std::unique_ptr<sf::Text> _titleText;
    std::vector<Button> _wordLengthButtons;

    Button _restartButton;
    Button _menuButton;

    WndResultState _resultState;
    int _selectedWordLength;

    std::unique_ptr<sf::Text> _wordLengthText;

    static const int WORD_LENGTH_MIN = 3;
    static const int WORD_LENGTH_MAX = 12;
};

#endif // PAUSEWND_H
