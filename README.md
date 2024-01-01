# Wordler
A simple approach to automatically play the game Wordle that iteratively looks for the most representative word out of the set of remaining valid words. The algorithm can be used interactively with game.cpp and can be evaluated with eval.cpp.

The list of five letter words could probably be improved, many of the words there do not look like valid Wordle words.

Evaluation results:
| Number of Guesses | Number of Words Found |
| :---: | :---: |
| 1 | 1 |
| 2 | 118 |
| 3 | 1,272 |
| 4 | 4,084 |
| 5 | 5,137 |
| 6 | 3,131 |
| 7+ | 2,177 |

Clearly, there is lots of room for improvement.