#include "kernel/types.h"
#include "kernel/stat.h"
#include "user.h"

int main() {
    char *addr = sbrk(0);  // Obtener la dirección actual del heap
    sbrk(4096);             // Reservar una página

    // Intentar proteger la página (convertirla en solo lectura)
    if (mprotect(addr, 1) == -1) {
        printf("mprotect falló\n");
    } else {
        printf("mprotect fue exitoso\n");
    }

    // Quitar la protección de solo lectura con munprotect antes de la escritura
    if (munprotect(addr, 1) == -1) {
        printf("munprotect falló\n");
    } else {
        printf("munprotect fue desactivado\n");
    }

    // Intentar escribir en la página protegida (esto debería ser exitoso ahora)
    char *ptr = addr;
    *ptr = 'A';  // Esto ya no debería causar una trampa
    printf("Escritura después de munprotect exitosa, valor en la dirección: %c\n", *ptr);

    // Intentar escribir en la página nuevamente para verificar
    *ptr = 'B';
    printf("Escritura después de la segunda prueba exitosa, valor en la dirección: %c\n", *ptr);

    exit(0);
}
