#include "../../headers/data/staff.h"
#include <stdio.h>

ErrorCode staff_isIDValid(int id) {
    if (id > 0 && id <= NUMBER_OF_STAFFS) {
        return NO_ERROR;
    }else{
        return ERROR_INVALID_MACHINE_NUMBER;
    }
}

const Staff* staff_getStaffByID(int id) {
    if (staff_isIDValid(id) == NO_ERROR) {
        return &(staff_list[id - 1]);
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
/*
Effect* staff_getStaffEffectByID(int id) {
    const Staff* member = staff_getStaffByID(id);
    if (member != NULL) {
        return &(member->effects);
    }else {
        return NULL;
    }
}
 */