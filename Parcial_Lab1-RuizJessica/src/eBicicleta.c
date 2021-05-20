/*
 * eBicicleta.c
 *
 *  Created on: 20 may. 2021
 *      Author: jessica
 */



#include "eBicicleta.h"

static int Bicicleta_idIncremental =  29;

/**
 * @fn void eBicicleta_cargaAutomaticaBicicleta(eBicicleta[], int)
 * @brief funcion para cargar los datos sin tener que cargarlos uno por uno.
 *
 * @param aBicicleta array que recibe para ser cargado.
 * @param cantidadBicicleta cantidad de Bicicleta a cargar
 */
void eBicicleta_cargaAutomaticaBicicleta(eBicicleta aBicicleta[], int cantidadBicicleta)
{
	int idBicicleta []= {25,26,27,28,29};
	char marcaBicicleta[][MAX_CHARS_CADENAS]={"akd", "bk", "dp", "jl", "ik"};
	int rodadoBicicleta []= {16,18,20,22,24};
	char color[][MAX_CHARS_CADENAS]= {"verde", "rojo", "amarillo","azul","violeta"};

	int i;
	if(aBicicleta != NULL && cantidadBicicleta > 0)
	{
		for(i=0; i<cantidadBicicleta; i++)
		{
			aBicicleta[i].idBicicleta = idBicicleta[i];
			strncpy(aBicicleta[i].marcaBicicleta , marcaBicicleta[i], MAX_CHARS_CADENAS);
			aBicicleta[i].rodadoBicicleta = rodadoBicicleta[i];
			strncpy(aBicicleta[i].color, color[i], MAX_CHARS_CADENAS);
			aBicicleta[i].isEmpty = OCUPADO;
		}
	}
}

/**@fn void eBicicleta_inicializar(eBicicleta aBicicleta[], int tamBicicleta)
 * @brief funcion que recorre e inicializa el array de eBicicleta
 * @aBicicleta array a ser inicializado su campo isEmpty con LIBRE.
 * @tamBicicleta tamaño del array a recorrer
 */
void eBicicleta_inicializar(eBicicleta aBicicleta[], int tamBicicleta)
{
	int i;
	if (aBicicleta != NULL && tamBicicleta > 0)
	{
		for (i = 0; i < tamBicicleta; i++)
		{
			aBicicleta[i].isEmpty = LIBRE;
		}
	}
}


/**@fn int eBicicleta_obtenerID()
 * @brief funcion que incrementa el ID cada vez que es usada.
 * @return devuelve el ID incrementado.
 */
int eBicicleta_obtenerID()
{
	return Bicicleta_idIncremental += 1;
}

/**@fn int eBicicleta_obtenerIndiceLibre(eBicicleta aBicicleta[], int tamBicicleta)
 * @brief funcion que busca indice con el campo isEmpty LIBRE
 * @aBicicleta array en el que se busca el indice LIBRE
 * @tamBicicleta tamaño del aBicicleta.
 * @return retorna -1 para indicar error, -2 si no encontro ningún
 * indice con campo isEmpty LIBRE y mayor si el retorno es mayor a 0
 * corresponde al indice con el campo isEmpty LIBRE.
 */
int eBicicleta_obtenerIndiceLibre(eBicicleta aBicicleta[], int tamBicicleta)
{
	int retorno = -1; //ERROR
	int i;
	if (aBicicleta != NULL && tamBicicleta > 0)
	{
		for (i = 0; i < tamBicicleta; i++)
		{
			if (aBicicleta[i].isEmpty == LIBRE) {
				retorno = i;// retorna indice libre.
				break;
			}
			retorno = -2; //aBicicleta lleno
		}
	}
	return retorno;
}

/**
 * @fn int eBicicleta_buscarIndicePorId(eBicicleta[], int, int, int*)
 * @brief funcion que busca el indice del ID que se le pasa por parametro.
 * @param aBicicleta array en el que buscar el indice.
 * @param tamBicicleta tamaño del aBicicleta.
 * @param id es el ID que va a ser comparado con los id del aBicicleta para buscar
 * el indice correspondiente.
 * @param indiceEncontrado puntero que va a guardar el indice encontrado.
 * @return retorna -2 para indicar error, -1 si no hay ningun Bicicleta con ese ID,
 * 0 si encontro el ID con el campo isEmpty OCUPADO y 1 si el ID corresponde a un Bicicleta dado de baja.
 */
