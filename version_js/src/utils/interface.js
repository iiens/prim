"use strict";
Object.defineProperty(exports, "__esModule", { value: true });
exports.Interface = void 0;
const map_1 = require("../model/map");
const game_1 = require("../game");
const machine_1 = require("../model/machine");
const utilities_1 = require("./utilities");
const config_1 = require("./config");
const translation_1 = require("./translation");
const logger_1 = require("../model/logger");
const events_1 = require("./events");
/**
 * \author Quentin Ra
 * \version 0.7
 * \date 20/03/2021
 *
 * This header contains any functions related to the interactions
 * between the player and the game.
 * <ul>
 * <li>print map</li>
 * <li>ask for level (see Difficulty) </li>
 * <li>ask for an action</li>
 * <li>ask for machine information for creation (see Machine)</li>
 * <li>ask for machine information for update/delete</li>
 * <li>ask for Staff information</li>
 * </ul>
 *
 */
class Interface {
    // reload show case with current selected case
    // should not be called in reload since we only want to call it when
    // a specific action is done (buy, update, destroy) and not at each reload.
    static get getLastCase() { return this.lastCase; }
    ;
    static set setLastCase(lastCase) { this.lastCase = lastCase; }
    ;
    static reloadShowCase() {
        if (this.lastCanvas == null)
            this.reload(); // reload so that's ok
        if (this.lastCase == null)
            return; // nothing to do
        console.log("redraw show case");
        // @ts-ignore call with last
        InterfaceUtils.handleCaseSelection(this.lastCase.tileX, this.lastCase.tileY, game_1.Game.map, document.getElementById('game-stats'), this.lastCanvas, 
        // @ts-ignore
        this.lastCase.tileSize, this.lastCase.startX, this.lastCase.startY);
    }
    static init() {
        this.reload();
        this.renderMap(game_1.Game.map); // TODO Corriger problème d'affichage image first turn
    }
    /**
     * Reload interface. We should use this
     * to update the map, the E,DD,... values
     * that are shown.
     */
    static reload() {
        let map = game_1.Game.map;
        this.renderGameScreen(map);
        this.renderMap(map);
        // this.renderActions()
    }
    /**
     * @brief Show the map
     *
     * We are waiting for a grid, like
     * <pre>
     *      0     1
     *   +----++----+
     * 0 | M  |     |
     *   +----++----+
     * </pre>
     * Where 0,1 are the column indexes and 0 is the row index. M is the first
     * letter for machine, but well no need to write a lot, just enough so that the
     * player can guess whether he would want to check this case or not.
     *
     * At the end, we want to find basic information such as
     * <ul>
     * <li>E value</li>
     * <li>DD value</li>
     * <li>which turn is it</li>
     * <li>number of FISE</li>
     * <li>number of FISA</li>
     * <li>the production mode</li>
     * <li>the number of hired staffs (or their names followed by the count if different of one)</li>
     * </ul>
     *
     * @param map a map
     * @param showResource true if we show a map of resources
     * @param showGarbage true if we show a map of garbage
     * @param save save showResource/showGarbage values. save is used if false.
     * @see Map type
     */
    static renderMap(map, showResource = false, showGarbage = false, save = false) {
        let logger = logger_1.Logger.Instance;
        logger.debug('Begin renderMap');
        if (save) { // set
            Interface.showGarbage = showGarbage;
            Interface.showResource = showResource;
        }
        else { // load and ignore curent value
            showResource = Interface.showResource;
            showGarbage = Interface.showGarbage;
        }
        // copy of https://stackoverflow.com/questions/9140101/creating-a-clickable-grid-in-a-web-browser
        const startX = 0;
        const startY = 0;
        const drawGrid = (canvas, ctx, tileSize) => {
            logger.debug('Begin drawGrid');
            for (let y = 0; y < map.getHeight; y++) {
                for (let x = 0; x < map.getWidth; x++) {
                    const Case = map.getCase(x, y);
                    const xx = x * tileSize + startX;
                    const yy = y * tileSize + startY;
                    // draw
                    ctx.strokeStyle = "#000";
                    ctx.strokeRect(xx, yy, tileSize, tileSize);
                    let content = "";
                    if (showResource) {
                        content = Case.numberResources() + "";
                    }
                    else if (showGarbage) {
                        content = Case.numberGarbage() + "";
                    }
                    else {
                        content = InterfaceUtils.getCaseText(Case);
                    }
                    if (Case.isMachine) {
                        InterfaceUtils.drawMachine(Case, ctx, xx, yy);
                    }
                    else {
                        InterfaceUtils.drawSpawner(content, ctx, xx, yy);
                    }
                }
            }
        };
        const size = map.getWidth;
        const tileSize = 35;
        let canvas = document.createElement("canvas");
        Interface.lastCanvas = canvas; // save
        canvas.width = tileSize * size + startX;
        canvas.height = tileSize * size + startY;
        const ctx = canvas.getContext("2d");
        if (ctx) {
            ctx.font = "15px Segoe UI";
            ctx.textBaseline = "top";
            drawGrid(canvas, ctx, tileSize);
            let grid = document.getElementById('game-grid');
            if (grid) {
                grid.innerHTML = '';
                grid.appendChild(canvas);
            }
        }
        let status = document.getElementById('game-stats');
        let tileX = -1;
        let tileY = -1;
        canvas.addEventListener("mousemove", evt => {
            //event.target.style.cursor = "pointer";
            tileX = Math.floor(((evt.offsetX - startX) / tileSize));
            tileY = Math.floor(((evt.offsetY - startY) / tileSize));
        });
        canvas.addEventListener("click", () => {
            InterfaceUtils.handleCaseSelection(tileX, tileY, map, status, canvas, tileSize, startX, startY);
        });
        canvas.addEventListener("mouseout", event => {
            /*if (status) {
                status.innerText = "";
            }*/
        });
        // at first show no case selected
        if (status) {
            // hides all
            for (let i of status.children) {
                i.classList.add('d-none');
            }
            InterfaceUtils.manageClass('tr-game-case-selected', true, 'd-none');
        }
    }
    /**
     * Update game status screen
     */
    static renderGameScreen(map) {
        let logger = logger_1.Logger.Instance;
        logger.debug('Begin renderGameScreen');
        // @ts-ignore
        win.replaceText('turn', map.getNumberTurn);
        // @ts-ignore
        win.replaceText('e', map.getNumberE);
        // @ts-ignore
        win.replaceText('dd', map.getNumberDD);
        // @ts-ignore
        win.replaceText('fise', map.getNumberFISE);
        // @ts-ignore
        win.replaceText('fisa', map.getNumberFISA);
        // @ts-ignore
        win.replaceText('mode', map.getProductionFISA === map_1.PRODUCTION_MODE.E ? "E" : "DD");
        // @ts-ignore
        win.replaceText('score', map.getPlayerScore);
        // @ts-ignore
        win.replaceText('garbage', map.numberPollution);
    }
    /**
     * Render action terminal
     * @brief Ask for the user action
     *
     * Ask for the user action
     * Should be a valid action, if not ask again.
     *
     * Actions returned should be implemented by
     *
     * <ul>
     * <li>{@link Action.SHOW_MAP}: interface_showMap</li>
     * <li>{@link Action.CANCEL_ACTION}: no function, can't be used here ! (only when an action got chosen)</li>
     * <li>{@link Action.EXIT} : caller should ends the program</li>
     * <li>{@link Action.LIST_ACTIONS} : call interface_listActions</li>
     * <li>{@link Action.END_TURN} : next turn, call of map_endTurn</li>
     *
     * <li>{@link Action.HIRE_FISE} : hire fise, call of map_hireFISE</li>
     * <li>{@link Action.HIRE_FISA} : hire fisa, call of map_hireFISA</li>
     * <li>{@link Action.CHANGE_FISA_MODE} : change fisa production mode, call of map_changeProductionFISA</li>
     *
     * <li>{@link Action.LIST_MACHINES} : should call interface_showMachinesList</li>
     * <li>{@link Action.BUY_MACHINE} : should ask interface_askAddMachine and interface_askMachineLocation</li>
     * then call map_addMachine
     * <li>{@link Action.BUY_STAFF} : should ask interface_askBuyStaff then map_buyStaff</li>
     * <li>{@link Action.LIST_STAFF} : should call interface_showStaffList</li>
     *
     * <li>{@link Action.UPGRADE_MACHINE} : interface_askMachineLocation then map_upgradeMachine</li>
     * <li>{@link Action.DESTROY_MACHINE} : interface_askMachineLocation then map_destroyMachine</li>
     * </ul>
     *
     * @return a valid action chosen by the user.
     * @see Action enum
     */
    static renderActions() {
        let logger = logger_1.Logger.Instance;
        logger.debug('Begin renderActions');
        let greetings = translation_1.Translation.get(translation_1.TrKeys.TERMINAL_HELP)
            .replace("help", game_1.Game.config.keys.help);
        // @ts-ignore
        $('.terminal').terminal([game_1.Game.mappings.getMappingsFunctions(), function notFound(command) {
                // @ts-ignore
                this.clear();
                // @ts-ignore
                this.echo(`[[;red;]Command ${command} Not Found!]`);
            }
        ], {
            greetings: greetings,
            name: 'action',
            height: 75,
            prompt: 'action> ',
            clear: true,
            autocompleteMenu: true,
            completion: game_1.Game.mappings.getKeys(),
            checkArity: false, // no check so allow default
        });
    }
}
exports.Interface = Interface;
Interface.showResource = false;
Interface.showGarbage = false;
class InterfaceUtils {
    static drawSpawner(content, ctx, xx, yy) {
        let logger = logger_1.Logger.Instance;
        logger.debug('Begin drawSpawner');
        let url = '../../assets/img/map/';
        const numberImage = 15;
        let img = new Image();
        if (content == "S ") {
            img.src = url + 'Resource.png';
        }
        else if (content == "G ") {
            // let gif = new GIF.loadFile(url+'Gate.gif');
            // ctx.drawImage(gif.image,0,0); // will draw the playing gif image
            img.src = url + 'Gate.png';
        }
        else {
            img.src = url + 'Sol/Random' + utilities_1.getRandomInt(numberImage) + '.png';
        }
        img.onload = function () {
            ctx.drawImage(img, xx + 1, yy + 1);
        };
    }
    static drawMachine(Case, ctx, xx, yy) {
        let logger = logger_1.Logger.Instance;
        logger.debug('Begin drawMachine');
        let mach = Case.getMachine();
        let img = new Image();
        switch (mach.type) {
            case machine_1.MachineStuff.MS_JUNKYARD:
                img.src = config_1.Config.getMachineStuff(mach.type)?.imageFile.get(machine_1.Cardinal.SOUTH);
                break;
            case machine_1.MachineStuff.MS_RECYCLING_CENTER:
            case machine_1.MachineStuff.MS_COLLECTOR:
            case machine_1.MachineStuff.MS_CONVEYOR_BELT:
                if (mach.isOrientationBottom(machine_1.Direction.OUT)) {
                    img.src = config_1.Config.getMachineStuff(mach.type)?.imageFile.get(machine_1.Cardinal.SOUTH);
                }
                else if (mach.isOrientationTop(machine_1.Direction.OUT)) {
                    img.src = config_1.Config.getMachineStuff(mach.type)?.imageFile.get(machine_1.Cardinal.NORTH);
                }
                else if (mach.isOrientationLeft(machine_1.Direction.OUT)) {
                    img.src = config_1.Config.getMachineStuff(mach.type)?.imageFile.get(machine_1.Cardinal.WEST);
                }
                else {
                    img.src = config_1.Config.getMachineStuff(mach.type)?.imageFile.get(machine_1.Cardinal.EAST);
                }
                if (mach.type == machine_1.MachineStuff.MS_CONVEYOR_BELT && (Case.numberResources() > 0 || Case.numberGarbage() > 0)) {
                    img.src = img.src.substring(0, img.src.length - 4);
                    img.src = img.src + "_BOX.png";
                }
                break;
            case machine_1.MachineStuff.MS_CROSS_BELT:
                if (mach.isOrientationBottomRight(machine_1.Direction.OUT)) {
                    img.src = config_1.Config.getMachineStuff(mach.type)?.imageFile.get(machine_1.Cardinal.EAST);
                }
                else if (mach.isOrientationTopLeft(machine_1.Direction.OUT)) {
                    img.src = config_1.Config.getMachineStuff(mach.type)?.imageFile.get(machine_1.Cardinal.WEST);
                }
                else if (mach.isOrientationBottomLeft(machine_1.Direction.OUT)) {
                    img.src = config_1.Config.getMachineStuff(mach.type)?.imageFile.get(machine_1.Cardinal.SOUTH);
                }
                else {
                    img.src = config_1.Config.getMachineStuff(mach.type)?.imageFile.get(machine_1.Cardinal.NORTH);
                }
                if ((Case.numberResources() > 0 || Case.numberGarbage() > 0)) {
                    img.src = img.src.substring(0, img.src.length - 4);
                    img.src = img.src + "_BOX.png";
                }
                break;
        }
        img.onload = function () {
            ctx.drawImage(img, xx + 1, yy + 1);
        };
    }
    static getCaseText(c) {
        let type = InterfaceUtils.parseCaseType(c);
        let orientation = InterfaceUtils.parseOrientation(c);
        return type + orientation;
    }
    static parseCaseType(c) {
        if (c === null || c === undefined)
            return " ";
        else {
            switch (c.caseType) {
                case map_1.CaseType.CASE_EMPTY: return " ";
                case map_1.CaseType.CASE_GATE: return "G";
                case map_1.CaseType.CASE_SOURCE: return "S";
                case map_1.CaseType.CASE_MACHINE: {
                    return config_1.Config.getMachineStuff(c.getMachine().type)?.tag;
                }
            }
            return "?";
        }
    }
    static parseOrientation(c) {
        let logger = logger_1.Logger.Instance;
        logger.debug('Begin parseOrientation');
        if (c == null)
            return " ";
        if (c.isMachine) {
            let m = c.getMachine();
            let s = m.type; //!< machine stuff
            let d = machine_1.Direction.IN;
            switch (s) { // NOLINT(hicpp-multiway-paths-covered)
                case machine_1.MachineStuff.MS_COLLECTOR:
                case machine_1.MachineStuff.MS_CONVEYOR_BELT:
                case machine_1.MachineStuff.MS_RECYCLING_CENTER:
                    d = machine_1.Direction.OUT;
                    if (m.isOrientationTop(d))
                        return '\u2191';
                    if (m.isOrientationBottom(d))
                        return '\u2191';
                    if (m.isOrientationLeft(d))
                        return '\u2191';
                    if (m.isOrientationRight(d))
                        return '\u2191';
                    break;
                case machine_1.MachineStuff.MS_CROSS_BELT:
                    d = machine_1.Direction.OUT;
                    if (m.isOrientationBottomRight(d))
                        return '3';
                    if (m.isOrientationBottomLeft(d))
                        return '1';
                    if (m.isOrientationTopLeft(d))
                        return '7';
                    if (m.isOrientationTopRight(d))
                        return '9';
                    break;
                case machine_1.MachineStuff.MS_JUNKYARD:
                    return ' '; // all
            }
        }
        return ' ';
    }
    /**
     * Set data-x and data-y for a div
     * @param id div id
     * @param x case x
     * @param y case y
     */
    static formalizeXY(id, x, y) {
        let div = document.getElementById(id);
        if (div) {
            div.setAttribute('data-x', x + "");
            div.setAttribute('data-y', y + "");
        }
    }
    /**
     * Set div inner text
     * @param id get by this ID
     * @param text with this text
     */
    static setText(id, text) {
        let div = document.getElementById(id);
        if (div)
            div.innerText = text;
    }
    static setImageSrc(id, src) {
        let image = document.getElementById(id);
        if (image)
            image.src = src;
    }
    static manageClass(id, remove, ...tokens) {
        let c = document.getElementById(id).classList;
        if (remove) {
            tokens.forEach(t => c.remove(t));
        }
        else {
            tokens.forEach(t => c.add(t));
        }
    }
    static setHTML(id, html) {
        let div = document.getElementById(id);
        if (div)
            div.innerHTML = html;
    }
    static handleCaseSelection(tileX, tileY, map, status, canvas, tileSize, startX, startY) {
        let ctx = canvas.getContext('2d');
        if (ctx) {
            let xx, yy;
            // color back in black last case
            let lastCase = Interface.getLastCase;
            if (lastCase) { // @ts-ignore
                xx = lastCase.tileX * tileSize + startX; // @ts-ignore
                yy = lastCase.tileY * tileSize + startX;
                ctx.strokeStyle = "#000";
                ctx.strokeRect(xx, yy, tileSize, tileSize);
            }
            xx = tileX * tileSize + startX;
            yy = tileY * tileSize + startY;
            // color new case
            ctx.strokeStyle = "#fff";
            ctx.strokeRect(xx, yy, tileSize, tileSize);
            // save new values
            Interface.setLastCase = { tileX, tileY, canvas, tileSize, startX, startY };
        }
        if (tileX >= 0 && tileY >= 0) {
            if (tileX < map.getWidth && tileY < map.getHeight) {
                if (status) {
                    // ...
                    let p = map.getCase(tileX, tileY);
                    let type = p.caseType;
                    let resource = 0, garbage = 0;
                    // hides all
                    for (let i of status.children) {
                        i.classList.add('d-none');
                    }
                    switch (type) {
                        case map_1.CaseType.CASE_GATE:
                            let box = p.getBox();
                            if (box != null) {
                                garbage = box.numberGarbage;
                            }
                            // show gate
                            InterfaceUtils.manageClass('gate-selected', true, 'd-none');
                            // set garbage
                            InterfaceUtils.setText('gate-selected-garbage', garbage + '');
                            break;
                        case map_1.CaseType.CASE_MACHINE:
                            let machineInfo = config_1.Config.getMachineStuff(p.getMachine().type);
                            // get number resources/garbage
                            for (let i = 0; i < machine_1.Machine.NUMBER_CARDINAL; i++) {
                                let box = p.getMachine().getBox(i);
                                if (box != null) {
                                    resource += box.numberResources;
                                    garbage += box.numberGarbage;
                                }
                            }
                            // show machine menu
                            InterfaceUtils.manageClass('machine-selected', true, 'd-none');
                            // update
                            InterfaceUtils.formalizeXY('update-selected', tileX, tileY);
                            // destroy
                            InterfaceUtils.formalizeXY('destroy-selected', tileX, tileY);
                            // don't show for collector since they won't be something on it
                            // todo: should be an attribute of machine info
                            InterfaceUtils.manageClass('machine-content-selected', p.getMachine().type !== machine_1.MachineStuff.MS_COLLECTOR, 'd-none');
                            // hides ressources div for some
                            InterfaceUtils.manageClass('machine-r-div-selected', !(p.getMachine().type === machine_1.MachineStuff.MS_RECYCLING_CENTER
                                || p.getMachine().type === machine_1.MachineStuff.MS_JUNKYARD), 'd-none');
                            // resources/garbage/level
                            InterfaceUtils.setText('machine-r-selected', resource + '');
                            InterfaceUtils.setText('machine-g-selected', garbage + '');
                            // information
                            InterfaceUtils.setText('machine-name-selected', machineInfo.name(translation_1.Translation.getLanguage()) + '');
                            let image = machineInfo.imageFile.get(machine_1.Cardinal.SOUTH);
                            InterfaceUtils.setImageSrc('machine-image-selected', image);
                            // check if upgrade div
                            let upgradeDIV = document.getElementById('upgrade-machine-div');
                            if (machineInfo.canUpgrade) {
                                InterfaceUtils.setText('machine-lvl-selected', p.getMachine().level + '');
                                let machineEvent = game_1.Game.map.getCostUpgrade(machineInfo, events_1.EventType.UPGRADE_MACHINE);
                                InterfaceUtils.setHTML('machine-info-selected', `
                                        ${machineInfo.upgrade(translation_1.Translation.getLanguage())} <br/>
                                        Cost ${machineEvent.costE} E ${machineEvent.costDD} DD
                                 `);
                                upgradeDIV.classList.remove('d-none');
                            }
                            else {
                                upgradeDIV.classList.add('d-none');
                            }
                            InterfaceUtils.setText('machine-desc', machineInfo.description(translation_1.Translation.getLanguage()));
                            break;
                        case map_1.CaseType.CASE_SOURCE:
                            // show buy menu since empty
                            InterfaceUtils.manageClass('source-selected', true, 'd-none');
                            break;
                        default:
                            // show buy menu since empty
                            InterfaceUtils.manageClass('empty-selected', true, 'd-none');
                            // buy, set x and y
                            InterfaceUtils.formalizeXY('buy-button', tileX, tileY);
                            break;
                    }
                }
            }
        }
    }
}
