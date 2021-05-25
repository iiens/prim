import {Case, CaseType, Map, PRODUCTION_MODE} from "../model/map"
import {Game} from "../game";
import {Action} from "./mappings";
import {Box, Cardinal, Direction, Machine, MachineInfo, MachineStuff} from "../model/machine";
import {getRandomInt} from "./utilities";
import {Config} from "./config";
import {Translation, TrKeys} from "./translation";
import {Logger} from "../model/logger";
import {EventType, MachineEvent} from "./events";

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
export class Interface {

    private static showResource = false;
    private static showGarbage = false;

    // current canvas
    private static lastCanvas: HTMLCanvasElement;
    private static lastCase: object;
    // reload show case with current selected case
    // should not be called in reload since we only want to call it when
    // a specific action is done (buy, update, destroy) and not at each reload.
    static get getLastCase () { return this.lastCase; };
    static set setLastCase (lastCase: object) { this.lastCase = lastCase; };

    static reloadShowCase() {
        if(this.lastCanvas == null) this.reload(); // reload so that's ok
        if(this.lastCase == null) return; // nothing to do
        console.log("redraw show case")
        // @ts-ignore call with last
        InterfaceUtils.handleCaseSelection(this.lastCase.tileX, this.lastCase.tileY, Game.map,
            document.getElementById('game-stats'), this.lastCanvas,
            // @ts-ignore
            this.lastCase.tileSize, this.lastCase.startX, this.lastCase.startY)
    }

    public static init(){
        this.reload();
        this.renderMap(Game.map); // TODO Corriger problème d'affichage image first turn
    }

