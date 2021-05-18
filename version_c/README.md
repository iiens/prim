# Prim

Our ``c-version`` compile with

* a **Makefile** : ``make``  then `make run`
* a **CMakeList**
* a **command** : ``gcc -Wall -Wextra -std=c99 src/main.c
  -o bin/prim`` then `./bin/prim`
* Using **docker** : ``docker build -t prim:latest .``
then ``docker run -it prim``
  
Unless you are using docker, you will have
to install ncurses

* check if installed :  `ls -la /usr/include/ncurses.h`
* if not install : `sudo apt-get install libncurses5-dev libncursesw5-dev`

### Tests

You can run tests with `make tests` then `make run_tests`,
CUnit is required.

### Documentation

You can find latest documentation in
``doxygen`` folder.

You can generates it using

* `doxygen Doxyfile`
* `style\doxygen.py DoxyCSS`

For the later one, you need python and Pygments

* install python and pip
* pip: `sudo apt-get install python3-pip` (linux)
* pygments: `pip3 install jinja2 Pygments`

### Team

Current version is ``1.0.x`` (2021-05-02).

Main contributors

* Valentin DREANO
* Antoine MAN
* Quentin RAMSAMY- -AGEORGES 
* Ramzy ZEBRIR

This game was requested by ``Dimitri WATEL``.