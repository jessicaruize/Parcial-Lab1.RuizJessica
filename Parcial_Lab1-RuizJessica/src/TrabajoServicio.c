/*
 * TrabajoServicio.c
 *
 *  Created on: 17 may. 2021
 *      Author: jessica
 */



#include"TrabajoServicio.h"

/**
 * @fn void mostrarMenu()
 * @brief funcion que muestra el menu de opciones.
 */
int eConjuntos_menu(int* opcion)
{
	int retorno;
	printf("\nMENU: \n1_Alta.\n2_Baja.\n3_Modificación\n4_Listado trabajos ordenados por año.\n5_Lista de Servicios.\n6_Total en pesos de los servicios prestados.\n"
		   "7_Listado de todos los trabajos ordenados por marca de la bicicleta.\n8_El o los servicios con más trabajos realizados.\n9_Listado de servicios con los "
		   "datos de las bicicletas que se lo realizaron.\n10_La cantidad de biciletas de color Rojo que realizaron un servicio  elegido por el usuario.\n0_Salir.\n");
	if(!utn_pedirEntero(opcion, "\nIngrese el numero correstpondiente a la acción que desea realizar: \n", "Error.\n", 0, 10, 2, 1))
	{
		retorno = 0;
	}
	return retorno;
}

/**
 * @fn int eConjuntos_cargarDatos(eTrabajo*, eServicio[], int)
 * @brief funcion que carga los datos requeridos para gestionar el alta
 * @param pTrabajo puntero en el que se van a cargar los datos.
 * @param aServicio array en el que se va a buscar unos datos para ser mostrados
 * y el usuario pueda elegir en base a eso, el servicio.
 * @param tamServicio tamaño del array aServicio
 * @return retorna -1 en caso de error y 0 si no hubo error.
 */
int eConjuntos_cargarDatos(eTrabajo* pTrabajo, eServicio aServicio[], int tamServicio, eBicicleta aBicicleta[], int tamBicicleta)
{
	int retorno = -1;
	int idMaximoServicio;
	int idMaximoBicicleta;
	int indiceServicio;
	int indiceBicicleta;
	if((pTrabajo != NULL) && (aServicio != NULL)&& tamServicio > 0 && aBicicleta != NULL && tamBicicleta > 0)
	{
		eBicicleta_mostrarTodos(aBicicleta, tamBicicleta);
		eBicicleta_buscarIdMaximo(aBicicleta, tamBicicleta, &idMaximoBicicleta);
		if(!utn_pedirEntero(&pTrabajo->idBicicleta, "Ingrese el ID de la bicicleta: ", "Error; ingrese ID de la bicicleta", 25, idMaximoBicicleta, 2, 1) &&
			!eBicicleta_buscarIndicePorId(aBicicleta, tamBicicleta, pTrabajo->idBicicleta, &indiceBicicleta))
		{
			pTrabajo->fecha = eTrabajo_pedirFecha("\nIngrese la fecha: \n", "Error.", 2, 2000, 2021);
			eServicio_mostrarTodos(aServicio, tamServicio);
			eServicio_buscarIdMaximo(aServicio, tamServicio, &idMaximoServicio);
			if(!utn_pedirEntero(&pTrabajo->idServicio, "\nIngrese el ID del servicio: \n", "\nError, ID no existe.\n", 1, idMaximoServicio, 2, 1) &&
			   !eServicio_buscarIndicePorId(aServicio, tamServicio, pTrabajo->idServicio, &indiceServicio))
			{
				retorno = 0;
			}
		}
	}
	return retorno;
}

/**
 * @fn int eConjuntos_alta(eTrabajo[], int, eServicio[], int)
 * @brief funcion que genera la alta lógica y asigna un ID, una vez
 * confirmada la accion de alta.
 * @param aTrabajo array en el que se busca el indice libre y se genera el alta.
 * @param tamTrabajo tamaño del array aTrabajo.
 * @param aServicio array que sirve para mostrar los datos de los servicios que
 * hay, para que el usuario pueda elegir uno y corroborar que no se ingresen datos incorrectos.
 * @param tamServicio tamaño del array aServicio
 * @return
 */
