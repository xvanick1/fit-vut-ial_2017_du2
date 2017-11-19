
/* c402.c: ********************************************************************}
{* Téma: Nerekurzivní implementace operací nad BVS
**                                     Implementace: Petr Přikryl, prosinec 1994
**                                           Úpravy: Petr Přikryl, listopad 1997
**                                                     Petr Přikryl, květen 1998
**			  	                        Převod do jazyka C: Martin Tuček, srpen 2005
**                                         Úpravy: Bohuslav Křena, listopad 2009
**                                         Úpravy: Karel Masařík, říjen 2013
**                                         Úpravy: Radek Hranický, říjen 2014
**                                         Úpravy: Radek Hranický, listopad 2015
**
** S využitím dynamického přidělování paměti, implementujte NEREKURZIVNĚ
** následující operace nad binárním vyhledávacím stromem (předpona BT znamená
** Binary Tree a je u identifikátorů uvedena kvůli možné kolizi s ostatními
** příklady):
**
**     BTInit .......... inicializace stromu
**     BTInsert ........ nerekurzivní vložení nového uzlu do stromu
**     BTPreorder ...... nerekurzivní průchod typu pre-order
**     BTInorder ....... nerekurzivní průchod typu in-order
**     BTPostorder ..... nerekurzivní průchod typu post-order
**     BTHeight ........ výpočet výšky stromu
**     BTDisposeTree ... zruš všechny uzly stromu
**
** U všech funkcí, které využívají některý z průchodů stromem, implementujte
** pomocnou funkci pro nalezení nejlevějšího uzlu v podstromu. Tyto pomocné
** funkce jsou:
**
**     Leftmost_Preorder
**     Leftmost_Inorder
**     Leftmost_Postorder
**
** Ve vaší implementaci si můžete definovat pomocné zásobníky pro uložení
** ukazetelů na uzly stromu (tStackP)
** nebo pro uložení booleovských hodnot TRUE/FALSE (tStackB).
** Pro práci s pomocnými zásobníky můžete použít následující funkce:
**
**     SInitP / SInitB ....... inicializace zásobníku
**     SPushP / SPushB ....... vložení prvku na vrchol zásobníku
**     SPopP / SPopB ......... odstranění prvku z vrcholu zásobníku
**     STopP / STopB ......... získání hodonty prvku na vrcholu zásobníku
**     STopPopP / STopPopB ... kombinace předchozích dvou funkcí
**     SSizeP / SSizeB ....... zjištění počtu prvků v zásobníku
**     SEmptyP / SEmptyB ..... zjištění, zda je zásobník prázdný
**
** Pomocné funkce pro práci ze zásobníky je zakázáno upravovat!
**
** Přesné definice typů naleznete v souboru c402.h. Uzel stromu je typu tBTNode,
** ukazatel na něj je typu tBTNodePtr. Jeden uzel obsahuje položku int Cont,
** která současně slouží jako užitečný obsah i jako vyhledávací klíč
** a ukazatele na levý a pravý podstrom (LPtr a RPtr).
**
** Příklad slouží zejména k procvičení nerekurzivních zápisů algoritmů
** nad stromy. Než začnete tento příklad řešit, prostudujte si důkladně
** principy převodu rekurzivních algoritmů na nerekurzivní. Programování
** je především inženýrská disciplína, kde opětné objevování Ameriky nemá
** místo. Pokud se Vám zdá, že by něco šlo zapsat optimálněji, promyslete
** si všechny detaily Vašeho řešení. Povšimněte si typického umístění akcí
** pro různé typy průchodů. Zamyslete se nad modifikací řešených algoritmů
** například pro výpočet počtu uzlů stromu, počtu listů stromunebo pro
** vytvoření zrcadlového obrazu stromu (pouze popřehazování ukazatelů
** bez vytváření nových uzlů a rušení starých).
**
** Při průchodech stromem použijte ke zpracování uzlu funkci BTWorkOut().
** Pro zjednodušení práce máte předem připraveny zásobníky pro hodnoty typu
** bool a tBTNodePtr. Pomocnou funkci BTWorkOut ani funkce pro práci
** s pomocnými zásobníky neupravujte
** Pozor! Je třeba správně rozlišovat, kdy použít dereferenční operátor *
** (typicky při modifikaci) a kdy budeme pracovat pouze se samotným ukazatelem
** (např. při vyhledávání). V tomto příkladu vám napoví prototypy funkcí.
** Pokud pracujeme s ukazatelem na ukazatel, použijeme dereferenci.
**/

