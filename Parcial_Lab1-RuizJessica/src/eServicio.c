/*
 * eServicio.c
 *
 *  Created on: 17 may. 2021
 *      Author: jessica
 */

#include "eServicio.h"

//fijarse cantidad de Servicio en la carga automatiCa

static int Servicio_idIncremental =  20004;

/**
 * @fn void eServicio_cargaAutomaticaServicio(eServicio[], int)
 * @brief funcion para cargar los datos sin tener que cargarlos uno por uno.
 *
 * @param aServicio array que recibe para ser cargado.
 * @param cantidadServicio cantidad de Servicio a cargar
 */
void eServicio_cargaAutomaticaServicio(eServicio aServicio[], int cantidadServicio)
{
	int id []= {20001,20002,20003,20004};
	char descripcion[][30]={"Limpieza", "Parche", "Centrado", "Cadena"};
	float precio []= {250, 300, 400, 350};
	int i;
	if(aServicio != NULL && cantidadServicio > 0)
	{
		for(i=0; i<cantidadServicio; i++)
		{
			aServicio[i].idServicio = id[i];
			strcpy(aServicio[i].descripcion, descripcion[i]);
			aServicio[i].precio = precio[i];
			aServicio[i].isEmpty = OCUPADO;
		}
	}
}

/**@fn void eServicio_inicializar(eServicio aServicio[], int tamServicio)
 * @brief funcion que recorre e inicializa el array de eServicio
 * @aServicio array a ser inicializado su campo isEmpty con LIBRE.
 * @tamServicio tamaño del array a recorrer
 */
void eServicio_inicializar(eServicio aServicio[], int tamServicio)
{
	int i;
	if (aServicio != NULL && tamServicio > 0)
	{
		for (i = 0; i < tamServicio; i++)
		{
			aServicio[i].isEmpty = LIBRE;
		}
	}
}


/**@fn int eServicio_obtenerID()
 * @brief funcion que incrementa el ID cada vez que es usada.
 * @return devuelve el ID incrementado.
 */
int eServicio_obtenerID()
{
	return Servicio_idIncremental += 1;
}

/**@fn int eServicio_obtenerIndiceLibre(eServicio aServicio[], int tamServicio)
 * @brief funcion que busca indice con el campo isEmpty LIBRE
 * @aServicio array en el que se busca el indice LIBRE
 * @tamServicio tamaño del aServicio.
 * @return retorna -1 para indicar error, -2 si no encontro ningún
 * indice con campo isEmpty LIBRE y mayor si el retorno es mayor a 0
 * corresponde al indice con el campo isEmpty LIBRE.
 */
int eServicio_obtenerIndiceLibre(eServicio aServicio[], int tamServicio)
{
	int retorno = -1; //ERROR
	int i;
	if (aServicio != NULL && tamServicio > 0)
	{
		for (i = 0; i < tamServicio; i++)
		{
			if (aServicio[i].isEmpty == LIBRE) {
				retorno = i;// retorna indice libre.
				break;
			}
			retorno = -2; //aServicio lleno
		}
	}
	return retorno;
}

/**
 * @fn int eServicio_buscarIndicePorId(eServicio[], int, int, int*)
 * @brief funcion que busca el indice del ID que se le pasa por parametro.
 * @param aServicio array en el que buscar el indice.
 * @param tamServicio tamaño del aServicio.
 * @param id es el ID que va a ser comparado con los id del aServicio para buscar
 * el indice correspondiente.
 * @param indiceEncontrado puntero que va a guardar el indice encontrado.
 * @return retorna -2 para indicar error, -1 si no hay ningun Servicio con ese ID,
 * 0 si encontro el ID con el campo isEmpty OCUPADO y 1 si el ID corresponde a un Servicio dado de baja.
 */
