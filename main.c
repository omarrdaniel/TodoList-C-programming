#include "todo.h"

int main() {
    // Variabili per controllo input e scelta utente
    int ch, check;
    // Ciclo infinito finchè non si decide di uscire dal programma
    while (1) {
        // Stampa del menu con le scelte
        displayMenu();
        // Ciclo di controllo correttezza input
        do {
            fflush(stdin);
            check = scanf("%d", &ch);
            if (check != 1) {
                printf("\nErrore nell'input, riprova!\n");
                fflush(stdin);
            }
        } while (check != 1);
        // Switch con i diversi case, ognuno per ogni funzione
        switch (ch) {
            case 1:
                createTask();
                break;
            case 2:
                printList();
                break;
            case 3:
                deleteTask();
                break;
            case 4:
                editTask();
                break;
            case 5:
                searchTask();
                break;
            case 0:
                return (stop());
            default:
                printf("\nScelta non valida\n");
        }
    }
}
