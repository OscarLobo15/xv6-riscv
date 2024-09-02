#include "kernel/types.h"
#include "user.h"

int main(int argc, char *argv[]) {
    int ppid = getppid();
    printf("El ID del proceso padre es: %d\n", ppid);  // Cambié el primer argumento a una cadena

    for (int i = 0; i < 3; i++) {
        int ancestor = getancestor(i);
        if (ancestor != -1) {
            printf("El ancestro %d es: %d\n", i, ancestor);  // Cambié el primer argumento a una cadena
        } else {
            printf("No hay ancestro %d\n", i);  // Cambié el primer argumento a una cadena
        }
    }

    exit(0);  // Cambié a exit(0) para indicar una salida exitosa
}