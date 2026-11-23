#include <stdio.h>
#include "coleccion.h"

int main() {
    tNodoArbol *arbol;
    tVideojuego juego;
    tString nombreBuscado;
    int opcion;

    inicializarArbol(&arbol);
    //Carga automatica de la coleccion si el archivo existe
    cargarColeccion(&arbol, "Juegos.dat");

	//Bucle del menu principal
    do {
        printf("\n1. Agregar juego\n");
        printf("2. Buscar por nombre\n");
        printf("3. Mostrar ordenados por genero\n");
        printf("4. Mostrar ordenados por anio\n");
        printf("5. Guardar coleccion\n");
        printf("6. Cargar coleccion\n");
        printf("0. Salir\n");
        printf("\nOpcion: ");
        scanf("%d", &opcion);

        switch (opcion) {
            case 1:
                cargarJuego(&juego);
                agregarJuego(&arbol, juego);
                break;
            case 2:
                printf("\nNombre a buscar: ");
                scanf(" %[^\n]", nombreBuscado);
                if (!buscarPorNombre(arbol, nombreBuscado)) {
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
                if (cargarColeccion(&arbol, "Juegos.dat")) {
    				printf("Coleccion cargada.\n");
				} else {
    				printf("No se encontro el archivo o esta vacio.\n");
				}	
                break;
            case 0:
                printf("Saliendo del programa...\n");
                break;
            default:
                printf("Opcion invalida intente nuevamente.\n");
                break;
        }
    } while (opcion != 0);

    return 0;
}
