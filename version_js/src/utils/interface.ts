import {Case, CaseType, Map, PRODUCTION_MODE} from "../model/map"
import {Game} from "../game";
import {Action} from "./mappings";
import {Direction, Machine, MachineInfo, MachineStuff} from "../model/machine";

/*
todo: legend not in brut code
todo: colors for machines/...
todo: errors in red
 */

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

    public static init(){
        this.reload();
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
        this.renderActions()
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
        if (save){ // set
           Interface.showGarbage = showGarbage;
           Interface.showResource = showResource;
        } else { // load and ignore curent value
            showResource =  Interface.showResource;
            showGarbage = Interface.showGarbage;
        }

        // copy of https://stackoverflow.com/questions/9140101/creating-a-clickable-grid-in-a-web-browser
        const startX : number = 25;
        const startY : number = 25;
        const drawGrid = (canvas: any, ctx: any, tileSize: number) => {
            for (let y = 0; y < map.getHeight ; y++) {
                ctx.fillStyle = "#000";
                ctx.fillText(y+"", 0,  y * tileSize + startY + tileSize / 2 - 5);
                for (let x = 0; x < map.getWidth; x++) {
                    const Case = <Case>map.getCase(x, y);
                    const xx = x * tileSize + startX;
                    const yy = y * tileSize + startY;
                    // draw
                    ctx.fillStyle = "#ddd";
                    ctx.strokeRect(xx, yy, tileSize, tileSize);
                    ctx.fillStyle = "#000";
                    ctx.fillText(x+"", xx + tileSize/2 - 5, 0);
                    let content : string = "";
                    if (showResource){
                        content = Case.numberResources()+"";
                    }  else if (showGarbage) {
                        content = Case.numberGarbage()+"";
                    } else {
                        content = InterfaceUtils.getCaseText(Case);
                    }
                    ctx.fillText(content, xx + tileSize/2 - 10, yy + tileSize/2 - 8);
                    if (Case.isMachine){
                        let machine: Machine = Case.getMachine();
                        if (machine.getInfo().canUpgrade){
                            let oldFont = ctx.font;
                            let texte = `lvl ${machine.level}`
                            ctx.font = "10px Segoe UI";
                            ctx.fillStyle = "#2261e0";
                            ctx.fillText(texte, xx + tileSize/2 - 10, yy + tileSize - 10);
                            ctx.font = oldFont;
                        }
                    }
                }
            }
        };

        const size = map.getWidth;
        const tileSize = 35;
        const canvas = document.createElement("canvas");
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
    }

    /**
     * Update game status screen
     */
    static renderGameScreen(map: Map) {
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
        // @ts-ignore
        $('.terminal').terminal([Game.mappings.getMappingsFunctions(),
            function notFound(command: string){
                // @ts-ignore
                this.clear();
                // @ts-ignore
                this.echo(`[[;red;]Command ${command} Not Found!]`);
            }
        ], {
            greetings: `Use ${Game.config.keys.help} to get the list of available actions`,
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
                    return <string>MachineInfo.getMachineStuff(c.getMachine().type)?.tag;
                }
            }
            return "?";
        }
    }

    private static parseOrientation(c: Case | null) : string {
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
                        return '8';
                    if ( m.isOrientationBottom(d) )
                        return '2';
                    if ( m.isOrientationLeft(d) )
                        return '4';
                    if ( m.isOrientationRight(d) )
                        return '6';
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
}