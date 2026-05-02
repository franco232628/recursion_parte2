#include <iostream>
#include <iomanip>
using namespace std;

/*
Estrategia:
Se recorren anillos concéntricos desde el punto inicial.
Cada anillo válido se marca con su nivel (radio).
Si un anillo no se puede completar, se detiene la recursión.
Se cuenta la cantidad de unidades (1) encontradas.
*/

int procesarAnillo(int mapa[][10], int marca[][10],
                   int n, int m,
                   int x, int y, int r) {

    int contador = 0;

    // 🔴 validar límites (anillo completo)
    if (x - r < 0 || x + r >= n || y - r < 0 || y + r >= m)
        return -1;

    // 🔵 recorrer borde y marcar nivel

    // fila superior
    for (int j = y - r; j <= y + r; j++) {
        marca[x - r][j] = r;
        if (mapa[x - r][j] == 1) contador++;
    }

    // fila inferior
    for (int j = y - r; j <= y + r; j++) {
        marca[x + r][j] = r;
        if (mapa[x + r][j] == 1) contador++;
    }

    // columna izquierda
    for (int i = x - r + 1; i <= x + r - 1; i++) {
        marca[i][y - r] = r;
        if (mapa[i][y - r] == 1) contador++;
    }

    // columna derecha
    for (int i = x - r + 1; i <= x + r - 1; i++) {
        marca[i][y + r] = r;
        if (mapa[i][y + r] == 1) contador++;
    }

    return contador;
}

int radarRec(int mapa[][10], int marca[][10],
             int n, int m,
             int x, int y, int r) {

    int cant = procesarAnillo(mapa, marca, n, m, x, y, r);

    // 🔴 si ya no hay anillo completo → parar
    if (cant == -1) return 0;

    return cant + radarRec(mapa, marca, n, m, x, y, r + 1);
}

int main() {

    int mapa[10][10] = {
        {0,0,0,1,0,1},
        {0,0,1,0,0,0},
        {0,1,0,0,0,1},
        {1,0,0,0,0,0},
        {0,1,0,0,0,0},
        {0,0,0,0,1,0}
    };

    int marca[10][10] = {0};

    int n = 6, m = 6;
    int x = 3, y = 2;

    int total = radarRec(mapa, marca, n, m, x, y, 0);

    cout << "Unidades encontradas: " << total << endl;

    // 🔥 imprimir niveles (recorrido del radar)
    cout << "\nMapa de niveles:\n";
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cout << setw(2) << marca[i][j] << " ";
        }
        cout << endl;
    }

    // 🔥 imprimir mapa original para comparar
    cout << "\nMapa original:\n";
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cout << setw(2) << mapa[i][j] << " ";
        }
        cout << endl;
    }
    // 🔥 imprimir niveles con bombas
    cout << "\nMapa de recorrido:\n";
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {

            if (mapa[i][j] == 1)
                cout << " * ";   // 💣 bomba
            else
                cout << setw(2) << marca[i][j] << " ";

        }
        cout << endl;
    }
    return 0;
}
/*
Unidades encontradas: 5

Mapa de niveles:
 0  0  0  0  0  0
 2  2  2  2  2  0
 2  1  1  1  2  0
 2  1  0  1  2  0
 2  1  1  1  2  0
 2  2  2  2  2  0

Mapa original:
 0  0  0  1  0  1
 0  0  1  0  0  0
 0  1  0  0  0  1
 1  0  0  0  0  0
 0  1  0  0  0  0
 0  0  0  0  1  0

Mapa de recorrido:
 0  0  0  *  0  *
 2  2  *  2  2  0
 2  *  1  1  2  *
 *  1  0  1  2  0
 2  *  1  1  2  0
 2  2  2  2  *  0

Process finished with exit code 0


*/