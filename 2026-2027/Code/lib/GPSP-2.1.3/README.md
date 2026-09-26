# General Purpose Serial Protocol (GPSP)

Serial protocol library for Arduino

Purpose of this library is to enable programmers to use a simple protocol to share accross all their Arduino based projects, allowing for simpler communication between their arduino and less confusion when trying to communicate between or with projects

This project was heavily inspired by AT command as this protocol syntax was inspired by it.


Before we can start using library, we need to include library to our sketch

``` C++

#include <GPSP.h>

```

First, we create simple GPSP object and pass it the Stream we want to use.

``` C++

GPSP protocol(Serial); // Or any other Serial, including a SoftwareSerial

```

Then we can create some function to link to our protocol.

``` C++
// Exemple:
// The stream in which this function was called
// Args : Array of c-string
// Size : The number of arguments
void ECHO(Stream &stream, const char args[][50], int size) {
}
```

If your function encounters an issue those methods are at your disposition.

``` C++
GPSP::printError(Stream &stream, const char *errorMessage);
```

Then we can define and link our commands

``` C++

void setup() {
    // Structure: Function, Command name, Command description
    protocol.defineCommand({ECHO, "ECHO", "Does something"});
}
```

The next step is to periodically update our protocol.

``` C++

void loop() {
    protocol.update();
}

```

Exemple call :

```
ECHO;
OR
ECHO\n
OR
ECHO=Arg1,Arg2,...;
OR
ECHO=Arg1,Arg2,...\n
```