int eConjuntos_alta(eTrabajo aTrabajo[], int tamTrabajo, eServicio aServicio[], int tamServicio, eBicicleta aBicicleta[], int tamBicicleta)
{
	int retorno = -1; //ERROR
	eTrabajo auxTrabajo;
	int indice;
	if(aTrabajo != NULL && tamTrabajo > 0 && aServicio != NULL && tamServicio > 0 && aBicicleta != NULL && tamBicicleta > 0)
	{
		indice = eTrabajo_obtenerIndiceLibre(aTrabajo, tamTrabajo);

		if (indice > -1)
		{
			if(!eConjuntos_cargarDatos(&auxTrabajo, aServicio, tamServicio, aBicicleta, tamBicicleta))
			{
				if(utn_verificar("\n¿Desea guardar los cambios[s/n]?\n", "Error", 2) == 0)
				{
					auxTrabajo.idTrabajo = eTrabajo_obtenerID();
					auxTrabajo.isEmpty = OCUPADO;
					aTrabajo[indice] = auxTrabajo;
					retorno = 0; //se dio de alta satisfactoriamente
				}
				else
				{
					retorno = 1; //Operacion cancelada
				}
			}
			else
			{
				retorno = -3; //datos mal ingresados
			}
		}
		else
		{
			if(indice == -2)
			{
				retorno = -2; //aTrabajo lleno.
			}
		}
	}

	return retorno;
}

/**
 * @fn int eConjuntos_mostrarUno(eTrabajo*, eServicio[], int)
 * @brief función que muestra un trabajo con los datos del servicio
 * @param pTrabajo puntero del que vamos a mostrar los datos
 * @param aServicio array en el que se va a buscar el servicio correspondiente para mostrarlo.
 * @param tamServicio tamaño del array aServicio
 * @return retorna -1 en caso de error y 0 si no hubo error.
 */
int eConjuntos_mostrarUno(eTrabajo* pTrabajo, eServicio aServicio[], int tamServicio, eBicicleta aBicicleta[], int tamBicicleta)
{
	int retorno = -1; //error.
	int indiceServicio;
	int indiceBicicleta;

	if((pTrabajo != NULL) && (aServicio != NULL) && (tamServicio > 0) && (aBicicleta != NULL) && (tamBicicleta > 0))
	{
		retorno = 0; //bien.
		eServicio_buscarIndicePorId(aServicio, tamServicio, pTrabajo->idServicio, &indiceServicio);
		eBicicleta_buscarIndicePorId(aBicicleta, tamBicicleta, pTrabajo->idBicicleta, &indiceBicicleta);
		printf("ID trabajo: %-4d \t ID Bicicleta: %-4d \t Marca de la bicicleta: %-15s \t Rodado de la bicicleta: %-4d  \tColor: %-15s\t "
			   "\nID servicio: %-4d ""\t Descripción: %-15s \t Precio: %-.2f \t Fecha de trabajo: %d/%d/%d\n\n", pTrabajo->idTrabajo,
																											  	 pTrabajo->idBicicleta,
																												 aBicicleta[indiceBicicleta].marcaBicicleta,
																												 aBicicleta[indiceBicicleta].rodadoBicicleta,
																												 aBicicleta[indiceBicicleta].color,
																												 pTrabajo->idServicio,
																												 aServicio[indiceServicio].descripcion,
																												 aServicio[indiceServicio].precio,
																												 pTrabajo->fecha.dia,
																												 pTrabajo->fecha.mes,
																												 pTrabajo->fecha.anio);
	}
	return retorno;
}

/**
 * @fn int eConjuntos_mostrarTodos(eTrabajo[], int, eServicio[], int)
 * @brief funcion que muestra todos los trabajos con los respectivos servicios.
 * @param aTrabajo array a recorrer en el que se va a buscar el campo isEmpty ocupado para ser mostrar.
 * @param tamTrabajo tamaño del array aTrabajo.
 * @param aServicio array del que se van a tomar los datos para mostrar el servicio que corresponde.
 * @param tamServicio tamaño del array aServicio.
 * @return retorna -1 en caso de error y 0 si hay para mostrar al menos un trabajo.
 */
