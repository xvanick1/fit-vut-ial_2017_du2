
/* ************************ s016-test.c **************************** */

#include "c016.h"

#include <stdio.h>
#include <math.h>
#include <stdlib.h>


tHTItem* UNDEFPTR;
tHTable* ptrht;

/* tiskne tData ze struktury */
void htPrintData ( tData* ptrdata ) {
	if ( ptrdata )
		printf ("%.2f\n", *ptrdata );
	else
		printf ("NULL\n");
}

/* tiskne tItem ze struktury */
void htPrintItem ( tHTItem* ptritem ) {
	if ( ptritem )
		printf ("%s - %.2f\n", ptritem->key, ptritem->data );
	else
		printf ("NULL\n");
}

/* tiskne celou tabulku */
void htPrintTable( tHTable* ptrht ) {
	int maxlen = 0;
	int sumcnt = 0;
	
	printf ("------------HASH TABLE--------------\n");
	for ( int i=0; i<HTSIZE; i++ ) {
		printf ("%i:",i);
		int cnt = 0;
		tHTItem* ptr = (*ptrht)[i];
		while ( ptr != NULL ) {
			printf (" (%s,%.2f)",ptr->key,ptr->data);
			if ( ptr != UNDEFPTR )
				cnt++;
			ptr = ptr->ptrnext;
		}
		printf ("\n");
	
		if (cnt > maxlen)
			maxlen = cnt;
		sumcnt+=cnt;
	}
	
	printf ("------------------------------------\n");
	printf ("Items count %i   The longest list %i\n",sumcnt,maxlen);
	printf ("------------------------------------\n");
}

/* vola funkci htInit a v pripade ze neni resena tiskne chybu */
void use_init ( tHTable* ptrht ) {
	solved = 1;
	htInit( ptrht );
	if ( ! solved )
		printf("[W] Funkce HTInit nebyla implementovana...\n");
}

/* vola funkci htSearch a tiskne vysledek,
 v pripade ze neni resena tiskne chybu */
void use_search( tHTable* ptrht, tKey key ) {
	solved = 1;
	tHTItem* ptritem = htSearch ( ptrht, key );
	if ( ! solved )
		printf("[W] Funkce HTSearch nebyla implementovana...\n");
	else 
		htPrintItem ( ptritem );
}

/* vola funkci htInsert a v pripade ze neni resena tiskne chybu */
void use_insert ( tHTable* ptrht, tKey key, tData data ) {
	solved = 1;
	htInsert( ptrht, key, data);
	if ( ! solved )
		printf("[W] Funkce HTInsert nebyla implementovana...\n");
}

/* vola funkci htRead a tiskne vysledek,
 v pripade ze neni resena tiskne chybu */
void use_read( tHTable* ptrht, tKey key ) {
	solved = 1;
	tData* ptrdata = htRead ( ptrht, key );
	if ( ! solved )
		printf("[W] Funkce HTSearch nebyla implementovana...\n");
	else 
		htPrintData ( ptrdata );
}

/* vola funkci htDelete a v pripade ze neni resena tiskne chybu */
void use_delete ( tHTable* ptrht, tKey key ) {
	solved = 1;
	htDelete( ptrht, key );
	if ( ! solved )
		printf("[W] Funkce HTDelete nebyla implementovana...\n");
}

/* vola funkci htClearAll a v pripade ze neni resena tiskne chybu */
void use_clear_all ( tHTable* ptrht  ) {
	solved = 1;
	htClearAll( ptrht );
	if ( ! solved )
		printf("[W] Funkce HTClearAll nebyla implementovana...\n");
}

