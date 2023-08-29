#include <stdio.h>
#include <stdlib.h>

#define COUNT 8

struct btree {//struttura dati dell'albero
    int valore;
    struct btree *leftPtr;
    struct btree *rightPtr;
};

typedef struct btree BST;

void init(BST **ptrPtr);
int isempty(BST *ptr);
int search(BST *ptr, int val);
int search_rec(BST *ptr, int val);
void print_rec(BST *ptr);
void ordinsert_rec(BST **ptrPtr, int val);

void delete_node(BST **root, int val);
BST* remove_node(BST *root, int val);

void print_bst2D_uil(BST *root, int space);
void print_bst2D(BST *root);

int main(void) {
    BST *albero;
    init(&albero);
    printf("Albero vuoto? %d\n", isempty(albero));
    
    ordinsert_rec(&albero, 2);
    printf("Albero vuoto? %d\n", isempty(albero));
    ordinsert_rec(&albero, 1);
    ordinsert_rec(&albero, 0);
    ordinsert_rec(&albero, 2);
    ordinsert_rec(&albero, 6);
    ordinsert_rec(&albero, 6);
    ordinsert_rec(&albero, 9);
    ordinsert_rec(&albero, 5);
    ordinsert_rec(&albero, 2);
    print_rec(albero);
    printf("\n");

    print_bst2D(albero);

    //albero = remove_node(albero, 5);
    albero = remove_node(albero, 1);
    albero = remove_node(albero, 6);
    delete_node(&albero, 5);
    //delete_node(&albero, 1);
    //delete_node(&albero, 6);
    print_rec(albero);
    printf("\n");

    print_bst2D(albero);

    int target = 9;
    printf("\nL'albero contiene %d? %d\n", target, search(albero, target));
    
    return 0;
}

void init(BST **ptrPtr) { //richiede puntatore di puntatore
    *ptrPtr = NULL;
}

// restituisce 1 se l'albero è vuoto, 0 altrimenti
int isempty(BST *ptr) {//richiede puntatore 
    return ptr == NULL;
}

// restituisce 1 se l'albero contiene l'elemento val, 0 altrimenti
int search(BST *ptr, int val) { //la versione iterativa è simile alla ricorsiva
//    if(ptr==NULL)    
//        return 0;         
    while(ptr != NULL) {                                    //ripete il ciclo finchè il puntatore non è NULL
        if(ptr->valore == val) {                            //caso in cui il valore viene ritrovato
            return 1;
        }
        else {
            if(ptr->valore > val)                           //valore del nodo > valore val inserito allora va a sinistra
                ptr = ptr->leftPtr;                             
            else                                            //destra altrimenti
                ptr = ptr->rightPtr;                        
        }
    }
    return 0;
}

// restituisce 1 se l'albero contiene l'elemento val, 0 altrimenti
int search_rec(BST *ptr, int val) {
    int found = 0;  //found inizializzato sempre a 0
    
    if(ptr != NULL) {                                       //se non sei arrivato alla fine
        if(ptr->valore == val) {                            //controlla il valore se uguale allora hai trovato l'elemento
            found = 1;
        }
        else {
            if(ptr->valore > val)                           //se il valore del nodo è maggiore del valore da trovare "val" allora vai a sinistra
                found += search_rec(ptr->leftPtr, val);     //incrementa found e richiama la funzione
            else                                            //destra altrimenti
                found += search_rec(ptr->rightPtr, val);
        }    
    }    
    
    return found;
}

// visita ricorsiva
void print_rec(BST *ptr) {
    if(ptr!=NULL) {
        //printf("%d ", ptr->valore); // visita in pre-ordine
        print_rec(ptr->leftPtr);
        //printf("%d ", ptr->valore); // visita simmetrica (in ordine)
        print_rec(ptr->rightPtr);
        printf("%d ", ptr->valore); // visita in post-ordine (in profondità / "depth-first")
    }
}
/*NOTARE CHE: PER print_rec e si richiede l'albero
    - la vista pre ordine stampa prima e poi richiama il puntatore sinistro e destro
    - la visita simmetrica ha la print al centro tra il sinistro e il destro
    - la visita post-ordine ha la stampa dopo aver richiamato entrambi i puntatori
        - SI VA AVANTI FINCHÈ IL PUNTATORE NON È NULL
*/

/* PICCOLA NOTA PER I BST
    - A sinistra ci sono gli elementi minori o uguali " <= " del valore del padre
    - A destra ci sono gli elementi maggiori " > " del valore del padre
*/

