# Sistema de Puntuaciones y Juego de Navegación Espacial

**Autor:** Ernesto Beltran

---

## Descripción general

Este proyecto es un juego de consola en C++ donde controlas una nave en una cuadrícula de `8x8` y tienes que llegar a la base antes de quedarte sin combustible.

Los resultados de todas las partidas se van guardando en una estructura de datos dinámica, se ordenan para armar un leaderboard, se pueden consultar de distintas formas y se guardan en un archivo de texto (`jugs.txt`) para que no se pierdan al cerrar el programa.

Cada partida se representa con la clase `Player`, que guarda:
* **Nombre del jugador** (`string`)
* **Puntuación obtenida** (`int`)

---

## Avances

### Avance 1
* Guardado de las puntuaciones en un `vector<Player>`.
* Ordenamiento del leaderboard de mayor a menor puntaje usando la clase `Sorts<T>` con Merge Sort y la sobrecarga del operador `>=` de `Player`.
* Lógica del juego interactivo en consola (`game.h`).

### Avance 2
* Agregué un historial de las últimas 5 partidas (`historial.h`) usando una fila circular de capacidad fija (`enqueue`, `dequeue`, `front`, `empty`, `full`, `clear`).
* Agregué `busquedas.h` con búsqueda binaria recursiva por puntaje y búsqueda secuencial por nombre.
* Implementé la lectura de archivo (`cargarArchivo`) para cargar las partidas guardadas al iniciar el programa.
* El menú pasó de 4 a 6 opciones.

**Cambios respecto al Avance 1:**
1. **Historial con pila:** Para ver las últimas partidas jugadas. Usé una pila porque la más antigua debe ir saliendo primero.
2. **Búsquedas (`busquedas.h`):** Para consultar partidas por puntaje o por nombre, además del leaderboard.
3. **Lectura de archivo:** Para mantener las partidas de sesiones anteriores al volver a abrir el programa.
4. **Menú de 6 opciones:** Se agregaron el historial y las dos búsquedas.

### Avance 3 (Actual)
En este avance ya tengo la aplicación completa funcionando, ya carga datos, los organiza, y deja hacer consultas y guarda todo.

* **Cambio de estructura de datos:** Reemplacé el `vector<Player>` y la fila circular del historial por una sola lista doblemente ligada (`DList<Player>` en `dlist.h`), recorrida con un iterador (`DListIterator`). Esta única lista guarda todas las partidas en orden cronológico y de ahí salen el leaderboard, el historial y las búsquedas (ya no se usa `enqueue`).
* **Merge Sort sobre la lista:** Adapté `Sorts<T>` para ordenar `DList<T>` dividiendo la lista en dos mitades, ordenando cada una y mezclándolas con iteradores.
* **Escritura de archivo:** Después de cada partida, `guardarArchivo` escribe en `jugs.txt` todas las partidas actuales de la lista.
* **Consultas:** Leaderboard (Top 10), historial reciente, partidas de un jugador por nombre y búsqueda por puntaje.
* **Validación de entradas:** Si en el menú se escribe una letra o algo que no sea un número, el programa avisa y vuelve a preguntar sin ciclarse.
* **Análisis de complejidad:** Puse la complejidad de todos los componentes y la complejidad final del programa.

**Cambios respecto al Avance 2:**
1. **Lista doblemente ligada en lugar de vector y pila:** La pila era de tamaño fijo (5) y solo servía para el historial, además de que tener dos estructuras separadas duplicaba los datos. Con la lista doblemente ligada todo esta en un solo lugar, crece dinámicamente nodo por nodo sin tener que redimensionar ni copiar arreglos, y agrega al final en $O(1)$ gracias al puntero `tail`.
2. **Eliminación de `historial.h`:** Ahora el historial simplemente toma las últimas 5 partidas de la lista. Como la lista se carga desde el archivo, el historial también muestra partidas de ejecuciones anteriores (antes solo mostraba las de la sesión actual).
3. **Búsqueda por nombre completa:** Ahora muestra todas las partidas de un jugador y no solo la primera que encontraba, para que pueda ver todo su historial.
4. **Leaderboard limitado al Top 10:** Antes mostraba todas las partidas; ahora muestra únicamente las 10 mejores puntuaciones.
5. **Guardado automático (`guardarArchivo`):** Antes el programa solo leía `jugs.txt` y las partidas nuevas se perdían al cerrar.
6. **Corrección en la complejidad del historial:** Imprimir el historial cuesta $O(n)$ y no $O(1)$, porque hay que recorrer la lista para llegar a los últimos 5 nodos.
7. **Validación en el menú (`leerEntero`):** Evita que el programa entre en un ciclo infinito si el usuario escribe texto en lugar de un número.
8. **Reordenamiento del menú:** La opción 4 ahora es buscar por nombre y la 5 buscar por puntaje.

