/*
 * eTrabajo.h
 *
 *  Created on: 17 may. 2021
 *      Author: jessica
 */

#ifndef ETRABAJO_H_
#define ETRABAJO_H_


#include <stdio.h>
#include <stdio_ext.h>
#include <stdlib.h>
#include "pedir_valores.h"


//*** DEFINE

#define MAX_CHARS_CADENAS 25
#define LIBRE 0
#define OCUPADO 1
#define BAJA -1
#define tamTrabajo_Trabajo 5


//*** ESTRUCTURA
typedef struct
{
	int dia;
	int mes;
	int anio;
}eFecha;

typedef struct
{
	int idTrabajo;
	int idBicicleta;
	int idServicio;
	eFecha fecha;
	int isEmpty;
} eTrabajo;
//***


/** INICIO CABECERAS DE FUNCION**/
void eTrabajo_cargaAutomaticaTrabajo(eTrabajo aTrabajo[], int cantidadTrabajo);
void eTrabajo_inicializar(eTrabajo aTrabajo[], int tamTrabajo);
int eTrabajo_obtenerID(void);
int eTrabajo_obtenerIndiceLibre(eTrabajo aTrabajo[], int tamTrabajo);
int eTrabajo_buscarIndicePorId(eTrabajo aTrabajo[], int tamTrabajo, int id, int* idEncontrado);
int eTrabajo_mostrarUno(eTrabajo* pTrabajo);
int eTrabajo_mostrarTodos(eTrabajo aTrabajo[], int tamTrabajo);
int eTrabajo_mostrarDadosDeBaja(eTrabajo aTrabajo[], int tamTrabajo);
int eTrabajo_buscarIdMaximo(eTrabajo aTrabajo[], int tamTrabajo, int* idMaximo);

//BORRAR--------------------------------------------------------------------------------------------------------------------------------
//ABM
int eTrabajo_cargarDatos(eTrabajo* paTrabajo);
int eTrabajo_modificarUno(eTrabajo* Trabajo);
int eTrabajo_alta(eTrabajo aTrabajo[], int tamTrabajo);
int eTrabajo_baja(eTrabajo aTrabajo[], int tamTrabajo);
int eTrabajo_modificacion(eTrabajo aTrabajo[], int tamTrabajo);
/** FIN CABECERAS DE FUNCION*/

//FUNCIONES FECHA
eFecha eTrabajo_pedirFecha(char* mensaje, char* mensajeError, int reintentos, int minAnio, int maxAnio);



#endif /* ETRABAJO_H_ */
