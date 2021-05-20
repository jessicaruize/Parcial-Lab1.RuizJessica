/*
 * TrabajoServicio.h
 *
 *  Created on: 17 may. 2021
 *      Author: jessica
 */

#ifndef TRABAJOSERVICIO_H_
#define TRABAJOSERVICIO_H_



#include <stdio.h>
#include <stdio_ext.h>
#include <stdlib.h>

#include "pedir_valores.h"

#include "eTrabajo.h"
#include "eServicio.h"

//*** DEFINE

#define MAX_CHARS_CADENAS 30
#define LIBRE 0
#define OCUPADO 1
#define BAJA -1

typedef struct
{
	int contador;
	int acumulador;
}eAuxiliar;

int eConjuntos_cargarDatos(eTrabajo* pTrabajo, eServicio aServicio[], int tamServicio);
int eConjuntos_alta(eTrabajo aTrabajo[], int tamTrabajo, eServicio aServicio[], int tamServicio);
int eConjuntos_mostrarUno(eTrabajo* pTrabajo, eServicio aServicio[], int tamServicio);
int eConjuntos_mostrarTodos(eTrabajo aTrabajo[], int tamTrabajo1, eServicio aServicio[], int tamServicio);
int eConjuntos_baja(eTrabajo aTrabajo[], int tamTrabajo1, eServicio aServicio[], int tamServicio);
int eConjuntos_modificarUno(eTrabajo* pTrabajo, eServicio aServicio[], int tamServicio);
int eConjuntos_modificacion(eTrabajo aTrabajo[], int tamTrabajo, eServicio aServicio[], int tamServicio);
int eConjuntos_Sort(eTrabajo aTrabajo[], int tamTrabajo, int criterio);

int econjuntos_mostrarTotalPesos(eTrabajo aTrabajo[], int tamTrabajo, eServicio aServicios[], int tamServicios, float* totalPesos);
int eConjuntos_menu(int* opcion);

/** INICIO CABECERAS DE FUNCION*/


/** SORT */
//CRITERIO -> -1 = MENOR A MAYOR
//CRITERIO ->  1 = MAYOR A MENOR


//ABM


/** FIN CABECERAS DE FUNCION*/




#endif /* TRABAJOSERVICIO_H_ */
