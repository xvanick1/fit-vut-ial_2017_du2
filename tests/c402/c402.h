
/* Hlavi�kov� soubor pro c402.c - nerekurz�vn� implementace operac� nad BVS
obsahuje jednak nutn� knihovny a extern� prom�nn�, ale rovn� definici datov�ch
typ�, se kter�mi se pracuje v p��slu�n�ch �loh�ch. Nemodifikovat! */

/* ********************** SOUBOR S HLAVI�KOU ********************** */
/* ********************** ------------------ ********************** */

/*  P�edm�t: Algoritmy (IAL) - FIT (Fakulta Informa�n�ch Technologi�)
    Hlavi�ka pro soubor: c402.c
    Vytvo�il: Martin Tu�ek, z��� 2005
    Upravil: Bohuslav K�ena, listopad 2009                           
    upravil: Karel Masa��k, ��jen 2013                               
    upravil: Radek Hranick�, ��jen 2014                              */
/* ***************************************************************** */

#include<stdio.h>
#include<stdlib.h>
#include<stdarg.h>
#include<stdbool.h>

#define FALSE 0
#define TRUE 1
#define MAXSTACK 30                      /* maxim�ln� po�et prvk� v z�sobn�ku */

extern int solved; 			                  /* indikace, zda byla funkce �e�ena */

typedef struct tBTNode	{                                      /* uzel stromu */
    int Cont;                                         /* u�ite�n� obsah uzlu  */
    struct tBTNode * LPtr;                                  /* lev� podstrom  */
    struct tBTNode * RPtr; 	  	                            /* prav� podstrom */
} *tBTNodePtr;                                     /* ukazatel na uzel stromu */

/* pomocn� z�sobn�ky */
typedef struct	{                          /* z�sobn�k hodnot typu tBTNodePtr */
    tBTNodePtr a[MAXSTACK];
    int top;
} tStackP;

typedef struct {                                 /* z�sobn�k hodnot typu bool */
    bool a[MAXSTACK];
    int top;
} tStackB;

/***prototypes***/
void BTInit (tBTNodePtr * );
void BTInsert (tBTNodePtr *, int );

void Leftmost_Preorder(tBTNodePtr, tStackP *);
void BTPreorder(tBTNodePtr );

void Leftmost_Inorder(tBTNodePtr, tStackP *);
void BTInorder(tBTNodePtr );

void Leftmost_Postorder(tBTNodePtr, tStackP *, tStackB *);
void BTPostorder(tBTNodePtr );

void BTDisposeTree(tBTNodePtr *);
/********end of prototypes******/

/* konec c402.h */
