#include <iostream>
#include <fstream>
#include <set>
#include "MyString.h"
#include <random>
#include <cctype>

#define MAX_FAULTS 7 
#define LETTERS_COUNT 26
#define BUFFERSIZE 1024
const char* FILE_NAME= "words.bin";


//Method for writting an array of words to a binary file
void writeWords()
{
	std::ofstream outputFile(FILE_NAME, std::ios::binary);

	if (!outputFile)
	{
		std::cerr << "Error opening the file for writing." << std::endl;
		return;
	}

	MyString words[3] = { "APPLE", "BANANA", "CHERRY" };


	for (const MyString& word : words) {
		size_t wordLength = word.getSize();
		outputFile.write((const char*)&wordLength, sizeof(wordLength));
		outputFile.write(word.c_str(), wordLength);
	}

	outputFile.close();
}

//Method for printing the letters when you start the game and the gallow
void printLetters(const char* letters)
{
	for (size_t i = 0; i < 24; i++)
	{
		if (i != 5 && i != 11 && i != 17 && i != 23)
		{
			std::cout << letters[i] << " | ";
		}
		else std::cout << letters[i] << "\n\n";
	}
	std::cout << "        " << letters[24] << " | " << letters[25] << "\n" << std::endl;
}
void printGallow(unsigned faults)
{
	switch (faults)
	{
	case 0:
	{
		std::cout << "   +---+\n       |\n       |\n       |\n       |\n       |\n =========" << std::endl;
	}break;
	case 1:
	{
		std::cout << "   +---+\n   |   |\n       |\n       |\n       |\n       |\n =========" << std::endl;
	}break;
	case 2:
	{
		std::cout << "   +---+\n   |   |\n   O   |\n       |\n       |\n       |\n =========" << std::endl;
	}break;
	case 3:
	{
		std::cout << "   +---+\n   |   |\n   O   |\n   |   |\n       |\n       |\n =========" << std::endl;
	}break;
	case 4:
	{
		std::cout << "   +---+\n   |   |\n   O   |\n  /|   |\n       |\n       |\n =========" << std::endl;
	}break;
	case 5:
	{
		std::cout << "   +---+\n   |   |\n   O   |\n  /|\\  |\n       |\n       |\n =========" << std::endl;
	}break;
	case 6:
	{
		std::cout << "   +---+\n   |   |\n   O   |\n  /|\\  |\n  /    |\n       |\n =========" << std::endl;
	}break;
	case 7:
	{
		std::cout << "   +---+\n   |   |\n   O   |\n  /|\\  |\n  / \\  |\n       |\n =========" << std::endl;
	}break;
	default:
		break;
	}
}

//Handles most of the writting to the console
void printSetup(const MyString& word, const char* letters, const MyString& answer, unsigned faults)
{
	system("cls");
	std::cout << "	The HANGMAN !\n\nGuess the word : ";

	if (faults != 7)
	{
		for (size_t i = 0; i < answer.getSize(); i++)
		{
			std::cout << answer[i] << " ";
		}
	}
	else
	{
		for (size_t i = 0; i < word.getSize(); i++)
		{
			std::cout << word[i] << " ";
		}
	}
	std::cout << "\n\n\n";
	printLetters(letters);
	printGallow(faults);
	if (word == answer)
	{
		std::cout << "You win the word was indeed " << answer << ". Good job!" << std::endl;
		return;
	}
	if (faults == 7)
	{
		std::cout << "No you got hanged :(";
		return;
	}
	std::cout << "Try with a letter :";
}