### Entrega final

**Cambios respecto al Avance 3:**

---

## Compilación y ejecución

### Compilar
Ejecuta el siguiente comando en la terminal dentro de la carpeta del proyecto:
```bash
g++ main.cpp -std=c++11 -o final
```

## ¿Cómo usar el programa?

Al ejecutar el programa aparece el menú principal en consola:

```text
 MENU PRINCIPAL 
1. Jugar
2. Ver Leaderboard
3. Ver Historial reciente
4. Buscar partidas por nombre
5. Buscar por puntaje
6. Salir
Selecciona una opcion: 
```

1. **Jugar:** Te pide tu nombre y empieza la partida. Juegas con la nave `[^]` en una cuadrícula de `8x8` y debes llegar a la base `(H)` usando las teclas `w`, `a`, `s`, `d` con un límite de 15 movimientos de combustible. Si llegas el puntaje es `movimientos_restantes * 150 + 1000`; si te quedas sin combustible, es `0`. Al terminar, la partida se agrega a la lista y se guarda en `jugs.txt`.
2. **Ver Leaderboard:** Ordena una copia de todas las partidas con Merge Sort y muestra el Top 10 de mayor a menor puntaje.
3. **Ver Historial reciente:** Muestra las últimas 5 partidas registradas, de la más vieja a la más reciente.
4. **Buscar partidas por nombre:** Muestra todas las partidas registradas bajo ese nombre.
5. **Buscar por puntaje:** Ordena la lista y muestra la posición y el nombre de cada jugador que tenga ese puntaje.
6. **Salir:** Termina el programa.

---

## Entradas y salidas

### Entradas
* **Archivo `jugs.txt`:** Se lee al iniciar. Tiene una línea por partida con el formato `nombre puntaje` (el nombre va sin espacios):
  ```text
  Raul 1750
  Julio 2200
  Cesar 1900
  Lalo 1450

  ```

### Salidas
* El mapa de `8x8` en cada turno, el combustible restante y el puntaje final de la partida.
* Listados del Top 10, del historial reciente y de los resultados de las búsquedas.
* Mensajes de aviso cuando no hay datos o no se encuentra lo buscado.
* El archivo `jugs.txt` actualizado con todas las partidas después de cada partida jugada.

---

## Estructura de archivos

* **`main.cpp`**: Menú principal, valida entradas y corre el programa.
* **`player.h`**: Clase `Player`, getters y sobrecarga de `>=`.
* **`dlist.h`**: Lista doblemente ligada (`DList`) y su iterador (`DListIterator`).
* **`scores.h`**: Clase `Sorts<T>` con Merge Sort para `DList`.
* **`busquedas.h`**: Búsqueda por nombre y por puntaje.
* **`archivo.h`**: Lectura (`cargarArchivo`) y escritura (`guardarArchivo`) de `jugs.txt`.
* **`game.h`**: El juego hecho por gemini.
* **`jugs.txt`**: Archivo donde se guardan las partidas.

---

## Desarrollo de competencias

### SICT0301: Evalúa los componentes

#### 1. Análisis de complejidad del algoritmo de ordenamiento
El único algoritmo de ordenamiento del proyecto es **Merge Sort** (`scores.h`), aplicado a la lista doblemente ligada:

| Función | ¿Qué hace? | Mejor caso | Caso promedio | Peor caso |
| :--- | :--- | :---: | :---: | :---: |
| `mergeList` | Mezcla dos listas ya ordenadas en una nueva, recorriéndolas con iteradores | $O(n)$ | $O(n)$ | $O(n)$ |
| `mergeSplit` | Divide la lista en dos mitades, ordena cada una recursivamente y las mezcla | $O(n \log n)$ | $O(n \log n)$ | $O(n \log n)$ |
| `mergeSort` | Llama a `mergeSplit` | $O(n \log n)$ | $O(n \log n)$ | $O(n \log n)$ |

