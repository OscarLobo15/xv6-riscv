#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int main() {
    char *addr = sbrk(0);  // Obtener la dirección actual del heap
    sbrk(4096);  // Reservar una página
    // Intentar proteger la nueva página
    if (mprotect(addr, 1) == -1) {
        printf("mprotect falló\n");
    } else {
        printf("mprotect fue exitoso\n");
    }

    // Intentar escribir en la página protegida
    char *ptr = addr;
    *ptr = 'A';  // Esto debería fallar si la protección es exitosa
    printf("Valor en la dirección: %c\n", *ptr);  // Verificar el valor

    // Desproteger la página y volver a intentar escribir
    if (munprotect(addr, 1) == -1) {
        printf("munprotect falló\n");
    } else {
        *ptr = 'A';  // Esto debería ser exitoso ahora
        printf("Valor en la dirección después de munprotect: %c\n", *ptr);
    }
    return 0;
}