int eConjuntos_mostrarTodos(eTrabajo aTrabajo[], int tamTrabajo, eServicio aServicio[], int tamServicio, eBicicleta aBicicleta[], int tamBicicleta)
{
	int i;
	int retorno = -1;//no hay nada para mostrar
	int contador = 0;
	if (aTrabajo != NULL && aServicio != NULL && tamTrabajo > 0 && tamServicio > 0 && aBicicleta != NULL && tamBicicleta > 0)
	{
		for (i = 0; i < tamTrabajo; i++)
		{
			if (aTrabajo[i].isEmpty == OCUPADO)
			{
				eConjuntos_mostrarUno(&aTrabajo[i], aServicio, tamServicio, aBicicleta, tamBicicleta);
				contador++;
			}
		}
	}
	if (contador > 0)
	{
		retorno = 0; //hay Trabajo para mostrar.
		printf("\n\nTOTAL: %d\n", contador);
	}

	return retorno;
}

/**
 * @fn int eConjuntos_baja(eTrabajo[], int, eServicio[], int)
 * @brief funcion en la que se va a gestionar la baja logica una vez confirmada la acción.
 * @param aTrabajo array que se va a usar para mostrar todos los trabajos así el usuario puede elegir el ID
 * correspondiente y ademas se va a usar para corroborar que el ID ingresado es de un trabajo con el campo isEmpty ocupado.
 * @param tamTrabajo tamaño del array atrabajo.
 * @param aServicio array que se usa para mostrar los servicios que corresponden a cada trabajo.
 * @param tamServicio tamaño del array aServicio.
 * @return retorna -3 si no hay ningun trabajo cargado, -2 en caso de error, -1 si el ID no existe,
 * 0 si se realizo la baja logica correctamente, 1 si el trabajo ya fue dado de baja o 2 si se cancelo la operación.
 */
int eConjuntos_baja(eTrabajo aTrabajo[], int tamTrabajo, eServicio aServicio[], int tamServicio, eBicicleta aBicicleta[], int tamBicicleta)
{
	int retorno = -2; //ERROR
	int idTrabajo;
	int indice;
	int idMaximo;
	int respuesta;
	eTrabajo buffer;
	int flag = 0;
	if(aTrabajo != NULL && tamTrabajo > 0 && aServicio != NULL && tamServicio > 0 && aBicicleta != NULL && tamBicicleta > 0)
	{
		if (!eConjuntos_mostrarTodos(aTrabajo, tamTrabajo, aServicio, tamServicio, aBicicleta, tamBicicleta))
		{
			flag = 1;
		}
		if (flag)
		{
			eTrabajo_buscarIdMaximo(aTrabajo, tamTrabajo, &idMaximo);
			if(utn_pedirEntero(&idTrabajo, "\nIngrese el ID del Trabajo que quiere dar de baja: \n", "\nError. \n", 1, idMaximo, 2, 1)==0)
			{

				respuesta = eTrabajo_buscarIndicePorId(aTrabajo, tamTrabajo, idTrabajo, &indice);
				switch (respuesta)
				{
					case -2: //ERROR
						retorno = -2;
					break;
					case 0: //OCUPADO
						buffer = aTrabajo[indice];
						eConjuntos_mostrarUno(&buffer, aServicio, tamServicio, aBicicleta, tamBicicleta);
						//eTrabajo_mostrarUno(&buffer);
						if(utn_verificar("\n¿Desea dar de baja este Trabajo [s/n]?", "\nError", 2)==0)
						{
							aTrabajo[indice].isEmpty = BAJA; //baja logica.
							retorno = 0; //BAJA CORRECTAMENTE.
						}
						else
						{
							retorno = 2; //baja cancelada
						}
					break;
					case 1: //BAJA
						retorno = 1; // Trabajo YA DADO DE BAJA
					break;
				}
			}
			else
			{
				retorno = -1; // ID no existe.
			}
		}
		else
		{
			retorno = -3; // no hay ningun Trabajo
		}
	}

	return retorno;
}

/**
 * @fn int eConjuntos_modificarUno(eTrabajo*, eServicio[], int)
 * @brief funcion que va a permitir modificar datos del trabajo.
 * @param pTrabajo puntero que va a ser modificado
 * @param aServicio array del que vamos a mostrar los servicios disponibles a elegir a travez del ID
 * para modificar el servicio actual y va a permitir corroborar si el ID es correcto.
 * @param tamServicio tamaño del array aServicio
 * @return retorna -1 en caso de error y 0 si no hubo error.
 */
