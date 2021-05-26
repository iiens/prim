# How to read the code

Electron is changing a lot and most of features
used here are deprecated or should not be used
in electron ``13.0.0``. 

Since we didn't have a lot of knowledge about electron,
we used some old templates as a base and we may change
that in the future

* [ ] do not use remote module
* [ ] do not use BrowserWindow ?
* [ ] use ipc / context isolation
* [ ] and they may be others things that we haven't figured

## Entry point

We use ``main.js`` as the entry point of our program. We
open our window here, load ``view/index.html`` and
choose that the ``preload.js`` script will be executed
after rendering the html.

In ``preload.js``, we are checking which page it is
and loading translation, modules, ... We are also saving
some variables globally using ``window`` but that's a mistake
and will be fixed.

## Pages

We got a page per view, and a script in ``view/handlers/``
for each view. Some may have more such as popup/go_back
script. We are simply using ``a`` tags to move between
pages, and ``localstorage`` to save session data.

``Game.ts`` is supposed to handle ``localstorage``-specific
actions.

## Model

You can find in this folder classes such as the ``Map``,
``Machines``-related, `Staff-related` classes... We
are creating staffs in ``Staffs.ts`` but machines
are created in ``utils/Config.ts``. Staffs creation
may be moved later but that's 600 lines of code used
by the map since everything is packaged so may are still
wondering how we should handle that.

## Utils

Events are used to ask all staffs is they want to modify
something that will happens such as the price
of a machine.

Code are errors code or success code used in the application.

Interface handle game-related interface methods such as
renderMap, ...

Mapping handles for each action, what code should be executed
such as "end turn" would trigger the call of the map
function "end turn" and reloading the map...

Translation is used to handles all translations,
we got a french and an english version for each text here.