#include "c402.h"
int solved;

void BTWorkOut (tBTNodePtr Ptr)		{
/*   ---------
** Pomocná funkce, kterou budete volat při průchodech stromem pro zpracování
** uzlu určeného ukazatelem Ptr. Tuto funkci neupravujte.
**/

	if (Ptr==NULL)
    printf("Chyba: Funkce BTWorkOut byla volána s NULL argumentem!\n");
  else
    printf("Výpis hodnoty daného uzlu> %d\n",Ptr->Cont);
}

/* -------------------------------------------------------------------------- */
/*
** Funkce pro zásobník hotnot typu tBTNodePtr. Tyto funkce neupravujte.
**/

void SInitP (tStackP *S)
/*   ------
** Inicializace zásobníku.
**/
{
	S->top = 0;
}

void SPushP (tStackP *S, tBTNodePtr ptr)
/*   ------
** Vloží hodnotu na vrchol zásobníku.
**/
{
                 /* Při implementaci v poli může dojít k přetečení zásobníku. */
  if (S->top==MAXSTACK)
    printf("Chyba: Došlo k přetečení zásobníku s ukazateli!\n");
  else {
		S->top++;
		S->a[S->top]=ptr;
	}
}

tBTNodePtr STopPopP (tStackP *S)
/*         --------
** Odstraní prvek z vrcholu zásobníku a současně vrátí jeho hodnotu.
**/
{
                            /* Operace nad prázdným zásobníkem způsobí chybu. */
	if (S->top==0)  {
		printf("Chyba: Došlo k podtečení zásobníku s ukazateli!\n");
		return(NULL);
	}
	else {
		return (S->a[S->top--]);
	}
}

tBTNodePtr STopP (tStackP *S)
/*         --------
** Vrátí hodnotu prvku na vrcholu zásobníku
**/
{
                            /* Operace nad prázdným zásobníkem způsobí chybu. */
	if (S->top==0)  {
		printf("Chyba: Došlo k podtečení zásobníku s ukazateli!\n");
		return(NULL);
	}
	else {
		return (S->a[S->top]);
	}
}

void SPopP (tStackP *S)
/*         --------
** Odstraní prvek z vrcholu zásobníku
**/
{
                            /* Operace nad prázdným zásobníkem způsobí chybu. */
	if (S->top==0)  {
		printf("Chyba: Došlo k podtečení zásobníku s ukazateli!\n");
	}
	else {
		S->top--;
	}
}

int SSizeP (tStackP *S) {
/*   -------
** Vrátí počet prvků v zásobníku
**/
  return(S->top);
}

bool SEmptyP (tStackP *S)
/*   -------
** Je-li zásobník prázdný, vrátí hodnotu true.
**/
{
  return(S->top==0);
}

/* -------------------------------------------------------------------------- */
/*
** Funkce pro zásobník hotnot typu bool. Tyto funkce neupravujte.
*/

void SInitB (tStackB *S) {
/*   ------
** Inicializace zásobníku.
**/

	S->top = 0;
}

void SPushB (tStackB *S,bool val) {
/*   ------
** Vloží hodnotu na vrchol zásobníku.
**/
                 /* Při implementaci v poli může dojít k přetečení zásobníku. */
	if (S->top==MAXSTACK)
		printf("Chyba: Došlo k přetečení zásobníku pro boolean!\n");
	else {
		S->top++;
		S->a[S->top]=val;
	}
}

bool STopPopB (tStackB *S) {
/*   --------
** Odstraní prvek z vrcholu zásobníku a současně vrátí jeho hodnotu.
**/
                            /* Operace nad prázdným zásobníkem způsobí chybu. */
	if (S->top==0) {
		printf("Chyba: Došlo k podtečení zásobníku pro boolean!\n");
		return(NULL);
	}
	else {
		return(S->a[S->top--]);
	}
}

bool STopB (tStackB *S)
/*         --------
** Vrátí hodnotu prvku na vrcholu zásobníku
**/
{
                            /* Operace nad prázdným zásobníkem způsobí chybu. */
	if (S->top==0)  {
		printf("Chyba: Došlo k podtečení zásobníku s ukazateli!\n");
		return(NULL);
	}
	else {
		return (S->a[S->top]);
	}
}

