# Informe Oscar Lobo

### getppid()
- Esta llamada retorna el ID del proceso padre del proceso que la invoca.

### getancestor(int)
- Esta llamada retorna el ancestro especificado:
  - getancestor(0): retorna el mismo proceso.
  - getancestor(1): retorna el padre.
  - getancestor(2): retorna el abuelo.
  - Retorna -1 si no hay suficientes ancestros.



## Modificaciones Realizadas

- **Archivo syscall.c**: Se agregaron las declaraciones de las funciones sys_getppid y sys_getancestor al final de las declaraciones de prototipos de funciones de manejo de llamadas al sistema. Lugeo, Se agregaron las entradas correspondientes a SYS_getppid y SYS_getancestor en el arreglo syscalls, que mapea los números de llamada al sistema a las funciones que las manejan. Se implementaron las funciones sys_getppid y sys_getancestor en el archivo sysproc.c. Los cambios realizados en este archivo permiten que las nuevas llamadas al sistema getppid y getancestor se integren correctamente en xv6 y puedan ser utilizadas por los programas de usuario.

- **Archivo sysproc.c**: Se agregaron las declaraciones de las funciones sys_getppid y sys_getancestor al final de las declaraciones de prototipos de funciones de manejo de llamadas al sistema. Se implementaron las funciones sys_getppid y sys_getancestor.

- **Archivo syscall.h**: Se agregaron las definiciones para SYS_getppid y SYS_getancestor al final de la lista existente de números de llamadas al sistema.

- **Archivo user.h**: Se agregaron las declaraciones para las funciones getppid y getancestor al final de la lista de llamadas al sistema.

- **Archivo usys.pl**: Se debieron agregar las entradas para las nuevas llamadas al sistema getppid y getancestor en el script, de manera que se generen los stubs correspondientes en usys.S.


- **Archivo yosoytupadre.c**: Se creo este archivo en donde se ejecuta el programa, este programa obtiene el ID del proceso padre utilizando getppid() y luego obtiene los ancestros (yo mismo, padre y abuelo) utilizando getancestor(). Imprime esta información y luego sale con un código de salida exitoso.

- **Archivo Makefile**: Se tuvo que añadir el nuevo archivo (yosoytupadre.c), en el cual se ejecuta el programa.



## Dificultades Encontradas y Soluciones

- **Comprensión del Código Existente**: La mayor dificultad fue entender cómo funcionaban las llamadas al sistema existentes. Esto lo resolví revisando la implementación de getpid() y otros ejemplos en sysproc.c. También tuve que buscar información en internet y apoyarme realizando preguntas a la IA.
- **Integración en el Makefile**: Asegurarse de que el nuevo programa se compilara correctamente requirió revisar la estructura del Makefile.
- **Resolver errores**: En el transcurso de la actividad me saltaron muchos errores que no sabia de que eran, por lo que tuve que investigar sobre ellos y ver para solucionarlos.
