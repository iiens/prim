// This file is required by the game.html file and will
// be executed in the renderer process for that window.
// No Node.js APIs are available in this process because
// `nodeIntegration` is turned off. Use `preload.js` to
// selectively enable features needed in the rendering
// process.

game.interface.init()

win.replaceText('max-score', game.config.constants.NUMBER_RESOURCE_WIN)