void SPopB (tStackB *S)
/*         --------
** Odstraní prvek z vrcholu zásobníku
**/
{
                            /* Operace nad prázdným zásobníkem způsobí chybu. */
	if (S->top==0)  {
		printf("Chyba: Došlo k podtečení zásobníku s ukazateli!\n");
	}
	else {
		S->top--;
	}
}

int SSizeB (tStackB *S) {
/*   -------
** Vrátí počet prvků v zásobníku
**/
  return(S->top);
}

bool SEmptyB (tStackB *S) {
/*   -------
** Je-li zásobník prázdný, vrátí hodnotu true.
**/
  return(S->top==0);
}

/* -------------------------------------------------------------------------- */
/*
** Následuje jádro domácí úlohy - funkce, které máte implementovat.
*/

void BTInit (tBTNodePtr *RootPtr)	{
/*   ------
** Provede inicializaci binárního vyhledávacího stromu.
**
** Inicializaci smí programátor volat pouze před prvním použitím binárního
** stromu, protože neuvolňuje uzly neprázdného stromu (a ani to dělat nemůže,
** protože před inicializací jsou hodnoty nedefinované, tedy libovolné).
** Ke zrušení binárního stromu slouží procedura BTDisposeTree.
**
** Všimněte si, že zde se poprvé v hlavičce objevuje typ ukazatel na ukazatel,
** proto je třeba při práci s RootPtr použít dereferenční operátor *.
**/

	(*RootPtr) = NULL;

}

void BTInsert (tBTNodePtr *RootPtr, int Content) {
/*   --------
** Vloží do stromu nový uzel s hodnotou Content.
**
** Z pohledu vkládání chápejte vytvářený strom jako binární vyhledávací strom,
** kde uzly s hodnotou menší než má otec leží v levém podstromu a uzly větší
** leží vpravo. Pokud vkládaný uzel již existuje, neprovádí se nic (daná hodnota
** se ve stromu může vyskytnout nejvýše jednou). Pokud se vytváří nový uzel,
** vzniká vždy jako list stromu. Funkci implementujte nerekurzivně.
**/

	tBTNodePtr subTree = (*RootPtr);	// Pomocná proměnná

	if ((*RootPtr) == NULL){		// Pokud je seznam prázdný tak vloříme jako kořen
		tBTNodePtr list = (tBTNodePtr) malloc(sizeof(struct tBTNode)); // Alokace paměti
		list->Cont = Content;
		list->LPtr = NULL;
		list->RPtr = NULL;
		(*RootPtr) = list;
	} else {						// Pokud seznam není prázdný
		while (subTree != NULL){				// Procházíme stromem dokud nenajdeme pázdný ukazatel
			if (Content < subTree->Cont){		// Test zda je klíč mensíš než aktuální klíč
				if (subTree->LPtr == NULL){		// Test zda je levý ukazatel je NULL
					tBTNodePtr list = (tBTNodePtr) malloc(sizeof(struct tBTNode)); // Alokace paměti
					list->Cont = Content;
					list->LPtr = NULL;
					list->RPtr = NULL;
					subTree->LPtr = list;		// Vložení listu
					subTree = subTree->LPtr;
				} else {
					subTree = subTree->LPtr;
				}
			} else if (Content > subTree->Cont){// Test zda je klíč větší než aktuální klíč
				if (subTree->RPtr == NULL){		// Test zda je pravý ukazatel NULL
					tBTNodePtr list = (tBTNodePtr) malloc(sizeof(struct tBTNode)); // Alokace paměti
					list->Cont = Content;
					list->LPtr = NULL;
					list->RPtr = NULL;
					subTree->RPtr = list;		// Vložení listu
					subTree = subTree->RPtr;
				} else {
					subTree = subTree->RPtr;
				}
			} else {
				return;
			}
		}
	}
}

/*                                  PREORDER                                  */

void Leftmost_Preorder (tBTNodePtr ptr, tStackP *Stack)	{
/*   -----------------
** Jde po levě větvi podstromu, dokud nenarazí na jeho nejlevější uzel.
**
** Při průchodu Preorder navštívené uzly zpracujeme voláním funkce BTWorkOut()
** a ukazatele na ně is uložíme do zásobníku.
**/

	if (ptr == NULL){					// Testování zda je ukazatel NULL
		return;
	} else {
		while (ptr != NULL){			// Test dokud je ukazatel nenulový
			BTWorkOut(ptr);				// Zpracování listu
			SPushP(Stack, ptr);			// Uložení na zásobník
			ptr = ptr->LPtr;			// Posun na levý podstrom
		}
	}

}

