/*
 * eTrabajo.c
 * Author: jessica
 */


#include "eTrabajo.h"

static int Trabajo_idIncremental =  5;

/**
 * @fn void eTrabajo_cargaAutomaticaTrabajo(eTrabajo[], int)
 * @brief funcion para cargar los datos sin tener que cargarlos uno por uno.
 *
 * @param aTrabajo array que recibe para ser cargado.
 * @param cantidadTrabajo cantidad de Trabajo a cargar
 */
void eTrabajo_cargaAutomaticaTrabajo(eTrabajo aTrabajo[], int cantidadTrabajo)
{
	int id []= {1,2,3,4,5};
	char marcaBicicleta[][30]={"akd", "bk", "dp", "jl", "ik"};
	int rodadoBicicleta []= {16,18,20,22,24};
	int idServicio []= {20001,20004,20002,20003,20001};
	eFecha aFecha []= {{2,5,2020}, {5,4,2019}, {22,6,2020}, {15,2,2019}, {4,9,2015}};

	int i;
	if(aTrabajo != NULL && cantidadTrabajo > 0)
	{
		for(i=0; i<cantidadTrabajo; i++)
		{
			aTrabajo[i].idTrabajo = id[i];
			strcpy(aTrabajo[i].marcaBicicleta , marcaBicicleta[i]);
			aTrabajo[i].rodadoBicicleta = rodadoBicicleta[i];
			aTrabajo[i].idServicio = idServicio[i];
			aTrabajo[i].fecha = aFecha[i];
			aTrabajo[i].isEmpty = OCUPADO;
		}
	}
}

/**@fn void eTrabajo_inicializar(eTrabajo aTrabajo[], int tamTrabajo)
 * @brief funcion que recorre e inicializa el array de eTrabajo
 * @aTrabajo array a ser inicializado su campo isEmpty con LIBRE.
 * @tamTrabajo tamaño del array a recorrer
 */
void eTrabajo_inicializar(eTrabajo aTrabajo[], int tamTrabajo)
{
	int i;
	if (aTrabajo != NULL && tamTrabajo > 0)
	{
		for (i = 0; i < tamTrabajo; i++)
		{
			aTrabajo[i].isEmpty = LIBRE;
		}
	}
}


/**@fn int eTrabajo_obtenerID()
 * @brief funcion que incrementa el ID cada vez que es usada.
 * @return devuelve el ID incrementado.
 */
int eTrabajo_obtenerID()
{
	return Trabajo_idIncremental += 1;
}

/**@fn int eTrabajo_obtenerIndiceLibre(eTrabajo aTrabajo[], int tamTrabajo)
 * @brief funcion que busca indice con el campo isEmpty LIBRE
 * @aTrabajo array en el que se busca el indice LIBRE
 * @tamTrabajo tamaño del aTrabajo.
 * @return retorna -1 para indicar error, -2 si no encontro ningún
 * indice con campo isEmpty LIBRE y mayor si el retorno es mayor a 0
 * corresponde al indice con el campo isEmpty LIBRE.
 */
int eTrabajo_obtenerIndiceLibre(eTrabajo aTrabajo[], int tamTrabajo)
{
	int retorno = -1; //ERROR
	int i;
	if (aTrabajo != NULL && tamTrabajo > 0)
	{
		for (i = 0; i < tamTrabajo; i++)
		{
			if (aTrabajo[i].isEmpty == LIBRE) {
				retorno = i;// retorna indice libre.
				break;
			}
			retorno = -2; //aTrabajo lleno
		}
	}
	return retorno;
}

/**
 * @fn int eTrabajo_buscarIndicePorId(eTrabajo[], int, int, int*)
 * @brief funcion que busca el indice del ID que se le pasa por parametro.
 * @param aTrabajo array en el que buscar el indice.
 * @param tamTrabajo tamaño del aTrabajo.
 * @param id es el ID que va a ser comparado con los id del aTrabajo para buscar
 * el indice correspondiente.
 * @param indiceEncontrado puntero que va a guardar el indice encontrado.
 * @return retorna -2 para indicar error, -1 si no hay ningun Trabajo con ese ID,
 * 0 si encontro el ID con el campo isEmpty OCUPADO y 1 si el ID corresponde a un Trabajo dado de baja.
 */
