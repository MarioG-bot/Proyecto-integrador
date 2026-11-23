#include <stdio.h>
#include "coleccion.h"

int main() {
    tNodoArbol *arbol;
    tVideojuego juego;
    char nombre[MAX_CADENA];
    int opcion;

    inicializarArbol(&arbol);

    do {
        printf("\n1. Agregar juego\n");
        printf("2. Buscar por nombre\n");
        printf("3. Mostrar ordenados por genero\n");
        printf("4. Mostrar ordenados por anio\n");
        printf("5. Guardar coleccion\n");
        printf("6. Cargar coleccion\n");
        printf("0. Salir\n");
        printf("Opcion: ");
        scanf("%d", &opcion);

        switch (opcion) {
            case 1:
                cargarJuego(&juego);
                agregarJuego(&arbol, juego);
                break;
            case 2:
                printf("Nombre a buscar: ");
                scanf(" %[^\n]", nombre);
                if (!buscarPorNombre(arbol, nombre)) {
                    printf("No se encontro el juego.\n");
                }
                break;
            case 3:
                mostrarPorGenero(arbol);
                break;
            case 4:
                mostrarPorAnio(arbol);
                break;
            case 5:
                guardarColeccion(arbol, "Juegos.dat");
                break;
            case 6:
                cargarColeccion(&arbol, "Juegos.dat");
                break;
        }
    } while (opcion != 0);

    return 0;
}
