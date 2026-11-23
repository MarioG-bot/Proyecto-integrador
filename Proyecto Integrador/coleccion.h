#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "videojuego.h"

//Tipos de datos definidos por el usuario
typedef struct nodo {
    tVideojuego info;
    struct nodo *izq;
    struct nodo *der;
} tNodoArbol;

//Lista auxiliar
typedef struct nodoLista {
    tVideojuego info;
    struct nodoLista *siguiente;
} tNodoLista;

//Prototipado
//Operaciones de arbol binario
void inicializarArbol(tNodoArbol **pArbol);
bool arbolVacio(tNodoArbol *pArbol);
void agregarJuego(tNodoArbol **pArbol, tVideojuego pJuego);
bool buscarPorNombre(tNodoArbol *pArbol, tString pNombre);

//Operaciones de lista enlazada
void insertarAdelante(tNodoLista **pLista, tVideojuego pJuego);
void pasarALista(tNodoArbol *pArbol, tNodoLista **pLista);
void ordenarListaGenero(tNodoLista *pLista);
void ordenarListaAnio(tNodoLista *pLista);
void mostrarLista(tNodoLista *pLista);
void liberarLista(tNodoLista **pLista);

//Listados ordenados
void mostrarPorGenero(tNodoArbol *pArbol);
void mostrarPorAnio(tNodoArbol *pArbol);

//Operaciones de archivos binarios
void guardarArbolEnArchivo(tNodoArbol *pArbol, FILE *pArchivo);
void guardarColeccion(tNodoArbol *pArbol, tString pNombreArchivo);
bool cargarColeccion(tNodoArbol **pArbol, tString pNombreArchivo);

//Implementacion
void inicializarArbol(tNodoArbol **pArbol) {
    *pArbol = NULL;
}

bool arbolVacio(tNodoArbol *pArbol) {
    return (pArbol == NULL);
}

void agregarJuego(tNodoArbol **pArbol, tVideojuego pJuego) {
    if (arbolVacio(*pArbol)) {
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

//Recorre ambos subarboles de forma recursiva
bool buscarPorNombre(tNodoArbol *pArbol, tString pNombre) {
    if (arbolVacio(pArbol)) {
        return false;
    }
    if (strcmp(pNombre, pArbol->info.nombre) == 0) {
        mostrarJuego(pArbol->info);
        return true;
    } else {
        return buscarPorNombre(pArbol->izq, pNombre) || buscarPorNombre(pArbol->der, pNombre);
    }
}

void insertarAdelante(tNodoLista **pLista, tVideojuego pJuego) {
    tNodoLista *nuevoNodo = (tNodoLista *)malloc(sizeof(tNodoLista));

    nuevoNodo->info = pJuego;
    nuevoNodo->siguiente = *pLista;

    *pLista = nuevoNodo;
}

//Almacena los datos del arbol en una lista temporal
void pasarALista(tNodoArbol *pArbol, tNodoLista **pLista) {
    if (!arbolVacio(pArbol)) {
        pasarALista(pArbol->izq, pLista);
        insertarAdelante(pLista, pArbol->info);
        pasarALista(pArbol->der, pLista);
    }
}

//Ordenamiento burbuja por genero
void ordenarListaGenero(tNodoLista *pLista) {
    tNodoLista *actual = pLista;
    tNodoLista *siguiente;
    tVideojuego aux;

    while (actual != NULL) {
        siguiente = actual->siguiente;
        while (siguiente != NULL) {
            if (strcmp(actual->info.genero, siguiente->info.genero) > 0) {
                aux = actual->info;
                actual->info = siguiente->info;
                siguiente->info = aux;
            }
            siguiente = siguiente->siguiente;
        }
        actual = actual->siguiente;
    }
}

//Ordenamiento burbuja por anio
void ordenarListaAnio(tNodoLista *pLista) {
    tNodoLista *actual = pLista;
    tNodoLista *siguiente;
    tVideojuego aux;

    while (actual != NULL) {
        siguiente = actual->siguiente;
        while (siguiente != NULL) {
            if (actual->info.anio > siguiente->info.anio) {
                aux = actual->info;
                actual->info = siguiente->info;
                siguiente->info = aux;
            }
            siguiente = siguiente->siguiente;
        }
        actual = actual->siguiente;
    }
}

void mostrarLista(tNodoLista *pLista) {
    tNodoLista *aux = pLista;

    while (aux != NULL) {
        mostrarJuego(aux->info);
        aux = aux->siguiente;
    }
}

void liberarLista(tNodoLista **pLista) {
    tNodoLista *aux;

    while (*pLista != NULL) {
        aux = *pLista;
        *pLista = (*pLista)->siguiente;
        free(aux);
        aux = NULL;
    }
}

void mostrarPorGenero(tNodoArbol *pArbol) {
    tNodoLista *lista = NULL;

    if (arbolVacio(pArbol)) {
        printf("No hay videojuegos cargados.\n");
    } else {
        pasarALista(pArbol, &lista);
        ordenarListaGenero(lista);
        printf("\n=== LISTADO ORDENADO POR GENERO ===\n");
		printf("-----------------------------------------------------------------------------------\n");
        mostrarLista(lista);
        liberarLista(&lista);
    }
}

void mostrarPorAnio(tNodoArbol *pArbol) {
    tNodoLista *lista = NULL;

    if (arbolVacio(pArbol)) {
        printf("No hay videojuegos cargados.\n");
    } else {
        pasarALista(pArbol, &lista);
        ordenarListaAnio(lista);
        printf("\n=== LISTADO ORDENADO POR ANIO ===\n");
        printf("-----------------------------------------------------------------------------------\n");
        mostrarLista(lista);
        liberarLista(&lista);
    }
}

//Recorre el arbol en preorden y guarda los datos en el archivo binario
void guardarArbolEnArchivo(tNodoArbol *pArbol, FILE *pArchivo) {
    if (!arbolVacio(pArbol)) {
        fwrite(&(pArbol->info), sizeof(tVideojuego), 1, pArchivo);
        guardarArbolEnArchivo(pArbol->izq, pArchivo);
        guardarArbolEnArchivo(pArbol->der, pArchivo);
    }
}

void guardarColeccion(tNodoArbol *pArbol, tString pNombreArchivo) {
    FILE *archivo = fopen(pNombreArchivo, "wb");
    if (archivo != NULL) {
        guardarArbolEnArchivo(pArbol, archivo);
        fclose(archivo);
        printf("Coleccion guardada.\n");
    } else {
        printf("Error al guardar el archivo.\n");
    }
}

//Lee los registros del archivo binario y los inserta en el arbol retornando true si cargo datos
bool cargarColeccion(tNodoArbol **pArbol, tString pNombreArchivo) {
    FILE *archivo = fopen(pNombreArchivo, "rb");
    tVideojuego aux;
    bool cargado = false;

    if (archivo != NULL) {
        while (fread(&aux, sizeof(tVideojuego), 1, archivo) == 1) {
            agregarJuego(pArbol, aux);
            cargado = true;
        }
        fclose(archivo);
    }

    return cargado;
}
