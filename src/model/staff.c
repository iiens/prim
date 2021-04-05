#include "../../headers/data/staff.h"

#include <stdio.h>
#include <stdlib.h>

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

const Effect* staff_getStaffEffectByID(int id) {
    const Staff* member = staff_getStaffByID(id);
    if (member != NULL) {
        return &(member->effects);
    }else {
        return NULL;
    }
}

char* staff_getStaffName(const Staff *staff) { return staff->name; }

int staff_getStaffCostE(const Staff *staff) { return staff->costE; }

int staff_getStaffCostDD(const Staff *staff) { return staff->costDD; }

char* staff_getStaffDescription(const Staff *staff) { return staff->description; }

const Effect* staff_getStaffEffect(const Staff *staff) { return &(staff->effects); }

const Staff *staffInfo_getByModeAndType(Mode mode, Target type){
    int indexS = 0, check;
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
}