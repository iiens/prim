/*!
 * \file effect.c
 * \author Ramzy ZEBRIR and Antoine Man
 * \version 0.1
 * \date 04/03/2021
 * \see staff.h
 *
 * Contains information about effects
 */

#include "../../headers/data/effect.h"

/*
 * Function to get Mode attribute from an effect
 */
Mode effect_getMode(const Effect *effect) { return effect->mode; }

/*
 * Function to get What attribute from an effect
 */
Target effect_getWhat(const Effect *effect) { return effect->what; }

/*
 * Function to get OnOther attribute from an effect
 */
bool effect_getOnOther(const Effect *effect) { return effect->onOther; }

/*
 * Function to get ModifierRes attribute from an effect
 */
int effect_getModifierRes(const Effect *effect) { return (int) effect->modifierRes; }

/*
 * Function to get ModifierFISA attribute from an effect
 */
int effect_getModifierFISA(const Effect *effect) { return effect->modifierFISA; }

/*
 * Function to get ModifierFISE attribute from an effect
 */
int effect_getModifierFISE(const Effect *effect) { return effect->modifierFISE; }

/*
 * Function to get ModifierE attribute from an effect
 */
int effect_getModifierE(const Effect *effect) { return effect->modifierE; }

/*
 * Function to get ModifierDD attribute from an effect
 */
int effect_getModifierDD(const Effect *effect) { return effect->modifierDD; }

/*
 * Function to get ModifierCapacity attribute from an effect
 */
int effect_getModifierCapacity(const Effect *effect) { return effect->modifierCapacity; }

/*
 * Function to get MinCostE attribute from an effect
 */
int effect_getMinCostE(const Effect *effect) { return effect->min_costE; }

/*
 * Function to get MinCostDD attribute from an effect
 */
int effect_getMinCostDD(const Effect *effect) { return effect->min_costDD; }

/*
 * Function to get Description attribute from an effect
 */
char *effect_getDescription(const Effect *effect) { return effect->description; }