int eConjuntos_modificarUno(eTrabajo* pTrabajo, eServicio aServicio[], int tamServicio, eBicicleta aBicicleta[], int tamBicicleta)
{
	int retorno = -1; //ERROR.
	int idMaximoServicio;
	int idMaximoBicicleta;
	int respuesta;
	int indiceServicio;
	int indiceBicileta;
	int seguir;

	if(pTrabajo != NULL && aServicio != NULL && tamServicio > 0 && aBicicleta != NULL && tamBicicleta > 0)
	{
		do
		{
			printf("\n\n\tMODIFICAR: \n\n1_Marca de la bicicleta.\n2_Servicio.\n3_Modificación terminada.");
			if(!utn_pedirEntero(&respuesta, "\n\nIngrese la opción que desea realizar: ", "\nError", 1, 3, 2, 1))
			{
				switch(respuesta)

				{
					case 1: //marca
						eBicicleta_mostrarTodos(aBicicleta, tamBicicleta);
						eBicicleta_buscarIdMaximo(aBicicleta, tamBicicleta, &idMaximoBicicleta);
						utn_pedirEntero(&pTrabajo->idBicicleta, "Ingrese el ID de la bicicleta: ", "Error, ingrese el id de la bicicleta: ", 25, idMaximoBicicleta, 2, 1);
						if(!eBicicleta_buscarIndicePorId(aBicicleta, tamBicicleta, pTrabajo->idBicicleta, &indiceBicileta))
						{
							seguir = 1;
						}
					break;
					case 2: //servicio
						eServicio_mostrarTodos(aServicio, tamServicio);
						eServicio_buscarIdMaximo(aServicio, tamServicio, &idMaximoServicio);
						utn_pedirEntero(&pTrabajo->idServicio, "\nIngrese el ID del servicio: \n", "\nError, ingrese un ID valido.\n", 1, idMaximoServicio, 2, 1);
						if(!eServicio_buscarIndicePorId(aServicio, tamServicio, pTrabajo->idServicio, &indiceServicio))
						{
							 seguir = 1;
						}
					break;
					case 3: // salir
						if(!utn_verificar("¿Modificación terminada? [s/n]", "Error", 2))
						{
							seguir = 0;
							retorno = 0;
						}
					break;
				}
			}

		}while(seguir != 0);
	}

	return retorno;
}

/**
 * @fn int eConjuntos_modificacion(eTrabajo[], int, eServicio[], int)
 * @brief función en la que se va a cargar los datos modificados una vez que se confirme la operación.
 * @param aTrabajo array que vamos a  usar para mostrar los trabajos asi el usuario puede elegir cual modificar,
 * se va a corroborar que el ID elegido sea correcto, y en caso de corfirmacion dicho array en el indice indicado sera modificado
 * @param tamTrabajo tamaño del arrat aTrabajo
 * @param aServicio array que vamos a usar para mostrar los servicios y corroborar que el ID es correcto para modificar el servicio.
 * @param tamServicio tamaño del array aServicio
 * @return retorna -4 si no hay ningun trabajo, -3 si el ID no existe, - 2 en caso de error, -1 si la modificacion fue cancelada,
 * 0 si se modifico correctamente y 1 si el trabajo elegido es un trabajo que anteriormente fue dado de baja.
 */
