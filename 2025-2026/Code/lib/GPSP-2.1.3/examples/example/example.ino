#include <GPSP.h>

GPSP protocol(Serial);

void setup() {
    Serial.begin(9600);
    protocol.defineCommand({ECHO, "ECHO", "Sends back what it received\nECHO={message}"});
    protocol.defineCommand({FIBONACCI, "FIBONACCI", "Display Fibonacci Series up to first parameter value\nFIBONACCI={Max value}\nFIBONACCI"});
    protocol.defineCommand({ANALOG, "ANALOG", "Control a pin\nANALOG={pin},{[0-255]}"});
    protocol.defineCommand({PINMODE, "PINMODE", "Sets the mode of a pin\nPINMODE={pin},{INPUT or OUTPUT}"});
}

void loop() {
  protocol.update();
}


// PINMODE={pin},{INPUT or OUTPUT}
void PINMODE(Stream &stream, const char args[][50], int size) {
  if (size < 2) {
    GPSP::printError(stream, "Missing arguments, 2 required, HELP=PINMODE for more info");
    return;
  }
  
  int pin = atoi(args[0]);
  if (strcmp(args[1], "INPUT") == 0) {
    pinMode(pin, INPUT);
  } else if (strcmp(args[1], "OUTPUT") == 0) {
    pinMode(pin, OUTPUT);
  }
}

// ANALOG={pin},{[0-255]}
void ANALOG(Stream &stream, const char args[][50], int size) {
  if (size < 2) {
    GPSP::printError(stream, "Missing arguments, 2 required, HELP=ANALOG for more info");
    return;
  }

  int pin = atoi(args[0]);
  int value = constrain(atoi(args[1]), 0, 255);
  analogWrite(pin, value);
}

// ECHO={message}
void ECHO(Stream &stream, const char args[][50], int size) {
  for (int i = 0; i < size; i++) {
    if (i != 0)
      stream.write(',');
    stream.print(args[i]);
  }
  stream.println();
}

// FIBONACCI={Max value}
// FIBONACCI
void FIBONACCI(Stream &stream, const char args[][50], int size) {
  int n = size > 0 ? atoi(args[0]) : 50;

  int t1 = 0, t2 = 1, nextTerm = 0;

  stream.println(t1);
  stream.println(t2);

  nextTerm = t1 + t2;

  while(nextTerm <= n) {
      stream.println(nextTerm);
      t1 = t2;
      t2 = nextTerm;
      nextTerm = t1 + t2;
  }
}



