#include "../../headers/data/difficulty.h"

#include "stdlib.h"
#include "stdio.h"

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