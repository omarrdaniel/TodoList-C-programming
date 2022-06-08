#include <time.h>
#include "todo.h"
#include "ctype.h"
#include "stdlib.h"
#include "string.h"

// Variabile con scope globale che si riferisce alla testa della lista
todo *head = NULL;

// Funzione che imposta l'indice numerico a tutti i nodi
void fixCounter() {
    // Viene usato un nodo di appoggio per spostarci nella lista partendo dalla testa
    todo *temp;
    temp = head;
    // Per ogni nodo presente nella lista, assegniamo il valore dell'indice
    // in ordine di inserimento
    for (int i = 1; temp != NULL; i++) {
        temp->indice = i;
        temp = temp->next;
    }
}

// Funzione per la creazione di una nuova task da inserire nella ToDo List
void createTask() {
    // Si usano due nodi di appoggio
    todo *new, *temp;

    // Temp parte sempre dalla testa e ci servirà per
    // scorrere la lista
    temp = head;

    // Carattere di scelta per continuare l'inserimento
    char c;

    // Ciclo con controllo in coda per inserimento delle nuove task
    do {
        // Caso in cui la lista sia vuota, il nuovo elemento diventa il primo
        if (head == NULL) {
            // Inizializzo il nuovo nodo da inserire
            new = (todo *) calloc(1, sizeof(todo));
            printf("\nDigita la nuova task da inserire:\n");
            fflush(stdin);
            fgets(new->name, BUFSIZ, stdin);
            new->indice = 1;
            new->next = NULL;
            // lo metto in testa
            head = new;
            // Se la lista non è vuota, l'elemento viene assegnato in coda
            // e vengono rifissati gli indici
        } else {
            temp = head;
            // Viene inizializzato il nuovo nodo da inserire
            new = (todo *) calloc(1, sizeof(todo));
            printf("\nDigita la nuova task da inserire:\n");
            fflush(stdin);
            fgets(new->name, BUFSIZ, stdin);
            new->next = NULL;
            new->indice = 0;
            // Lo aggiungo in coda e sistemo gli indici numerici
            while (temp->next != NULL) {
                temp = temp->next;
            }
            temp->next = new;
            fixCounter();
        }
        // Richiesta all'utente se vuole inserire un altro nodo
        printf("\nVuoi inserire un'altra task?\nDigita 'y' o 'n': ");
        fflush(stdin);
        scanf("%c", &c);
        if (tolower(c) != 121) {
            if (tolower(c) != 110) {
                printf("\nErrore, carattere non valido!\n");
                printf("\nUscita dalla funzione di creazione di una nuova task!\n");
            }
        }
        fflush(stdin);
    } while (tolower(c) == 121);
}

// Funzione per stampare tutti i nodi della lista in ordine
void printList() {
    // Si sfrutta un nodo di supporto per scorrere la lista
    todo *temp;
    temp = head;
    // Se la lista è vuota, mi fermo subito
    if (head == NULL) {
        printf("\nLa lista e' vuota!\n");
        // Altrimenti si scorre e si stampa il contenuto di nodo per nodo
    } else {
        while (temp != NULL) {
            printf("%d.)", temp->indice);
            printf("%s", temp->name);
            fflush(stdin);
            temp = temp->next;
        }
        // Pause per permettere all'utente di leggere la lista fermando temporaneamente il programma
        // System ci permette di chiamare ed eseguire un comando del sistema operativo
        system("pause");
    }
}

// Funzione per eliminare un nodo dalla lista
int deleteTask() {
    int del;
    todo *prev, *temp;
    if(head == NULL) {
        printf("La lista e' vuota!");
    } else {
        // Assegniamo la testa al nodo di supporto "temp"
        temp = head;
        // Viene chiesto all'utente l'indice per cercare la task da cancellare
        // Si effettua un controllo sull'input dell'utente per assicurarci che sia corretto
        // Se viene rilevato un input non adatto, termina la funzione
        printf("\nDigita l'indce della task da cancellare: ");
        fflush(stdin);
        int check = scanf("%d", &del);
        if (check < 1) {
            printf("\nErrore nell'input, uscita dalla funzione!\n");
            fflush(stdin);
        } else {
            // Si verifica se l'elemento da eliminare è il primo, così da non scorrere tutta la lista
            if (temp != NULL && temp->indice == del) {
                head = temp->next;
                // Liberiamo la memoria Heap, allocata dinamicamente in precedenza
                free(temp);
                printf("\nTask cancellata correttamente!\n");
                fixCounter();
            } else {
                // Se non è il primo nodo, si scorre fino a trovare quello richiesto
                while (temp != NULL && temp->indice != del) {
                    prev = temp;
                    temp = temp->next;
                }

                // In caso di Miss, viene segnalato all'utente e viene ritornato -1
                if (temp == NULL) {
                    printf("\nTask non trovata!\n");
                    return -1;
                }
                prev->next = temp->next;
                free(temp);
                printf("\nTask cancellata correttamente!\n");

                fixCounter();
            }
        }
    }
}