int eServicio_buscarIndicePorId(eServicio aServicio[], int tamServicio, int id, int* indiceEncontrado)
{
	int retorno = -2; // error.
	int i;
	if (aServicio != NULL && tamServicio > 0 && indiceEncontrado != NULL)
	{
		retorno = -1; // No hay ningun Servicio con ese ID

		for (i = 0; i < tamServicio; i++)
		{
			if (aServicio[i].idServicio == id && aServicio[i].isEmpty == OCUPADO)
			{
				*indiceEncontrado = i;
				retorno = 0; // Servicio ocupado
				break;
			}
			else
			{
				if(aServicio[i].idServicio == id && aServicio[i].isEmpty == BAJA)
				{
					*indiceEncontrado = i;
					retorno = 1; //Servicio dado de baja
					break;
				}
			}
		}
	}

	return retorno;
}

/**
 * @fn int eServicio_mostrarUno(eServicio*)
 * @brief funcion que va a mostrar un Servicio.
 * @param pServicio puntero qdel que vamos a recibir la informacion a mostrar.
 * @return retorna -1 error, o si salio bien.
 */
int eServicio_mostrarUno(eServicio* pServicio) //------------------------------------------------
{
	int retorno = -1; //error.
	if(pServicio != NULL)
	{
		retorno = 0; //bien.
		printf("Descripción: %-15s \t precio: %-.2f \t ID: %-4d\n", pServicio->descripcion,
																    pServicio->precio,
																    pServicio->idServicio);
	}//////////////////EJEMPLO////////////////////////////////////////////////////////////
	return retorno;
}

/**
 * @fn int eServicio_mostrarTodos(eServicio[], int)
 * @brief funcion que muestra todos los datos del array siempre y
 * cuando el campo isEmpty se encuentre lleno.
 * @param aServicio array que se va a recorrer para mostrar.
 * @param tamServicio tamaño del aServicio.
 * @return retorna -1 en caso de error y 0 si hay Gen para mostrar y 1 si no hay Servicio para mostrar.
 */
int eServicio_mostrarTodos(eServicio aServicio[], int tamServicio)
{
	int i;
	int retorno = -1;//no hay nada para mostrar
	int contador = 0;
	if (aServicio != NULL && tamServicio > 0)
	{
		puts("\nLista de servicios: ");
		for (i = 0; i < tamServicio; i++)
		{
			if (aServicio[i].isEmpty == OCUPADO)
			{
				eServicio_mostrarUno(&aServicio[i]);
				contador++;
			}
		}
	}
	if (contador > 0)
	{
		retorno = 0; //hay Servicio para mostrar.
		printf("\n\nTOTAL: %d\n", contador);
	}
	return retorno;
}

/**
 * @fn int eServicio_mostrarDadosDeBaja(eServicio[], int, int*)
 * @brief funcion que muestra los Servicio dados de baja.
 * @param aServicio array a recorrer en el que se va a buscar los Servicio dados de baja.
 * @param tamServicio tamaño del array aServicio.
 * @return retorna -1 en caso de error y 0 si hay Servicio para mostrar y 1 si no hay Servicio para mostrar.
 */
int eServicio_mostrarDadosDeBaja(eServicio aServicio[], int tamServicio)
{
	int i;
	int retorno = -1;//no hay nada para mostrar
	int contador = 0;
	if (aServicio != NULL && tamServicio > 0)
	{
		puts("Lista de servicios dados de baja");
		for (i = 0; i < tamServicio; i++)
		{
			if (aServicio[i].isEmpty == BAJA)
			{
				eServicio_mostrarUno(&aServicio[i]);
				contador++;
			}
		}
	}
	if (contador > 0)
	{
		retorno = 0; //hay Servicio dado de baja para mostrar.
	}
	else
	{
		retorno = 1; // no hay Servicio para mostrar
	}
	return retorno;
}

/**
 * @fn int eServicio_buscarIdMaximo(eServicio[], int, int*).
 * @brief funcion que busca el ID maximo de un array entre los que tienen el campo isEmpty OCUPADO.
 * @param aServicio array a recorrer y encontrar el mayor ID.
 * @param tamServicio tamaño del array aServicio.
 * @param idMaximo puntero que guarda como valor el id máximo encontrado.
 * @return retorna -1 en caso de error y 0 si se encontro el ID maximo.
 */
