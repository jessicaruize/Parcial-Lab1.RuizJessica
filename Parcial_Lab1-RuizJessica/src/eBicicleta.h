/*
 * eBicicleta.h
 *
 *  Created on: 20 may. 2021
 *      Author: jessica
 */

#ifndef EBICICLETA_H_
#define EBICICLETA_H_

#include "pedir_valores.h"

#define MAX_CHARS_CADENAS 25
#define LIBRE 0
#define OCUPADO 1
#define BAJA -1

typedef struct
{
	int idBicicleta; //(comienza en 25)
	char marcaBicicleta[MAX_CHARS_CADENAS]; //(máximo 25 caracteres)
	int rodadoBicicleta;
	char color[MAX_CHARS_CADENAS]; // (cadena)
	int isEmpty;
}eBicicleta;


/** INICIO CABECERAS DE FUNCION**/
void eBicicleta_cargaAutomaticaBicicleta(eBicicleta aBicicleta[], int cantidadBicicleta);
void eBicicleta_inicializar(eBicicleta aBicicleta[], int tamBicicleta);
int eBicicleta_obtenerID(void);
int eBicicleta_obtenerIndiceLibre(eBicicleta aBicicleta[], int tamBicicleta);
int eBicicleta_buscarIndicePorId(eBicicleta aBicicleta[], int tamBicicleta, int id, int* idEncontrado);
int eBicicleta_mostrarUno(eBicicleta* pBicicleta);
int eBicicleta_mostrarTodos(eBicicleta aBicicleta[], int tamBicicleta);
int eBicicleta_mostrarDadosDeBaja(eBicicleta aBicicleta[], int tamBicicleta);
int eBicicleta_buscarIdMaximo(eBicicleta aBicicleta[], int tamBicicleta, int* idMaximo);



//eliminar-------------------------------------------------------------------------------------------------------------------------------------------------
//ABM
int eBicicleta_cargarDatos(eBicicleta* paBicicleta);
int eBicicleta_modificarUno(eBicicleta* Bicicleta);
int eBicicleta_alta(eBicicleta aBicicleta[], int tamBicicleta);
int eBicicleta_baja(eBicicleta aBicicleta[], int tamBicicleta);
int eBicicleta_modificacion(eBicicleta aBicicleta[], int tamBicicleta);
/** FIN CABECERAS DE FUNCION*/



#endif /* EBICICLETA_H_ */
