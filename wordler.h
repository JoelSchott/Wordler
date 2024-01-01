#ifndef WORDLER_H
#define WORDLER_H

#include <iostream>
#include <fstream>
#include <string>

const int LENGTH = 5;
const int NUM_LETTERS = 26;
const char CORRECT = 'g';
const char CLOSE = 'y';
const char WRONG = 'b';

class WordNode {
    public:
        std::string word;
        WordNode* next = NULL;
};

void clearWordList(WordNode* wordList);

WordNode* readWordList(std::string const & wordFile);

bool valid(std::string const & word, std::string const & resultWord, std::string const & result);

void filterWordList(WordNode* & wordList, std::string const & word, std::string const & result);

void computeLetterCounts(WordNode* wordList, int letterCounts[LENGTH][NUM_LETTERS]);

std::string findOptimalWord(WordNode* wordList, int letterCounts[LENGTH][NUM_LETTERS]);

int charIndex(char c);

#endif