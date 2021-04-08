#include "../../headers/data/staff.h"

#include <stdio.h>
#include <stdlib.h>

struct Staff_S {
    int id; //!< id of the character
    char* name; //!< name of the character
    int costE; //!< Price in E of the character
    int costDD; //!< Price in DD of the character
    char* description; //!< description of character effects
    Effect effects; //!< array which contains the target of the effect
}; //!< information about staff

const Staff staff_list[] = {
        {1, "Fetia Bannour", 100, 30, "The cost of constructing collectors"
                                      " decreases by 10E and 1DD ", .effects = {
                .mode = CONSTRUCTION,
                .onOther = 0,
                .what.machine = MS_COLLECTOR,
                .modifierE = -10,
                .modifierDD = -1,
                .min_costE = 10,
                .min_costDD = 1,
                .description = "The cost of constructing collectors decreases by 10EE and 1DD (min 10E\n"
                               "and 1DD)."
        }

        },
        {2, "Kevin Goilard", 100, 30, "The cost of constructing conveyor belt"
                                      " decreases by 3E and 1DD ", .effects = {
                .mode = CONSTRUCTION,
                .onOther = 0,
                .what.machine = MS_CONVEYOR_BELT,
                .modifierE = -3,
                .modifierDD = -1,
                .min_costE = 3,
                .min_costDD = 1,
                .description = "The cost of constructing conveyor belt decreases by 3E and 1DD (min 3EE\n"
                               "and 1DD)."
        }

        },
        {3, "Vincent Jeannas", 100, 30, "The cost of constructing cross"
                                        " decreases by 8E and 1DD ", .effects = {
                .mode = CONSTRUCTION,
                .onOther = 0,
                .what.machine = MS_CROSS,
                .modifierE = -8,
                .modifierDD = -1,
                .min_costE = 8,
                .min_costDD = 1,
                .description = "The cost of constructing cross decreases by 8E and 1DD (min 8EE\n"
                               "and 1DD)."
        }

        },
        {4, "Thomas Laurent", 100, 30, "The cost of constructing recycling center"
                                       " decreases by 25E and 2DD ", .effects = {
                .mode = CONSTRUCTION,
                .onOther = 0,
                .what.machine = MS_RECYCLING_CENTER,
                .modifierE = -25,
                .modifierDD = -2,
                .min_costE = 25,
                .min_costDD = 2,
                .description = "The cost of constructing conveyor belt decreases by 25E and 2DD (min 25E\n"
                               "and 2DD)."
        }

        },

        {5, "Massinissa Merabet", 100, 30, "The cost of constructing junkyard"
                                           " decreases by 5E and 5DD ", .effects = {
                .mode = CONSTRUCTION,
                .onOther = 0,
                .what.machine = MS_JUNKYARD,
                .modifierE = -5,
                .modifierDD = -5,
                .min_costE = 5,
                .min_costDD = 5,
                .description = "The cost of constructing conveyor belt decreases by 5E and 5DD (min 5E\n"
                               "and 5DD)."
        }

        },


        {6, "Stefi Nouleho", 200, 100, "The cost of upgrading collectors"
                                       " decreases by 25E and 5DD ", .effects = {
                .mode = UPGRADE,
                .onOther = 0,
                .what.machine = MS_COLLECTOR,
                .modifierE = -25,
                .modifierDD = -5,
                .min_costE = 25,
                .min_costDD = 5,
                .description = "The cost of upgrading collectors decreases by 25E and 5DD (min 25E\n"
                               "and 5DD)."
        }

        },


        {7, "Vitera Y", 200, 100, "The cost of upgrading recycling center"
                                  " decreases by 75E and 5DD ", .effects = {
                .mode = UPGRADE,
                .onOther = 0,
                .what.machine = MS_RECYCLING_CENTER,
                .modifierE = -75,
                .modifierDD = -5,
                .min_costE = 75,
                .min_costDD = 5,
                .description = "The cost of upgrading recycling center decreases by 75E and 5DD (min 75E\n"
                               "and 5DD)."
        }

        },

        {8, "Laurence Bourard", 200, 100, "The cost of upgrading junkyard"
                                          " decreases by 10E and 30DD ", .effects = {
                .mode = UPGRADE,
                .onOther = 0,
                .what.machine = MS_JUNKYARD,
                .modifierE = -10,
                .modifierDD = -30,
                .min_costE = 20,
                .min_costDD = 30,
                .description = "The cost of upgrading junkyard decreases by 10E and 30DD (min 20E\n"
                               "and 30DD)."
        }

        },

        {9, "Nicolas Brunel", 100, 200, "The cost of destroying collectors"
                                        " decreases by 3E and 10DD ", .effects = {
                .mode = DESTROY,
                .onOther = 0,
                .what.machine = MS_COLLECTOR,
                .modifierE = -3,
                .modifierDD = -10,
                .min_costE = 3,
                .min_costDD = 10,
                .description = "The cost of destroying recycling center decreases by 3E and 10DD (min 3E\n"
                               "and 10DD)."
        }

        },

        {10, "Anastase Charantonis", 100, 200, "The cost of destroying conveyor"
                                               " belt decreases by 3E and 10DD ", .effects = {
                .mode = DESTROY,
                .onOther = 0,
                .what.machine = MS_CONVEYOR_BELT,
                .modifierE = -3,
                .modifierDD = -10,
                .min_costE = 3,
                .min_costDD = 10,
                .description = "The cost of destroying conveyor belt decreases by 3E and 10DD (min 3E\n"
                               "and 10DD)."
        }

        },

        {11, "Catherine Dubois", 100, 200, "The cost of destroying cross"
                                           " decreases by 3E and 10DD ", .effects = {
                .mode = DESTROY,
                .onOther = 0,
                .what.machine = MS_CROSS,
                .modifierE = -3,
                .modifierDD = -10,
                .min_costE = 3,
                .min_costDD = 10,
                .description = "The cost of destroying conveyor belt decreases by 3E and 10DD (min 3E\n"
                               "and 10DD)."
        }

        },

        {12, "Stefiana Dumbrava", 100, 200, "The cost of destroying recycling center"
                                            " decreases by 5E and 25DD ", .effects = {
                .mode = DESTROY,
                .onOther = 0,
                .what.machine = MS_RECYCLING_CENTER,
                .modifierE = -5,
                .modifierDD = -25,
                .min_costE = 5,
                .min_costDD = 25,
                .description = "The cost of destroying recycling center decreases by 5E and 25DD (min 5E\n"
                               "and 25DD)."
        }

        },

        {13, "Alain Faye", 100, 200, "The cost of destroying junkyard"
                                     " decreases by 5E and 10DD ", .effects = {
                .mode = DESTROY,
                .onOther = 0,
                .what.machine = MS_JUNKYARD,
                .modifierE = -5,
                .modifierDD = -10,
                .min_costE = 5,
                .min_costDD = 10,
                .description = "The cost of destroying junkyard decreases by 5E and 10DD (min 5E\n"
                               "and 10DD)."
        }

        },

        {14, "Anne-Laure Ligozat", 1000, 10, "Half garbage of each case are remove"
                , .effects = {
                .mode = DESTROY,
                .onOther = 0,
                .what.other = DESTROY_GARBAGE,
                .modifierRes = 1/2, // multiply for each case this number of garbage by this number
                .description = "Half garbage of each case are remove"
        }

        },

        {15, "Christophe Mouilleron", 1000, 400, "School hire 20 FISE and 10 FISA"
                , .effects = {
                .mode = HIRE,
                .onOther = 1,
                .what.other = SUB_HIRE,
                .modifierFISE = +20,
                .modifierFISA = +10,
                .description = "School hire 20 FISE and 10 FISA"

        }

        },

        {16, "Marie Szafranski", 1000, 400, "When a resource is send at the gate"
                                            " it count for 2 but number of garbage is 1 ", .effects = {
                .mode = SEND_DOOR,
                .onOther = 1,
                .what.other = NONE,
                .modifierRes = 2,
                .description = "When a resource is send at the gate it count for 2 but number of garbage "
                               " is 1"
        }

        },

        {17, "Gael Thomas", 1000, 400, "When a garbage leave the door it has a one"
                                       " in 10 chance of disappearing ", .effects = {
                .mode = DOOR_OUT,//<!todo : not implement yet make a variable with a randomize if = 1 remove
                //garbage
                .onOther = 0,
                .what.machine = MS_RECYCLING_CENTER,
                .description = "When a garbage leave the door it has a one"
                               "in 10 chance of disappearing"
        }

        },

        {18, "Eric Lejeune", 1000, 200, "The cost of FISE decreases by 5E and 2DD"
                                        " (min 5E and 2DD)", .effects = {
                .mode = ON_BUY,
                .onOther = 1,
                .what.other = SUB_FISE,
                .modifierE = -5,
                .modifierDD = -2,
                .min_costE = 5,
                .min_costDD = 2,
                .description = "The cost of FISE decreases by 5E and 2DD min 5E and 2DD"
        }

        },

        {19, "Christine Mathias", 1000, 200, "The cost of FISA decreases by 5E and 2DD"
                                             " (min 5E and 2DD)", .effects = {
                .mode = ON_BUY,
                .onOther = 1,
                .what.other = SUB_FISA,
                .modifierE = -5,
                .modifierDD = -2,
                .min_costE = 5,
                .min_costDD = 2,
                .description = "The cost of FISA decreases by 5E and 2DD min 5E and 2DD"
        }

        },

        {20, "Stefiana Dumbrava", 100, 200, "The cost of destroying recycling center"
                                            " decreases by 5E and 25DD ", .effects = {
                .mode = DESTROY,
                .onOther = 0,
                .what.machine = MS_RECYCLING_CENTER,
                .modifierE = -5,
                .modifierDD = -25,
                .min_costE = 5,
                .min_costDD = 25,
                .description = "The cost of destroying recycling center decreases by 5E and 25DD (min 5E\n"
                               "and 25DD)."
        }

        },

        {21, "Stefiana Dumbrava", 100, 200, "The cost of destroying recycling center"
                                            " decreases by 5E and 25DD ", .effects = {
                .mode = DESTROY,
                .onOther = 0,
                .what.machine = MS_RECYCLING_CENTER,
                .modifierE = -5,
                .modifierDD = -25,
                .min_costE = 5,
                .min_costDD = 25,
                .description = "The cost of destroying recycling center decreases by 5E and 25DD (min 5E\n"
                               "and 25DD)."
        }

        },
};