int eBicicleta_buscarIndicePorId(eBicicleta aBicicleta[], int tamBicicleta, int id, int* indiceEncontrado)
{
	int retorno = -2; // error.
	int i;
	if (aBicicleta != NULL && tamBicicleta > 0 && indiceEncontrado != NULL)
	{
		retorno = -1; // No hay ningun Bicicleta con ese ID
		for (i = 0; i < tamBicicleta; i++)
		{
			if (aBicicleta[i].idBicicleta == id && aBicicleta[i].isEmpty == OCUPADO)
			{
				*indiceEncontrado = i;
				retorno = 0; // Bicicleta ocupado
				break;
			}
			else
			{
				if(aBicicleta[i].idBicicleta == id && aBicicleta[i].isEmpty == BAJA)
				{
					*indiceEncontrado = i;
					retorno = 1; //Bicicleta dado de baja
					break;
				}
			}
		}
	}

	return retorno;
}

/**
 * @fn int eBicicleta_mostrarUno(eBicicleta*)
 * @brief funcion que va a mostrar un Bicicleta.
 * @param pBicicleta puntero qdel que vamos a recibir la informacion a mostrar.
 * @return retorna -1 error, o si salio bien.
 */
int eBicicleta_mostrarUno(eBicicleta* pBicicleta)
{
	int retorno = -1; //error.
	if(pBicicleta != NULL)
	{
		retorno = 0; //bien.
		printf("ID Bicicleta: %-4d \t Marca de la bicicleta: %-15s \t Rodado de la bicicleta: %-4d \t color: %-15s \n", pBicicleta->idBicicleta,
																													    pBicicleta->marcaBicicleta,
																													    pBicicleta->rodadoBicicleta,
																													    pBicicleta->color);
	}
	return retorno;
}

/**
 * @fn int eBicicleta_mostrarTodos(eBicicleta[], int)
 * @brief funcion que muestra todos los datos del array siempre y
 * cuando el campo isEmpty se encuentre lleno.
 * @param aBicicleta array que se va a recorrer para mostrar.
 * @param tamBicicleta tamaño del aBicicleta.
 * @return retorna -1 en caso de error y 0 si hay Gen para mostrar y 1 si no hay Bicicleta para mostrar.
 */
int eBicicleta_mostrarTodos(eBicicleta aBicicleta[], int tamBicicleta)
{
	int i;
	int retorno = -1;//no hay nada para mostrar
	int contador = 0;
	if (aBicicleta != NULL && tamBicicleta > 0)
	{
		for (i = 0; i < tamBicicleta; i++)
		{
			if (aBicicleta[i].isEmpty == OCUPADO)
			{
				eBicicleta_mostrarUno(&aBicicleta[i]);
				contador++;
			}
		}
	}
	if (contador > 0)
	{
		retorno = 0; //hay Bicicleta para mostrar.
		printf("\n\nTOTAL: %d\n", contador);
	}
	else
	{
		retorno = 1; //no hay Bicicleta para mostrar
	}

	return retorno;
}

/**
 * @fn int eBicicleta_mostrarDadosDeBaja(eBicicleta[], int, int*)
 * @brief funcion que muestra los Bicicleta dados de baja.
 * @param aBicicleta array a recorrer en el que se va a buscar los Bicicleta dados de baja.
 * @param tamBicicleta tamaño del array aBicicleta.
 * @return retorna -1 en caso de error y 0 si hay Bicicleta para mostrar y 1 si no hay Bicicleta para mostrar.
 */
int eBicicleta_mostrarDadosDeBaja(eBicicleta aBicicleta[], int tamBicicleta)
{
	int i;
	int retorno = -1;//no hay nada para mostrar
	int contador = 0;
	puts("\n\t> LISTADO Bicicleta");
	if (aBicicleta != NULL && tamBicicleta > 0)
	{
		for (i = 0; i < tamBicicleta; i++)
		{
			if (aBicicleta[i].isEmpty == BAJA)
			{
				eBicicleta_mostrarUno(&aBicicleta[i]);
				contador++;
			}
		}
	}
	if (contador > 0)
	{
		retorno = 0; //hay Bicicleta dado de baja para mostrar.
	}
	else
	{
		retorno = 1; // no hay Bicicleta para mostrar
	}
	return retorno;
}

/**
 * @fn int eBicicleta_buscarIdMaximo(eBicicleta[], int, int*).
 * @brief funcion que busca el ID maximo de un array entre los que tienen el campo isEmpty OCUPADO.
 * @param aBicicleta array a recorrer y encontrar el mayor ID.
 * @param tamBicicleta tamaño del array aBicicleta.
 * @param idMaximo puntero que guarda como valor el id máximo encontrado.
 * @return retorna -1 en caso de error y 0 si se encontro el ID maximo.
 */
