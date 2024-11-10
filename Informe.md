# Informe Oscar Lobo

## Funcionamiento del Sistema de Protección de Memoria
El sistema de protección de memoria implementado en xv6 utiliza dos nuevas funciones de sistema: `mprotect` y `munprotect`. Estas funciones permiten marcar regiones de memoria como solo lectura y revertir esta protección, respectivamente. La funcionalidad tiene como objetivo mejorar la gestión de memoria en el kernel, evitando que procesos escriban en regiones específicas de memoria de forma inadvertida.

### mprotect
Esta función permite marcar una región de memoria, comenzando en una dirección específica (`addr`) y con una longitud (`len`), como solo lectura. El número de páginas involucradas se calcula y se actualizan los permisos en la tabla de páginas correspondiente, desactivando el bit de escritura de cada entrada de tabla de página (PTE).

### munprotect
Esta función se utiliza para revertir la protección de solo lectura, devolviendo los permisos de escritura a una región de memoria previamente protegida. Similar a `mprotect`, la función recorre las páginas afectadas y restaura el permiso de escritura en las PTE correspondientes.

### Manejo de Excepciones
Se añadió una lógica en el archivo `trap.c` para capturar y manejar las excepciones de protección de página (fallos de protección de escritura). Si un proceso intenta escribir en una página marcada como solo lectura, se genera un fallo que el kernel detecta y maneja adecuadamente, finalizando el proceso de forma controlada.

## Modificaciones Realizadas

### Archivo `proc.h`
Se añadieron nuevas funciones de sistema (`mprotect` y `munprotect`) en la estructura de las llamadas al sistema. No fue necesario añadir nuevos campos a la estructura `proc`, ya que la implementación se basa en la manipulación de los bits de las tablas de páginas existentes.

### Archivo `sysproc.c`
Se implementaron las funciones `sys_mprotect` y `sys_munprotect`. Estas funciones manejan los argumentos proporcionados por el proceso, validan las direcciones y actualizan las PTEs de la tabla de páginas para establecer o quitar la protección de solo lectura.

- **`sys_mprotect`**: Desactiva el bit de escritura (`PTE_W`) de las PTEs de las páginas involucradas.
- **`sys_munprotect`**: Restaura el bit de escritura (`PTE_W`) en las PTEs de las páginas especificadas.

Ambas funciones incluyen validaciones para asegurar que las direcciones estén alineadas a páginas y que la región solicitada esté dentro del espacio de memoria del proceso.

### Archivo `syscall.c`
Se añadieron las llamadas a las funciones `sys_mprotect` y `sys_munprotect` en la lista de llamadas al sistema, asegurando que el kernel pueda reconocer y manejar estas nuevas funciones.

### Archivo `syscall.h`
Se asignaron los números de llamada al sistema para `SYS_mprotect` y `SYS_munprotect`, lo que permite que el kernel las identifique y las asocie con las funciones correspondientes en `sysproc.c`.

### Archivo `trap.c`
Se añadió un bloque de manejo de excepciones para capturar los fallos de protección de página. Cuando se produce un intento de escritura en una página de solo lectura, el kernel imprime un mensaje con detalles sobre el fallo, incluyendo la dirección de memoria y el PID del proceso. Luego, el proceso es finalizado de forma controlada.

### Archivo `test_mprotect.c`
Se creó un programa de prueba que simula la protección de memoria y su reversión. Este programa reserva una página de memoria, la marca como solo lectura con `mprotect`, intenta escribir en ella (lo que genera un fallo de protección) y luego la desprotege con `munprotect` para confirmar que se puede escribir nuevamente.

El programa imprime mensajes para verificar el éxito de las operaciones y observar el comportamiento del kernel durante la protección y desprotección de la memoria.

### Archivo `Makefile`
Se añadieron las reglas de compilación para el archivo `test_mprotect.c`, permitiendo que el programa de prueba sea compilado y ejecutado junto con el resto de los programas de usuario.

## Dificultades Encontradas y Soluciones

### Manejo de Errores de Protección
Durante la implementación, surgieron errores al manipular las PTEs, especialmente en la validación de direcciones y la alineación a páginas. La solución involucró revisar la documentación de xv6 y entender cómo funcionan las tablas de páginas y las entradas de las PTEs. La IA fue una herramienta fundamental para resolver dudas y encontrar soluciones rápidas cuando la documentación era limitada.

### Validación de Pruebas
Al realizar pruebas con el programa `test_mprotect`, se observaron fallos de segmentación al intentar escribir en páginas protegidas. Esto confirmó que la protección funcionaba, pero también reveló la necesidad de un manejo adecuado en `trap.c` para capturar y reportar estos fallos de forma clara.

