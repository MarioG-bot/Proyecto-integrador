#include <stdio.h>
#include <string.h>

#define MAX 50

//Tipos de datos definidos por el usuario
typedef char tString[MAX];

typedef struct {
    int id;
    tString nombre;
    tString genero;
    int anio;
} tVideojuego;

//Prototipado
void cargarJuego(tVideojuego *pJuego);
void seleccionarGenero(tString pGenero);
void mostrarJuego(tVideojuego pJuego);

//Implementaciones
void cargarJuego(tVideojuego *pJuego) {
	printf("\nINGRESAR LOS DATOS DEL VIDEOJUEGO\n");
    printf("ID: ");
    scanf("%d", &pJuego->id);

    printf("Nombre: ");
    scanf(" %[^\n]", pJuego->nombre);

    seleccionarGenero(pJuego->genero);

    printf("Anio: ");
    scanf("%d", &pJuego->anio);
}

//Generos predeterminados para estandarizar el texto y evitar errores de tipeo
void seleccionarGenero(tString pGenero) {
    int opcion;

    do {
        printf("Seleccione el genero:\n");
        printf("+[1]. Accion\n");
        printf("+[2]. Aventura\n");
        printf("+[3]. Carreras\n");
        printf("+[4]. Deportes\n");
        printf("+[5]. Disparos\n");
        printf("+[6]. Estrategia\n");
        printf("+[7]. RPG\n");
        printf("Opcion: ");
        scanf("%d", &opcion);

        switch (opcion) {
            case 1:
                strcpy(pGenero, "Accion");
                break;
            case 2:
                strcpy(pGenero, "Aventura");
                break;
            case 3:
                strcpy(pGenero, "Carreras");
                break;
            case 4:
                strcpy(pGenero, "Deportes");
                break;
            case 5:
                strcpy(pGenero, "Disparos");
                break;
            case 6:
                strcpy(pGenero, "Estrategia");
                break;
            case 7:
                strcpy(pGenero, "RPG");
                break;
            default:
                printf("\nOpcion invalida. Intente nuevamente.\n");
                break;
        }
    } while (opcion < 1 || opcion > 7);
}

void mostrarJuego(tVideojuego pJuego) {
    printf("ID: %-4d | Nombre: %-28s | Genero: %-12s | Anio: %d\n", pJuego.id, pJuego.nombre, pJuego.genero, pJuego.anio);
}
