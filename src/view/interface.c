/*!
 * This file is like a
 * the design pattern adaptor
 * also called wrapper.
 *
 * But since we are in C, we need to put a
 * if(...) then call method, we can't do something
 * more efficient and generic.
 */

#include "../../headers/interface.h"

//\////////////////////////////\//
//\/ interface related
//\////////////////////////////\//

// init
ErrorCode interface_init() {
    return NO_ERROR;
}

// reload
ErrorCode interface_reload(const Map* map) {
    return NO_ERROR;
}

// close
ErrorCode interface_close() {
    return NO_ERROR;
}

//\////////////////////////////\//
//\/ Show related functions
//\////////////////////////////\//

void interface_showMap(const Map* map){
    // do nothing
}

void interface_showStaffList(const Map* map){
    // do nothing
}

void interface_showMachinesList(){
    // do nothing
}

void interface_listActions(){
    // do nothing
}

//\////////////////////////////\//
//\/ ask for user input
//\////////////////////////////\//

// action
Action interface_chooseAction(){
    // todo: you can switch that
    return ACTION_EXIT;
}

// difficulty
Difficulty interface_chooseDifficulty(){
    return DIFFICULTY_EASY;
}

Machine* interface_askAddMachine(){
    //todo: if you need a machine
    back = true; // go back
    return NULL;
}

Vector2D* interface_askMachineLocation(){
    //todo: if you need a vector2D
    back = true; // go back
    return NULL;
}

Staff* interface_askBuyStaff(){
    //todo: if you need a staff
    back = true;
    return NULL;
}

//\////////////////////////////\//
//\/ others
//\////////////////////////////\//

void interface_showError(ErrorCode e){

}