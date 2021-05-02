/**
 *
 * This file is supposed to replace any
 * values that are used in rules.html
 * and may change according to the current
 * configuration.
 *
 */
// 10 000 ressources
win.replaceText('game-goal', config.constants.NUMBER_RESOURCE_WIN)
// minus 1 DD per turn
win.replaceText('game-dd-malus',1) //todo: should be a const
// number of sources
win.replaceText('game-nb-sources',config.constants.NUMBER_OF_SOURCES)
// production per turn
win.replaceText('game-production', config.constants.NB_RESOURCE_PRODUCT_BY_SOURCE)
// source produces each x turns
win.replaceText('game-turns-prod', config.constants.NB_TURN_PRODUCTION_SOURCE)
// fise E production
win.replaceText('game-fise-e', config.constants.PRODUCTION_FISE_E)
// fise DD production
win.replaceText('game-fise-dd', config.constants.PRODUCTION_FISE_DD)
// fisa E production
win.replaceText('game-fisa-e', config.constants.PRODUCTION_FISA_E)
// fisa DD production
win.replaceText('game-fisa-dd', config.constants.PRODUCTION_FISA_DD)
// how many turn fisa produce
win.replaceText('game-fisa-turn', config.constants.NB_TURN_FISA)