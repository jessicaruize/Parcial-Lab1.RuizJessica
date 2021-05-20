/*
 ============================================================================
 Name        : Parcial_Lab1-RuizJessica.c
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdio_ext.h>
#include <stdlib.h>
#include "TrabajoServicio.h"
#include "eTrabajo.h"
#include "eServicio.h"

#define TAM_TRABAJO 15
#define TAM_SERVICIO 10
#define TAM_ESTRUCTURA3 8

int main(void)
{
	setbuf(stdout, NULL);
	int opcion;
	int bufferRespuestas;
	float totalPesos;
	eTrabajo Trabajo[TAM_TRABAJO];
	eTrabajo_inicializar(Trabajo, TAM_TRABAJO);
	eTrabajo_cargaAutomaticaTrabajo(Trabajo, 5);
	eServicio Servicio[TAM_SERVICIO];
	eServicio_inicializar(Servicio, TAM_SERVICIO);
	eServicio_cargaAutomaticaServicio(Servicio, 4);

	do {
		if(!eConjuntos_menu(&opcion))
		{
			printf("\nOpción elegida: %d\n\n", opcion);
			switch (opcion)
			{
				case 0:
					bufferRespuestas = utn_verificar("¿Desea salir [s/n]?", "Error.\n", 2);
					if(bufferRespuestas == 0)
					{
						opcion = 50; //si
					}
					break;
				case 1:
					//ALTA
					bufferRespuestas = eConjuntos_alta(Trabajo, TAM_TRABAJO, Servicio, TAM_SERVICIO);
					switch (bufferRespuestas)
					{
						case -3:
							puts("Datos mal ingresados.\n");
						break;
						case -2:
							puts("No hay espacio para guardar otro Trabajo.\n");
						break;
						case -1:
							puts("Error.\n");
						break;
						case 0:
							puts("Alta exitosa.\n");
						break;
						case 1:
							puts("Operacion cancelada con exito.\n");
						break;
					}
				break;
				case 2: //BAJA
					bufferRespuestas = eConjuntos_baja(Trabajo, TAM_TRABAJO, Servicio, TAM_SERVICIO);
					switch (bufferRespuestas)
					{
						case -3:
							puts("\nNo hay trabajos para dar de baja.\n");
						break;
						case -2:
							puts("\nError.\n");
						break;
						case -1:
							bufferRespuestas = utn_verificar("ID no existe.\n¿Desea volver al menu?\n [s/n]", "Error.\n", 2);
							if(bufferRespuestas == 1)
							{
								opcion = 50; //no.
							}
						break;
						case 0:
							puts("\nBaja exitosa.\n");
						break;
						case 1:
							puts("\nTrabajo ya dado de baja.\n");
						break;
						case 2:
							printf("\nBaja cancelada \n\n.");
						break;
					}

				break;
				case 3: //MODIFICACION
					opcion = eConjuntos_modificacion(Trabajo, TAM_TRABAJO, Servicio, TAM_SERVICIO);
					switch(opcion)
					{
						case -4:
							puts("\nNo hay trabajo para modificar.");
						break;
						case -3:
							printf("\nID no existe.n");
						break;
						case -2:
							printf("\nError.\n");
						break;
						case -1:
							printf("\nModificación cancelada.\n");
						break;
						case 0:
							printf("\nModificación exitosa.\n");
						break;
						case 1:
							printf("\nTrabajo dado de baja, no se puede modificar.\n");
						break;
					}
				break;
				case 4: //trabajos ordenados por año.
					if(!eTrabajo_SortAnio(Trabajo, TAM_TRABAJO))
					{
						eConjuntos_mostrarTodos(Trabajo, TAM_TRABAJO, Servicio, TAM_SERVICIO);
					}else
					{
						puts("No hay trabajos para mostrar.");
					}
				break;
				case 5://Lista de Servicios.
					if(eServicio_mostrarTodos(Servicio, TAM_SERVICIO))
					{
						puts("No hay servicios para mostrar.");
					}
				break;
				case 6://_Total en pesos de los servicios prestados.
					if(!econjuntos_mostrarTotalPesos(Trabajo, TAM_TRABAJO, Servicio, TAM_SERVICIO, &totalPesos))
					{
						printf("Total de pesos recaudados con los servicios prestados es: %.2f\n", totalPesos);
					}
					else
					{
						puts("No hay trabajos.");
					}
				break;
			}
		}
	}while(opcion != 50);
	printf("Gracias.");
	return EXIT_SUCCESS;
}