    /**
     * Reload interface. We should use this
     * to update the map, the E,DD,... values
     * that are shown.
     */
    public static reload(){
        let map = Game.map;
        this.renderGameScreen(map)
        this.renderMap(map)
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
    static renderMap(map: Map, showResource = false, showGarbage = false,
                     save = false) {
        let logger = Logger.Instance;
        logger.debug('Begin renderMap');

        if (save){ // set
           Interface.showGarbage = showGarbage;
           Interface.showResource = showResource;
        } else { // load and ignore curent value
            showResource =  Interface.showResource;
            showGarbage = Interface.showGarbage;
        }

        // copy of https://stackoverflow.com/questions/9140101/creating-a-clickable-grid-in-a-web-browser
        const startX : number = 0;
        const startY : number = 0;
        const drawGrid = (canvas: any, ctx: any, tileSize: number) => {
            logger.debug('Begin drawGrid');

            for (let y = 0; y < map.getHeight ; y++) {
                for (let x = 0; x < map.getWidth; x++) {
                    const Case = <Case>map.getCase(x, y);
                    const xx = x * tileSize + startX;
                    const yy = y * tileSize + startY;
                    // draw
                    ctx.strokeStyle = "#000";
                    ctx.strokeRect(xx, yy, tileSize, tileSize);
                    let content : string = "";
                    if (showResource){
                        content = Case.numberResources()+"";
                    }  else if (showGarbage) {
                        content = Case.numberGarbage()+"";
                    } else {
                        content = InterfaceUtils.getCaseText(Case);
                    }

                    if (Case.isMachine){
                        InterfaceUtils.drawMachine(Case, ctx, xx, yy);
                    } else {
                        InterfaceUtils.drawSpawner(content,ctx,xx,yy);
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
        if (ctx){
            ctx.font = "15px Segoe UI";
            ctx.textBaseline = "top";
            drawGrid(canvas, ctx, tileSize);
            let grid = document.getElementById('game-grid');
            if (grid){
                grid.innerHTML = '';
                grid.appendChild(canvas);
            }
        }

        let status = document.getElementById('game-stats');
        let tileX = -1;
        let tileY = -1;
        canvas.addEventListener("mousemove", evt => {
            //event.target.style.cursor = "pointer";
            tileX = Math.floor(((evt.offsetX-startX) / tileSize));
            tileY = Math.floor(((evt.offsetY-startY) / tileSize));
        });

        canvas.addEventListener("click", () => {
            InterfaceUtils.handleCaseSelection(tileX, tileY, map, status,
                canvas, tileSize, startX, startY)
        });

        canvas.addEventListener("mouseout", event => {
            /*if (status) {
                status.innerText = "";
            }*/
        });

        // at first show no case selected
        if (status){
            // hides all
            for (let i of status.children) {
                i.classList.add('d-none');
            }
            InterfaceUtils.manageClass('tr-game-case-selected', true, 'd-none')
        }
    }

    /**
     * Update game status screen
     */
    static renderGameScreen(map: Map) {
        let logger = Logger.Instance;
        logger.debug('Begin renderGameScreen');

        // @ts-ignore
        win.replaceText('turn', map.getNumberTurn)
        // @ts-ignore
        win.replaceText('e', map.getNumberE)
        // @ts-ignore
        win.replaceText('dd', map.getNumberDD)
        // @ts-ignore
        win.replaceText('fise', map.getNumberFISE)
        // @ts-ignore
        win.replaceText('fisa', map.getNumberFISA)
        // @ts-ignore
        win.replaceText('mode', map.getProductionFISA === PRODUCTION_MODE.E?"E":"DD")
        // @ts-ignore
        win.replaceText('score', map.getPlayerScore)
        // @ts-ignore
        win.replaceText('garbage', map.numberPollution)
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
        let logger = Logger.Instance;
        logger.debug('Begin renderActions');

        let greetings = (<string>Translation.get(TrKeys.TERMINAL_HELP))
            .replace("help", Game.config.keys.help)

        // @ts-ignore
        $('.terminal').terminal([Game.mappings.getMappingsFunctions(),
            function notFound(command: string){
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
            completion: Game.mappings.getKeys(),
            checkArity: false, // no check so allow default
        });
    }
}

class InterfaceUtils {

    static drawSpawner(content: any, ctx: any, xx: number, yy: number) {
        let logger = Logger.Instance;
        logger.debug('Begin drawSpawner');

        let url = '../../assets/img/map/';
        const numberImage : number = 15;
        let img = new Image();
        if(content == "S "){
            img.src = url+'Resource.png';
            img.onload = function() { ctx.drawImage(img, xx+1, yy+1); }
        } else if(content == "G "){
            // let gif = new GIF.loadFile(url+'Gate.gif');
            // ctx.drawImage(gif.image,0,0); // will draw the playing gif image
            img.src = url+'gate/convert_1.png';
            let i = 1;
            let canCall = true;
            img.onload = () => {
                if (canCall){
                    canCall = false;
                    setTimeout(function () {
                        i++;
                        if (i == 100) i = 1; // reset
                        img.src = `${url}gate/convert_${i}.png`;
                        ctx.drawImage(img, xx+1, yy+1);
                        canCall = true;
                    }, 60)
                }
                ctx.drawImage(img, xx+1, yy+1);
            }
        } else {
            img.src = url+'Sol/Random'+getRandomInt(numberImage)+'.png';
            img.onload = function() { ctx.drawImage(img, xx+1, yy+1); }
        }
    }

    static drawMachine(Case: Case, ctx: any, xx: number, yy: number) {
        let logger = Logger.Instance;
        logger.debug('Begin drawMachine');

        let mach = Case.getMachine();
        let img = new Image();

        switch (mach.type) {
            case MachineStuff.MS_JUNKYARD:
                img.src = <string>Config.getMachineStuff(mach.type)?.imageFile.get(Cardinal.SOUTH);
                break;

            case MachineStuff.MS_RECYCLING_CENTER:
            case MachineStuff.MS_COLLECTOR:
            case MachineStuff.MS_CONVEYOR_BELT:
                if (mach.isOrientationBottom(Direction.OUT)) { img.src = <string>Config.getMachineStuff(mach.type)?.imageFile.get(Cardinal.SOUTH);
                } else if (mach.isOrientationTop(Direction.OUT)) { img.src = <string>Config.getMachineStuff(mach.type)?.imageFile.get(Cardinal.NORTH);
                } else if (mach.isOrientationLeft(Direction.OUT)) { img.src = <string>Config.getMachineStuff(mach.type)?.imageFile.get(Cardinal.WEST);
                } else { img.src = <string>Config.getMachineStuff(mach.type)?.imageFile.get(Cardinal.EAST); }

                if(mach.type == MachineStuff.MS_CONVEYOR_BELT && (Case.numberResources() > 0 || Case.numberGarbage() > 0)) {
                    img.src = img.src.substring(0, img.src.length-4);
                    img.src = img.src+"_BOX.png";
                }
                break;
            case MachineStuff.MS_CROSS_BELT:
                if (mach.isOrientationBottomRight(Direction.OUT)) { img.src = <string>Config.getMachineStuff(mach.type)?.imageFile.get(Cardinal.EAST);
                } else if (mach.isOrientationTopLeft(Direction.OUT)) { img.src = <string>Config.getMachineStuff(mach.type)?.imageFile.get(Cardinal.WEST);
                } else if (mach.isOrientationBottomLeft(Direction.OUT)) { img.src = <string>Config.getMachineStuff(mach.type)?.imageFile.get(Cardinal.SOUTH);
                } else { img.src = <string>Config.getMachineStuff(mach.type)?.imageFile.get(Cardinal.NORTH); }

                if((Case.numberResources() > 0 || Case.numberGarbage() > 0)) {
                    img.src = img.src.substring(0, img.src.length-4);
                    img.src = img.src+"_BOX.png";
                }
                break;
        }
        img.onload = function() {
            ctx.drawImage(img, xx+1, yy+1);
        }
    }

    static getCaseText(c: Case | null) {
        let type = InterfaceUtils.parseCaseType(c);
        let orientation = InterfaceUtils.parseOrientation(c);
        return type+orientation;
    }

    private static parseCaseType(c: Case | null) : string {
        if (c === null || c === undefined) return " ";
        else {
            switch (c.caseType) {
                case CaseType.CASE_EMPTY: return " ";
                case CaseType.CASE_GATE: return "G";
                case CaseType.CASE_SOURCE: return "S"
                case CaseType.CASE_MACHINE: {
                    return <string>Config.getMachineStuff(c.getMachine().type)?.tag;
                }
            }
            return "?";
        }
    }

    private static parseOrientation(c: Case | null) : string {
        let logger = Logger.Instance;
        logger.debug('Begin parseOrientation');

        if (c == null) return " ";
        if ( c.isMachine ) {
            let m : Machine = c.getMachine();
            let s : MachineStuff = m.type; //!< machine stuff
            let d : Direction = Direction.IN;
            switch ( s ) { // NOLINT(hicpp-multiway-paths-covered)
                case MachineStuff.MS_COLLECTOR:
                case MachineStuff.MS_CONVEYOR_BELT:
                case MachineStuff.MS_RECYCLING_CENTER:
                    d = Direction.OUT;
                    if ( m.isOrientationTop(d) )
                        return '\u2191';
                    if ( m.isOrientationBottom(d) )
                        return '\u2191';
                    if ( m.isOrientationLeft(d) )
                        return '\u2191';
                    if ( m.isOrientationRight(d) )
                        return '\u2191';
                    break;
                case MachineStuff.MS_CROSS_BELT:
                    d = Direction.OUT;
                    if ( m.isOrientationBottomRight(d) )
                        return '3';
                    if ( m.isOrientationBottomLeft(d) )
                        return '1';
                    if ( m.isOrientationTopLeft(d) )
                        return '7';
                    if ( m.isOrientationTopRight(d) )
                        return '9';
                    break;
                case MachineStuff.MS_JUNKYARD:
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
    static formalizeXY(id: string, x: number, y: number) {
        let div = document.getElementById(id);
        if (div){
            div.setAttribute('data-x', x+"");
            div.setAttribute('data-y', y+"");
        }
    }

    /**
     * Set div inner text
     * @param id get by this ID
     * @param text with this text
     */
    static setText(id: string, text: string) {
        let div = document.getElementById(id)
        if (div) div.innerText = text;
    }

    static setImageSrc(id: string, src: string) {
        let image = <HTMLImageElement>document.getElementById(id)
        if (image) image.src = src;
    }

    static manageClass(id: string, remove: boolean, ...tokens: string[]) {
        let c = (<HTMLElement>document.getElementById(id)).classList;
        if (remove){
            tokens.forEach(t => c.remove(t))
        } else {
            tokens.forEach(t => c.add(t))
        }
    }

    static setHTML(id: string, html: string) {
        let div = document.getElementById(id)
        if (div) div.innerHTML = html;
    }

    static handleCaseSelection(tileX: number, tileY: number, map: Map, status: HTMLElement | null,
                               canvas: HTMLCanvasElement, tileSize: number, startX: number, startY: number)
    {
        let ctx = canvas.getContext('2d');
        if (ctx){
            let xx, yy;
            // color back in black last case
            let lastCase = Interface.getLastCase;
            if (lastCase){ // @ts-ignore
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
            Interface.setLastCase = { tileX, tileY, canvas, tileSize, startX, startY }
        }


        if(tileX >= 0 && tileY >= 0) {
            if (tileX < map.getWidth && tileY < map.getHeight) {
                if (status) {
                    // ...
                    let p = <Case>map.getCase(tileX, tileY);
                    let type = <CaseType>p.caseType;
                    let resource = 0, garbage = 0;

                    // hides all
                    for (let i of status.children) {
                        i.classList.add('d-none');
                    }

                    switch (type) {
                        case CaseType.CASE_GATE:
                            let box = p.getBox();
                            if (box != null) {
                                garbage = box.numberGarbage;
                            }
                            // show gate
                            InterfaceUtils.manageClass('gate-selected', true, 'd-none');
                            // set garbage
                            InterfaceUtils.setText('gate-selected-garbage', garbage + '')
                            break;
                        case CaseType.CASE_MACHINE:
                            let machineInfo = <MachineInfo>Config.getMachineStuff(p.getMachine().type);
                            // get number resources/garbage
                            for (let i = 0; i < Machine.NUMBER_CARDINAL; i++) {
                                let box = <Box>p.getMachine().getBox(i);
                                if (box != null) {
                                    resource += box.numberResources;
                                    garbage += box.numberGarbage;
                                }
                            }
                            // show machine menu
                            InterfaceUtils.manageClass('machine-selected', true, 'd-none');
                            // update
                            InterfaceUtils.formalizeXY('update-selected', tileX, tileY)
                            // destroy
                            InterfaceUtils.formalizeXY('destroy-selected', tileX, tileY)
                            // don't show for collector since they won't be something on it
                            // todo: should be an attribute of machine info
                            InterfaceUtils.manageClass('machine-content-selected',
                                p.getMachine().type !== MachineStuff.MS_COLLECTOR, 'd-none')
                            // hides ressources div for some
                            InterfaceUtils.manageClass('machine-r-div-selected',
                                !(p.getMachine().type === MachineStuff.MS_RECYCLING_CENTER
                                || p.getMachine().type === MachineStuff.MS_JUNKYARD), 'd-none')
                            // resources/garbage/level
                            InterfaceUtils.setText('machine-r-selected', resource + '')
                            InterfaceUtils.setText('machine-g-selected', garbage + '')
                            // information
                            InterfaceUtils.setText('machine-name-selected', machineInfo.name(
                                Translation.getLanguage()
                            ) + '')
                            let image = <string>machineInfo.imageFile.get(Cardinal.SOUTH);
                            InterfaceUtils.setImageSrc('machine-image-selected', image)

                            // check if upgrade div
                            let upgradeDIV = <HTMLElement>document.getElementById('upgrade-machine-div');
                            if (machineInfo.canUpgrade) {
                                InterfaceUtils.setText('machine-lvl-selected', p.getMachine().level + '')

                                let machineEvent : MachineEvent = Game.map.getCostUpgrade(machineInfo,
                                    EventType.UPGRADE_MACHINE);

                                InterfaceUtils.setHTML('machine-info-selected',`
                                        ${machineInfo.upgrade(Translation.getLanguage())} <br/>
                                        ${Translation.get(TrKeys.GAME_COST)} ${machineEvent.costE} E ${machineEvent.costDD} DD
                                 `);
                                upgradeDIV.classList.remove('d-none')
                            } else {
                                upgradeDIV.classList.add('d-none')
                            }
                            InterfaceUtils.setText('machine-desc',
                                machineInfo.description(Translation.getLanguage()))
                            break;
                        case CaseType.CASE_SOURCE:
                            // show buy menu since empty
                            InterfaceUtils.manageClass('source-selected', true, 'd-none');
                            break;
                        default:
                            // show buy menu since empty
                            InterfaceUtils.manageClass('empty-selected', true, 'd-none');
                            // buy, set x and y
                            InterfaceUtils.formalizeXY('buy-button', tileX, tileY)
                            break;
                    }
                }
            }
        }
    }
}