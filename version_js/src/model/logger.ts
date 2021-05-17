const fs = require('fs');

export class Logger {
    private static instance : Logger | undefined;

    private readonly _fileName : string;

    private _level : Logger.Levels;

    private _console : boolean;

    private constructor() {
        this._fileName = "./logs/log.json";

        // Écriture des nouvelles données
        fs.writeFileSync(this._fileName, '{}');

        // Initialisation
        this._level = Logger.Levels.Debug;
        this._console = false;
    }

    static get Instance() : Logger {
        if (Logger.instance === undefined) {
            Logger.instance = new Logger();
        }

        return Logger.instance;
    };

    set level(value: Logger.Levels) {
        this._level = value;
    };

    set console(value: boolean) {
        this._console = value;
    };

    log(message: string, level: Logger.Levels) {
        if (level >= this._level) {
            let env: { datetime: string; level: string; message: string; } | undefined = undefined;

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
                    }
                    break;
                case Logger.Levels.Info:
                    if (this._console) {
                        console.info(message);
                    }
                    env = {
                        datetime: datetime,
                        level: "Info",
                        message: message
                    }
                    break;
                case Logger.Levels.Warning:
                    if (this._console) {
                        console.warn(message);
                    }
                    env = {
                        datetime: datetime,
                        level: "Warning",
                        message: message
                    }
                    break;
                case Logger.Levels.Error:
                    if (this._console) {
                        console.error(message);
                    }
                    env = {
                        datetime: datetime,
                        level: "Error",
                        message: message
                    }
                    break;
                default:
                    break;
            }

            if (env !== undefined) {
                // Récupération des données dans le fichier
                let dataFile: string = fs.readFileSync(this._fileName, 'utf8');

                // Transformation des données en Json
                let dataJson = JSON.parse(dataFile);

                // Vérification de la présence de Json
                if (dataJson.messages === undefined) {
                    dataJson.messages = [];
                }

                // Ajout des nouvelle données
                dataJson.messages.push(env);

                // Transformation du tableau en json
                let dataWrite = JSON.stringify(dataJson);

                // Placement de retour à a ligne après chaque fin d'objet
                const searchRegExp = new RegExp('},', 'g');
                dataWrite = dataWrite.replace(searchRegExp, '},\n')

                // Écriture des nouvelles données
                fs.writeFileSync(this._fileName, dataWrite);
            }
        }
    }

    debug (message: string) {
        this.log(message, Logger.Levels.Debug);
    }

    info (message: string) {
        this.log(message, Logger.Levels.Info);
    }

    warn (message: string) {
        this.log(message, Logger.Levels.Warning);
    }

    error (message: string) {
        this.log(message, Logger.Levels.Error);
    }
}

export namespace Logger {
    export enum Levels {
        Debug,
        Info,
        Warning,
        Error,
        Off
    }
}