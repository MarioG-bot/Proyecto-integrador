#include <stdio.h>

#define MAX_CADENA 50

typedef struct {
    int id;
    char nombre[MAX_CADENA];
    char genero[MAX_CADENA];
    int anio;
} tVideojuego;

/* Prototipos */
void cargarJuego(tVideojuego *pJuego);
void mostrarJuego(tVideojuego pJuego);

/* Implementaciones */
void cargarJuego(tVideojuego *pJuego) {
    printf("ID: ");
    scanf("%d", &pJuego->id);
    
    printf("Nombre: ");
    scanf(" %[^\n]", pJuego->nombre);
    
    printf("Genero: ");
    scanf(" %[^\n]", pJuego->genero);
    
    printf("Anio: ");
    scanf("%d", &pJuego->anio);
}

void mostrarJuego(tVideojuego pJuego) {
    printf("[ID: %d] %s | Genero: %s | Anio: %d\n", pJuego.id, pJuego.nombre, pJuego.genero, pJuego.anio);
}