int eTrabajo_buscarIndicePorId(eTrabajo aTrabajo[], int tamTrabajo, int id, int* indiceEncontrado)
{
	int retorno = -2; // error.
	int i;
	if (aTrabajo != NULL && tamTrabajo > 0 && indiceEncontrado != NULL)
	{
		retorno = -1; // No hay ningun Trabajo con ese ID
		for (i = 0; i < tamTrabajo; i++)
		{
			if (aTrabajo[i].idTrabajo == id && aTrabajo[i].isEmpty == OCUPADO)
			{
				*indiceEncontrado = i;
				retorno = 0; // Trabajo ocupado
				break;
			}
			else
			{
				if(aTrabajo[i].idTrabajo == id && aTrabajo[i].isEmpty == BAJA)
				{
					*indiceEncontrado = i;
					retorno = 1; //Trabajo dado de baja
					break;
				}
			}
		}
	}

	return retorno;
}

/**
 * @fn int eTrabajo_mostrarUno(eTrabajo*)
 * @brief funcion que va a mostrar un Trabajo.
 * @param pTrabajo puntero qdel que vamos a recibir la informacion a mostrar.
 * @return retorna -1 error, o si salio bien.
 */
int eTrabajo_mostrarUno(eTrabajo* pTrabajo)
{
	int retorno = -1; //error.
	if(pTrabajo != NULL)
	{
		retorno = 0; //bien.
		printf("ID trabajo: %-4d \t Marca de la bicicleta: %-15s \t Rodado de la bicicleta: %-4d \t ID servicio: %-4d \t Fecha: %d/%d/%d\n", pTrabajo->idTrabajo,
																								   	   	   	  	  	  	  	  	   pTrabajo->marcaBicicleta,
																																   pTrabajo->rodadoBicicleta,
																																   pTrabajo->idServicio,
																																   pTrabajo->fecha.dia,
																																   pTrabajo->fecha.mes,
																																   pTrabajo->fecha.anio);
	}
	return retorno;
}

/**
 * @fn int eTrabajo_mostrarTodos(eTrabajo[], int)
 * @brief funcion que muestra todos los datos del array siempre y
 * cuando el campo isEmpty se encuentre lleno.
 * @param aTrabajo array que se va a recorrer para mostrar.
 * @param tamTrabajo tamaño del aTrabajo.
 * @return retorna -1 en caso de error y 0 si hay Gen para mostrar y 1 si no hay Trabajo para mostrar.
 */
int eTrabajo_mostrarTodos(eTrabajo aTrabajo[], int tamTrabajo)
{
	int i;
	int retorno = -1;//no hay nada para mostrar
	int contador = 0;
	if (aTrabajo != NULL && tamTrabajo > 0)
	{
		for (i = 0; i < tamTrabajo; i++)
		{
			if (aTrabajo[i].isEmpty == OCUPADO)
			{
				eTrabajo_mostrarUno(&aTrabajo[i]);
				contador++;
			}
		}
	}
	if (contador > 0)
	{
		retorno = 0; //hay Trabajo para mostrar.
		printf("\n\nTOTAL: %d\n", contador);
	}
	else
	{
		retorno = 1; //no hay Trabajo para mostrar
	}

	return retorno;
}

/**
 * @fn int eTrabajo_mostrarDadosDeBaja(eTrabajo[], int, int*)
 * @brief funcion que muestra los Trabajo dados de baja.
 * @param aTrabajo array a recorrer en el que se va a buscar los Trabajo dados de baja.
 * @param tamTrabajo tamaño del array aTrabajo.
 * @return retorna -1 en caso de error y 0 si hay Trabajo para mostrar y 1 si no hay Trabajo para mostrar.
 */
