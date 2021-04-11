#include "../../headers/data/difficulty.h"

//todo: Rename, LVL isn't inside our voc. Use `difficulty_get(int id)` or something else
Difficulty difficulty_getLVL(int id)  {
    switch (id) {
        case 1:
            return DIFFICULTY_EASY;
        case 2:
            return DIFFICULTY_MEDIUM;
        case 3:
            return DIFFICULTY_HARD;
        default:
            return -1;
    }
}

int difficulty_getNumberOfDifficulties() {
    return NUMBER_DIFFICULTY;
}