void BTPreorder (tBTNodePtr RootPtr)	{
/*   ----------
** Průchod stromem typu preorder implementovaný nerekurzivně s využitím funkce
** Leftmost_Preorder a zásobníku ukazatelů. Zpracování jednoho uzlu stromu
** realizujte jako volání funkce BTWorkOut().
**/

	tStackP stP;
	SInitP(&stP);							// inicializace zásobníku
	if (RootPtr == NULL){					// Testování zda je ukazatel NULL
		return;
	} else {
		Leftmost_Preorder(RootPtr, &stP);	// Uložím si "levou cestu na zásobník
		while (!SEmptyP(&stP)){				// Procházíme dokud zásobník není prázdný
			RootPtr = STopPopP(&stP);					// Vrátí list z vrcholu zásobníku
			Leftmost_Preorder(RootPtr->RPtr, &stP);		// Procházím pravý podstrom
		}
	}

}


/*                                  INORDER                                   */

void Leftmost_Inorder(tBTNodePtr ptr, tStackP *Stack)		{
/*   ----------------
** Jde po levě větvi podstromu, dokud nenarazí na jeho nejlevější uzel.
**
** Při průchodu Inorder ukládáme ukazatele na všechny navštívené uzly do
** zásobníku.
**/

	if (ptr == NULL){				// Testování zda je ukazatel NULL
		return;
	} else {
		while (ptr != NULL){		// Procházíme dokud ukazatel není NULL
			SPushP(Stack, ptr);		// Uložíme list na zásobník
			ptr = ptr->LPtr;		// Posuneme se na levý podstrom
		}
	}

}

void BTInorder (tBTNodePtr RootPtr)	{
/*   ---------
** Průchod stromem typu inorder implementovaný nerekurzivně s využitím funkce
** Leftmost_Inorder a zásobníku ukazatelů. Zpracování jednoho uzlu stromu
** realizujte jako volání funkce BTWorkOut().
**/

	tStackP stP;
	SInitP(&stP);		// inicializace zásobníku
	if (RootPtr == NULL){					// Testování zda je ukazatel NULL
		return;
	} else {
		Leftmost_Inorder(RootPtr, &stP);	// Uložím si "levou cestu na zásobník
		while (!SEmptyP(&stP)){				// Procházím dokud zásobník není prázdný
			RootPtr = STopPopP(&stP);				// Získání listu z vrcholu zásobníku
			BTWorkOut(RootPtr);						// Zpracování listu
			Leftmost_Inorder(RootPtr->RPtr, &stP);	// Procházím pravý podstrom
		}
	}

}

/*                                 POSTORDER                                  */

void Leftmost_Postorder (tBTNodePtr ptr, tStackP *StackP, tStackB *StackB) {
/*           --------
** Jde po levě větvi podstromu, dokud nenarazí na jeho nejlevější uzel.
**
** Při průchodu Postorder ukládáme ukazatele na navštívené uzly do zásobníku
** a současně do zásobníku bool hodnot ukládáme informaci, zda byl uzel
** navštíven poprvé a že se tedy ještě nemá zpracovávat.
**/

	if (ptr == NULL){					// Testování zda je ukazatel NULL
		return;
	} else {
		while (ptr != NULL){			// Procházíme dokud ukazatel není NULL
			SPushP(StackP, ptr);		// Uložíme list na zásobník
			SPushB(StackB, FALSE);		// Uložíme ukazatel na zásobník
			ptr = ptr->LPtr;
		}
	}

}

void BTPostorder (tBTNodePtr RootPtr)	{
/*           -----------
** Průchod stromem typu postorder implementovaný nerekurzivně s využitím funkce
** Leftmost_Postorder, zásobníku ukazatelů a zásobníku hotdnot typu bool.
** Zpracování jednoho uzlu stromu realizujte jako volání funkce BTWorkOut().
**/

	tStackP stP;
	SInitP(&stP);		// Inicializace zásobníku
	tStackB stB;
	SInitB(&stB);		// Inicializace zásobníku
	if (RootPtr == NULL){							// Testování zda je ukazatel NULL
		return;
	} else {
		Leftmost_Postorder(RootPtr, &stP, &stB);	// Uložím si "levou cestu na zásobník
		while (!SEmptyP(&stP)){						// Procházím dokud zásobník není prázdný
			RootPtr = STopPopP(&stP);				// Získáme list z vrcholu zásobníku
			SPushP(&stP, RootPtr);					// Vložíme na zásobník

			if (!STopPopB(&stB)){					// Pokud vrchol zásobníku je prázdný
				RootPtr = RootPtr->RPtr;			// Posunutí na pravý ukazatel
				SPushB(&stB, TRUE);					// Vložení na zásobník
				Leftmost_Postorder(RootPtr, &stP, &stB); // Procházím pravý podstrom
			} else {
				STopPopP(&stP);						// Smažeme ze zásobníku
				BTWorkOut(RootPtr);					// Práce s listem
			}
		}
	}

}


