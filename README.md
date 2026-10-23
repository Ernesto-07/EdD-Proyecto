# Sistema de Puntuaciones y Juego de Navegación Espacial

## Descripción General del Proyecto
Este proyecto es un sistema interactivo de navegación espacial desarrollado en C++ que permite a los usuarios jugar una misión en una cuadrícula $8 \times 8$, guardar las puntuaciones de cada partida y gestionarlas a través de un leaderboard ordenado y un historial de partidas recientes.

El programa almacena los datos de los participantes mediante la clase `Player`, que contiene:
- Nombre del Jugador (`string`)
- Puntuación Obtenida (`int`)

---

## Descripción del Avance 1
En el primer avance se implementó la base del juego y la gestión dinámica de puntuaciones:
- Registro de puntuaciones en un `std::vector<Player>`.
- Ordenamiento del leaderboard de mayor a menor puntaje mediante la clase `Sorts<T>` utilizando el algoritmo **Merge Sort** y la sobrecarga del operador `>=`.
- Lógica básica del juego interactivo en consola dentro de `game.h`.

---

## Descripción del Avance 2
En este segundo avance se incorporó una nueva estructura de datos lineal: una **Fila / Buffer Circular** de tamaño estático ($MAX = 5$) a través de la clase `Historial` (`historial.h`):
- **Almacenamiento de Partidas Recientes:** Permite registrar las últimas 5 partidas jugadas sin sobrecargar la memoria.
- **Sobrescritura Automática (FIFO):** Cuando el historial alcanza su capacidad máxima (5 elementos), la partida más antigua es reemplazada automáticamente por la más nueva mediante aritmética modular (`head = (head + 1) % MAX`).
- **Integración al Menú Principal:** Se añadió la opción en consola para consultar el historial reciente en orden cronológico (de la más antigua a la más reciente entre las últimas 5).

---

## Cambios con respecto al Avance 1
1. **Incorporación de la clase `Historial` (`historial.h`):** Se añadió la estructura de datos Fila/Buffer Circular para almacenar únicamente las 5 partidas más recientes.
2. **Actualización del Menú Principal (`main.cpp`):** Se agregó la opción `3. Ver Historial reciente` y se desplazó la opción `Salir` al número `4`.
3. **Separación de responsabilidades de consulta:** Ahora el usuario puede ver tanto la tabla global ordenada (Leaderboard) como el flujo secuencial directo de las últimas partidas jugadas (Historial).

---

## Estructura y Archivos del Proyecto
- `main.cpp`: Contiene el menú principal, el flujo del programa, el registro dinámico de jugadores y la interacción con el usuario.
- `player.h`: Define la clase `Player` con sus atributos (nombre y puntaje), getters y la sobrecarga del operador `>=` para la comparación de puntuaciones.
- `scores.h`: Contiene la clase plantilla `Sorts<T>` con la implementación del algoritmo **Merge Sort** y su análisis de complejidad temporal.
- `game.h`: Contiene la lógica del juego de navegación espacial en la cuadrícula de $8 \times 8$, el conteo de movimientos/combustible y la función del cálculo de puntaje.
- `historial.h`: Contiene la clase `Historial`, que implementa la **Fila / Buffer Circular** estática para el registro de las últimas 5 partidas.

---

## ¿Cómo usar el programa?

Al ejecutar el programa se muestra el menú principal en consola:

    --- MENU PRINCIPAL ---
    1. Jugar
    2. Ver Leaderboard
    3. Ver Historial reciente
    4. Salir
    Selecciona una opcion:

### Opciones del Menú:
1. **Jugar:**
   Solicita el nombre del jugador e inicia la partida de navegación espacial.
   - **Mecánica del juego:** El jugador controla una nave `[^]` en una cuadrícula de $8 \times 8$ e intenta llegar a la estación base `(H)` usando los controles `w`, `a`, `s`, `d`.
   - **Puntuación:** El objetivo es completar la misión utilizando la menor cantidad de movimientos posible. Entre más combustible ahorre, mayor será el puntaje calculated al llegar a la base.

2. **Ver Leaderboard:**
   Toma el vector con todos los jugadores registrados, ejecuta el algoritmo **Merge Sort** para ordenarlos por su puntaje de forma descendente y despliega la tabla de posiciones en pantalla. Si no hay partidas registradas, muestra un mensaje de aviso.

3. **Ver Historial reciente:**
   Muestra el registro de las últimas 5 partidas jugadas guardadas en la Fila/Buffer circular, ordenadas cronológicamente de la más antigua a la más reciente de ese bloque.

4. **Salir:**
   Muestra un mensaje de despedida y finaliza la ejecución del programa.

---

## Instrucciones para compilar y ejecutar

### Compilación:
Ejecuta el siguiente comando en la terminal:
```bash
g++ -std=c++11 main.cpp -o avance2
```

### Ejecución:
Ejecuta el siguiente comando en la terminal:
```bash
./avance2
```

---

## Cumplimiento de las Sub-competencias

### SICT0301: Evalúa los componentes

#### Análisis de complejidad de las Estructuras de Datos

