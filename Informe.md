# Informe Oscar Lobo


## Funcionamiento del Sistema de Prioridades

El sistema de prioridades implementado utiliza dos campos nuevos: **priority** y **boost** . La prioridad determina el orden en que se seleccionan los procesos para ejecución, con valores más bajos indicando mayor prioridad. El boost ajusta la prioridad de un proceso de forma dinámica.

Cada proceso tiene su prioridad inicializada en 0, lo que significa que todos los procesos empiezan con la máxima prioridad. El campo boost se inicializa en 1.

El boost incrementa o decrementa la prioridad de un proceso en cada ciclo de planificación:

- Si la prioridad alcanza 9, el boost se cambia a -1.
- Si la prioridad baja a 0, el boost se cambia a 1.

Esto crea un efecto de "rebote", donde los procesos alternan entre ser más o menos prioritarios.


## Modificaciones Realizadas

- **Archivo proc.h:** Se añadieron los nuevos campos priority y boost a la estructura proc, que representa los procesos en xv6. Estos campos son fundamentales para implementar el sistema de prioridades en el planificador. El campo priority indica la prioridad del proceso (un valor más bajo indica una mayor prioridad), mientras que boost es utilizado para aumentar temporalmente la prioridad del proceso, aplicando una lógica de envejecimiento que evita que los procesos de baja prioridad queden indefinidamente bloqueados.

- **Archivo proc.c:** Se modificó el planificador principal de xv6 para que ahora considere el campo priority al decidir qué proceso ejecutar. El planificador ahora selecciona el proceso con la prioridad más alta (es decir, el valor más bajo de priority). Adicionalmente, se implementó la funcionalidad de "boost", donde los procesos de baja prioridad reciben un incremento temporal de su prioridad para evitar inanición. Esto se maneja de forma que el campo boost sea utilizado en función de un contador que disminuye con el tiempo y otorga prioridad temporal a los procesos envejecidos.

- **Archivo test_priority.c:** Se creó un programa de prueba que lanza 20 procesos, asignando diferentes valores de prioridad a cada proceso, y simula su ejecución. Este programa permite verificar que el planificador ejecuta primero los procesos con mayor prioridad y observa el comportamiento de los procesos cuando se aplica el boost. Se añadieron impresiones para observar el comportamiento de las prioridades y los boosts durante la ejecución de los procesos.

- **Archivo Makefile**: Se tuvo que añadir el nuevo archivo (test_priority.c), en el cual se ejecuta el programa.



## Dificultades Encontradas y Soluciones

- **Resolver errores**: En el transcurso de la actividad me saltaron muchos errores que no sabia de que eran, por lo que tuve que investigar sobre ellos y ver para solucionarlos. La IA fue de vital ayuda, ya que muchas veces no sabia como solucionar los errores y no había info al respecto.
