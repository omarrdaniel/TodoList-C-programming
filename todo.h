#include "stdio.h"

// Struttura del nodo todo
typedef struct ToDo todo;

struct ToDo {
    char name[BUFSIZ];
    int indice;
    todo *next;
};

// Variabile che si riferirà alla testa
todo *head;

// Lista dei metodi poi implementati nel relativo .c
void fixCounter();

void createTask();

int deleteTask();

void displayMenu();

void printList();

void editTask();

int searchTask();

int stop();
