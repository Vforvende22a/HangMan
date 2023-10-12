# Hangman Console Game in C++

This is a Hangman console game implemented in C++. It utilizes the following libraries:

- `iostream`
- `fstream`
- `set`
- `random`

Additionally, the game includes a custom class, `MyString`, which is also included.

## Features
- **Write Words to Binary File**: The game provides a method to write words to a binary file. These words are used as the secret words for the Hangman game.

- **Read Words from Binary File**: The game also includes a method to read words from the same binary file, allowing you to maintain a list of words for the game.

- **Random Word Selection**: Before starting each game, the program chooses a random word from the list of words read from the binary file. This adds an element of unpredictability to each playthrough.

- **User Guessing**: The game lets users guess the selected word by trying different letters. The program manages the user's guesses, keeps track of correct and incorrect guesses, and displays the current state of the word being guessed.

This Hangman game provides an entertaining way to test your word-guessing skills within the console environment.

