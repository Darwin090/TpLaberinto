#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define TAM 15  // Tamaño de la matriz del laberinto

// Definir las direcciones de movimiento: arriba, abajo, izquierda, derecha
int movimientos[4][2] = {{-2, 0}, {2, 0}, {0, -2}, {0, 2}};

// Funcion para inicializar la matriz del laberinto con muros
void inicializar_matriz(char laberinto[TAM][TAM]) {
    for (int i = 0; i < TAM; i++) {
        for (int j = 0; j < TAM; j++) {
            laberinto[i][j] = '#';  // Pared
        }
    }
}

// Verifica si una celda esta dentro de los limites del laberinto
int es_valido(int x, int y) {
    return x >= 0 && x < TAM && y >= 0 && y < TAM;
}

// Función para barajar las direcciones de movimiento
void barajar_direcciones(int mov[4][2]) {
    for (int i = 0; i < 4; i++) {
        int j = rand() % 4;
        int temp[2] = {mov[i][0], mov[i][1]};
        mov[i][0] = mov[j][0];
        mov[i][1] = mov[j][1];
        mov[j][0] = temp[0];
        mov[j][1] = temp[1];
    }
}

// Función recursiva para generar el laberinto
void generar_laberinto(char laberinto[TAM][TAM], int x, int y) {
    laberinto[x][y] = ' ';  // Marca la celda actual como un camino

    // Barajar las direcciones para que el laberinto sea aleatorio
    barajar_direcciones(movimientos);

    for (int i = 0; i < 4; i++) {
        int nx = x + movimientos[i][0];
        int ny = y + movimientos[i][1];
        int nx_medio = x + movimientos[i][0] / 2;
        int ny_medio = y + movimientos[i][1] / 2;

        if (es_valido(nx, ny) && laberinto[nx][ny] == '#') {
            // Hacer un camino en la celda intermedia
            laberinto[nx_medio][ny_medio] = ' ';
            // Recursivamente generar el laberinto desde la nueva celda
            generar_laberinto(laberinto, nx, ny);
        }
    }
}

// Funcion para imprimir el laberinto en la consola
void imprimir_laberinto(char laberinto[TAM][TAM]) {
    for (int i = 0; i < TAM; i++) {
        for (int j = 0; j < TAM; j++) {
            printf("%c", laberinto[i][j]);
        }
        printf("\n");
    }
}

int main() {
    // Inicializar la matriz del laberinto
    char laberinto[TAM][TAM];
    inicializar_matriz(laberinto);

    // Inicializar la semilla para los números aleatorios
    srand(time(NULL));

    // Generar el laberinto comenzando desde la celda (1, 1)
    generar_laberinto(laberinto, 1, 1);

    // Establecer punto de inicio y punto de salida
    laberinto[1][0] = 'S';  // Punto de inicio
    laberinto[TAM-2][TAM-1] = 'E';  // Punto de salida

    // Imprimir el laberinto
    imprimir_laberinto(laberinto);

    return 0;
}
