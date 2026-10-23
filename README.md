# Sistema de Puntuaciones y Juego de Navegación Espacial

**Autor:** Ernesto Beltran

## Descripción General del Proyecto
Este proyecto es un juego de consola en C++ en el que el jugador controla una nave en una cuadrícula $8 \times 8$ y debe llegar a la base antes de quedarse sin combustible. Las puntuaciones se guardan en estructuras de datos y se pueden consultar mediante un leaderboard ordenado, un historial de partidas recientes y dos tipos de búsqueda.

Cada participante se representa con la clase `Player`, que contiene:
- Nombre del jugador (`string`)
- Puntuación obtenida (`int`)

---

## Descripción del Avance 1
- Registro de puntuaciones en un `std::vector<Player>`.
- Ordenamiento del leaderboard de mayor a menor puntaje con la clase `Sorts<T>`, usando **Merge Sort** y la sobrecarga del operador `>=`.
- Lógica del juego interactivo en consola dentro de `game.h`.

## Descripción del Avance 2
- Se incorporó una **Fila** de capacidad fija (`MAX_HISTORIAL = 5`) dentro de la clase `Historial` (`historial.h`), que guarda las últimas 5 partidas.
- La fila se implementó como un arreglo circular con los atributos `head`, `tail` y `counter`, y las operaciones `enqueue`, `dequeue`, `front`, `empty`, `full` y `clear`.
- Cuando la fila está llena, `add()` hace `dequeue()` de la partida más antigua y después `enqueue()` de la nueva.

## Descripción del Avance 3 (actual)
- **Búsquedas** (`busquedas.h`):
  - `bs_rec` / `bs_aux`: búsqueda binaria **recursiva** por puntaje sobre el leaderboard ordenado con Merge Sort.
  - `bs_seq`: búsqueda **secuencial** por nombre sobre la lista sin ordenar.
- **Lectura de archivo:** al iniciar, el programa carga los jugadores de `jugadores.txt` al `vector<Player>`.
- **Análisis de complejidad** comentado en todas las funciones.

---

## Cambios con respecto al avance anterior
1. Se agregó `busquedas.h` con `bs_seq`, `bs_aux` y `bs_rec`.
2. Se agregó la función `cargarArchivo` en `main.cpp`, que lee `jugadores.txt`.
3. El menú pasó de 4 a 6 opciones: se agregaron las búsquedas (4 y 5) y **Salir** pasó a ser la opción 6.
4. `Historial` dejó de usar sobrescritura directa y ahora usa operaciones explícitas de fila (`enqueue`, `dequeue`, `front`, etc.).

---

## Estructura y Archivos del Proyecto
- `main.cpp`: menú principal, flujo del programa, carga del archivo, registro de jugadores y consultas.
- `player.h`: clase `Player` (nombre y puntaje), getters y sobrecarga de `>=`.
- `scores.h`: clase plantilla `Sorts<T>` con **Merge Sort**.
- `game.h`: lógica del juego de navegación espacial y cálculo del puntaje.
- `historial.h`: clase `Historial`, que implementa la **Fila** circular de las últimas 5 partidas.
- `busquedas.h`: búsqueda binaria recursiva (`bs_rec`, `bs_aux`) y búsqueda secuencial (`bs_seq`).
- `jugadores.txt`: datos iniciales de jugadores.

### Formato de `jugadores.txt`
Una línea por jugador, con el formato `nombre puntaje` (el nombre sin espacios):

```
Ana 2350
Luis 1450
Maria 1000
Pedro 0
```

El archivo se abre con ruta relativa, por lo que debe estar en la carpeta **desde donde se ejecuta el programa**. Si no existe, el programa inicia con la lista vacía.

---

## ¿Cómo usar el programa?

Al ejecutar el programa se muestra el menú principal:

```
 MENU PRINCIPAL
1. Jugar
2. Ver Leaderboard
3. Ver Historial reciente
4. Buscar por puntaje (binaria)
5. Buscar por nombre (secuencial)
6. Salir
Selecciona una opcion:
```

### Opciones del menú
1. **Jugar:** pide el nombre e inicia la partida. El jugador controla una nave `[^]` en una cuadrícula de $8 \times 8$ y debe llegar a la base `(H)` con `w`, `a`, `s`, `d`, con 15 movimientos de combustible. Si llega, el puntaje es `movimientos restantes * 150 + 1000`; si no, es 0. El jugador se guarda en el vector y en el historial.
2. **Ver Leaderboard:** ordena con Merge Sort a todos los jugadores (incluidos los cargados del archivo) de mayor a menor puntaje y muestra la tabla.
3. **Ver Historial reciente:** muestra las últimas 5 partidas jugadas en esta ejecución, de la más antigua a la más reciente. Los jugadores cargados del archivo no aparecen aquí.
4. **Buscar por puntaje:** ordena la lista y aplica búsqueda binaria recursiva. Si varios jugadores tienen el mismo puntaje, los muestra todos.
5. **Buscar por nombre:** busca secuencialmente en la lista y muestra el primer jugador con ese nombre.
6. **Salir:** muestra un mensaje de despedida y termina el programa.

---

## Instrucciones para compilar y ejecutar

### Compilación
```bash
g++ -std=c++17 main.cpp -o avance3
```

### Ejecución
```bash
./avance3
```
(En Windows: `avance3.exe`). Asegúrate de que `jugadores.txt` esté en la carpeta desde la que ejecutas.

---

## Cumplimiento de las Sub-competencias

### SICT0301: Evalúa los componentes

#### Análisis de complejidad de las estructuras de datos

