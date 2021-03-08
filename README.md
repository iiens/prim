# IT Project in C

The subject can be found
at in the doc folder and the git
at https://gitlab.pedago.ensiie.fr/groupe-1-projet-info-s2/projet-info-s2-en-c/-/tree/lot_a.

Must be compiled must our Makefile (make build,
make run) or using ``gcc -Wall -Wextra -std=c99 src/main.c``.

### Description

Nothing for now.

### Code guidelines

**General**
* code and comments should be written in english
* we should write include by alphabetical order, and a comment by include
* use relevant names for variables when it's smart to do so (not index instead of i)
* lines should have less that 79 columns

**Syntax**
* we will write `if ( ... ) {` (same spaces and { at the end)
* same for : for, while, switch statements
* functions should be coded like this (excluding declarations and main)
```c
  void name( args )
  {
  // code
  }  
  ```
* this is how a struct should be declared
```c
typedef struct MachineInfo_S {
    int type; //!< int which represent the type of the machine
} MachineInfo; //!< ....
```
* you must declare all variables at the start of a bloc
* first declare then initialize variables
* if a variable is only read, then use const
* no hard-coded values, use enum or define
* the pointer star (`*`) must be after the type not the name

Adapted from
* https://suckless.org/
* https://man.openbsd.org/style
* http://doc.cat-v.org/bell_labs/pikestyle
* https://www.kernel.org/doc/Documentation/process/coding-style.rst

### Team

* Valentin DREANO
* Antoine MAN
* Quentin RAMSAMY--AGEORGES 
*  Ramzy ZEBRIR