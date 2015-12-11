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
0b00111100,
0b01000000,
0b01000000,
0b01000000,
0b01000000,
0b00111100,
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
0,
0b00111100,
0b01000010,
0b01000010,
0b00111100,
0,
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
int j; //ridici promenna druheho cyklu
unsigned char tmp;
x = x % VELIKOST_POLE;

for (i = VELIKOST_PANELU -1; i >= 0; i--) //Pro kazdy sloupec v panelu
{
	tmp = loginSloupce[(i-x >= 0) ? (i-x) : (VELIKOST_POLE + (i-x))]; //Horizontalni rotace, podle promenne x se do promenne tmp
																	  //ulozi odpovidajici znak z pole loginSloupce
	y = y % 8; //Zajisti, ze y bude v rozmezi 0-7
	for (j = 0; j < y; j++) //Vertikalni rotace
		tmp = (tmp >> 1) | (tmp << 7); //Rotace smerem doprava realizovana pomoci bitovych posuvu
	
	zobrazovaciPanel[i] = tmp; //Vlozi (pripadne zrotovanou) polozku do zobrazovaciho panelu 
}
}

void zpomaleni(unsigned char rychlostRotace, unsigned char *tlacitkoInit, unsigned char *tlacitkoHoriz, unsigned char *tlacitkoVert, unsigned *operace) //Funkce realizujici zpomaleni
{
	int i;
	int koeficient = 4525 - rychlostRotace*15; //Koeficient urcujici miru zpozdeni
	for(i = 0; i < koeficient; i++) //Cyklus realizujici zpozdeni
	{
		if(*tlacitkoInit) //V tomto cyklu muze byt zmacknuto tlacitko, ktere by se bez pritomnosti techto podminek ignorovalo
			*operace = INIT;
		else if (*tlacitkoHoriz)
			*operace = ROT_HORIZONTAL;
		else if (*tlacitkoVert)
			*operace = ROT_VERTICAL; 
	}
}

void main(void) {
unsigned char *tlacitkoInit = (unsigned char *) 0x00B0;
unsigned char *tlacitkoHoriz = (unsigned char *) 0x00B1;
unsigned char *tlacitkoVert = (unsigned char *) 0x00B2;
unsigned char *rychlostRotace = (unsigned char *) 0x00B3;
unsigned char *zobrazovaciPanel = (unsigned char *) 0x00B4;

int x = 0; //Index zvestujici se pri horizontalnim posunu
int y = 0; //Index zvetsujici se pri vertikalnim posunu
unsigned operace = 0; //promenna urcujici, zda se jedna o INIT, horizontalni, ci vertikalni rotaci
*tlacitkoInit = 0; //Inicializace tlacitek, bez tohoto bude program hlasit chybu
*tlacitkoHoriz = 0;
*tlacitkoVert = 0;
*rychlostRotace = 0;
nastavPanel(zobrazovaciPanel, x, y); //Vykresleni prvnich 4 pismen loginu pri prvnim spusteni


  EnableInterrupts; /* enable interrupts */
  /* include your code here */



  for(;;) {
    __RESET_WATCHDOG(); /* feeds the dog */
  	if(*tlacitkoInit) //Kontrola, zda neni stisknuto nejake z tlacitek, pokud neni uchova se hodnota tlacitka z predchoziho stavu (aby napriklad stale dochazelo k rotaci)
  		operace = INIT;
  	else if (*tlacitkoHoriz)
  		operace = ROT_HORIZONTAL;
  	else if (*tlacitkoVert)
  		operace = ROT_VERTICAL;
    
    if (operace == INIT) //Inicializace na pocatecni hodnoty
   	{
   		nastavPanel(zobrazovaciPanel, 0, 0);
   		x = 0;
   		y = 0;
   	} 
   	else if (operace == ROT_HORIZONTAL) //Horizontalni rotace, zvysuje se promenna x
   	{
   		nastavPanel(zobrazovaciPanel, ++x, y);
   		zpomaleni(*rychlostRotace, tlacitkoInit, tlacitkoHoriz, tlacitkoVert, &operace);
   	} 
   	else if(operace == ROT_VERTICAL) //Vertikalni rotace, zvysuje se promenna y
   	{
   		nastavPanel(zobrazovaciPanel, x, ++y);
   		zpomaleni(*rychlostRotace, tlacitkoInit, tlacitkoHoriz, tlacitkoVert, &operace);
   	}
  } /* loop forever */
  /* please make sure that you never leave main */
}
