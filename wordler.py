from typing import List


LENGTH = 5
NUM_LETTERS = 26
CORRECT = 'g'
WRONG_POS = 'y'
WRONG = 'b'


class WordNode:
    def __init__(self, word: str):
        self.word = word
        self.next = None


def char_index(c: str):
    return ord(c) - 97


def read_word_list(words_file: str) -> WordNode:
    head = None
    tail = None
    with open(words_file, 'r') as f:
        for i, word in enumerate(f):
            node = WordNode(word.strip())
            if i == 0:
                head = node
                tail = node
            else:
                tail.next = node
                tail = tail.next
    return head


def valid(word: str, result_word: str, result: str) -> bool:
    for i in range(LENGTH):
        if result[i] == CORRECT:
            if word[i] != result_word[i]:
                return False
        elif result[i] == WRONG_POS:
            if word[i] == result_word[i] or result_word[i] not in word:
                return False
        else:
            if result_word[i] in word:
                return False
    return True


def filter_word_list(head: WordNode, result_word: str, result: str) -> WordNode:
    while (head is not None) and (not valid(head.word, result_word, result)):
        head = head.next
    if head is None:
        return None
    prev = head
    node = prev.next
    while node is not None:
        if valid(node.word, result_word, result):
            prev = node
        else:
            prev.next = node.next
        node = prev.next
    return head


def compute_letter_counts(head: WordNode, letter_counts: List[List[int]]):
    for i in range(LENGTH):
        for j in range(NUM_LETTERS):
            letter_counts[i][j] = 0
    while head is not None:
        for i in range(LENGTH):
            letter_counts[i][char_index(head.word[i])] += 1
        head = head.next


def find_optimal_word(head: WordNode, letter_counts: List[List[int]]) -> str:
    best_count = 0
    best_word = None
    while head is not None:
        count = 0
        for i in range(LENGTH):
            count += letter_counts[i][char_index(head.word[i])]
        if count > best_count:
            best_count = count
            best_word = head.word
        head = head.next
    return best_word


def main(words_file: str):
    word_list = read_word_list(words_file)
    letter_counts = [[0 for _ in range(NUM_LETTERS)] for _ in range(LENGTH)]
    for i in range(6):
        compute_letter_counts(word_list, letter_counts)
        best_word = find_optimal_word(word_list, letter_counts)
        print('The next word is:', best_word)
        result = input(f'What was the result? ({CORRECT} for correct, {WRONG_POS} for wrong position, {WRONG} for wrong): ')
        if result == CORRECT * LENGTH:
            break
        word_list = filter_word_list(word_list, best_word, result)


if __name__ == '__main__':
    main('five_letter_words.txt')
