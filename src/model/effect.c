#include "../../headers/data/effect.h"

//todo: too much methods without a "comment"
// please use a method block comment
// such as
// /*
// * these methods are used for ...
// */
// then some methods again and again. To split since it's unreadable :-(

Mode effect_getMode(const Effect *effect) { return effect->mode; }

Target effect_getWhat(const Effect *effect){ return effect->what; }

bool effect_getOnOther(const Effect *effect){ return effect->onOther; }

//todo: modifierRes is a float, please cast it to int
int effect_getModifierRes(const Effect *effect){ return effect->modifierRes; }

int effect_getModifierFISA(const Effect *effect){ return effect->modifierFISA; }

int effect_getModifierFISE(const Effect *effect){ return effect->modifierFISE; }

int effect_getModifierE(const Effect *effect){ return effect->modifierE; }

int effect_getModifierDD(const Effect *effect){ return effect->modifierDD; }

int effect_getModifierCapacity(const Effect *effect){ return effect->modifierCapacity; }

int effect_getMinCostE(const Effect *effect){ return effect->min_costE; }

int effect_getMinCostDD(const Effect *effect){ return effect->min_costDD; }

char* effect_getDescription(const Effect *effect){ return effect->description; }