//Get the count of words from the file to dynamically allocate memory
unsigned getWordsCount()
{
	std::ifstream file(FILE_NAME, std::ios::binary);
	unsigned count = 0;
	if (!file)
	{
		throw std::invalid_argument("File is bad!");
	}
	else
	{
		size_t size = 0;
		char* buff = nullptr;
		while (!file.eof())
		{
			file.read((char*)&size, sizeof(size));
			buff = new char[size];
			file.read(buff, size);
			count++;
			delete[] buff;
		}
	}
	file.close();
	return count - 1;
}
//Read words from the binary file they are written to
void getWords(MyString*& words, unsigned wordsCount)
{
	std::ifstream file(FILE_NAME, std::ios::binary);
	if (!file)
	{
		throw std::invalid_argument("File is bad!");
	}
	else
	{
		size_t wordLength = 0;
		unsigned index = 0;

		MyString word;
		char* buff = nullptr;
		for (size_t i = 0; i < wordsCount; i++)
		{
			file.read((char*)(&wordLength), sizeof(wordLength));
			buff = new char[wordLength + 1];
			file.read(buff, wordLength);
			buff[wordLength] = '\0';
			word = buff;
			words[index] = word;
			index++;
			delete[]buff;
		}
	}
	file.close();
}
unsigned getRandomNumb(unsigned wordsCount)
{
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<unsigned> distribution(0, wordsCount - 1);
	unsigned randomNum = distribution(gen);
	return randomNum;
}
//Gets a random word from the dynamic array with a random index
MyString getRandomWord()
{

	const unsigned wordsCount = getWordsCount();
	if (wordsCount == 0)
	{
		throw std::invalid_argument("File is bad!");
	}
	MyString* words = new MyString[wordsCount];
	getWords(words, wordsCount);
	unsigned randomNum = getRandomNumb(wordsCount);
	MyString word = words[randomNum];
	delete[] words;
	return word;
}

//Get a set with winning letters to check if a guessed letters is from the random word
std::set<char> getWinningLetters(const MyString& word)
{
	size_t wordSize = word.getSize();
	if (wordSize != 0)
	{
		std::set<char> winningLetters;

		for (size_t i = 0; i < wordSize; i++)
		{
			winningLetters.insert(word.c_str()[i]);;
		}
		return winningLetters;
	}
	else throw std::invalid_argument("Bad word");
}

void toUpper(char& guess)
{
	if (guess < 'A' || guess>'Z')
	{
		guess -= 'a' - 'A';
	}
}
bool isLetter(const char letter)
{
	if (letter < 65 || letter>90)
		return false;
	return true;
}

//Handles most of the logic
void GuessLetter(const MyString& word, MyString& answer, char guess, std::set<char>& winningLetters, char* letters, unsigned& faults)
{
	if (winningLetters.count(guess))
	{
		for (size_t i = 0; i < word.getSize(); i++)
		{
			if (word[i] == guess)
			{
				answer[i] = guess;
			}
		}
	}
	for (size_t i = 0; i < LETTERS_COUNT; i++)
	{
		if (letters[i] == guess)
		{
			if (winningLetters.count(letters[i]) == 0)
			{
				faults++;
			}
			letters[i] = '_';
		}
	}
	printSetup(word, letters, answer, faults);
}

int main()
{
	char letters[LETTERS_COUNT] = { 'A','B','C','D','E','F',
									'G','H','I','J','K','L',
									'M','N','O','P','Q','R',
									'S','T','U','V','W','X',
											'Y','Z' };

	MyString word;
	try
	{
		word = getRandomWord();
	}
	catch (const std::exception& e)
	{
		std::cerr << e.what();
		return 1;
	}

	MyString answer = word;
	for (size_t i = 0; i < word.getSize(); i++)
	{
		answer[i] = '_';
	}
	//Sets the string answer to _ so when a player guesses a letter it replaces _ with the guessed letter. Later
	//the string answer is printed 

	std::set<char> winningLetters = getWinningLetters(word);

	unsigned faults = 0;
	printSetup(word, letters, answer, faults);  //Initial set up
	char guess;

	while (faults < MAX_FAULTS && word != answer)
	{
		// the buffer sentence ensures that white spaces aren`t entered as a guess and makes it easier to validate later
		char* sentence = new char[BUFFERSIZE];
		std::cin.getline(sentence, BUFFERSIZE);
		unsigned sentenceSize = strnlen_s(sentence, BUFFERSIZE);
		if (sentenceSize != 1)
		{
			std::cout << "Please enter a letter not " << sentenceSize << " characters" << std::endl;
			continue;
		}
		guess = sentence[0];
		delete[] sentence;
		toUpper(guess);
		if (!isLetter(guess))
		{
			std::cout << "Please enter a letter!\n";
			continue;
		}

		GuessLetter(word, answer, guess, winningLetters, letters, faults);
	}
}