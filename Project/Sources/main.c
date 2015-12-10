/* Jindrich Dudek */
/* xdudek04       */
/* Projekt do IMP */
/* 2015           */
#include <hidef.h> /* for EnableInterrupts macro */
#include "derivative.h" /* include peripheral declarations */

/* Pole obsahujici jednotlive sloupce pro kazdy znak. MSB odpovida spodni diode ve visualisation tool. */
unsigned char *loginColumns = {
/* znak x : */
0, //Prvni sloupec
0b01000010, //Druhy sloupec
0b00100100, // ...
0b00011000,
0b00011000,
0b00100100,
0b01000010,
0,
/* znak - d : */
0, //Prvni sloupec
0b00110000, //Druhy sloupec
0b01001000, // ...
0b01001000,
0b01001000,
0b01001000,
0b01111110,
0,
/* znak - u :  */
0,
0b00111110,
0b01000000,
0b01000000,
0b01000000,
0b01000000,
0b00111110,
0,
/* znak - d : */
0,
0b00110000,
0b01001000,
0b01001000,
0b01001000,
0b01001000,
0b01111110,
0,
/* znak - e : */
0,
0,
0b00111100,
0b01001010,
0b01001010,
0b01001010,
0b00101100,
0,
/* znak - k : */
0,
0,
0b01111110,
0b00011000,
0b00100100,
0b01000010,
0,
0,
/* znak - 0 : */
0,
0b00011000,
0b00100100,
0b01000010,
0b01000010,
0b00100100,
0b00011000,
0,
/* znak - 4: */
0,
0b00011110,
0b00010000,
0b00010000,
0b01111000,
0b00010000,
0,
0
};

void main(void) {

  EnableInterrupts; /* enable interrupts */
  /* include your code here */



  for(;;) {
    __RESET_WATCHDOG(); /* feeds the dog */
  } /* loop forever */
  /* please make sure that you never leave main */
}
