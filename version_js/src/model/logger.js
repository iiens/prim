"use strict";
Object.defineProperty(exports, "__esModule", { value: true });
exports.Logger = void 0;
const fs = require('fs');
const path = require('path');
class Logger {
    constructor() {
        this._fileName = path.join(__dirname, "log.json");
        // Écriture des nouvelles données
        // fs.writeFileSync(this._fileName, '{}');
        // Initialisation
        this._level = Logger.Levels.Warning;
        this._console = false;
    }
    static get Instance() {
        if (Logger.instance === undefined) {
            Logger.instance = new Logger();
        }
        return Logger.instance;
    }
    ;
    set level(value) {
        this._level = value;
    }
    ;
    set console(value) {
        this._console = value;
    }
    ;
    log(message, level) {
        if (level >= this._level) {
            let env = undefined;
            let currentsDate = new Date();
            let datetime = currentsDate.getDate() + "/"
                + (currentsDate.getMonth() + 1) + "/"
                + currentsDate.getFullYear() + " @ "
                + currentsDate.getHours() + ":"
                + currentsDate.getMinutes() + ":"
                + currentsDate.getSeconds();
            switch (level) {
                case Logger.Levels.Debug:
                    if (this._console) {
                        console.debug(message);
                    }
                    env = {
                        datetime: datetime,
                        level: "Debug",
                        message: message
                    };
                    break;
                case Logger.Levels.Info:
                    if (this._console) {
                        console.info(message);
                    }
                    env = {
                        datetime: datetime,
                        level: "Info",
                        message: message
                    };
                    break;
                case Logger.Levels.Warning:
                    if (this._console) {
                        console.warn(message);
                    }
                    env = {
                        datetime: datetime,
                        level: "Warning",
                        message: message
                    };
                    break;
                case Logger.Levels.Error:
                    if (this._console) {
                        console.error(message);
                    }
                    env = {
                        datetime: datetime,
                        level: "Error",
                        message: message
                    };
                    break;
                default:
                    break;
            }
            if (env !== undefined) {
                // // Récupération des données dans le fichier
                // let dataFile: string = fs.readFileSync(this._fileName, 'utf8');
                //
                // // Transformation des données en Json
                // let dataJson = JSON.parse(dataFile);
                //
                // // Vérification de la présence de Json
                // if (dataJson.messages === undefined) {
                //     dataJson.messages = [];
                // }
                //
                // // Ajout des nouvelle données
                // dataJson.messages.push(env);
                //
                // // Transformation du tableau en json
                // let dataWrite = JSON.stringify(dataJson);
                //
                // // Placement de retour à a ligne après chaque fin d'objet
                // const searchRegExp = new RegExp('},', 'g');
                // dataWrite = dataWrite.replace(searchRegExp, '},\n')
                //
                // // Écriture des nouvelles données
                // fs.writeFileSync(this._fileName, dataWrite);
            }
        }
    }
    debug(message) {
        this.log(message, Logger.Levels.Debug);
    }
    info(message) {
        this.log(message, Logger.Levels.Info);
    }
    warn(message) {
        this.log(message, Logger.Levels.Warning);
    }
    error(message) {
        this.log(message, Logger.Levels.Error);
    }
}
exports.Logger = Logger;
(function (Logger) {
    let Levels;
    (function (Levels) {
        Levels[Levels["Debug"] = 0] = "Debug";
        Levels[Levels["Info"] = 1] = "Info";
        Levels[Levels["Warning"] = 2] = "Warning";
        Levels[Levels["Error"] = 3] = "Error";
        Levels[Levels["Off"] = 4] = "Off";
    })(Levels = Logger.Levels || (Logger.Levels = {}));
})(Logger = exports.Logger || (exports.Logger = {}));
