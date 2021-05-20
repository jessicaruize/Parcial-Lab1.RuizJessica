/*
 * eServicio.h
 *
 *  Created on: 17 may. 2021
 *      Author: jessica
 */

#ifndef ESERVICIO_H_
#define ESERVICIO_H_



#include "pedir_valores.h"



//*** DEFINE

#define MAX_CHARS_CADENAS 25
#define LIBRE 0
#define OCUPADO 1
#define BAJA -1
#define tamServicio_Servicio 5


//*** ESTRUCTURA
typedef struct
{
	int idServicio;
	char descripcion[MAX_CHARS_CADENAS];
	float precio;
	int isEmpty;
} eServicio;
//***


/** INICIO CABECERAS DE FUNCION*////prototipos
void eServicio_cargaAutomaticaServicio(eServicio aServicio[], int cantidadServicio);
void eServicio_inicializar(eServicio aServicio[], int tamServicio);
int eServicio_obtenerID(void);
int eServicio_obtenerIndiceLibre(eServicio aServicio[], int tamServicio);
int eServicio_buscarIndicePorId(eServicio aServicio[], int tamServicio, int id, int* idEncontrado);
int eServicio_mostrarUno(eServicio* pServicio);
int eServicio_mostrarTodos(eServicio aServicio[], int tamServicio);
int eServicio_mostrarDadosDeBaja(eServicio aServicio[], int tamServicio);
int eServicio_buscarIdMaximo(eServicio aServicio[], int tamServicio, int* idMaximo);


/** SORT */
//CRITERIO -> -1 = MENOR A MAYOR
//CRITERIO ->  1 = MAYOR A MENOR

//ABM
int eServicio_cargarDatos(eServicio* paServicio);
int eServicio_modificarUno(eServicio* Servicio);
int eServicio_alta(eServicio aServicio[], int tamServicio);
int eServicio_baja(eServicio aServicio[], int tamServicio);
int eServicio_modificacion(eServicio aServicio[], int tamServicio);
/** FIN CABECERAS DE FUNCION*/

//FUNCIONES
/*
 * permite abstraer codigo
 * se puede reutilizar
 * mas facil de mantener
 * recibe (argumentos/parametros)variables locales.
 *
 * */




#endif /* ESERVICIO_H_ */
