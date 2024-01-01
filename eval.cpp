#include "wordler.h"

std::string evaluteGuess(std::string const & guess, std::string const & real) {
    bool in;
    std::string eval = "";
    for (int i = 0; i < LENGTH; i++) {
        if (guess[i] == real[i]) {
            eval += CORRECT;
        } else {
            in = false;
            for (int j = 0; j < LENGTH; j++) {
                if (guess[i] == real[j]) {
                    in = true;
                    break;
                }
            }
            if (in) {
                eval += CLOSE;
            } else {
                eval += WRONG;
            }
        }
    }
    return eval;
}

int numGuesses(std::string word) {
    int letterCounts[LENGTH][NUM_LETTERS];
    WordNode* wordList = readWordList("five_letter_words.txt");
    std::string bestWord;
    std::string result;
    bool OK = false;
    int guesses = 0;
    while (!OK) {
        guesses++;
        computeLetterCounts(wordList, letterCounts);
        bestWord = findOptimalWord(wordList, letterCounts);
        result = evaluteGuess(bestWord, word);
        OK = true;
        for (int j = 0; j < LENGTH; j++) {
            if (result[j] != CORRECT) {
                OK = false;
                break;
            }
        }
        if (OK) {
            break;
        }
        filterWordList(wordList, bestWord, result);
    }
    clearWordList(wordList);
 
    return guesses;
}

int main() {
    int guesses;
    int guessCounts[7];
    for (int i = 0; i < 7; i++) {
        guessCounts[i] = 0;
    }
    std::string word;
    std::ifstream f("five_letter_words.txt");
    while (std::getline(f, word)) {
        guesses = numGuesses(word);
        if (guesses > 6) {
            guessCounts[6]++;
        } else {
            guessCounts[guesses - 1]++;
        }
    }
    f.close();
    for (int i = 0; i < 6; i++) {
        std::cout << "Number of words found with " << i + 1 << " guesses: " << guessCounts[i] << std::endl;
    }
    std::cout << "Number of missed words: " << guessCounts[6] << std::endl;

    return 0;
}

