#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "videojuego.h"

typedef struct nodo {
    tVideojuego info;
    struct nodo *izq;
    struct nodo *der;
} tNodoArbol;

/* Prototipos */
void inicializarArbol(tNodoArbol **pArbol);
void agregarJuego(tNodoArbol **pArbol, tVideojuego pJuego);
bool buscarPorNombre(tNodoArbol *pArbol, char pNombre[]);
void pasarAVector(tNodoArbol *pArbol, tVideojuego pVec[], int *pCant);
void mostrarPorAnio(tNodoArbol *pArbol);
void mostrarPorGenero(tNodoArbol *pArbol);
void guardarRec(tNodoArbol *pArbol, FILE *pArchivo);
void guardarColeccion(tNodoArbol *pArbol, char pNombreArchivo[]);
void cargarColeccion(tNodoArbol **pArbol, char pNombreArchivo[]);

/* Implementaciones */
void inicializarArbol(tNodoArbol **pArbol) {
    *pArbol = NULL;
}

void agregarJuego(tNodoArbol **pArbol, tVideojuego pJuego) {
    if (*pArbol == NULL) {
        *pArbol = (tNodoArbol *)malloc(sizeof(tNodoArbol));
        (*pArbol)->info = pJuego;
        (*pArbol)->izq = NULL;
        (*pArbol)->der = NULL;
    } else {
        if (pJuego.id < (*pArbol)->info.id) {
            agregarJuego(&(*pArbol)->izq, pJuego);
        } else if (pJuego.id > (*pArbol)->info.id) {
            agregarJuego(&(*pArbol)->der, pJuego);
        } else {
            printf("Ya existe un juego con ese ID.\n");
        }
    }
}

bool buscarPorNombre(tNodoArbol *pArbol, char pNombre[]) {
    if (pArbol == NULL) {
        return false;
    }
    if (strcmp(pNombre, pArbol->info.nombre) == 0) {
        mostrarJuego(pArbol->info);
        return true;
    } else {
        return buscarPorNombre(pArbol->izq, pNombre) || buscarPorNombre(pArbol->der, pNombre);
    }
}

void pasarAVector(tNodoArbol *pArbol, tVideojuego pVec[], int *pCant) {
    if (pArbol != NULL) {
        pasarAVector(pArbol->izq, pVec, pCant);
        pVec[*pCant] = pArbol->info;
        (*pCant)++;
        pasarAVector(pArbol->der, pVec, pCant);
    }
}

void mostrarPorAnio(tNodoArbol *pArbol) {
    tVideojuego vec[100];
    int cant = 0;
    int i, j;
    tVideojuego aux;

    pasarAVector(pArbol, vec, &cant);

    for (i = 0; i < cant - 1; i++) {
        for (j = 0; j < cant - 1 - i; j++) {
            if (vec[j].anio > vec[j + 1].anio) {
                aux = vec[j];
                vec[j] = vec[j + 1];
                vec[j + 1] = aux;
            }
        }
    }

    for (i = 0; i < cant; i++) {
        mostrarJuego(vec[i]);
    }
}

void mostrarPorGenero(tNodoArbol *pArbol) {
    tVideojuego vec[100];
    int cant = 0;
    int i, j;
    tVideojuego aux;

    pasarAVector(pArbol, vec, &cant);

    for (i = 0; i < cant - 1; i++) {
        for (j = 0; j < cant - 1 - i; j++) {
            if (strcmp(vec[j].genero, vec[j + 1].genero) > 0) {
                aux = vec[j];
                vec[j] = vec[j + 1];
                vec[j + 1] = aux;
            }
        }
    }

    for (i = 0; i < cant; i++) {
        mostrarJuego(vec[i]);
    }
}

void guardarRec(tNodoArbol *pArbol, FILE *pArchivo) {
    if (pArbol != NULL) {
        fwrite(&(pArbol->info), sizeof(tVideojuego), 1, pArchivo);
        guardarRec(pArbol->izq, pArchivo);
        guardarRec(pArbol->der, pArchivo);
    }
}

void guardarColeccion(tNodoArbol *pArbol, char pNombreArchivo[]) {
    FILE *archivo = fopen(pNombreArchivo, "wb");
    if (archivo != NULL) {
        guardarRec(pArbol, archivo);
        fclose(archivo);
        printf("Coleccion guardada.\n");
    } else {
        printf("Error al guardar el archivo.\n");
    }
}

void cargarColeccion(tNodoArbol **pArbol, char pNombreArchivo[]) {
    FILE *archivo = fopen(pNombreArchivo, "rb");
    tVideojuego aux;
    if (archivo != NULL) {
        while (fread(&aux, sizeof(tVideojuego), 1, archivo) == 1) {
            agregarJuego(pArbol, aux);
        }
        fclose(archivo);
        printf("Coleccion cargada.\n");
    } else {
        printf("No se encontro el archivo.\n");
    }
}