int eConjuntos_modificacion(eTrabajo aTrabajo[], int tamTrabajo, eServicio aServicio[], int tamServicio, eBicicleta aBicicleta[], int tamBicicleta)
{
	int retorno = -2; //ERROR;
	int idTrabajo;
	int indice;
	int respuesta;
	int idMaximo;
	int flag = 0;
	eTrabajo auxiliar;
	if(aTrabajo != NULL && tamTrabajo > 0 && aServicio != NULL && tamServicio > 0 && aBicicleta != NULL && tamBicicleta > 0)
	{

		if (eConjuntos_mostrarTodos(aTrabajo, tamTrabajo, aServicio, tamServicio, aBicicleta, tamBicicleta)==0)
		{
			flag = 1;
		}
		if (flag)
		{
			eTrabajo_buscarIdMaximo(aTrabajo, tamTrabajo, &idMaximo);
			if(!utn_pedirEntero(&idTrabajo, "\ningrese el ID del Trabajo que quiere modificar", "\nError, ID mal ingresado.", 1, idMaximo, 2, 1))
			{
				respuesta = eTrabajo_buscarIndicePorId(aTrabajo, tamTrabajo, idTrabajo, &indice);
				switch (respuesta)
				{//////////////////////////////////////////////////////////////////////////////
					case -2: //ERROR
						retorno = -2;
					break;
					case 0: //OCUPADO
						auxiliar = aTrabajo[indice];
						eConjuntos_mostrarUno(&auxiliar, aServicio, tamServicio, aBicicleta, tamBicicleta);
						eConjuntos_modificarUno(&auxiliar, aServicio, tamServicio, aBicicleta, tamBicicleta);
						if(!utn_verificar("\n¿Desea confirmas la modificación?[s/n]?\n", "nError", 2))
						{
							aTrabajo[indice]= auxiliar;
							retorno = 0; //MODIFICADO CORRECTAMENTE.
						}
						else
						{
							retorno = -1; // MODIFICACION CANCELADA
						}
					break;
					case 1: //BAJA
						retorno = 1; // Trabajo  DADO DE BAJA
					break;
				}
			}
			else
			{
				retorno = -3; //ID no existe.
			}
		}
		else
		{
			retorno = -4; //no hay Trabajo para modificar.
		}
	}
	return retorno;
}
/**
 * @fn int eTrabajo_SortAnio(eTrabajo[], int)
 * @brief  funcion que ordena por año de menor a mayor y en caso de tener el mismo año ordena por marca.
 * @param aTrabajo array a ser ordenado
 * @param tamTrabajo tamaño del array aTrabajo.
 * @return retorna -1 en caso de error y 0 si no hubo error.
 */
int eConjuntos_SortAnio(eTrabajo aTrabajo[], int tamTrabajo, eBicicleta aBicicleta[], int tamBicicleta)
{
	int retorno = -1;
	int i;
	int j;
	eTrabajo aux;
	if(aTrabajo != NULL && tamTrabajo > 0 && aBicicleta != NULL && tamBicicleta > 0)
	{
		retorno = 0;
		int indiceBicicleta1;
		int indiceBicicleta2;
		for (i = 0; i < tamTrabajo - 1; i++)
			{
				for (j = i + 1; j < tamTrabajo; j++)
				{
					if(aTrabajo[i].fecha.anio > aTrabajo[j].fecha.anio)
					{
						aux = aTrabajo[i];
						aTrabajo[i] = aTrabajo[j];
						aTrabajo[j] = aux;
					}
					if(aTrabajo[i].fecha.anio == aTrabajo[j].fecha.anio)
					{
						eBicicleta_buscarIndicePorId(aBicicleta, tamBicicleta, aTrabajo[i].idBicicleta, &indiceBicicleta1);
						eBicicleta_buscarIndicePorId(aBicicleta, tamBicicleta, aTrabajo[j].idBicicleta, &indiceBicicleta2);
						if(strncmp(aBicicleta[indiceBicicleta1].marcaBicicleta, aBicicleta[indiceBicicleta2].marcaBicicleta, MAX_CHARS_CADENAS)>0)
						{
							aux = aTrabajo[i];
							aTrabajo[i] = aTrabajo[j];
							aTrabajo[j] = aux;
						}
					}
				}
			}
	}
	return retorno;
}


/**
 * @fn int econjuntos_mostrarTotalPesos(eTrabajo[], int, eServicio[], int, float*)
 * @brief funcion que acumula todos los precios de los servicios prestados para mostrar el total.
 * @param aTrabajo array en el que se va a buscar todos los trabajos hechos,
 * @param tamTrabajo tamaño del array aTrabajo.
 * @param aServicios array del que se toma los precios de cada servicio prestado.
 * @param tamServicios tamaño del array aServicio.
 * @param totalPesos puntero que va a guardar el valor total de los precios acumulados por todos los trabajos realizados.
 * @return retorna -1 en caso de error y 0 si hay pesos acumulados.
 */
