
/* Hlavi�kov� soubor pro c016.h - Tabulka s Rozpt�len�mi Polo�kami,
**  obsahuje jednak nutn� includes a externovan� prom�nn�,
**  ale rovne� definici datov�ch typ�. Tento soubor neupravujte!
**  T�ma:  Tabulka s explicitn� z�et�zen�mi synonymy
**                      Prvn� implementace: Petr P�ikryl, prosinec 1994
**                      Do jazyka C prepsal a upravil: Vaclav Topinka, 2005
**                      �pravy: Karel Masa��k, ��jen 2013
**                      �pravy: Radek Hranick�, ��jen 2014
**
***/


#ifndef _HASHTABLE_H_
#define _HASHTABLE_H_

#include <stdlib.h>
#include <string.h>

extern int solved;			/* externi promenna pouzivana v testeru */

/* Maxim�ln� velikost pole pro implementaci
   vyhled�vac� tabulky. �e�en� procedury v�ak
   vyu��vaj� pouze HTSIZE prvk� pole (viz deklarace t�to prom�nn�).
*/
#define MAX_HTSIZE 101

/* typ kl��e (nap��klad identifikace zbo��) */
typedef char* tKey;

/* typ obsahu (nap��klad cena zbo��) */
typedef float tData;

/*Datov� polo�ka TRP s explicitn� �et�zen�mi synonymy*/
 typedef struct tHTItem{
	tKey key;				/* kl��  */
	tData data;				/* obsah */
	struct tHTItem* ptrnext;	/* ukazatel na dal�� synonymum */
} tHTItem;

/* TRP s explicitn� z�et�zen�mi synonymy. */
typedef tHTItem* tHTable[MAX_HTSIZE];

/* Pro ��ely testov�n� je vhodn� m�t mo�nost volby velikosti pole,
   kter�m je vyhled�vac� tabulka implementov�na. Fyzicky je deklarov�no
   pole o rozm�ru MAX_HTSIZE, ale p�i implementaci va�ich procedur uva�ujte
   velikost HTSIZE.  Ve skriptu se p�ed vol�n�m �e�en�ch procedur mus�
   objevit p��kaz HTSIZE N, kde N je velikost po�adovan�ho prostoru.
   
   POZOR! Pro spr�vnou funkci TRP mus� b�t hodnota t�to prom�nn� prvo��slem.
*/
extern int HTSIZE;

/* Hlavi�ky �e�en�ch procedur a funkc�. */

int hashCode ( tKey key );

void htInit ( tHTable* ptrht );

tHTItem* htSearch ( tHTable* ptrht, tKey key );

void htInsert ( tHTable* ptrht, tKey key, tData data );

tData* htRead ( tHTable* ptrht, tKey key );

void htDelete ( tHTable* ptrht, tKey key );

void htClearAll ( tHTable* ptrht );

#endif
