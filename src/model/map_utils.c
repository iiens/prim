#include "../../headers/utils/map_utils.h"

//todo: Ramzy constant ?
int map_utils_getSizeByDifficulty(Difficulty d)
{
    switch ( d ) {
        case DIFFICULTY_EASY:
            return 10;
        case DIFFICULTY_MEDIUM:
            return 20;
        case DIFFICULTY_HARD:
            return 30;
    }
    return -1;
}