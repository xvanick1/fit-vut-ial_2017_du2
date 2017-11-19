
/* c401.c: **********************************************************}
{* Téma: Rekurzivní implementace operací nad BVS
**                                         Vytvořil: Petr Přikryl, listopad 1994
**                                         Úpravy: Andrea Němcová, prosinec 1995
**                                                      Petr Přikryl, duben 1996
**                                                   Petr Přikryl, listopad 1997
**                                  Převod do jazyka C: Martin Tuček, říjen 2005
**                                         Úpravy: Bohuslav Křena, listopad 2009
**                                         Úpravy: Karel Masařík, říjen 2013
**                                         Úpravy: Radek Hranický, říjen 2014
**                                         Úpravy: Radek Hranický, listopad 2015
**                                         Úpravy: Radek Hranický, říjen 2016
**
** Implementujte rekurzivním způsobem operace nad binárním vyhledávacím
** stromem (BVS; v angličtině BST - Binary Search Tree).
**
** Klíčem uzlu stromu je jeden znak (obecně jím může být cokoliv, podle
** čeho se vyhledává). Užitečným (vyhledávaným) obsahem je zde integer.
** Uzly s menším klíčem leží vlevo, uzly s větším klíčem leží ve stromu
** vpravo. Využijte dynamického přidělování paměti.
** Rekurzivním způsobem implementujte následující funkce:
**
**   BSTInit ...... inicializace vyhledávacího stromu
**   BSTSearch .... vyhledávání hodnoty uzlu zadaného klíčem
**   BSTInsert .... vkládání nové hodnoty
**   BSTDelete .... zrušení uzlu se zadaným klíčem
**   BSTDispose ... zrušení celého stromu
**
** ADT BVS je reprezentován kořenovým ukazatelem stromu (typ tBSTNodePtr).
** Uzel stromu (struktura typu tBSTNode) obsahuje klíč (typu char), podle
** kterého se ve stromu vyhledává, vlastní obsah uzlu (pro jednoduchost
** typu int) a ukazatel na levý a pravý podstrom (LPtr a RPtr). Přesnou definici typů 
** naleznete v souboru c401.h.
**
** Pozor! Je třeba správně rozlišovat, kdy použít dereferenční operátor *
** (typicky při modifikaci) a kdy budeme pracovat pouze se samotným ukazatelem 
** (např. při vyhledávání). V tomto příkladu vám napoví prototypy funkcí.
** Pokud pracujeme s ukazatelem na ukazatel, použijeme dereferenci.
**/

#include "c401.h"
int solved;

void BSTInit (tBSTNodePtr *RootPtr) {
/*   -------
** Funkce provede počáteční inicializaci stromu před jeho prvním použitím.
**
** Ověřit, zda byl již strom předaný přes RootPtr inicializován, nelze,
** protože před první inicializací má ukazatel nedefinovanou (tedy libovolnou)
** hodnotu. Programátor využívající ADT BVS tedy musí zajistit, aby inicializace
** byla volána pouze jednou, a to před vlastní prací s BVS. Provedení
** inicializace nad neprázdným stromem by totiž mohlo vést ke ztrátě přístupu
** k dynamicky alokované paměti (tzv. "memory leak").
**	
** Všimněte si, že se v hlavičce objevuje typ ukazatel na ukazatel.	
** Proto je třeba při přiřazení přes RootPtr použít dereferenční operátor *.
** Ten bude použit i ve funkcích BSTDelete, BSTInsert a BSTDispose.
**/
	
	*RootPtr = NULL; // Inicializujeme Koreň
	
}	

