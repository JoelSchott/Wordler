#include "wordler.h"

void clearWordList(WordNode* wordList) {
    WordNode* next;
    while (wordList != NULL) {
        next = wordList->next;
        delete wordList;
        wordList = next;
    }
}

WordNode* readWordList(std::string const & wordFile) {
    WordNode* head;
    WordNode* tail;
    bool first = true;
    std::string line;
    std::ifstream f(wordFile);
    while (std::getline(f, line)) {
        WordNode* node = new WordNode();
        node->word = line;
        if (first) {
            head = node;
            tail = node;
            first = false;
        } else {
            tail->next = node;
            tail = node;
        }
    }   
    f.close();
    return head;
}

bool valid(std::string const & word, std::string const & resultWord, std::string const & result) {
    bool found;
    for (int i = 0; i < LENGTH; i++) {
        if (result[i] == CORRECT) {
            if (word[i] != resultWord[i]) {
                return false;
            }
        } else if (result[i] == CLOSE) {
            if (word[i] == resultWord[i]) {
                return false;
            }
            found = false;
            for (int j = 0; j < LENGTH; j++) {
                if (word[j] == resultWord[i]) {
                    found = true;
                    break;
                }
            }
            if (!found) {
                return false;
            }
        } else {
            for (int j = 0; j < LENGTH; j++) {
                if (word[j] == resultWord[i]) {
                    return false;
                }
            }
        }
    }
    return true;
}

void filterWordList(WordNode* & wordList, std::string const & word, std::string const & result) {
    WordNode* prev;
    while (wordList != NULL && !valid(wordList->word, word, result)) {
        prev = wordList;
        wordList = wordList->next;
        delete prev;
    }
    if (wordList == NULL) {
        return;
    }
    prev = wordList;
    WordNode* node = prev->next;
    while (node != NULL) {
        if (valid(node->word, word, result)) {
            prev = node;
        } else {
            prev->next = node->next;
            delete node;
        }
        node = prev->next;
    }
}

void computeLetterCounts(WordNode* wordList, int letterCounts[LENGTH][NUM_LETTERS]) {
    for (int i = 0; i < LENGTH; i++) {
        for (int j = 0; j < NUM_LETTERS; j++) {
            letterCounts[i][j] = 0;
        }
    }
    while (wordList != NULL) {
        for (int i = 0; i < LENGTH; i++) {
            letterCounts[i][charIndex(wordList->word[i])]++;
        }
        wordList = wordList->next;
    }
}

std::string findOptimalWord(WordNode* wordList, int letterCounts[LENGTH][NUM_LETTERS]) {
    int bestCount = 0;
    int count;
    std::string bestWord;
    while (wordList != NULL) {
        count = 0;
        for (int i = 0; i < LENGTH; i++) {
            count += letterCounts[i][charIndex(wordList->word[i])];
        }
        if (count > bestCount) {
            bestCount = count;
            bestWord = wordList->word;
        }
        wordList = wordList->next;
    }
    return bestWord;
}

int charIndex(char c) {
    int i = c;
    return i - 97;
}

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