int BTHeight (tBTNodePtr RootPtr) {
/*   ----------
** Vypočítá výšku BVS bez použití rekurze
**
** Návratová hodnota je výška stromu. Funkci implementujte nerekurzivně
** bez deklarování jakékoli další pomocné funkce, která není v zadání.
** Využijte pomocných zásobníků. Je doporučeno použít jeden ze zásobníků
** pro průběžné ukládání cesty od kořene stromu. Počet uzlů na takovéto
** cestě můžete zjistit použitím funkce SSizeP. Výška stromu je rovna
** délce (počtu hran) nejdelší cesty  od kořene k lisu.
**
** Výška prázdného stromu však není definována. V případě prázdného stromu
** bude funkce vracet hodnotu -1.
**/
	if(RootPtr == NULL)
	{
		return (-1);

	}
	else
	{
		tBTNodePtr POM1 = RootPtr;;
		tBTNodePtr LAST_POM = NULL;
		tStackP stack;
		int maxH = 0;

		SInitP(&stack);
		int counter = 30;
		SPushP(&stack, RootPtr);
		while((POM1 != NULL) && counter)
		{
			counter--;
			if (LAST_POM == NULL) {
				Leftmost_Preorder(POM1, &stack);
				POM1 = STopP(&stack);
				while ((POM1->RPtr == NULL) && (POM1 != RootPtr))
				{
					POM1 = STopPopP(&stack);
					if ((POM1->LPtr == NULL) && (POM1->RPtr == NULL))
					{
						LAST_POM = POM1;
						if (SSizeP(&stack) > maxH)
						{
							maxH = SSizeP(&stack);
						}
					}

					printf("///%d\n", POM1->Cont);
					POM1 = STopP(&stack);
				}
				printf("FOUNDED-%d\n", POM1->Cont);
			}

			if (LAST_POM == POM1->RPtr){
				POM1 = STopPopP(&stack);
				while (LAST_POM == POM1->RPtr){
					LAST_POM = POM1;
					printf("/-/%d\t", POM1->Cont);
					POM1 = STopPopP(&stack);
					printf("/-/%d\n", POM1->Cont);
					if (LAST_POM == POM1) return maxH-1;
				}
				SPushP(&stack, POM1);
				POM1 = POM1->RPtr;
				LAST_POM = NULL;
			} else {
				LAST_POM = NULL;
				POM1 = POM1->RPtr;
			}
		}
		return (maxH -1);
	}

}


void BTDisposeTree (tBTNodePtr *RootPtr)	{
/*   -------------
** Zruší všechny uzly stromu a korektně uvolní jimi zabranou paměť.
**
** Funkci implementujte nerekurzivně s využitím zásobníku ukazatelů.
**/

	tStackP stP;
	SInitP(&stP);			// Inicializace zásobníku
	tBTNodePtr list = (*RootPtr);		// Pomocný ukazatel
	tBTNodePtr list2 = NULL;			// Pomocný ukazatel2

	if ((*RootPtr) == NULL){							// Test zda je ukazatel null
		return;
	} else {
		do {
			if ((list == NULL) && !(SEmptyP(&stP))){	// Test zda je ukazatel NULL a není prázný zásobník
				list = STopPopP(&stP);					// Obnova ukazatele
			} else {
				if (list->RPtr != NULL){				// Test zda exituje pravý podstrom
					SPushP(&stP, list->RPtr);			// Uloží ukazatel na pravý podstrom na zásobník...s
				}
				list2 = list;					// uložení ukazatele do další proměnné
				list = list->LPtr;				// Posunu se vlevo
				free(list2);					// Uvaolním paměť
			}
		} while ((list !=  NULL) || (!SEmptyP(&stP)));
	}
	(*RootPtr) = NULL;
}

/* konec c402.c */