int BSTSearch (tBSTNodePtr RootPtr, char K, int *Content)	{
/*  ---------
** Funkce vyhledá uzel v BVS s klíčem K.
**
** Pokud je takový nalezen, vrací funkce hodnotu TRUE a v proměnné Content se
** vrací obsah příslušného uzlu.´Pokud příslušný uzel není nalezen, vrací funkce
** hodnotu FALSE a obsah proměnné Content není definován (nic do ní proto
** nepřiřazujte).
**
** Při vyhledávání v binárním stromu bychom typicky použili cyklus ukončený
** testem dosažení listu nebo nalezení uzlu s klíčem K. V tomto případě ale
** problém řešte rekurzivním volání této funkce, přičemž nedeklarujte žádnou
** pomocnou funkci.
**/

	if(RootPtr == NULL){
		return FALSE; // Nenašli sme uzol
	}
	else{
		if(RootPtr->Key == K){
			*Content = RootPtr->BSTNodeCont;
			return  TRUE; // Našli sme uzol
		}
		else{
			if(RootPtr->Key > K){ // Hľadáme v ľavom podstrome
				return(BSTSearch(RootPtr->LPtr, K, Content));
			}
			else{ // Hľadáme v pravom podstrome
				return(BSTSearch(RootPtr->RPtr, K, Content));
			}
		}
	}
} 


void BSTInsert (tBSTNodePtr* RootPtr, char K, int Content)	{	
/*   ---------
** Vloží do stromu RootPtr hodnotu Content s klíčem K.
**
** Pokud již uzel se zadaným klíčem ve stromu existuje, bude obsah uzlu
** s klíčem K nahrazen novou hodnotou. Pokud bude do stromu vložen nový
** uzel, bude vložen vždy jako list stromu.
**
** Funkci implementujte rekurzivně. Nedeklarujte žádnou pomocnou funkci.
**
** Rekurzivní implementace je méně efektivní, protože se při každém
** rekurzivním zanoření ukládá na zásobník obsah uzlu (zde integer).
** Nerekurzivní varianta by v tomto případě byla efektivnější jak z hlediska
** rychlosti, tak z hlediska paměťových nároků. Zde jde ale o školní
** příklad, na kterém si chceme ukázat eleganci rekurzivního zápisu.
**/

	if(*RootPtr == NULL){
		tBSTNodePtr CreateNode = malloc(sizeof(struct tBSTNode));
		if(CreateNode == NULL){ // Kontrujeme úspešnosť alokácie
			return;
		}
		else{
			CreateNode->Key = K; // Kopírujeme kľúč
			CreateNode->BSTNodeCont = Content; // Kopírujeme obsah
			CreateNode->LPtr = NULL; // Nastavíme ukazateľ na ľavý podstrom na NULL
			CreateNode->RPtr = NULL; // Nastavíme ukazateľ na pravý podstrom na NULL
			*RootPtr = CreateNode; // Vložíme nový uzol
		}
	}
	else{
		if((*RootPtr)->Key > K){
			BSTInsert(&((*RootPtr)->LPtr), K, Content); // Využijeme rekurziu a ideme vľavo
		}
		else if((*RootPtr)->Key < K){
			BSTInsert(&((*RootPtr)->RPtr), K, Content); // Využijeme rekurziu a ideme vpravo
		}
		else{
			(*RootPtr)->BSTNodeCont = Content; // Prepíšeme obsah uzlu novým
		}
	}
}

void ReplaceByRightmost (tBSTNodePtr PtrReplaced, tBSTNodePtr *RootPtr) {
/*   ------------------
** Pomocná funkce pro vyhledání, přesun a uvolnění nejpravějšího uzlu.
**
** Ukazatel PtrReplaced ukazuje na uzel, do kterého bude přesunuta hodnota
** nejpravějšího uzlu v podstromu, který je určen ukazatelem RootPtr.
** Předpokládá se, že hodnota ukazatele RootPtr nebude NULL (zajistěte to
** testováním před volání této funkce). Tuto funkci implementujte rekurzivně. 
**
** Tato pomocná funkce bude použita dále. Než ji začnete implementovat,
** přečtěte si komentář k funkci BSTDelete(). 
**/

	if(*RootPtr == NULL){ // Testujeme hodnotu ukazateľa RootPtr
		return;
	}
	else{
		if((*RootPtr)->RPtr != NULL){ // Testujeme "najpravejší" uzol
			ReplaceByRightmost(PtrReplaced,&(*RootPtr)->RPtr); // Ak nie je "najpravejší" tak rekurze
		}
		else{ // Ak je "najpravejší" ....
			PtrReplaced->Key = (*RootPtr)->Key; // Kopírujeme kľúč
			PtrReplaced->BSTNodeCont = (*RootPtr)->BSTNodeCont; // Kopírujeme obsah
			tBSTNodePtr NewNode = (*RootPtr); // Uložíme do pomocného uzla
			(*RootPtr) = (*RootPtr)->LPtr; // Posunieme sa ďalej
			free(NewNode); // Uvolníme pomocný uzol
		}
	}
}

