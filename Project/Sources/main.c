/* Jindrich Dudek */
/* xdudek04       */
/* Projekt do IMP */
/* 2015           */
#include <hidef.h> /* for EnableInterrupts macro */
#include "derivative.h" /* include peripheral declarations */

#define VELIKOST_PANELU 32
#define VELIKOST_POLE 64
#define INIT 0
#define ROT_HORIZONTAL 1
#define ROT_VERTICAL 2


/* Pole obsahujici jednotlive sloupce pro kazdy znak. MSB odpovida spodni diode ve visualisation tool. */
unsigned char loginSloupce[] = {
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

void nastavPanel(unsigned char *zobrazovaciPanel,int x, int y) {
int i; //ridici promenna cyklu
x = x % VELIKOST_POLE;

for (i = VELIKOST_PANELU -1; i >= 0; i--)
	zobrazovaciPanel[i] = loginSloupce[(i-x >= 0) ? (i-x) : (VELIKOST_POLE + (i-x))];

}

void main(void) {
unsigned char *tlacitkoInit = (unsigned char *) 0x00B0;
unsigned char *tlacitkoHoriz = (unsigned char *) 0x00B1;
unsigned char *tlacitkoVert = (unsigned char *) 0x00B2;
unsigned char *rychlostRotace = (unsigned char *) 0x00B3;
unsigned char *zobrazovaciPanel = (unsigned char *) 0x00B4;

int x = 0;
int y = 0;
unsigned operace = 0;
*tlacitkoInit = 0;
*tlacitkoHoriz = 0;
*tlacitkoVert = 0;
*rychlostRotace = 127;
nastavPanel(zobrazovaciPanel, x, y);


  EnableInterrupts; /* enable interrupts */
  /* include your code here */



  for(;;) {
    __RESET_WATCHDOG(); /* feeds the dog */
  	if(*tlacitkoInit)
  		operace = INIT;
  	else if (*tlacitkoHoriz)
  		operace = ROT_HORIZONTAL;
  	else if (*tlacitkoVert)
  		operace = ROT_VERTICAL;
    
    if (operace == INIT)
   	{
   		nastavPanel(zobrazovaciPanel, 0, 0);
   		x = 0;
   		y = 0;
   	} 
   	else if (operace == ROT_HORIZONTAL)
   	{
   		nastavPanel(zobrazovaciPanel, ++x, 0);
   	} 
   	else if(operace == ROT_VERTICAL)
   	{
   		nastavPanel(zobrazovaciPanel, 8, 8);
   	}
  } /* loop forever */
  /* please make sure that you never leave main */
}