int eTrabajo_mostrarDadosDeBaja(eTrabajo aTrabajo[], int tamTrabajo)
{
	int i;
	int retorno = -1;//no hay nada para mostrar
	int contador = 0;
	puts("\n\t> LISTADO Trabajo");
	if (aTrabajo != NULL && tamTrabajo > 0)
	{
		for (i = 0; i < tamTrabajo; i++)
		{
			if (aTrabajo[i].isEmpty == BAJA)
			{
				eTrabajo_mostrarUno(&aTrabajo[i]);
				contador++;
			}
		}
	}
	if (contador > 0)
	{
		retorno = 0; //hay Trabajo dado de baja para mostrar.
	}
	else
	{
		retorno = 1; // no hay Trabajo para mostrar
	}
	return retorno;
}

/**
 * @fn int eTrabajo_buscarIdMaximo(eTrabajo[], int, int*).
 * @brief funcion que busca el ID maximo de un array entre los que tienen el campo isEmpty OCUPADO.
 * @param aTrabajo array a recorrer y encontrar el mayor ID.
 * @param tamTrabajo tamaño del array aTrabajo.
 * @param idMaximo puntero que guarda como valor el id máximo encontrado.
 * @return retorna -1 en caso de error y 0 si se encontro el ID maximo.
 */
int eTrabajo_buscarIdMaximo(eTrabajo aTrabajo[], int tamTrabajo, int* idMaximo)
{
	int i;
	int retorno = -1;
	if(aTrabajo != NULL && idMaximo !=NULL)
	{
		for(i=0; i<tamTrabajo; i++)
		{
			if((i == 0 || aTrabajo[i].idTrabajo > *idMaximo) && aTrabajo[i].isEmpty == OCUPADO)
			{
				*idMaximo = aTrabajo[i].idTrabajo;
				retorno= 0;
			}
		}
	}
	return retorno;
}


/**
 * @fn int eTrabajo_SortAnio(eTrabajo[], int)
 * @brief  funcion que ordena por año de menor a mayor y en caso de tener el mismo año ordena por marca.
 * @param aTrabajo array a ser ordenado
 * @param tamTrabajo tamaño del array aTrabajo.
 * @return retorna -1 en caso de error y 0 si se ordeno correctamente.
 */
int eTrabajo_SortAnio(eTrabajo aTrabajo[], int tamTrabajo)
{
	int retorno = -1;
	int i;
	int j;
	eTrabajo aux;
	if(aTrabajo != NULL && tamTrabajo > 0)
	{
		for (i = 0; i < tamTrabajo - 1; i++)
			{
				for (j = i + 1; j < tamTrabajo; j++)
				{
					eTrabajo_SortAnioSolo(aTrabajo, i, j, &aux);
					eTrabajo_SortMarca(aTrabajo, i, j, &aux);
					retorno = 0;

				}
			}
	}

	return retorno;
}

/**
 * @fn int eTrabajo_SortAnioSolo(eTrabajo[], int, int, eTrabajo*)
 * @brief funcion que va a ordenar los años de mayor a menor.
 * @param aTrabajo array a ser ordenado.
 * @param indiceTrabajo1 indice recibito por valor que va a ser usado en el array aTrabajo para ordenar
 * @param indiceTrabajo2 indice recibito por valor que va a ser usado en el array aTrabajo para ordenar
 * @param aux puntero auxiliar para poder realizar el cambio.
 * @return
 */
int eTrabajo_SortAnioSolo(eTrabajo aTrabajo[], int indiceTrabajo1, int indiceTrabajo2, eTrabajo *aux)
{
	int retorno = -1;
	if ((aTrabajo != NULL && indiceTrabajo1 > -1 && indiceTrabajo2 > -1 && aux != NULL) &&
		 (aTrabajo[indiceTrabajo1].isEmpty == OCUPADO && aTrabajo[indiceTrabajo2].isEmpty == OCUPADO) &&
		(aTrabajo[indiceTrabajo1].fecha.anio > aTrabajo[indiceTrabajo2].fecha.anio))
		{
			*aux = aTrabajo[indiceTrabajo1];
			aTrabajo[indiceTrabajo1] = aTrabajo[indiceTrabajo2];
			aTrabajo[indiceTrabajo2] = *aux;
			retorno = 0;
		}
	return retorno;
}