int econjuntos_mostrarTotalPesos(eTrabajo aTrabajo[], int tamTrabajo, eServicio aServicios[], int tamServicios, float* totalPesos)
{
	int retorno = -1; //error.
	float acumulador = 0;
	int i;
	int j;
	if(aTrabajo != NULL && tamTrabajo > 0 && aServicios != NULL && tamServicios > 0)
	{
		for(i=0; i<tamTrabajo; i++)
		{
			if(aTrabajo[i].isEmpty == OCUPADO)
			{
				for(j=0; j< tamServicios; j++)
				{
					if(aServicios[j].isEmpty == OCUPADO)
					{
						if(aTrabajo[i].idServicio==aServicios[j].idServicio)
						{
							acumulador += aServicios[j].precio;
							retorno = 0; // hay para mostrar

						}
					}
				}
			}
		}
	}
	*totalPesos = acumulador;
	return retorno;
}


int eConjuntos_OrdenMarca(eTrabajo aTrabajo[], int tamTrabajo, eBicicleta aBicicleta[], int tamBicicleta)
{
	int retorno = -1;
	int i;
	int j;
	eTrabajo aux;
	int indiceBicicleta1;
	int indiceBicicleta2;

	if(aBicicleta != NULL && tamBicicleta > 0 && aTrabajo != NULL && tamTrabajo > 0)
	{
		retorno = 0;
		for(i=0; i<tamTrabajo; i++)
		{
			for(j=0; j<tamBicicleta; j++)
			{
				eBicicleta_buscarIndicePorId(aBicicleta, tamBicicleta, aTrabajo[i].idBicicleta, &indiceBicicleta1);
				eBicicleta_buscarIndicePorId(aBicicleta, tamBicicleta, aTrabajo[j].idBicicleta, &indiceBicicleta2);
				if(strncmp(aBicicleta[indiceBicicleta1].marcaBicicleta, aBicicleta[indiceBicicleta2].marcaBicicleta, MAX_CHARS_CADENAS) < 0)
				{
					aux = aTrabajo[i];
					aTrabajo[i] = aTrabajo[j];
					aTrabajo[j] = aux;
				}

			}
		}
	}

	return retorno;
}


//El o los servicios con más trabajos realizados.
int eConjuntos_ServiciosConMasTrabajos(eServicio aServicio[], int tamServicio, eTrabajo aTrabajo[], int tamTrabajo)
{
	int retorno = -1;
	int i;
	int j;
	int k;
	int idMayor;
	int indiceMayor;
	int flag = 0;
	eAuxiliar aAuxiliar[tamServicio];


	if(aServicio != NULL && tamServicio > 0 && aTrabajo != NULL && tamTrabajo > 0)
	{
		for(k=0; k<tamServicio; k++)
		{
			aAuxiliar[k].contador = 0;
		}

		for(i=0; i<tamTrabajo; i++)
		{
			for(j=0; j<tamServicio; j++)
			{
				if(aTrabajo[i].idServicio == aServicio[j].idServicio)
				{
					aAuxiliar[j].contador ++;
				}
			}
			if(flag == 0 || aAuxiliar[j].contador > aAuxiliar[j-1].contador)
			{
				flag = 1;
				idMayor = aServicio[i].idServicio;
			}
		}
	}
	if(flag == 1)
	{
		eServicio_buscarIndicePorId(aServicio, tamServicio, idMayor, &indiceMayor);
		eServicio_mostrarUno(&aServicio[indiceMayor]);
	}

	return retorno;
}



//Listado de servicios con los datos de las bicicletas que se lo realizaron.
int Econjuntos_listadoServiciosBicicletas(eServicio aServicio[], int tamServicio, eBicicleta aBicicleta[], int tamBicicleta, eTrabajo aTrabajo[], int tamTrabajo)
{
	int retorno = -1;
	int i;
	int j;
	if(aServicio != NULL && tamServicio>0 && aBicicleta != NULL && tamBicicleta >0 && aTrabajo != NULL && tamTrabajo > 0)
	for(i=0; i<tamTrabajo;i++)
	{

	}


	return retorno;
}