1. **Vector (`std::vector<Player> listaJugadores`):**
   - **Inserción (`push_back`):**
     - *Mejor y caso promedio:* $O(1)$, la inserción al final del vector es inmediata si hay capacidad disponible.
     - *Peor caso:* $O(n)$, si el vector alcanza su límite de capacidad, reasigna memoria y copia los $n$ elementos existentes a la nueva dirección.
   - **Acceso por índice (`listaJugadores[i]`):**
     - *Mejor, promedio y peor caso:* $O(1)$, el acceso directo a la memoria mediante índice en un arreglo dinámico contiguo es en tiempo constante.
   - **Complejidad Espacial:** $O(n)$, donde $n$ es la cantidad total de jugadores registrados a lo largo de la ejecución.

2. **Fila / Buffer Circular (`Historial data[MAX]` con $MAX = 5$):**
   - **Inserción (`add`):**
     - *Mejor, promedio y peor caso:* $O(1)$, la adición de una partida realiza operaciones aritméticas modulares básicas (`(head + count) % MAX`) sobre un arreglo estático. Si la estructura está llena, sobrescribe el elemento en `head` e incrementa la posición en tiempo constante.
   - **Consulta / Impresión (`print`):**
     - *Mejor, promedio y peor caso:* $O(1)$ constante (acotado por $O(k)$ donde $k \le 5$). Recorre como máximo $MAX$ posiciones fijas, por lo que no depende de cuántas partidas totales se hayan jugado en la sesión.
   - **Complejidad Espacial:** $O(1)$, ya que utiliza una cantidad de memoria estática y acotada a exactamente 5 elementos `Player`.

#### Análisis de complejidad del Algoritmo de Ordenamiento (Merge Sort)

El algoritmo Merge Sort implementado en `scores.h` presenta el siguiente comportamiento:

| Caso | Complejidad Temporal |
| :--- | :--- |
| **Mejor caso** | $O(n \log n)$ |
| **Caso promedio** | $O(n \log n)$ |
| **Peor caso** | $O(n \log n)$ |

- **Desglose:** La función `mergeSplit` divide recursivamente el vector en mitades hasta llegar a elementos individuales ($\log n$ niveles de división). Posteriormente, `mergeArray` combina las partes ordenadas en un arreglo temporal mediante un recorrido lineal $O(n)$.
- **Complejidad Final del Sistema:** Dado que las operaciones de inserción y consulta en el historial son $O(1)$, la complejidad dominante en las operaciones de procesamiento global del sistema está determinada por el ordenamiento del leaderboard, resultando en una complejidad final del programa de **$O(n \log n)$**.

---

### SICT0302: Toma decisiones

1. **Selección de Merge Sort para el Leaderboard:**
   A diferencia de algoritmos elementales como Bubble Sort o Selection Sort ($O(n^2)$), Merge Sort garantiza un tiempo de ejecución constante de $O(n \log n)$ independientemente de la disposición inicial de los datos. Además, al ser un algoritmo estable, conserva el orden relativo de registro entre jugadores que obtienen exactamente el mismo puntaje.

2. **Selección de la Fila / Buffer Circular (`Historial`) para partidas recientes:**
   Para gestionar el historial reciente de partidas, se seleccionó una **Fila (Queue) implementada mediante un arreglo circular de tamaño fijo** ($MAX = 5$). 
   - *Justificación:* Mantener todas las partidas jugadas en un vector ilimitado requeriría un consumo creciente de memoria y desplazamientos de elementos $O(n)$ si quisiéramos eliminar los más antiguos. Con la Fila Circular, se logra una inserción de $O(1)$ y un límite rígido de memoria $O(1)$, garantizando eficiencia para un requerimiento de "últimas $N$ partidas".

---

### SICT0303: Implementa acciones científicas

1. **Mecanismos para consultar información de las estructuras:**
   - **Consulta del Leaderboard (`listaJugadores` + `Sorts`):** Se implementó la consulta mediante el método `mergeSort()`, el cual genera una copia ordenada descendente del vector original y la despliega secuencialmente mediante un ciclo $O(n)$.
   - **Consulta del Historial (`Historial::print`):** Se implementó la lectura de la Fila circular calculando el desplazamiento de índices `(head + i) % MAX`, lo que permite consultar e imprimir los datos preservando el orden FIFO (First In, First Out).

2. **Mecanismos de lectura e ingreso de datos a las estructuras:**
   - Durante la ejecución interactiva, las entradas del usuario (nombre ingresado por consola y puntuación obtenida dinámicamente en `game.play()`) se empaquetan en instancias de la clase `Player`. 
   - Estas instancias son cargadas de manera correcta en ambas estructuras mediante invocaciones explícitas de `listaJugadores.push_back(nuevoJugador)` para el almacenamiento dinámico total y `historial.add(nuevoJugador)` para el buffer circular.

---

## Créditos y Reconocimientos
- **Lógica del Juego (`game.h`):** El código base de la lógica del juego de navegación espacial fue desarrollado con apoyo de Gemini para la simulación de cuadrícula en consola, bajo autorización del profesor para la exploración de la mecánica de juego.