void BSTDelete (tBSTNodePtr *RootPtr, char K) 		{
/*   ---------
** Zruší uzel stromu, který obsahuje klíč K.
**
** Pokud uzel se zadaným klíčem neexistuje, nedělá funkce nic. 
** Pokud má rušený uzel jen jeden podstrom, pak jej zdědí otec rušeného uzlu.
** Pokud má rušený uzel oba podstromy, pak je rušený uzel nahrazen nejpravějším
** uzlem levého podstromu. Pozor! Nejpravější uzel nemusí být listem.
**
** Tuto funkci implementujte rekurzivně s využitím dříve deklarované
** pomocné funkce ReplaceByRightmost.
**/

	if(*RootPtr == NULL){ // Testujeme hodnotu ukazateľa RootPtr
		return;
	}
	else{
		if((*RootPtr)->Key == K){ //Testujeme či uzol so zadaným kľúčom existuje
            tBSTNodePtr TempNode;
            if((*RootPtr)->RPtr == NULL){ //Testujeme či existuje pravý podstrom
                TempNode = *RootPtr; // Uložíme si ukazateľ na pravý podstrom
                *RootPtr = (*RootPtr)->LPtr; // Pokračujeme do ľavého podstromu
                free(TempNode); // Korektne uvolníme
            }

			else if((*RootPtr)->LPtr == NULL){ //Testujeme či existuje ľavý podstrom
                TempNode = *RootPtr; // Uložíme si ukazateľ na ľavý podstrom
                *RootPtr = (*RootPtr)->RPtr; // Pokračujeme do pravého podstromu
                free(TempNode); // Korektne uvolníme
            }
            else{
                ReplaceByRightmost((*RootPtr), &(*RootPtr)->LPtr); // Voláme pomocnú funkiu pre dosiahnutie "najpravejšieho" uzlu ľaveého podstromu
            }
        }
        else{
			if((*RootPtr)->Key < K){ //Testujeme či je hľadaný kľúč menší než náš
				BSTDelete(&(*RootPtr)->RPtr, K); // Ak áno využijeme rekurziu a postujujeme vľavo
			}
			if((*RootPtr)->Key > K){ //Testujeme či je hľadaný kľúč väčší než náš
				BSTDelete(&(*RootPtr)->LPtr, K); // Ak áno využijeme rekurziu a postujujeme pravo
			}
		}
	}
} 

void BSTDispose (tBSTNodePtr *RootPtr) {	
/*   ----------
** Zruší celý binární vyhledávací strom a korektně uvolní paměť.
**
** Po zrušení se bude BVS nacházet ve stejném stavu, jako se nacházel po
** inicializaci. Tuto funkci implementujte rekurzivně bez deklarování pomocné
** funkce.
**/

	if(*RootPtr == NULL){
		return;
	}
	else{
		BSTDispose(&(*RootPtr)->LPtr);	// Rekurziou odstraňujeme ľavý podstrom
		BSTDispose(&(*RootPtr)->RPtr);	// Rekurziou odstraňujeme pravý podstrom
		free((*RootPtr)); //Korektne uvoľňujeme
        *RootPtr = NULL;
	}
}

/*Pri písaní tohto kódu som vychádzal z výukovych materiálov predmetu IAL*/

/* konec c401.c */