/**
 * @fn void eTrabajo_SortMarca(eTrabajo[], int, int, eTrabajo*)
 * @brief  funcion que va a ordenar alfabeticamente las marcas que tengas el mismo año de trabajo.
 * @param aTrabajo array en el que se va a comparar los años y las marcas con los indices correspondientes.
 * @param indiceTrabajo1 indice que sera aplicado en el array aTrabajo para comparar.
 * @param indiceTrabajo2 indice que sera aplicado en el array aTrabajo para comparar.
 * @param aux puntero auxiliar para poder realizar el cambio.
 */
void eTrabajo_SortMarca(eTrabajo aTrabajo[], int indiceTrabajo1, int indiceTrabajo2, eTrabajo* aux)
{
	if ((aTrabajo != NULL && indiceTrabajo1 > -1 && indiceTrabajo2 > -1 && aux != NULL) &&
		(aTrabajo[indiceTrabajo1].isEmpty == OCUPADO && aTrabajo[indiceTrabajo2].isEmpty == OCUPADO) &&
	    (aTrabajo[indiceTrabajo1].fecha.anio == aTrabajo[indiceTrabajo2].fecha.anio) &&
		(strcmp(aTrabajo[indiceTrabajo1].marcaBicicleta, aTrabajo[indiceTrabajo2].marcaBicicleta)>0))
			{
				*aux = aTrabajo[indiceTrabajo1];
				aTrabajo[indiceTrabajo1] = aTrabajo[indiceTrabajo2];
				aTrabajo[indiceTrabajo2] = *aux;
			}
}

/**
 * @fn eFecha eTrabajo_pedirFecha(char*, char*, int, int, int)
 * @brief funcion que pide una fecha, corrobora que se cumplan los rangos del calendario.
 * @param mensaje, puntero que recibe el mensaje a mostrar antes de pedir la fecha.
 * @param mensajeError puntero que recibe el mensaje a mostrar ante un error.
 * @param reintentos cantidad de reintentos permitidos.
 * @param minAnio año minimo aceptable.
 * @param maxAnio año maximo aceptable.
 * @return retorna la fecha que el usuario escribio.
 */
eFecha eTrabajo_pedirFecha(char* mensaje, char* mensajeError, int reintentos, int minAnio, int maxAnio)
{
	eFecha miFecha;
	eFecha retorno;
	if(mensaje != NULL && mensajeError != NULL &&
	   reintentos > 0 && minAnio > 0 && maxAnio > 0)
	{
		do
		{
			printf("%s", mensaje);
			if(!utn_pedirEntero(&miFecha.dia, "\nIngrese día", "Error", 1, 31, 2, 1) &&
			   !utn_pedirEntero(&miFecha.mes, "\nIngrese mes", "Error", 1, 12, 2, 1)&&
			   !utn_pedirEntero(&miFecha.anio, "\nIngrese año", "Error", minAnio, maxAnio, 2, 1))
			{
				switch(miFecha.mes)
				{
					case 2:
						if(miFecha.dia <29)
						{
							retorno = miFecha;
							reintentos = -2;
						}
						else{
							puts("ERRoR");
						}
					break;
					case (4 || 6 || 9 || 11):
						if(miFecha.dia < 31)
						{
							retorno = miFecha;
							reintentos = -2;
						}
						else{
							puts("ERRoR");
						}
					break;
					default:
						retorno = miFecha;
						reintentos = -2;
					break;
				}
			}
			if(reintentos == -2)
			{
				break;
			}
			reintentos--;
			printf("%s", mensajeError);
		}while(reintentos > -1);
	}
	return retorno;
}