int eServicio_buscarIdMaximo(eServicio aServicio[], int tamServicio, int* idMaximo)
{
	int i;
	int retorno = -1;
	if(aServicio != NULL && idMaximo !=NULL)
	{
		for(i=0; i<tamServicio; i++)
		{
			if((i == 0 || aServicio[i].idServicio > *idMaximo) && aServicio[i].isEmpty == OCUPADO)
			{
				*idMaximo = aServicio[i].idServicio;
				retorno= 0;
			}
		}
	}
	return retorno;
}


//ABM
/**
 * @fn int eServicio_cargarDatos(eServicio*)
 * @brief funcion que pide los datos a cargar y los verifica.
 * @param pServicio puntero en el que se van a guardar los valores obtenidos.
 * @return retorna -1 en caso de error y 0 si salio bien.
 */
int eServicio_cargarDatos(eServicio* pServicio)
{
	int retorno = -1;
	if(pServicio != NULL)
	{

		if(!utn_pedirAlfabetico(pServicio->descripcion, "Ingrese nombre: ", "Error.\n", 2) &&
		!utn_pedirFlotante(&pServicio->precio, "Ingrese precio", "Error.", 0, 99999999, 2, 1))
		{
			 retorno = 0;
		}

	}
	return retorno;
}
/**
 * @fn int eServicio_modificarUno(eServicio*)
 * @brief funcion que modifica los datos requeridos.
 * @param pServicio Servicio que va a ser modificado por algun motivo.
 * @return retorna -1 en caso de error, 0 modificacion exitosa.
 */