int staff_isIDValid(int id) {
    for (int i = 0; i < NUMBER_OF_STAFFS; ++i) {
        if (staff_list[i].id == id) {
            return i;
        }
    }
    return -1;
}

const Staff* staff_getStaffByID(int id) {
    int index = staff_isIDValid(id);
    if (index >= 0) {
        return &(staff_list[index]);
    } else {
        return NULL;
    }
}

char* staff_getStaffNameByID(int id) {
    const Staff* member = staff_getStaffByID(id);
    if (member != NULL) {
        return member->name;
    }else {
        return NULL;
    }
}

int staff_getStaffCostEByID(int id) {
    const Staff* member = staff_getStaffByID(id);
    if (member != NULL) {
        return member->costE;
    }else {
        return -1;
    }
}

int staff_getStaffCostDDByID(int id) {
    const Staff* member = staff_getStaffByID(id);
    if (member != NULL) {
        return member->costDD;
    }else {
        return -1;
    }
}

char* staff_getStaffDescriptionByID(int id) {
    const Staff* member = staff_getStaffByID(id);
    if (member != NULL) {
        return member->description;
    }else {
        return NULL;
    }
}

const Effect* staff_getStaffEffectByID(int id) {
    const Staff* member = staff_getStaffByID(id);
    if (member != NULL) {
        return &(member->effects);
    }else {
        return NULL;
    }
}

