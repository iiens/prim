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

int map_utils_getSizeByDifficulty(Difficulty d) {
    switch (d) { // NOLINT(hicpp-multiway-paths-covered)
        case DIFFICULTY_EASY:
            return 10;
        case DIFFICULTY_MEDIUM:
            return 20;
        case DIFFICULTY_HARD:
            return 30;
    }
    return -1;
}