* **Explicación:** En cada llamada, dividir la lista cuesta $O(n)$ y mezclar cuesta $O(n)$. Cada nivel de recursión divide el tamaño a la mitad, así que hay $\log n$ niveles: $T(n) = 2T(n/2) + O(n) = O(n \log n)$.
* **Consistencia:** El tiempo no depende del orden inicial de los datos (la lista siempre se divide y se mezcla completa), por eso los tres casos son iguales.
* **Espacio extra:** $O(n)$ por las listas auxiliares que se crean al dividir y mezclar, más $O(\log n)$ de pila de recursión.
* **Dónde se observa:** `scores.h`, con el análisis línea por línea en los comentarios.

#### 2. Análisis de complejidad de la estructura de datos
La única estructura de datos es la lista doblemente ligada `DList<Player>` con su iterador (`dlist.h`):

| Operación | Mejor caso | Caso promedio | Peor caso |
| :--- | :---: | :---: | :---: |
| `add`, `addFirst` (agregar) | $O(1)$ | $O(1)$ | $O(1)$ |
| `empty`, `length` | $O(1)$ | $O(1)$ | $O(1)$ |
| Iterador: `begin`, `operator()`, `operator++` | $O(1)$ | $O(1)$ | $O(1)$ |
| Constructor copia y `operator=` | $O(n)$ | $O(n)$ | $O(n)$ |
| `clear` y destructor `~DList` | $O(n)$ | $O(n)$ | $O(n)$ |

* `add` es $O(1)$ en todos los casos porque la lista guarda `tail` y no tiene que recorrerse para llegar al final. Complejidad espacial de la lista: $O(n)$.

**Usos de la estructura en el programa:**

| Uso | Operaciones de la lista | Complejidad |
| :--- | :--- | :---: |
| Cargar `jugs.txt` (`cargarArchivo`) | `add` por cada línea | $O(n)$ |
| Registrar una partida (Opción 1) | `add` | $O(1)$ |
| Ordenar para *leaderboard* y búsqueda por puntaje (Opciones 2 y 5) | Copias, `add` e iteradores dentro de Merge Sort | $O(n \log n)$ |
| Mostrar el Top 10 (Opción 2) | Iterador, máximo 10 elementos | $O(1)$ |
| Historial reciente (Opción 3) | Iterador: saltar $n - 5$ elementos y mostrar 5 | $O(n)$ |
| Buscar por nombre y por puntaje (Opciones 4 y 5) | Iterador recorriendo toda la lista | $O(n)$ |
| Guardar `jugs.txt` (`guardarArchivo`) | Iterador recorriendo toda la lista | $O(n)$ |
| Liberar la memoria al terminar | Destructor | $O(n)$ |

* **Dónde se observa:** `dlist.h` (con la complejidad de cada método en los comentarios) y en `main.cpp`, `busquedas.h` y `archivo.h`.

#### 3. Análisis de los demás componentes y complejidad final del programa

| Componente | Mejor caso | Caso promedio | Peor caso |
| :--- | :---: | :---: | :---: |
| `Player` (constructor, *getters*, `operator>=`) | $O(1)$ | $O(1)$ | $O(1)$ |
| `leerEntero` | $O(1)$ | $O(1)$ | $O(1)$ |
| `Game::play` (máximo 15 movimientos sobre un mapa fijo de `8x8`) | $O(1)$ | $O(1)$ | $O(1)$ |
| `buscarPorNombre` (recorre toda la lista) | $O(n)$ | $O(n)$ | $O(n)$ |
| `buscarPorPuntaje` (recorre toda la lista) | $O(n)$ | $O(n)$ | $O(n)$ |
| `cargarArchivo` | $O(n)$ | $O(n)$ | $O(n)$ |
| `guardarArchivo` | $O(n)$ | $O(n)$ | $O(n)$ |

**Complejidad de cada opción del menú:**
* **Al iniciar (cargar archivo):** $O(n)$
* **1. Jugar:** $O(n)$ (jugar y agregar son $O(1)$, guardar el archivo es $O(n)$)
* **2. Ver Leaderboard:** $O(n \log n)$ (ordenar) + $O(1)$ (Top 10) = $O(n \log n)$
* **3. Ver Historial reciente:** $O(n)$
* **4. Buscar partidas por nombre:** $O(n)$
* **5. Buscar por puntaje:** $O(n \log n)$ (ordenar) + $O(n)$ (buscar) = $O(n \log n)$

