
/* Hlavi�kov� soubor pro c401.c - rekurz�vn� implementace operaci nad BVS,
obsahuje jednak nutn� knihovny a extern� prom�nn�, ale rovn� 
definici datov�ch typ�, se kter�mi se pracuje v jdenotliv�ch
funkc�ch. Nemodifikovat! */

/* ********************** SOUBOR S HLAVI�KOU ********************** */
/* ********************** ------------------ ********************** */

/*  vytvo�il: Martin Tu�ek
    p�edm�t: Algoritmy (IAL) - FIT (Fakulta Informacnich Technologi�)
    hlavicka pro soubor: c401.c
    datum: z��� 2005
    upravil: Bohuslav K�ena, listopad 2009
    upravil: Karel Masa��k, ��jen 2013                               
    upravil: Radek Hranick�, ��jen 2014                              */
/* ***************************************************************** */

#include<stdio.h>
#include<stdlib.h>
#include<stdarg.h>

#define TRUE 1
#define FALSE 0

extern int solved;                        /* indikace, zda byla funkce �e�ena */

/* uzel stromu */
                                                                                                            
typedef struct tBSTNode {
	char Key;			                                                      /* kl�� */
	int BSTNodeCont;                                            /* u�ite�n� obsah uzlu */
	struct tBSTNode * LPtr;                                    /* lev� podstrom */
	struct tBSTNode * RPtr;                                   /* prav� podstrom */
} *tBSTNodePtr;	

/* prototypy funkc� */

void BSTInit   (tBSTNodePtr *);
int BSTSearch  (tBSTNodePtr, char, int *);
void BSTInsert (tBSTNodePtr *, char, int);
void BSTDelete (tBSTNodePtr *, char);
void BSTDispose(tBSTNodePtr *);

/* konec c401.h */