// Funzione per stampare il menu delle scelte a video
void displayMenu() {
    printf("\n\t **** Benvenuto nella tua ToDo list personale ****");

    printf("\n\n\n\t\t\tMENU PRINCIPALE\n\t\t=====================\n\t\t[1] Crea una nuova task\n\t\t[2] Visualizza la tua ToDo list\n\t\t[3] Cancella una task\n\t\t[4] Modifica una task\n\t\t[5] Cerca una task\n\t\t[0] Esci\n\t\t=====================\n\t\t");

    printf("\nDigita la tua scelta:\n");
}

// Funzione per modificare il nome di una task
void editTask() {
    int find;
    todo *temp;
    // Viene segnalato se la lista è vuota
    if (head == NULL) {
        printf("\nLa lista e' vuota\n");
        // Se è presente un solo elemento si va a modificare quello senza chiedere l'indice
    } else if (head->next == NULL) {
        char new_name[BUFSIZ];
        printf("\nUn solo elemento presente, verra' modificato quest'ultimo\n");
        printf("\nDigita il nuovo nome per la task: \n");
        fflush(stdin);
        fgets(new_name, BUFSIZ, stdin);
        strncpy(head->name, new_name, BUFSIZ);
    } else {
        // Si chiede all'utente l'indice del nodo da modificare sempre effettuando controllo sull'input
        temp = head;
        char new_name[BUFSIZ];
        printf("\nDigita l'indice della task da modificare: ");
        fflush(stdin);
        int check = scanf("%d", &find);
        if (check < 1) {
            printf("\nErrore nell'input, uscita dalla funzione!\n");
            fflush(stdin);
        } else {
            // Si scorre la lista finchè non viene trovato il nodo richiesto
            while (temp != NULL) {
                if (temp->indice == find) {
                    printf("\nTask trovata correttamente!\n");
                    printf("\nDigita il nuovo nome per la task: \n");
                    fflush(stdin);
                    fgets(new_name, BUFSIZ, stdin);
                    strncpy(temp->name, new_name, BUFSIZ);
                    temp = temp->next;
                } else {
                    temp = temp->next;
                }
            }
        }
    }
}

// Funzione per cercare un nodo all'interno della lista utilizzando il nome (ritorna 1 se trovato, -1 se non trovato)
int searchTask() {
    todo *temp;
    char find[BUFSIZ];
    // Se la lista è vuota, viene segnalato subito
    if (head == NULL) {
        printf("\nLa lista e' vuota!\n");
        // Se la lista ha un solo elemento, viene stampato a video quel nodo
    } else if (head->next == NULL) {
        printf("\nLa lista ha un solo elemento ed e' il seguente: \n");
        printList();
        // Altrimenti si scorre la lista finchè non si trova l'elemento richiesto. Se non presente, viene segnalato l'errore all'utente
    } else {
        temp = head;
        printf("\nDigita il nome della task che vuoi trovare\n");
        fflush(stdin);
        fgets(find, BUFSIZ, stdin);
        while (temp != NULL) {
            if (strcmp(temp->name, find) == 0) {
                printf("\nTask trovata alla posizione %d\n", temp->indice);
                return 1;
            }
            temp = temp->next;
        }
        printf("\nTask non trovata!\n");
        return -1;
    }
}

// Funzione per la terminazione del programma e salvataggio lista finale nel file
int stop() {
    // Creazione del puntatore al file che verrà creato e aperto in modalità append
    FILE *fp = fopen("ToDoList.txt", "a");
    todo *temp = head;
    // Per Inserire data di salvataggio su file della ToDo List
    time_t t;
    time(&t);
    // Controllo sul puntatore al file
    if (fp == NULL) {
        return -1;
    }
    // Scrittura su file di testo delle informazioni necessarie
    fprintf(fp, "\nLa seguente ToDo List e' stata creata il: %s\n", ctime(&t));
    while (temp != NULL) {
        fprintf(fp, "%d.)%s", temp->indice, temp->name);
        temp = temp->next;
    }
    return 1;
}