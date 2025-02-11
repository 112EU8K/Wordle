# Wordle-CPP-SFML (Modified Version)

## Overview
This is a modified version of a Wordle clone created by [Squirrelbear](https://github.com/Squirrelbear/Wordle-CPP-SMFL).


## Planned
  - **log errors to the window**
  - **Find all the words in each length**
  - **General Timer**
  - **Clear Progress Button**
  - **Split words into different files for different categories of gameplay**
  - **hint button**
  - **give up button**
  - **Time Attack mode: Guess all the words in a specified time**
  - **Streaks**
   ## Maybe...
   - **`Android Version`**
   - **a dictionary**
   - **Scrolling BackGround**
   - **`themes`**
   - **Transition effect**
   - **Increase attempts**
   - **background music**
   - **Add SFX**
       - SFX for `words that don't exist`
       - SFX for `failing`
       - SFX for `winning`
   - `BUTTON PRESS SFX`
   - `surround typing sound`
  - **timer that displays how much it took to guess the word**

## TODO
  - Fix resizing the window
  - After the player wins or loses nothing happen, I should fix that

## Key Code Changes & Fixes
### **Adding Error Messages for Invalid Words**
Previously, errors were only logged to `std::cerr`. Now, an on-screen message box is displayed when a guessed word is invalid:
```cpp
if (!_wordDatabase->isValidWord(guessedWord)) {
    _messageBox.setMessage("Invalid word! Not found in the dictionary.");
    return;
}
```

## Gameplay
- Players have a limited number of attempts to guess the correct word.
- Letters are color-coded to indicate correctness:
  - **Green**: The correct letter is in the correct position.
  - **Yellow**: The correct letter but in the wrong position.
  - **Gray**: Incorrect letter.

## Credits
- Original code by [Squirrelbear](https://github.com/Squirrelbear).
- Modifications and enhancements by [112EU8K](https://github.com/112EU8K).

## License
This project follows the same licensing as the original repository. See [LICENSE](https://github.com/112EU8K/Wordle/blob/main/LICENSE) for details.