1. **Vector (`vector<Player> listaJugadores`):**
   - `push_back`: mejor y promedio $O(1)$; peor caso $O(n)$ cuando se redimensiona y copia los elementos (amortizado $O(1)$).
   - Acceso por índice: $O(1)$ en todos los casos.
   - Recorrido completo: $O(n)$.
   - Complejidad espacial: $O(n)$.

2. **Fila circular (`Player data[MAX_HISTORIAL]`, con `MAX_HISTORIAL = 5`):**

   | Operación | Mejor | Promedio | Peor |
   |:---|:---|:---|:---|
   | `enqueue`, `dequeue`, `front` | $O(1)$ | $O(1)$ | $O(1)$ |
   | `empty`, `full`, `clear` | $O(1)$ | $O(1)$ | $O(1)$ |
   | `add` (`dequeue` si está llena + `enqueue`) | $O(1)$ | $O(1)$ | $O(1)$ |
   | `print` | $O(1)$ | $O(1)$ | $O(1)$ (recorre máximo 5 elementos) |

   Complejidad espacial: $O(1)$, porque la memoria está acotada a 5 elementos `Player`.

3. **Lectura del archivo (`cargarArchivo`):** $O(n)$ en todos los casos, con $n$ el número de líneas, y un `push_back` amortizado $O(1)$ por línea.

#### Análisis de complejidad de los algoritmos

| Algoritmo | Mejor | Promedio | Peor |
|:---|:---|:---|:---|
| Merge Sort (`mergeSort`) | $O(n \log n)$ | $O(n \log n)$ | $O(n \log n)$ |
| Búsqueda binaria recursiva (`bs_rec` / `bs_aux`) | $O(1)$ | $O(\log n)$ | $O(\log n)$ |
| Búsqueda secuencial (`bs_seq`) | $O(1)$ | $O(n)$ | $O(n)$ |
| Recorrido de vecinos con el mismo puntaje | $O(1)$ | $O(1)$ | $O(n)$ (si todos tienen el mismo puntaje) |
| `Game::play` | $O(1)$ | $O(1)$ | $O(1)$ (máximo 15 movimientos) |

- **Merge Sort:** `mergeSplit` divide el vector recursivamente en mitades ($\log n$ niveles) y `mergeArray` combina las partes con un recorrido lineal $O(n)$.
- **Búsqueda binaria:** descarta la mitad de la lista en cada llamada recursiva. Funciona porque la lista está ordenada de mayor a menor.
- **Opción 4 completa:** como se ordena antes de buscar, cuesta $O(n \log n)$ (ordenar) + $O(\log n)$ (buscar) + $O(n)$ en el peor caso (vecinos con el mismo puntaje), es decir, $O(n \log n)$.
- **Complejidad final del programa:** las operaciones del historial son $O(1)$ y las búsquedas son menores o iguales a $O(n \log n)$, por lo que la operación dominante es el ordenamiento: **$O(n \log n)$**.

---

### SICT0302: Toma decisiones

1. **Vector para todos los jugadores:** crece dinámicamente, agregar al final es $O(1)$ amortizado y permite el acceso por índice que necesita la búsqueda binaria.

2. **Fila circular para el historial:** solo interesan las últimas $N$ partidas y la más antigua debe salir primero, que es el comportamiento FIFO de una fila. Con un arreglo circular, `enqueue` y `dequeue` son $O(1)$ y la memoria queda acotada. Un vector ilimitado consumiría memoria creciente, y eliminar el primer elemento costaría $O(n)$ por los desplazamientos.

3. **Merge Sort para el leaderboard:** garantiza $O(n \log n)$ en todos los casos, a diferencia de Bubble Sort o Selection Sort ($O(n^2)$). Además es estable: conserva el orden de registro entre jugadores con el mismo puntaje.

4. **Búsqueda binaria recursiva por puntaje:** la lista ya se ordena con Merge Sort, así que se puede descartar la mitad en cada paso: $O(\log n)$ en lugar de $O(n)$.

5. **Búsqueda secuencial por nombre:** la lista está ordenada por puntaje y no por nombre, por lo que no se puede usar búsqueda binaria. Hay que revisar elemento por elemento: $O(n)$.

---

### SICT0303: Implementa acciones científicas

1. **Mecanismos para consultar información de las estructuras:**
   - **Leaderboard:** `mergeSort()` genera una copia ordenada del vector y se despliega con un ciclo $O(n)$.
   - **Historial (`Historial::print`):** recorre la fila circular desde `head` avanzando con `(i + 1) % MAX_HISTORIAL`, preservando el orden FIFO.
   - **Búsqueda por puntaje:** `bs_rec` consulta la lista ordenada en $O(\log n)$.
   - **Búsqueda por nombre:** `bs_seq` consulta la lista sin ordenar en $O(n)$.

2. **Mecanismos de lectura de archivos para cargar datos a las estructuras:**
   - Al iniciar, `cargarArchivo` abre `jugadores.txt`, lee cada línea (`nombre puntaje`) y crea un `Player` por línea con `push_back` sobre `listaJugadores`.
   - Estos jugadores se usan en el leaderboard y en ambas búsquedas, igual que los jugadores registrados durante la partida.
   - Durante la ejecución, el nombre ingresado por consola y el puntaje de `game.play()` también se cargan al vector (`push_back`) y a la fila del historial (`historial.add`).

---

## Créditos y Reconocimientos
- **Lógica del Juego (`game.h`):** el código base de la lógica del juego de navegación espacial fue desarrollado con apoyo de Gemini para la simulación de cuadrícula en consola, bajo autorización del profesor para la exploración de la mecánica de juego.
