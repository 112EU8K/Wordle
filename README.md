# Wordle-CPP-SFML (Modified Version)

## Overview
This is a modified version of a Wordle clone created by [Squirrelbear](https://github.com/Squirrelbear/Wordle-CPP-SMFL).


## Planned
  - **Find all the words in each length**
  - **Add a general timer**
  - **Add a clear progress button**
  - **Split words into different files for different categories gameplay**
  - **Add hint button**
  - **Add a Time Attack mode where you have a set of words in a specified time**
   ## Maybe...
   - **Transition effect**
   - **Increase attempts**
   - **Add background music**
   - **Add SFX**
       - SFX for `words that don't exist`
       - SFX for `failing`
       - SFX for `winning`
   - `BUTTON PRESS SFX`
   - `surround typing sound`
  - **Add a timer that displays how much it took to guess the word**


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
  - **Green**: Correct letter in the correct position.
  - **Yellow**: Correct letter but in the wrong position.
  - **Gray**: Incorrect letter.

## Credits
- Original code by [Squirrelbear](https://github.com/Squirrelbear).
- Modifications and enhancements by [112EU8K](https://github.com/112EU8K).

## License
This project follows the same licensing as the original repository. See `LICENSE` for details.