int eBicicleta_buscarIdMaximo(eBicicleta aBicicleta[], int tamBicicleta, int* idMaximo)
{
	int i;
	int retorno = -1;
	if(aBicicleta != NULL && idMaximo !=NULL)
	{
		for(i=0; i<tamBicicleta; i++)
		{
			if((i == 0 || aBicicleta[i].idBicicleta > *idMaximo) && aBicicleta[i].isEmpty == OCUPADO)
			{
				*idMaximo = aBicicleta[i].idBicicleta;
				retorno= 0;
			}
		}
	}
	return retorno;
}








//ABM
/**
 * @fn int eBicicleta_cargarDatos(eBicicleta*)
 * @brief funcion que pide los datos a cargar y los verifica.
 * @param pBicicleta puntero en el que se van a guardar los valores obtenidos.
 * @return retorna -1 en caso de error y 0 si salio bien.
 */
int eBicicleta_cargarDatos(eBicicleta* pBicicleta)
{
	int retorno = -1;
	if(pBicicleta != NULL)
	{
		if(!utn_pedirAlfanumerico(pBicicleta->marcaBicicleta, "\n\nIngrese marca de la bicicleta: ", "\nError, ingrese un dato correcto.\n", 2) &&
		   !utn_pedirEntero(&pBicicleta->rodadoBicicleta, "Ingrese el rodado de la bicicleta: ", "Error, ingrese un dato correcto.", 10, 30, 2, 1) &&
		   !utn_pedirAlfabetico(pBicicleta->color, "Ingrese el color de la bicicleta: ", "Error. ingrese un color.", 2))
		{
			retorno = 0;
		}


	}
	return retorno;
}
/**
 * @fn int eBicicleta_modificarUno(eBicicleta*)
 * @brief funcion que modifica los datos requeridos.
 * @param pBicicleta Bicicleta que va a ser modificado por algun motivo.
 * @return retorna -1 en caso de error, 0 modificacion exitosa.
 */
int eBicicleta_modificarUno(eBicicleta* pBicicleta)
{
	int retorno = -1;
	int respuesta;
	int seguir;
	do
	{
		printf("\n\n\tMODIFICAR: \n\n1_Marca.\n2_Rodado.\n3_Color\n4_Modificación terminada.");
		if(!utn_pedirEntero(&respuesta, "\n\nIngrese la opción que desea realizar: ", "\nError", 1, 6, 2, 1))
		{
			switch(respuesta)

			{
				case 1: //Descripcion
					utn_pedirAlfabetico(pBicicleta->marcaBicicleta, "Ingrese la descripcion: ", "Error", 2);
					seguir=0;
				break;
				case 2: //precio
					utn_pedirEntero(&pBicicleta->rodadoBicicleta, "Ingrese precio: ", "Error", 0, 1000000, 2, 1);
					seguir = 0;
				break;
				case 3://color
					utn_pedirAlfabetico(pBicicleta->color, "Ingrese el color: ", "Error, ingrese el color", 2);
				break;
				case 4: // salir
					if(!utn_verificar("¿Modificación terminada? [s/n]", "Error", 2))
					{
						seguir = 1;
						retorno = 0;
					}
					else
					{
						seguir = 0;
					}
				break;
			}
		}

	}while(seguir != 1);

	return retorno;
}
/**
* @fn int eBicicleta_alta(eBicicleta[], int)
 * @brief funcion que verifica si el usuario desea guardar el alta y en ese caso crea el
 * alta con su ID, cambia el campo isEmpty a ocupado y guarda los datos en el indice correspondiente.
 * @param aBicicleta array en el que se gestiona el alta.
 * @param tamBicicleta tamaño del array aBicicleta.
 * @return retorna -2 si el array esta lleno, -1 si hubo un error, 0 si se dio de alta  orrrectamente
 * y 1 si la operación fue cancelada.
 */
int eBicicleta_alta(eBicicleta aBicicleta[], int tamBicicleta)
{
	int retorno = -1; //ERROR
	eBicicleta auxBicicleta;
	int indice;
	if(aBicicleta != NULL && tamBicicleta > 0)
	{
		indice = eBicicleta_obtenerIndiceLibre(aBicicleta, tamBicicleta);

		if (indice > -1 && (!eBicicleta_cargarDatos(&auxBicicleta)))
		{

			if(utn_verificar("¿Desea guardar los cambios[s/n]?", "Error", 2) == 0)
			{
				auxBicicleta.idBicicleta = eBicicleta_obtenerID();
				auxBicicleta.isEmpty = OCUPADO;
				aBicicleta[indice] = auxBicicleta;
				retorno = 0; //se dio de alta satisfactoriamente
			}
			else
			{
				retorno = 1; //Operacion cancelada
			}
		}
		else
		{
			if(indice == -2)
			{
				retorno = -2; //aBicicleta lleno
			}
		}
	}

	return retorno;
}
/**
 * @fn int eBicicleta_baja(eBicicleta[], int)
 * @brief funcion que da de baja pidiendo el ID correspondiente
 * al Bicicleta que se desea dar de baja.
 * @param aBicicleta array en el que se va a gestionar la baja logica.
 * @param tamBicicleta tamaño del array aBicicleta.
 * @return retorna-2 si hubo error, -1 si ID no existe, 0 si se
 * realizo la baja, 1 si el Bicicleta ya se habia dado de baja y 2 si la operación fue cancelada.
 */
