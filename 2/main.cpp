#include <iostream>
using namespace std;

/*
Estrategia:
Desde una posición inicial (x,y) el robot se expande en forma de pirámide.
En cada nivel:
- avanza en dirección vertical (arriba o abajo)
- desde ese punto genera dos ramas diagonales
Se controla el alcance para limitar la profundidad.
Se marcan los nodos visitados para no contar duplicados.
*/

void buscar(int mapa[][10], int n, int m,
            int x, int y,
            int dx,        // dirección vertical: -1 arriba, +1 abajo
            int alcance,
            int &contador) {

    // 🔴 caso base: sin alcance
    if (alcance < 0) return;

    // 🔴 fuera de matriz
    if (x < 0 || x >= n || y < 0 || y >= m) return;

    // 🟡 si hay artefacto
    if (mapa[x][y] == 1) {
        contador++;
        mapa[x][y] = 2; // marcar como visitado
    }

    // 🔵 marcar recorrido
    if (mapa[x][y] == 0) mapa[x][y] = 9;

    // 🔥 expansión en pirámide

    // diagonal izquierda
    buscar(mapa, n, m, x + dx, y - 1, dx, alcance - 1, contador);

    // diagonal derecha
    buscar(mapa, n, m, x + dx, y + 1, dx, alcance - 1, contador);

    // recto (vertical)
    buscar(mapa, n, m, x + dx, y, dx, alcance - 1, contador);
}

int main() {

    int mapa[10][10] = {0};

    // 🔹 artefactos (como tu ejemplo)
    mapa[3][3] = 1;
    mapa[3][4] = 1;
    mapa[4][5] = 1;
    mapa[5][4] = 1;
    mapa[5][7] = 1;
    mapa[7][5] = 1;

    int n = 10, m = 10;

    int x = 5, y = 5;
    int alcance = 3;

    int contador = 0;

    // 🔥 exploración hacia ARRIBA
    buscar(mapa, n, m, x, y, -1, alcance, contador);

    // 🔥 exploración hacia ABAJO
    buscar(mapa, n, m, x, y, 1, alcance, contador);

    cout << "Artefactos encontrados: " << contador << endl;

    // 🔹 imprimir mapa final
    cout << "\nMapa:\n";
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {

            if (mapa[i][j] == 1 || mapa[i][j] == 2)
                cout << "A ";   // artefacto
            else if (mapa[i][j] == 9)
                cout << "* ";   // recorrido
            else
                cout << ". ";   // vacío
        }
        cout << endl;
    }

    return 0;
}
/*
Artefactos encontrados: 4

Mapa:
. . . . . . . . . .
. . . . . . . . . .
. . * * * * * * * .
. . . A A * * * . .
. . . . * A * . . .
. . . . A * . A . .
. . . . * * * . . .
. . . * * A * * . .
. . * * * * * * * .
. . . . . . . . . .
 */