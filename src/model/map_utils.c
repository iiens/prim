#include "../../headers/utils/map_utils.h"
#include "../../headers/utils/const.h"

//todo: Ramzy constant ?
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

// TODO Valentin ; faire documentation en anglais
ErrorCode map_tryBuy(Map *m, int costE, int costDD) {
    if (map_getNumberE(m) >= costE) {
        if (map_getNumberDD(m) >= costDD) {
            map_setNumberE(m, costE);
            map_setNumberDD(m, costDD);

            return NO_ERROR;
        } else {
            return ERROR_NOT_ENOUGH_DD;
        }
    } else {
        return ERROR_NOT_ENOUGH_E;
    }
}

void productionFise(Map *m) {
    int productionE = PRODUCTION_FISE_E;
    int productionDD = PRODUCTION_FISE_DD;

    int numberFise = map_getNumberFISE(m);

    // Prendre en compte les effets de staff
    const Staff* staff = staffInfo_getByModeAndType(PRODUCTION, (Target) {.other = SUB_FISE});
    const Effect * effect = staff_getStaffEffect(staff);
    int idStaff = staff_getStaffID(staff);
    int numberStaff = 0; // TODO Valentin : récupérer nombre de fois staff possédé
    int modifE = effect_getModifierE(effect);
    int modifDD = effect_getModifierDD(effect);

    map_setNumberE(m, (productionE + (modifE * numberStaff)) * numberFise);
    map_setNumberDD(m, (productionDD+ (modifDD * numberStaff)) * numberFise);
}

void productionFisa(Map *m) {
    if (map_getNumberTurn(m) % NB_TURN_FISA == 0) {
        int productionE = PRODUCTION_FISA_E;
        int productionDD = PRODUCTION_FISA_DD;
        int numberFisa = map_getNumberFISA(m);

        // Prendre en compte les effets de staff
        const Staff* staff = staffInfo_getByModeAndType(PRODUCTION, (Target) {.other = SUB_FISA});
        const Effect * effect = staff_getStaffEffect(staff);
        int idStaff = staff_getStaffID(staff);
        int numberStaff = 0; // TODO Valentin : récupérer nombre de fois staff possédé
        int modifE = effect_getModifierE(effect);
        int modifDD = effect_getModifierDD(effect);

        if (map_getProductionFISA(m) == E_VALUE) {
            map_setNumberE(m, (productionE + (modifE * numberStaff)) * numberFisa);
        } else {
            map_setNumberDD(m, (productionDD+ (modifDD * numberStaff)) * numberFisa);
        }
    }
}

ErrorCode map_sendResourcesToGate(Map *m, int resources) {

    return NO_ERROR;
}

ErrorCode staff_actionAnneLaureLigozat(Map *m, int idStaff) {
    // Parcourir toutes les cases pour supprimer la moitie des déchets
    return NO_ERROR;
}

ErrorCode staff_actionChristopheMouilleron(Map *m, int idStaff) {
    // Récupération du staff et de son effet
    const Staff *staff = staff_getStaffByID(idStaff);
    const Effect *effect = staff_getStaffEffect(staff);

    // Recupération du nombre de fise et fisa
    int modifierFise = effect_getModifierFISE(effect);
    int modifierFisa = effect_getModifierFISA(effect);

    // Ajout des fise et fisa
    map_setNumberFISE(m, modifierFise);
    map_setNumberFISA(m, modifierFisa);

    return NO_ERROR;
}

ErrorCode staff_actionLaurentPrevel(Map *m, int idStaff) {
    // Récupération du staff et de son effet
    const Staff *staff = staff_getStaffByID(idStaff);
    const Effect *effect = staff_getStaffEffect(staff);
    int coefficient = effect_getModifierRes(effect);

    // Récupération du nomnre de fise et fisa
    int numberFise = map_getNumberFISE(m);
    int numberFisa = map_getNumberFISA(m);

    // Calcule du nombre de diplomé
    int fiseGraduate = numberFise * coefficient;
    int fisaGraduate = numberFisa * coefficient;

    // Nouveau nombre de fise et fisa
    map_setNumberFISE(m, (fiseGraduate * -1));
    map_setNumberFISA(m, (fisaGraduate * -1));

    // Envoie des ressource à la porte
    map_sendResourcesToGate(m, fisaGraduate + fiseGraduate);
    return NO_ERROR;
}