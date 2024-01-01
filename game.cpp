#include "wordler.h"

int main() {
    int letterCounts[LENGTH][NUM_LETTERS];
    WordNode* wordList = readWordList("five_letter_words.txt");
    std::string bestWord;
    std::string result;
    bool OK;
    for (int i = 0; i < 6; i++) {
        computeLetterCounts(wordList, letterCounts);
        bestWord = findOptimalWord(wordList, letterCounts);
        std::cout << "The next word to try is: " << bestWord << std::endl;
        std::cout << "What was the result? (" << CORRECT << " for correct, " << CLOSE << " for close, " << WRONG << " for wrong): ";
        std::getline(std::cin, result);
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
 
    return 0;
}