int eBicicleta_baja(eBicicleta aBicicleta[], int tamBicicleta)
{
	int retorno = -2; //ERROR
	int idBicicleta;
	int indice;
	int idMaximo;
	int respuesta;
	eBicicleta buffer;

	int flag = 0;
	if (eBicicleta_mostrarTodos(aBicicleta, tamBicicleta)==0)
	{
		flag = 1;
	}
	if (flag)
	{
		eBicicleta_buscarIdMaximo(aBicicleta, tamBicicleta, &idMaximo);
		if(utn_pedirEntero(&idBicicleta, "\nIngrese el ID del Bicicleta que quiere dar de baja: \n", "\nError. \n", 1, idMaximo, 2, 1)==0)
		{

			respuesta = eBicicleta_buscarIndicePorId(aBicicleta, tamBicicleta, idBicicleta, &indice);
			switch (respuesta)
			{
				case -2: // ERROR.
					retorno = -2;
				break;
				case 0: //OCUPADO
					buffer = aBicicleta[indice];
					eBicicleta_mostrarUno(&buffer);
					if(utn_verificar("\n¿Desea dar de baja este Bicicleta [s/n]?", "\nError", 2)==0)
					{
						aBicicleta[indice].isEmpty = BAJA; //baja logica.
						retorno = 0; //BAJA REALIZADA.
					}
					else
					{
						retorno = 2; // operacion cancelada
					}
				break;
				case 1: //BAJA
					retorno = 1; // Bicicleta YA DADO DE BAJA
				break;
			}
		}
		else
		{
			retorno = -1; // ID no existe.
		}
	}

	return retorno;
}
/**
 * @fn int eBicicleta_Modificacion(eBicicleta[], int)
 * @brief funcion en la que corrobora si el ID ingresado es corecto para luego realizar la
 * modificacion y una vez confirmada la accion se hace los cambios.
 * @param aBicicleta array en el que se busca el indice del ID para realizar la modificacion deseada.
 * @param tamBicicleta tamaño del array aBicicleta.
 * @return retorna -2 en caso de error, -1 si el ID no existe, 0 si se realizo la modificación
 * y 1 si el Bicicleta ya estaba dado de baja y 2 si la operacion fue cancelada.
 */
int eBicicleta_modificacion(eBicicleta aBicicleta[], int tamBicicleta)
{
	int retorno = -2; //ERROR;
	int idBicicleta;
	int indice;
	int respuesta;
	int idMaximo;
	int flag = 0;
	eBicicleta auxiliar;
	if(aBicicleta != NULL && tamBicicleta > 0)
	{
		if (eBicicleta_mostrarTodos(aBicicleta, tamBicicleta)==0)
		{
			flag = 1;
		}
		if (flag)
		{
			eBicicleta_buscarIdMaximo(aBicicleta, tamBicicleta, &idMaximo);
			if(!utn_pedirEntero(&idBicicleta, "\ningrese el ID del Bicicleta que quiere modificar", "\nError", 1, idMaximo, 2, 1))
			{
				respuesta = eBicicleta_buscarIndicePorId(aBicicleta, tamBicicleta, idBicicleta, &indice);
				switch (respuesta)
				{
					case -2: //ERROR
						retorno = -2;
					break;
					case 0: //OCUPADO
						auxiliar = aBicicleta[indice];
						eBicicleta_mostrarUno(&auxiliar);
						eBicicleta_modificarUno(&auxiliar);
						if(!utn_verificar("\n¿Desea confirmas la modificación?[s/n]?\n", "nError", 2))
						{
							aBicicleta[indice]= auxiliar;
							retorno = 0; //MODIFICADO CORRECtamBicicletaENTE.
						}
						else
						{
							retorno = 2; // modificacion cancelada
						}
					break;
					case 1: //BAJA
						retorno = 1; // Bicicleta  DADO DE BAJA
					break;
				}
			}
			else
			{
				retorno = -1;
			}
		}
	}
	return retorno;
}