int staff_getStaffID(const Staff *staff) { return staff->id; }

char* staff_getStaffName(const Staff *staff) { return staff->name; }

int staff_getStaffCostE(const Staff *staff) { return staff->costE; }

int staff_getStaffCostDD(const Staff *staff) { return staff->costDD; }

char* staff_getStaffDescription(const Staff *staff) { return staff->description; }

const Effect* staff_getStaffEffect(const Staff *staff) { return &(staff->effects); }

const Staff *staffInfo_getByModeAndType(Mode mode, Target type){
    int check;
    for (int i = 0; i < NUMBER_OF_STAFFS; ++i) {
        if(staff_list[i].effects.mode == mode){

            if(staff_list[i].effects.onOther){
                check = staff_list[i].effects.what.other == type.other;
            } else {
                check = staff_list[i].effects.what.machine == type.machine;
            }

            if(check){
                return &(staff_list[i]);
            }
        }
    }
    return NULL;
}

Dictionary* staff_createStaffDictionary() {
    Dictionary* dict = (Dictionary*) malloc(sizeof(Dictionary));
    Couple* tabStaff = (Couple*) malloc(NUMBER_OF_STAFFS*sizeof(Couple));

    dict->length = NUMBER_OF_STAFFS;
    for (int i = 0; i < dict->length; ++i) {
        tabStaff[i].keys.content.number = staff_list[i].id;
        tabStaff[i].values.content.number = 0;
    }
    dict->entries = tabStaff;

    return dict;
}

int staff_getNumberStaffByID(const Dictionary* dict, int id) {
    int index = staff_isIDValid(id);
    if (index >= 0) {
        return dict->entries[index].values.content.number;
    } else {
        return -1;
    }
}

void staff_hireStaff(Dictionary* dict, int id) {
    int index = staff_isIDValid(id);
    if (index >= 0) {
        dict->entries[index].values.content.number++;
    }
}

ErrorCode staff_destroyStaffDictionary(Dictionary* dict) {
    free(dict->entries);
    free(dict);
    return NO_ERROR;
}