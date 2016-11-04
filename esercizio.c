/*Programma che consente la gestione delle operazioni di base con le liste collegate:
1)Inserimento di nuovi elementi.
2)Rimozione di elementi.
3)Stampa della lista.*/
#include<stdio.h>
#include<stdlib.h>
//Definizione della struttura rappresentante un nodo della lista.
struct nodo{
	int info;//Valore del nodo (intero).
	struct nodo *next;//Riferimento al nodo successivo.
};
//Definizione degli alias.
typedef struct nodo node;
typedef node* nodePtr;
//-PROTOTIPI DELLE FUNZIONI NECESSARIE-
/*Funzione print(nodePtr list), che consente di stampare l'intera lista.
nodePtr list => Riferimento al primo elemento della lista.*/
void print(nodePtr list);
/*Funzione insert(nodePtr *list,int value), che consente di inserire un elemento in coda
alla lista.
nodePtr *list => Puntatore al puntatore al primo elemento della lista.
int value=>Valore di inserire nella lista.*/
void insert(nodePtr *list,int value);
/*Funzione delete(nodePtr *list,int value), che consente di eliminare un elemento dalla lista
avente come valore quello passato come parametro alla funzione.
nodePtr list => Puntatore al puntatore al primo elemento della lista.
int value => Valore dell'elemento da rimuovere.*/
void delete(nodePtr *list,int value);
int main()
{
	int scelta;
	int elemento;
	//Lista vuota.
	node *lista=NULL;
	printf("Gestore lista collegata lista collegata\n");
	printf("*****************************************\n");
	do
	{
		printf("1.Aggiungi un elemento alla lista.\n");
		printf("2.Rimuovi un elemento dalla lista.\n");
		printf("3.Stampa la lista.\n");
		printf("4.Esci.\n");
		scanf("%d",&scelta);
		switch(scelta)
		{
			case 1:
				printf("\nInserire l'elemento da inserire nella lista: ");
				scanf("%d",&elemento);
				insert(&lista,elemento);
				printf("\nLista aggiornata: \n\n");
				print(lista);
				printf("\n\n");
				break;
			case 2:
				printf("\nInserire l'elemento da eliminare nella lista: ");
				scanf("%d",&elemento);
				delete(&lista,elemento);
				printf("\nLista aggiornata: \n\n");
				print(lista);
				printf("\n\n");
				break;
			case 3:
				printf("\n\nLista:\n\n");
				print(lista);
				printf("\n\n");
				break;
			case 4:
				break;
			default:
				printf("\n\nVoce non presente nel menu'\n\n");
				break;

		}

	}
	while(scelta!=4);

}
/*Definizione della funzione "print(nodePtr list)", necessaria alla stampa della lista, mediante la
rappresentazione parentetica.*/
void print(nodePtr list)
{
	printf("(");
	//Puntatore necessario alla scansione della lista.
	nodePtr p = list;
	/*Il ciclo di stampa continua fino a quando il valore di p non è uguale a "NULL"
	(fine della lista).*/
	while(p!=NULL)
	{
		//Stampa dell'elemento.
		printf("%d",p->info);
		p=p->next;
		/*Se non si è arrivati all'ultimo elemento, viene stampata
		anche la ",".*/
		if(p!=NULL)
		{
			printf(",");
		}
	}
	printf(")");
}
/*Definizione della funzione "insert(nodePtr *list,int value)", necessaria
ad aggiungere un nuovo elemento in coda alla lista.*/
void insert(nodePtr *list,int value)
{
	//Definizione di un puntatore di tipo "nodePtr", necessario a scorrere la lista.
	nodePtr index;
	/*Allocazione della memoria necessaria per la creazione di un nuovo nodo, mediante
	la funzioni "malloc()" e "sizeof()".*/
	nodePtr newNode = malloc(sizeof(node));
	//Verifica della corretta allocazione dell'elemento.
	if(newNode!=NULL)
	{
		/*Se il processo di allocazione è andato a buon fine, al nodo verranno asseganti:
		1)Il valore passato come parametro al campo "info".
		2)Il valore "NULL", al campo "next" (l'elemento viene aggiunto in coda alla lista).*/
		newNode->info=value;
		newNode->next=NULL;
		/*Se il riferimento al primo elemento della lista è nullo, la lista è vuota, e il riferimento
		viene aggiornato con il puntatore al nuvo nodo, restituito mediante la funzione "malloc()", invocata
		precedentemente.*/
		if((*list)==NULL)
		{
			*list=newNode;
		}
		else
		{
			/*Nel caso in cui il riferimento al primo elemento non sia nulla, la lista viene scansionata
			fino a trovare l'ultimo elemento della lista (avente campo "next" con valore "NULL").*/
			index=*list;
			while(index->next!=NULL)
			{
				index=index->next;
			}
			/*Il campo "next" dell'ultimo elemento della lista viene aggiornato con il riferimento
			al nuovo nodo, contenuto nella variabile puntatore "newNode".*/
			index->next=newNode;
		}
	}
	else
	{
		//Se l'allocazione non è andata a buon fine, viene generato un messaggio di errore.
		printf("\n\nAttenzione, si e' verificato un errore in fase di allocazione della memoria!\n\n");
	}
}
/*Definizione della funzione "delete(nodePtr *list,int value)", necessaria
ad eliminare un elemento dalla lista, dato il valore del suo campo "info". (nel caso
in cui gli elementi abbiano valori ripetuti, verrà eliminato esclusivamente il primo elemento trovato
avente valore del campo "info" corrispondente a quello del parametro intero "value".*/
void delete(nodePtr *list,int value)
{
	//Puntatore necessario a scorrere tutta la lista.
	nodePtr p;
	//Verifica che la lista non sia vuota.
	if((*list)!=NULL)
	{
		//Verifica se l'elemento da eliminare è il primo della lista.
		if((*list)->info==value)
		{
			/*Salvataggio dell'attuale riferimento al primo elemento della
			lista in una variabile temporanea.*/
			p=*list;
			/*Il riferimento al primo elemento della lista viene sostituito con
			il riferimento al secondo elemento.*/
			*list=(*list)->next;
			/*La memoria riservata all'elemento rimosso viene deallocata mediante la funzione
			"free().*/
			free(p);
		}
		else
		{
			/*Nel caso in cui l'elemento da eliminare non sia il primo della lista, la lista
			viene scansionata finché non si è arrivati all'ultimo elemento, o finché non
			si è arrivati all'elemento che precede quello da eliminare.*/
			p=(*list);
			while(p->next!=NULL && p->next->info!=value)
			{
				p=p->next;
			}
			/*Se l'elemento è presente nella lista, viene modificato il riferimento
			del nodo precedente quello da eliminare, con il riferimento al nodo successivo. La memoria
			viene successivamente deallocata.*/
			if(p->next!=NULL)
			{
				nodePtr q=p->next;
				p->next=p->next->next;
				free(q);
			}

		}
	}
}