/* Hlavni funkce pro testovani */
int main(int argc, char* argv[] ) {
	UNDEFPTR = (tHTItem*) malloc ( sizeof(tHTable) );
	UNDEFPTR->key = "*UNDEF*";
	UNDEFPTR->data = -1;
	UNDEFPTR->ptrnext = NULL;
	ptrht = (tHTable*) malloc ( sizeof(tHTable) );
	for ( int i=0; i<MAX_HTSIZE; (*ptrht)[i++] = UNDEFPTR );

/********************* SCRIPT START ******************************************/
	printf ("Hash Table - testing script\n");
	printf ("---------------------------\n");
	printf ("\nLet's set HTSIZE to 19 ( must be prime )\n");
/**/	HTSIZE = 19;
	htPrintTable(ptrht);

	printf ("\n[TEST01] Lets read velvet without init, -> NULL\n");
	use_read( ptrht, "velvet" );
	htPrintTable ( ptrht );

	printf ("\n[TEST02] Lets delete gambrinus and kofola without init, no change \n");
	use_delete( ptrht, "gambrinus" );
	use_delete( ptrht, "kofola" );
	htPrintTable ( ptrht );

	printf ("\n[TEST03] Search for non-existing velvet without init, NULL\n");
	use_search ( ptrht, "velvet" );
	htPrintTable(ptrht);

	printf ("\n[TEST04] Table initialization, no UNDEF values, empty table\n");
	use_init ( ptrht );
	htPrintTable(ptrht);

	printf ("\n[TEST05] Let's try htInsert() krusovice at the first poss\n");
	use_insert ( ptrht, "krusovice", 1.50 );
	htPrintTable(ptrht);

	printf ("\n[TEST06] Search for existing item krusovice,\n");
	use_search (ptrht,"krusovice");

	printf ("\n[TEST07] Let's insert next items\n");
	use_insert ( ptrht, "korgon", 18.00 );
	use_insert ( ptrht, "zlaty bazant", 20.00);
	use_insert ( ptrht, "gambrinus", 18.50);
	use_insert ( ptrht, "starobrno", 16.50);
	use_insert ( ptrht, "plzen", 25.00);
	use_insert ( ptrht, "velvet", 26.00);
	use_insert ( ptrht, "kelt", 30.00);
	use_insert ( ptrht, "kofola", 15.00);
        use_insert ( ptrht, "kruvosice", 66.15);
	htPrintTable(ptrht);

	printf ("\n[TEST08] htSearch for \"starobrno\" may ret value\n");
	use_search ( ptrht, "starobrno" );
	htPrintTable(ptrht);

	printf ("\n[TEST09] htSearch for \"gambrinus\" may ret value\n");
	use_search ( ptrht, "gambrinus" );
	htPrintTable(ptrht);

	printf ("\n[TEST10] htSearch for \"krusovice\" may ret value\n");
	use_search ( ptrht, "krusovice" );
	htPrintTable(ptrht);

	printf ("\n[TEST11] htSearch for \"kruvosice\" may ret value\n");
	use_search ( ptrht, "kruvosice" );
	htPrintTable(ptrht);

	printf ("\n[TEST12] htSearch for existing hash \"krusivoce\" may ret NULL\n");
	use_search ( ptrht, "krusivoce" );
	htPrintTable(ptrht);

	printf ("\n[TEST13] Let's change korgon price to 12.50\n");
	use_insert ( ptrht, "korgon", 12.50);
	use_search ( ptrht, "korgon" );
	htPrintTable(ptrht);

	printf ("\n[TEST14] How much is kruvosice?\n");
	use_read ( ptrht, "kruvosice" );

	printf ("\n[TEST15] How much is gambrinus?\n");
	use_read ( ptrht, "gambrinus" );

	printf ("\n[TEST16] How much is krusovice\n");
	use_read ( ptrht, "krusovice" );

	printf ("\n[TEST17] Lets delete gambrinus\n");
	use_delete( ptrht, "gambrinus" );
	htPrintTable ( ptrht );

	printf ("\n[TEST18] Writeback gambrinus and delete krusovice\n");
	use_insert ( ptrht, "gambrinus", 18.50);
	use_delete( ptrht, "krusovice" );
	htPrintTable ( ptrht );

	printf ("\n[TEST19] Writeback krusovice and delete kruvosice\n");
	use_insert ( ptrht, "krusovice", 1.50);
	use_delete( ptrht, "kruvosice" );
	htPrintTable ( ptrht );

	printf ("\n[TEST20] Let's delete whole table\n");
	use_clear_all ( ptrht );
	htPrintTable ( ptrht );

	printf ("\n[TEST21] And search for non-existing velvet, NULL\n");
	use_search ( ptrht, "velvet" );
	htPrintTable(ptrht);

	printf ("\n[TEST22] Lets read velvet -> NULL\n");
	use_read( ptrht, "velvet" );
	htPrintTable ( ptrht );        

	printf ("\n[TEST23] free whole table, and try to test list\n");
	use_clear_all ( ptrht );
	free ( UNDEFPTR );
	free ( ptrht );

	UNDEFPTR = (tHTItem*) malloc ( sizeof(tHTable) );
	UNDEFPTR->key = "*UNDEF*";
	UNDEFPTR->data = -1;
	UNDEFPTR->ptrnext = NULL;
	ptrht = (tHTable*) malloc ( sizeof(tHTable) );
	for ( int i=0; i<1; (*ptrht)[i++] = UNDEFPTR );

	printf ("\n[TEST24] set HTSIZE to 1\n");
	HTSIZE = 1;
	htPrintTable(ptrht);

	printf ("\n[TEST25] try search velvet again, NULL\n");
       	use_search ( ptrht, "velvet" );
	htPrintTable(ptrht);

	printf ("\n[TEST26] try read velvet, NULL\n");
	use_read ( ptrht, "velvet" );
	htPrintTable(ptrht);

	printf ("\n[TEST27] init list\n");
	use_init ( ptrht );
        htPrintTable(ptrht);

	printf ("\n[TEST28] add some items, 18,17,16,15,14,13,12,11\n");
	use_insert ( ptrht, "krusovice", 11.50);
	use_insert ( ptrht, "gambrinus", 12.50);
	use_insert ( ptrht, "velvet", 13.50);
	use_insert ( ptrht, "pivo", 14.50);	
        use_insert ( ptrht, "radegast", 15.50);
	use_insert ( ptrht, "kozel", 16.50);
	use_insert ( ptrht, "holba", 17.50);
	use_insert ( ptrht, "smedny mnich", 18.50);
	htPrintTable ( ptrht );

       	printf ("\n[TEST29] try read velvet\n");        
	use_read ( ptrht, "velvet" );
	htPrintTable(ptrht);

        printf ("\n[TEST30] try search velvet\n");        
	use_search ( ptrht, "velvet" );
	htPrintTable(ptrht);

	printf ("\n[TEST31] exchange the prices via replace, 11,12,13,14,15,16,17,18\n");
	use_insert ( ptrht, "krusovice", 18.50);
	use_insert ( ptrht, "gambrinus", 17.50);
	use_insert ( ptrht, "velvet", 16.50);
	use_insert ( ptrht, "pivo", 15.50);	
        use_insert ( ptrht, "radegast", 14.50);
	use_insert ( ptrht, "kozel", 13.50);
	use_insert ( ptrht, "holba", 12.50);
	use_insert ( ptrht, "smedny mnich", 11.50);
	htPrintTable ( ptrht );

	printf ("\n[TEST32] delete first and last\n");
	use_delete ( ptrht, "krusovice" );
	use_delete ( ptrht, "smedny mnich" );
	htPrintTable ( ptrht );

	printf ("\n[TEST33] delete all by one\n");
	use_delete ( ptrht, "gambrinus" );
	use_delete ( ptrht, "velvet" );
	use_delete ( ptrht, "pivo" );	
        use_delete ( ptrht, "radegast" );
	use_delete ( ptrht, "kozel" );
	use_delete ( ptrht, "holba" );
	htPrintTable ( ptrht );

	printf ("\n[TEST34] add items again, 18,17,16,15,14,13,12,11\n");
	use_insert ( ptrht, "krusovice", 11.50);
	use_insert ( ptrht, "gambrinus", 12.50);
	use_insert ( ptrht, "velvet", 13.50);
	use_insert ( ptrht, "pivo", 14.50);	
        use_insert ( ptrht, "radegast", 15.50);
	use_insert ( ptrht, "kozel", 16.50);
	use_insert ( ptrht, "holba", 17.50);
	use_insert ( ptrht, "smedny mnich", 18.50);
	htPrintTable ( ptrht );	

	printf ("\n[TEST35] delete whole table\n");
	use_clear_all ( ptrht );
	htPrintTable ( ptrht );

	printf ("\n[TEST36] delete emty table\n");
	use_clear_all ( ptrht );
        htPrintTable ( ptrht );

	printf ("\n[TEST37] try delete velvet :) AGAIN!\n");
        use_delete ( ptrht, "velvet");
        htPrintTable ( ptrht );

	printf ("\n[TEST38] free table!\n");
	use_clear_all ( ptrht );
	free ( UNDEFPTR );
	free ( ptrht );

	printf ("\n[TEST39] now make ptrht NULL and call every function\n");
        ptrht = NULL;
        use_init (ptrht);
       	printf ("\n[TEST40] after init call\n");
        use_insert (ptrht, "kozel", 66.6);
	printf ("\n[TEST41] after insert call\n");
        use_search (ptrht, "kozel");
       	printf ("\n[TEST42] after search call\n");
        use_read (ptrht, "kozel");
	printf ("\n[TEST43] after read call\n");
        use_delete (ptrht, "kozel");
	printf ("\n[TEST44] after delete call\n");
        use_clear_all (ptrht);
	printf ("\n[TEST45] after delete all call, and init again\n");
        use_init (ptrht);
	printf ("\n[***TEST***] congratz ;)\n");

	return 0;	
}