**Complejidad final del programa:**
* **Tiempo:** **$O(n \log n)$**, porque la operación más costosa es el ordenamiento con Merge Sort; todo lo demás es $O(n)$ o menor.
* **Espacio:** **$O(n)$**, por la lista de partidas, la copia ordenada y las listas auxiliares del Merge Sort.

---

### SICT0302: Toma decisiones

#### Algoritmo de ordenamiento
Usé **Merge Sort** para ordenar las partidas por puntaje de mayor a menor porque:
* Garantiza $O(n \log n)$ en todos los casos; algoritmos como Bubble Sort o Selection Sort son $O(n^2)$ y se volverían lentos con muchas partidas.
* Solo necesita recorrer las listas de principio a fin sin acceder a posiciones intermedias, lo que lo hace ideal para una lista ligada (otros algoritmos como Quick Sort dependen del acceso directo por índice).
* Es estable: en un empate (`>=`) se toma primero el elemento de la izquierda, así que las partidas con el mismo puntaje conservan su orden cronológico.
* Se aplica sobre una copia de la lista y no sobre la original, porque la original debe conservar el orden cronológico para el historial y para guardar el archivo.

*Dónde se observa:* `scores.h` y su uso en `main.cpp` (opciones 2 y 5).

#### Estructura de datos
Usé una **lista doblemente ligada (`DList`)** para guardar todas las partidas porque:
* Es dinámica: no se sabe cuántas partidas se jugarán, y la lista crece un nodo a la vez sin tamaño fijo ni copias por redimensionar como pasa en un `vector`.
* Agregar al final es $O(1)$ gracias a `tail`, que es la operación más frecuente (cada partida nueva).
* Una sola estructura sirve para todo: el *leaderboard*, el historial y las búsquedas salen de la misma lista, en lugar de mantener datos duplicados en un vector y en una fila circular de tamaño fijo.
* Todo el recorrido se hace con `DListIterator`, que avanza elemento por elemento en $O(1)$ sin exponer los nodos.
* *Limitación / mejora a futuro:* el puntero `previous` de cada nodo no se aprovecha en las consultas actuales ya que el iterador solo avanza hacia adelante, pero permitiría recorrer el historial desde el final hacia atrás en $O(1)$ o eliminar nodos en $O(1)$.

*Dónde se observa:* `dlist.h` y su uso en `main.cpp`, `scores.h`, `busquedas.h` y `archivo.h`.

---

### SICT0303: Implementa acciones científicas

* **Consultas sobre la estructura (`main.cpp` y `busquedas.h`):**
  * **Leaderboard (Opción 2):** `mergeSort` genera una copia ordenada de la lista y se recorre con un iterador para mostrar el Top 10.
  * **Historial reciente (Opción 3):** Se recorre la lista con un iterador saltando las partidas viejas y se muestran las últimas 5.
  * **Buscar por nombre (Opción 4):** `buscarPorNombre` recorre la lista y muestra todas las partidas del jugador.
  * **Buscar por puntaje (Opción 5):** `buscarPorPuntaje` recorre la lista ordenada y muestra la posición y el nombre de cada jugador con ese puntaje.
* **Lectura de archivos (`cargarArchivo` en `archivo.h`):** Abre `jugs.txt` al iniciar y lee cada línea (`nombre puntaje`) con `archivo >> nombre >> puntos`. Por cada línea crea un `Player` y lo agrega a la lista con `add`. Si el archivo no existe, la lista empieza vacía. Como se cargan en el mismo orden en que se guardaron, se conserva el orden cronológico.
* **Escritura de archivos (`guardarArchivo` en `archivo.h`):** Se llama después de cada partida. Recorre la lista con un iterador y escribe cada partida en una línea (`nombre puntaje`) de `jugs.txt`. Como se escribe el contenido completo de la lista, el archivo siempre es un reflejo exacto de la estructura en memoria.

---

## Créditos y reconocimientos

* **Lógica del juego (`game.h`):** El código base de la simulación de cuadrícula en consola fue desarrollado con apoyo de **Gemini**, bajo autorización del profesor para hacer la mecánica del juego.