int eServicio_modificarUno(eServicio* pServicio)
{
	int retorno = -1;
	int respuesta;
	int seguir;
	do
	{
		printf("\n\n\tMODIFICAR: \n\n1_Descripción.\n2_Precio.\n3_Modificación terminada.");
		if(!utn_pedirEntero(&respuesta, "\n\nIngrese la opción que desea realizar: ", "\nError", 1, 3, 2, 1))
		{
			switch(respuesta)

			{
				case 1: //Descripcion
					utn_pedirAlfabetico(pServicio->descripcion, "Ingrese la descripcion: ", "Error", 2);
					seguir=0;
				break;
				case 2: //precio
					utn_pedirFlotante(&pServicio->precio, "Ingrese precio: ", "Error", 0, 1000000, 2, 1);
					seguir = 0;
				break;
				case 3: // salir
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
 * @fn int eServicio_alta(eServicio[], int)
 * @brief funcion que verifica si el usuario desea guardar el alta y en ese caso crea el
 * alta con su ID, cambia el campo isEmpty a ocupado y guarda los datos en el indice correspondiente.
 * @param aServicio array en el que se gestiona el alta.
 * @param tamServicio tamaño del array aServicio.
 * @return retorna -2 si el array esta lleno, -1 si hubo un error, 0 si se dio de alta  orrrectamente
 * y 1 si la operación fue cancelada.
 */
int eServicio_alta(eServicio aServicio[], int tamServicio)
{
	int retorno = -1; //ERROR
	eServicio auxServicio;
	int indice;
	if(aServicio != NULL && tamServicio > 0)
	{
		indice = eServicio_obtenerIndiceLibre(aServicio, tamServicio);

		if (indice > -1 && (!eServicio_cargarDatos(&auxServicio)))
		{

			if(utn_verificar("¿Desea guardar los cambios[s/n]?", "Error", 2) == 0)
			{
				auxServicio.idServicio = eServicio_obtenerID();
				auxServicio.isEmpty = OCUPADO;
				aServicio[indice] = auxServicio;
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
				retorno = -2; //aServicio lleno
			}
		}
	}

	return retorno;
}
/**
 * @fn int eServicio_baja(eServicio[], int)
 * @brief funcion que da de baja pidiendo el ID correspondiente
 * al Servicio que se desea dar de baja.
 * @param aServicio array en el que se va a gestionar la baja logica.
 * @param tamServicio tamaño del array aServicio.
 * @return retorna-2 si hubo error, -1 si ID no existe, 0 si se
 * realizo la baja, 1 si el Servicio ya se habia dado de baja y 2 si la operación fue cancelada.
 */
int eServicio_baja(eServicio aServicio[], int tamServicio)
{
	int retorno = -2; //ERROR
	int idServicio;
	int indice;
	int idMaximo;
	int respuesta;
	eServicio buffer;

	int flag = 0;
	if (eServicio_mostrarTodos(aServicio, tamServicio)==0)
	{
		flag = 1;
	}
	if (flag)
	{
		eServicio_buscarIdMaximo(aServicio, tamServicio, &idMaximo);
		if(utn_pedirEntero(&idServicio, "\nIngrese el ID del Servicio que quiere dar de baja: \n", "\nError. \n", 1, idMaximo, 2, 1)==0)
		{

			respuesta = eServicio_buscarIndicePorId(aServicio, tamServicio, idServicio, &indice);
			switch (respuesta)
			{
				case -2: // ERROR.
					retorno = -2;
				break;
				case 0: //OCUPADO
					buffer = aServicio[indice];
					eServicio_mostrarUno(&buffer);
					if(utn_verificar("\n¿Desea dar de baja este Servicio [s/n]?", "\nError", 2)==0)
					{
						aServicio[indice].isEmpty = BAJA; //baja logica.
						retorno = 0; //BAJA REALIZADA.
					}
					else
					{
						retorno = 2; // operacion cancelada
					}
				break;
				case 1: //BAJA
					retorno = 1; // Servicio YA DADO DE BAJA
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
 * @fn int eServicio_Modificacion(eServicio[], int)
 * @brief funcion en la que corrobora si el ID ingresado es corecto para luego realizar la
 * modificacion y una vez confirmada la accion se hace los cambios.
 * @param aServicio array en el que se busca el indice del ID para realizar la modificacion deseada.
 * @param tamServicio tamaño del array aServicio.
 * @return retorna -2 en caso de error, -1 si el ID no existe, 0 si se realizo la modificación
 * y 1 si el Servicio ya estaba dado de baja y 2 si la operacion fue cancelada.
 */
int eServicio_modificacion(eServicio aServicio[], int tamServicio)
{
	int retorno = -2; //ERROR;
	int idServicio;
	int indice;
	int respuesta;
	int idMaximo;
	int flag = 0;
	eServicio auxiliar;
	if(aServicio != NULL && tamServicio > 0)
	{
		if (eServicio_mostrarTodos(aServicio, tamServicio)==0)
		{
			flag = 1;
		}
		if (flag)
		{
			eServicio_buscarIdMaximo(aServicio, tamServicio, &idMaximo);
			if(!utn_pedirEntero(&idServicio, "\ningrese el ID del Servicio que quiere modificar", "\nError", 1, idMaximo, 2, 1))
			{
				respuesta = eServicio_buscarIndicePorId(aServicio, tamServicio, idServicio, &indice);
				switch (respuesta)
				{
					case -2: //ERROR
						retorno = -2;
					break;
					case 0: //OCUPADO
						auxiliar = aServicio[indice];
						eServicio_mostrarUno(&auxiliar);
						eServicio_modificarUno(&auxiliar);
						if(!utn_verificar("\n¿Desea confirmas la modificación?[s/n]?\n", "nError", 2))
						{
							aServicio[indice]= auxiliar;
							retorno = 0; //MODIFICADO CORRECtamServicioENTE.
						}
						else
						{
							retorno = 2; // modificacion cancelada
						}
					break;
					case 1: //BAJA
						retorno = 1; // Servicio  DADO DE BAJA
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

