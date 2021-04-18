# Tâche B

Le dossier `docs/` contient nos document et la dernière version
officielle de la documentation.

Vous pouvez compiler la documentation
* avec `doxygen Doxyfile` (à la racine)
* avec `style\doxygen.py DoxyCSS` (à la racine)

    * vous devez avoir python et pip d'installé
    * `sudo apt-get install python3-pip` (linux)
    * `pip3 install jinja2 Pygments`

sachant que le résultat se trouve dans `doxygen/`
et que la deuxième commande génère une belle
interface pour notre documentation.
  
La tâche B compile avec
`make`
(à la racine) et se lance avec `make run`.
Attention à avoir ncurses d'installé

  * `sudo apt-get install libncurses5-dev libncursesw5-dev`
  * on peut vérifier son installation
    en regardant si le fichier `ls -la /usr/include/ncurses.h` existe

Le projet compile aussi avec un CMakeList, ou encore
avec un docker. Pour la docker, les instructions
sont dans le Dockerfile.