// inserimento in ordine (con ricorsione) 
void ordinsert_rec(BST **ptrPtr, int val){ //NB: GLI INSERIMENTI ANCHE NELLA PILA RICHIEDEVANO IL DOPPIO PUNTATORE NELLA LORO IMPLEMENTAZIONE
    if((*ptrPtr) != NULL) {                                 //Se NON si è alla fine si va avanti fino a trovarla
        if(val<=(*ptrPtr)->valore)                          //Se valore è <= del valore del padre allora vai a sinistra
            ordinsert_rec(&((*ptrPtr)->leftPtr), val);
        else                                                //Destra altrimenti
            ordinsert_rec(&((*ptrPtr)->rightPtr), val);
    }    
    else {                                                  //Se si è arrivati alla fine
        (*ptrPtr) = (BST*)malloc(sizeof(BST));              //si alloca un nuovo spazio tramite questa funzione
        (*ptrPtr)->valore = val;                            //si inserisce il valore
        (*ptrPtr)->leftPtr = NULL;                          //inizializiamo sinistro e destro a NULL ptr
        (*ptrPtr)->rightPtr = NULL;
    }  
}

// ritorna NULL se albero vuoto o se diventa vuoto dopo eliminazione del nodo
BST* remove_node(BST *root, int val) {
    /* If the node becomes NULL, it will return NULL. Two possible cases:
     * 1. If we send the empty tree. i.e root == NULL
     * 2. If the given node is not present in the tree */
    if(root == NULL)
        return NULL;

    // If root->value < val, val must be present in the right subtree
    if(root->valore < val)
        root->rightPtr = remove_node(root->rightPtr, val);
    
    // If root->value > val, val must be present in the left subtree
    else if(root->valore > val)
        root->leftPtr = remove_node(root->leftPtr, val);
    
    /* This part will be executed only if the root->value == val
     * The actual removal starts from here! */
    else {
        // Case 1: Leaf node
        if(root->leftPtr == NULL && root->rightPtr == NULL)
        {
            free(root);
            return NULL;
        }
        // Case 2: Node has right child
        else if(root->leftPtr == NULL)
        {
            BST *tmp = root->rightPtr;
            free(root);
            return tmp;
        }
        // Case 3: Node has left child
        else if(root->rightPtr == NULL)
        {
            BST *tmp = root->leftPtr;
            free(root);
            return tmp;
        }
        // Case 4: Node has both left and right children
        else {
            // save the ptr to left subtree
            BST *tmp = root->leftPtr;
            
            // find the min node on the right subtree (i.e. the left most node)
            BST *rightMin = root->rightPtr;
            while(rightMin->leftPtr != NULL){
                rightMin = rightMin->leftPtr;
            }

            // add the left subtree to the rightMin node
            rightMin->leftPtr = tmp;
            free(root);
            return root->rightPtr;
            //root = root->rightPtr;
        }

    }
    //return the actual root's address
    return root;
}

// cancellazione di un nodo (versione alternativa)
void delete_node(BST **root, int val) {
    if(*root == NULL)
        return;

    if(val != (*root)->valore){
        if(val > (*root)->valore)
            delete_node(&((*root)->rightPtr), val);
        else
            delete_node(&((*root)->leftPtr), val);
    }
    else {
        BST *node_to_leaf = (*root)->leftPtr;
        BST *node_to_delete = *root;

        *root = (*root)->rightPtr;
        free(node_to_delete);

        BST *iteratore = *root;
        if (iteratore != NULL) {
            while (iteratore->leftPtr != NULL) {
                iteratore = iteratore->leftPtr;
            }
            iteratore->leftPtr = node_to_leaf;
        }
        else {
            *root = node_to_leaf;
        }
    }
}

// funzione di stampa/visualizzazione dell'albero
void print_bst2D_util(BST *root, int space){
    
    // Base case
    if (root == NULL)
        return;
 
    // Increase distance between levels
    space += COUNT;
 
    // Process right child first
    print_bst2D_util(root->rightPtr, space);
 
    // Print current node after space
    // count
    printf("\n");
    for (int i = COUNT; i < space; i++)
        printf(" ");
    printf("%d\n", root->valore);
 
    // Process left child
    print_bst2D_util(root->leftPtr, space);
}

void print_bst2D(BST *root){
    // Pass initial space count as 0
    print_bst2D_util(root, 0);
}