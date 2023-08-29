#include <stdio.h>
#include <stdlib.h>

struct node
{
    int val;
    struct node *next;
};
//regola di buona programmazione
typedef struct node List;//questa ci consente di richiamare le funzioni in modo più carino
//typedef struct node* List; al prof non piace

int isempty(struct node *ptr); //controlla se la lista è vuota, 1 se vuota 0 altrimenti
void print_list(struct node *ptr);
void pre_insert(struct node **ptr, int value);
struct node* pre_insert_bis(struct node *ptr, int value);
void suf_insert(struct node **ptr, int value);
void ord_insert(struct node **ptr, int value);

//Versioni ricorsive
void print_list_rec(struct node *ptr);
void suf_insert_rec(struct node **ptr, int value);

//definiamo una pila FILO
void push(struct node **ptr, int value);
void pop(struct node **ptr);

//definiamo una queue FIFO
void enqueue(struct node **ptr, int value);//inserimento
void dequeue(struct node **ptr);//cancellazione

//funzione clone
void clone_list(List *srcPtr, List **destPtr){
    while (srcPtr != NULL)
    {   
        //printf("%d", ptr->value);
        *destPtr = malloc(sizeof(List));
        (*destPtr)->val = srcPtr -> val;
        (*destPtr)->next = NULL;
        destPtr = &((*destPtr)->next);
        //suf_insert(destPtr, srcPtr->value);
        srcPtr = srcPtr->next;
    }
    
}

void clone_list_inversa(List *srcPtr, List **destPtr){//altenativa
    while(srcPtr != NULL){
        pre_insert(&((*destPtr)), srcPtr->val);
        srcPtr = srcPtr->next;
    }
}

void clone_list_alternativa(List *srcPtr, List **destPtr){//altenativa
    while(srcPtr != NULL){
        suf_insert(&((*destPtr)), srcPtr->val);
        srcPtr = srcPtr->next;
    }
}


int main(){
    printf("Prima lista\n\n");

    struct node *list = NULL; //inizializzazione, il primo elemento punterà a nulla
    List *stack = NULL;
    List *coda = NULL;
    List *clone = NULL;

    printf("Lista vuota? %d\n", isempty(list));
    //puoi commentare da qui
    
    pre_insert(&list,93);//perchè puntatore a puntatore
    pre_insert(&list,5);
    pre_insert(&list,29);
    list = pre_insert_bis(list, 77);
    suf_insert(&list,17);
    suf_insert_rec(&list,57);
    //A qui per provare ord_insert
    ord_insert(&list, 69);
    ord_insert(&list, 96);
    ord_insert(&list, 85);
    clone_list(list, &clone);
    //decommentare da qui


    //SECONDA PARTE CANCELLAZIONE PILA
    /*push(&stack, 93);
    push(&stack, 5);
    push(&stack, 17);
    printf("PILA INIZIO: ");
    print_list_rec(stack);
    printf("\n");
    pop(&stack);
    pop(&stack);
    //pop(&stack); darà errore perchè manca controllo lista vuota di stack su print_list ma funziona

    //Terza parte CODE
    enqueue(&coda, 99);
    enqueue(&coda, 3);
    enqueue(&coda, 37);
    printf("CODA INIZIO: ");
    print_list_rec(coda);
    printf("\n");
    dequeue(&coda);*/

    printf("Lista vuota? %d\n", isempty(list));

   // print_list(list);
    printf("\n");
   // print_list_rec(list);
    printf("\n");
    /*printf("PILA :");
    print_list(stack);
    printf("\n");
    printf("CODA: ");
    print_list(coda);*/
    print_list(clone);

    return 0;
}

int isempty(struct node *ptr){
    if(ptr == NULL)//no ptr next perchè se la lista è vuota il valore puntato non esiste;
        return 1;
    else
        return 0;
    /*altrimenti
    return(ptr == NULL);
    */
}

void print_list(struct node *ptr){
    while(ptr != NULL){
        printf("%d ", ptr->val);
        ptr = ptr -> next;
    }
    printf("\n");
}

/*
inserimento in testa: + semplice e costo O(1)
inserimento in coda: + complesso e costo O(n)
*/

// IL PROF PREFERISCE QUESTA

