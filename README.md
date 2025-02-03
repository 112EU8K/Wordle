# Wordle-CPP-SFML (Modified Version)

## Overview
This is a modified version of the Wordle clone created by [Squirrelbear](https://github.com/Squirrelbear/Wordle-CPP-SMFL). The project is built using **C++** and **SFML** for graphical rendering. Various enhancements and bug fixes have been applied to improve functionality and maintainability.

## Features
- **Word validation**: Ensures that guessed words exist in the dictionary.
- **Error handling**: Displays an error message box in the SFML window when an invalid word is entered.
- **Random word selection**: Uses `std::default_random_engine` for randomized word selection.
- **Grid-based gameplay**: Players can enter words and receive feedback on correctness.
- **Event-driven game loop**: Handles keyboard and mouse input using SFML.


## Planned
- **Change the .exe file icon**
- **Make the window Full-Screen**
- **MainMenuTitle**
    ## Maybe...
  - **Add background music, one for the main menu, one for the game!**
    - **Add a timer that displays how much it took to guess the word** ~~OR FAIL~~


## Key Code Changes & Fixes
### 1. **Fixing Uninitialized Reference in `SFMLGame`**
The original code contained an uninitialized reference to `std::default_random_engine`. This was fixed by initializing it correctly:
```cpp
std::default_random_engine _randomEngine;
```
And in the constructor:
```cpp
_randomEngine(std::random_device{}())
```

### 2. **Adding Error Messages for Invalid Words**
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
  - **Green**: Correct letter in the correct position.
  - **Yellow**: Correct letter but in the wrong position.
  - **Gray**: Incorrect letter.

## Credits
- Original code by [Squirrelbear](https://github.com/Squirrelbear/Wordle-CPP-SMFL).
- Modifications and enhancements by `112EU8K`.

## License
This project follows the same licensing as the original repository. See `LICENSE` for details.

## Notes
Written by ChatGPT because  ¯\_(ツ)_/¯
- The Planned section was written by me ~~**obviously**~~
