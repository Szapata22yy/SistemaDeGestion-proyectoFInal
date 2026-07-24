#include "destinos.h"
#include <stdio.h>

void menu(FilaDestinos *fila);

int main()
{
    FilaDestinos destinos;
    inicializarFilaDestinos(&destinos);
    menu(&destinos);
    return 0;
}

void menu(FilaDestinos *fila)
{
    int opcion;

    do
    {
        printf("\n=========================================\n");
        printf("   SISTEMA PORTUARIO TURISTICO\n");
        printf("          BUENAVENTURA\n");
        printf("=========================================\n");
        printf("1. Registrar nuevo destino\n");
        printf("2. Mostrar destinos registrados\n");
        printf("3. Buscar destino\n");
        printf("4. Modificar destino\n");
        printf("5. Salir\n");
        printf("=========================================\n");
        printf("Seleccione una opcion: ");
        if (scanf("%d", &opcion) != 1)
        {
            printf("Entrada invalida.\n");
            scanf("%*s");
            opcion = 0;
            continue;
        }

        switch(opcion)
        {
            case 1:
                registrarDestino(fila);
                break;

            case 2:
                mostrarDestinos(fila);
                break;

            case 3:
                {
                    int codigo;
                    printf("Ingrese el codigo del destino a buscar: ");
                    if (scanf("%d", &codigo) != 1)
                    {
                        printf("Entrada invalida.\n");
                        scanf("%*s");
                        break;
                    }

                    Destino *destino = buscarDestino(fila, codigo);
                    if (destino != NULL)
                    {
                        printf("\nDestino encontrado:\n");
                        printf("Codigo: %d\n", destino->codigo);
                        printf("Nombre: %s\n", destino->nombre);
                        printf("Empresa: %s\n", destino->empresa);
                    }
                    else
                    {
                        printf("\nDestino no encontrado.\n");
                    }
                }
                break;

            case 4:
                modificarDestino(fila);
                break;

            case 5:
                liberarFilaDestinos(fila);
                printf("\nGracias por usar el sistema.\n");
                break;

            default:
                printf("\nOpcion invalida. Intente nuevamente.\n");
        }

    } while(opcion != 5);
}