#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int main(void) {
    int i;
    int pid;

    // Bucle para crear 20 procesos
    for(i = 0; i < 20; i++) {
        pid = fork();
        if(pid < 0) {
            printf("Error al crear el proceso\n");
            exit(1);
        }
        if(pid == 0) { // Proceso hijo
            // Desincronización de salidas con sleep para evitar colisiones de impresión
            sleep(i * 10);

            // Formato de impresión del proceso hijo
            printf("Proceso hijo %d creado, PID: %d\n", i, getpid());

            sleep(200); // Simular trabajo con un sleep más largo

            // Imprimir mensaje cuando el proceso hijo termina
            printf("Proceso hijo %d con PID: %d terminando\n", i, getpid());
            exit(0); // Proceso hijo termina aquí
        } else {
            // Formato de impresión del proceso padre tras crear el hijo
            printf("Proceso padre: creó hijo %d con PID: %d\n", i, pid);
        }
    }

    // Proceso padre espera a que todos los hijos terminen
    for(i = 0; i < 20; i++) {
        int child_pid = wait(0); // Esperar a que cada proceso hijo termine
        printf("Proceso padre: hijo con PID %d ha terminado\n", child_pid);
    }

    // Imprimir mensaje cuando el proceso padre termina
    printf("Proceso padre terminando\n");
    exit(0); // Salida exitosa del proceso padre
}