void pre_insert(struct node **ptr, int value){//inserimento in testa
    struct node *tmp = *ptr;

    *ptr = malloc(sizeof(struct node));

    (*ptr)->val = value;//ATTENZIONE ALLE PARENTESI
    (*ptr)->next = tmp;// Per forza dell'operatore *(ptr) non va bene

}

/* IL PROF DEFINISCE QUESTA FUNZIONE COME BRUTTA

void node* pre_insert(struct node *ptr, int value){//inserimento in testa
    struct node *tmp = ptr;

    ptr = malloc(sizeof(struct node));

    ptr->val = value;
    ptr->next = tmp;

    return ptr; //richiede che nel main si faccia una assegnazione 
    //nel main: list = pre_insert(list,93);

}*/

void suf_insert(struct node **ptr, int value){//INSERIMENTO IN CODA
    //struct node *tmp = *ptr;

    while(*ptr != NULL){//alla fine del ciclo (*ptr) punterà all'ultimo elemento
        ptr = &((*ptr)->next); 
    }
    /*
    interpretiamo: quando aggiornate bisogna scorrere all'indirizzo di memoria
    tradotto quando arriviamo in fondo abbiamo bisogno del ptr originario.
    */
    
    
    /*VOLENDO 
    *ptr = malloc(sizeof(struct node));

    (*ptr)->val = value;//ATTENZIONE ALLE PARENTESI
    (*ptr)->next = tmp;// Per forza dell'operatore *(ptr) non va bene
    MA */ 
    
    pre_insert(ptr,value);

}

struct node* pre_insert_bis(struct node *ptr, int value){//obiettivo togliere la presenza del puntatore a puntatore
    struct node *tmp;
    tmp = ptr;
    ptr = malloc(sizeof(struct node));

    (ptr)->val = value;//ATTENZIONE ALLE PARENTESI
    (ptr)->next = tmp;// Per forza dell'operatore *(ptr) non va bene
}

void print_list_rec(struct node *ptr){
    if(ptr != NULL){
        printf("%d ", ptr->val);
        print_list_rec(ptr->next);
    }
}

void suf_insert_rec(struct node **ptr, int value){
    if(*ptr != NULL){
        suf_insert_rec(&((*ptr)->next), value);
    }
    else{
        pre_insert(ptr, value);
    }
}

//inserimento "ordinato"
void ord_insert(struct node **ptr, int value){
    // > value stampa in ordine decrescente || < stampa in ordine crescente
    while(*ptr != NULL && (*ptr)->val < value){
        ptr = &((*ptr)->next);
    }

    pre_insert(ptr, value);
}

void push(struct node**ptr, int val){
    while(*ptr != NULL){
        ptr = &((*ptr)->next);
    }
    pre_insert(ptr, val);
}

void pop(struct node**ptr){
    if(*ptr == NULL){//pila vuota
        printf("pila vuota\n");
    } else if((*ptr)->next == NULL){//siamo arrivati in fondo e quello è l'elemento da liberare
        //*ptr = NULL; questa va bene
        free(*ptr);//il prof preferisce questa qui
    }else{//qui siamo nel mezzo della lista
        List *tmp, *current = *ptr;//creo variabile di appoggio, current servirà per scorrere, entrambe inizializzate a ptr
        while(current->next != NULL){
            //ptr = &((*ptr)->next); (CONCETTO)
            tmp = current;//usiamo questo perchè ci permette di aggiornare il next al puntatore giusto
            current = current->next;
        }//quando esco da qui sono sul penultimo
        tmp->next = NULL;//aggiorna il penultimo
        free(current);//libero l'ultimo
    }
}

void enqueue(struct node **ptr, int value){
    while(*ptr != NULL){
        ptr = &((*ptr)->next);
    }
    pre_insert(ptr, value);
}

void dequeue(struct node **ptr){
    if(*ptr == NULL){//pila vuota
        printf("Coda vuota\n");
    } else if((*ptr)->next == NULL){
        free(*ptr);
    }else{
        List *tmpPtr = *ptr;

        *ptr = (*ptr)->next;

        //cancella elemento in coda
        tmpPtr->next = NULL;
        free(tmpPtr);
    }
}