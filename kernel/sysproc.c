#include "types.h"
#include "riscv.h"
#include "defs.h"
#include "param.h"
#include "memlayout.h"
#include "spinlock.h"
#include "proc.h"

uint64
sys_exit(void)
{
    int n;
    argint(0, &n);
    exit(n);
    return 0;  // not reached
}

uint64
sys_getpid(void)
{
    return myproc()->pid;
}

uint64
sys_fork(void)
{
    return fork();
}

uint64
sys_wait(void)
{
    uint64 p;
    argaddr(0, &p);
    return wait(p);
}

uint64
sys_sbrk(void)
{
    uint64 addr;
    int n;

    argint(0, &n);
    addr = myproc()->sz;
    if (growproc(n) < 0)
        return -1;
    return addr;
}

uint64
sys_sleep(void)
{
    int n;
    uint ticks0;

    argint(0, &n);
    if (n < 0)
        n = 0;
    acquire(&tickslock);
    ticks0 = ticks;
    while (ticks - ticks0 < n) {
        if (killed(myproc())) {
            release(&tickslock);
            return -1;
        }
        sleep(&ticks, &tickslock);
    }
    release(&tickslock);
    return 0;
}

uint64
sys_kill(void)
{
    int pid;

    argint(0, &pid);
    return kill(pid);
}

// return how many clock tick interrupts have occurred since start.
uint64
sys_uptime(void)
{
    uint xticks;

    acquire(&tickslock);
    xticks = ticks;
    release(&tickslock);
    return xticks;
}

// Implementación de getppid
uint64 sys_getppid(void) {
    return myproc()->parent ? myproc()->parent->pid : -1;  // Retorna el PID del proceso padre o -1 si no tiene padre
}

// Función para obtener el ancestro
int getancestor(int n) {
    struct proc *p = myproc(); // Obtiene el proceso actual

    // Debug: imprime el PID del proceso actual
    //printf("Proceso actual PID: %d\n", p->pid); // Usa printf en lugar de cprintf

    // Si n es 0, retorna el ID del proceso actual
    if (n == 0) {
        return p->pid; // Asegúrate de que esto retorne el PID correcto
    }

    // Navega a través de los padres
    for (int i = 1; i <= n; i++) {
        if (p->parent == 0) {
            return -1; // No hay ancestro
        }
        p = p->parent; // Mueve al proceso padre
    }
    return p->pid; // Retorna el ID del ancestro
}

// Implementación de getancestor
uint64 sys_getancestor(void) {
    int n;
    argint(0, &n);
    if (n < 0) { // Verifica el retorno de argint()
        return -1; // Manejo de errores si no se puede obtener el argumento
    }
    //printf("Valor de n: %d\n", n); // Debug: imprime el valor de n
    return getancestor(n); // Llama a la función getancestor
}