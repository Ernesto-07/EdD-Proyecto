# Sistema de Puntuaciones y Juego de Navegación Espacial

## Descripción del avance

En este proyecto hice un programa para jugar una misión de navegación espacial y guardar los puntajes de los jugadores en una tabla de posiciones ordenada. El programa utiliza una clase `Player` para almacenar los datos principales de cada participante:

* **Nombre del Jugador** (`string`)
* **Puntuación Obtenida** (`int`)

La información de los jugadores se registra dinámicamente en un `vector`. El programa permite jugar partidas individuales, registrar los resultados obtenidos y visualizarlos en una tabla ordenada de mayor a menor puntaje.

Para realizar el ordenamiento se implementó el algoritmo **Merge Sort**, mediante la clase `Sorts<T>`. El algoritmo ordena a los jugadores comparando sus puntajes mediante la sobrecarga del operador `>=`.

El programa está dividido en archivos para mantener una estructura modular limpia:

* **main.cpp**: Contiene el menú principal, el flujo del programa y la interacción con el usuario.
* **player.h**: Contiene la clase `Player`, sus atributos, constructores, getters y la sobrecarga de operadores para comparación.
* **scores.h**: Contiene la implementación del algoritmo **Merge Sort** (`Sorts<T>`) y su análisis de complejidad.
* **game.h**: Contiene la lógica del juego interactivo en cuadrícula (misión espacial de navegación).

---

## ¿Cómo usar el programa?

Al ejecutar el programa se muestra el menú principal en consola:

```text
--- MENU PRINCIPAL ---
1. Jugar
2. Ver Leaderboard
3. Salir
Selecciona una opcion:
```

### 1. Jugar
Al seleccionar la opción 1, el programa solicita el nombre del jugador e inicia la partida de navegación espacial. 

**Mecánica ligera del juego:**
El jugador controla una nave `[^]` en un mapa espacial e intenta llegar a la estación base `(H)` usando los controles `w`, `a`, `s`, `d`. El objetivo es completar la misión utilizando la menor cantidad de movimientos posible. Entre más combustible ahorre el jugador, mayor será el puntaje calculado al llegar a la base.

### 2. Ver Leaderboard
Al seleccionar la opción 2, el programa toma el vector con todos los jugadores registrados, ejecuta el algoritmo **Merge Sort** para ordenarlos por su puntaje de forma descendente y despliega la tabla de posiciones en pantalla.

Si aún no hay partidas jugadas, el sistema despliega el mensaje:
`Aun no hay jugadores registrados.`

### 3. Salir
Finaliza la ejecución del programa.

---

## Cumplimiento de las sub-competencias

### SICT0301: Evalúa los componentes

Para este avance se realizó el análisis de complejidad del algoritmo de ordenamiento utilizado en `scores.h`.

El programa utiliza **Merge Sort**, cuya complejidad temporal es:

| Caso | Complejidad |
| :--- | :--- |
| **Mejor caso** | $O(n \log n)$ |
| **Caso promedio** | $O(n \log n)$ |
| **Peor caso** | $O(n \log n)$ |

La función `mergeSort` realiza la llamada inicial dividiendo el vector mediante `mergeSplit`. Esta función divide de forma recursiva el arreglo en dos mitades hasta llegar a subarreglos de un solo elemento (requiriendo $\log n$ divisiones). Posteriormente, utiliza la función `mergeArray` para combinar las partes nuevamente de forma ordenada.

La combinación mediante `mergeArray` recorre los elementos de ambas partes para colocarlos en orden en el arreglo temporal, teniendo una complejidad lineal de $O(n)$. Por lo tanto, al combinar los $\log n$ niveles con el trabajo de $O(n)$ por nivel, la complejidad total del algoritmo es $O(n \log n)$ en todos sus casos.

El análisis de complejidad detallado también se encuentra indicado directamente en `scores.h` mediante comentarios línea por línea.

---

### SICT0302: Toma decisiones

Para organizar la tabla de posiciones se seleccionó **Merge Sort** como algoritmo de ordenamiento debido a que garantiza un rendimiento estable de $O(n \log n)$ independientemente de si los puntajes de los jugadores ingresados están previamente ordenados, en orden inverso o desordenados.

A diferencia de algoritmos simples como Bubble Sort o Insertion Sort, Merge Sort mantiene su eficiencia optimizada para escalar adecuadamente ante un número elevado de registros.

---

## Créditos y Reconocimientos

* **Estructura Base y Algoritmo de Ordenamiento:** Desarrollo realizado para la materia utilizando la plantilla genérica MergeSort.
* **Lógica del Juego (`game.h`):** El módulo del juego de navegación espacial fue desarrollado íntegramente con la asistencia y co-creación de **Gemini (Modelo de IA de Google)** como herramienta de apoyo para el desarrollo interactivo en consola C++.
