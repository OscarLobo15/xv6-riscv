#include "types.h"
#include "riscv.h"
#include "defs.h"
#include "param.h"
#include "memlayout.h"
#include "spinlock.h"
#include "proc.h"

uint64 sys_exit(void) {
    int n;
    argint(0, &n);
    exit(n);
    return 0;  // not reached
}

uint64 sys_getpid(void) {
    return myproc()->pid;
}

uint64 sys_fork(void) {
    return fork();
}

uint64 sys_wait(void) {
    uint64 p;
    argaddr(0, &p);
    return wait(p);
}

uint64 sys_sbrk(void) {
    uint64 addr;
    int n;

    argint(0, &n);
    addr = myproc()->sz;
    if (growproc(n) < 0)
        return -1;
    return addr;
}

uint64 sys_sleep(void) {
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

uint64 sys_kill(void) {
    int pid;
    argint(0, &pid);
    return kill(pid);
}

uint64 sys_uptime(void) {
    uint xticks;
    acquire(&tickslock);
    xticks = ticks;
    release(&tickslock);
    return xticks;
}

// Helper function to calculate number of pages
static int num_pages(uint64 addr, int len) {
    return (PGROUNDUP(addr + len) - PGROUNDDOWN(addr)) / PGSIZE;
}

// mprotect implementation
uint64 sys_mprotect(void) {
    uint64 addr;
    int len;
    argaddr(0, &addr);  // No comparaciones con -1
    argint(1, &len);    // No comparaciones con -1

    if (addr == 0 || len <= 0 || addr % PGSIZE != 0) // Verificar alineación de página
        return -1;

    struct proc *p = myproc();
    if (addr + len * PGSIZE > p->sz) // Verificar que el rango esté dentro del espacio de proceso
        return -1;

    pte_t *pte;
    int pages = num_pages(addr, len);
    uint64 start_addr = PGROUNDDOWN(addr);

    for (int i = 0; i < pages; i++) {
        pte = walk(p->pagetable, start_addr + i * PGSIZE, 0);
        if (!pte || !(*pte & PTE_V))
            return -1;
        *pte &= ~PTE_W; // Disable write permission
    }
    sfence_vma();
    return 0;
}

// munprotect implementation
uint64 sys_munprotect(void) {
    uint64 addr;
    int len;
    argaddr(0, &addr);  // No comparaciones con -1
    argint(1, &len);    // No comparaciones con -1

    if (addr == 0 || len <= 0 || addr % PGSIZE != 0) // Verificar alineación de página
        return -1;

    struct proc *p = myproc();
    if (addr + len * PGSIZE > p->sz) // Verificar que el rango esté dentro del espacio de proceso
        return -1;

    pte_t *pte;
    int pages = num_pages(addr, len);
    uint64 start_addr = PGROUNDDOWN(addr);

    for (int i = 0; i < pages; i++) {
        pte = walk(p->pagetable, start_addr + i * PGSIZE, 0);
        if (!pte || !(*pte & PTE_V))
            return -1;
        *pte |= PTE_W; // Enable write permission
    }
    sfence_vma();
    return 0;
}
