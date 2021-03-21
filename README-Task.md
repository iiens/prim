# Tâche A

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
  
La tâche A compile avec
`gcc -Wall -Wextra -std=c99 -c src/main.c -o obj/main.o`
(à la racine).

Le projet compile aussi avec un CMakeList, même s'il 
y a un erreur pour le moment car il n'arrive
pas à assembler l'exécutable (ce qui est normal
car les fonctions n'ont pas été codées).