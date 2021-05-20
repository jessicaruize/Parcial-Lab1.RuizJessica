/*
 * pedir_valores.c
 *
 *  Created on: 15 abr. 2021
 *      Author: jessica
 */

#include "pedir_valores.h"

static int pedirCadena(char cadena[], int longitud);
static int esEntero(char cadena[], int limite);
static int pedirEntero (int* pResultado);
static int esFlotante(char cadena[], int limite);
static int pedirFlotante (float* pResultado);
static int esAlfabetico(char cadena[], int limite);
static int pedirAlfabetico(char cadena[], int longitud);
static int esAlfabeticoEspacio(char cadena[], int limite);
static int pedirAlfabeticoEspacio(char cadena[], int longitud);
static int esAlfanumerico(char cadena[], int limite);
static int pedirAlfanumerico(char cadena[], int longitud);
static int esAlfanumericoEspacio(char cadena[], int limite);
static int pedirAlfanumericoEspacio(char cadena[], int longitud);

static int esVeificable(char cadena[], int limite);
static int verificar(char cadena[], int longitud);


/*
 * @fn static int pedirCadena(char[], int)
 * @brief funcion que recibe un array y un entero que es el tamaño de esa cadena
 * corrige errores que se puede cometer con fgets.
 * @param cadena[] array recibido en el cual se envia la informacion una vez depurada.
 * @param longitud variable que trae el valor del tamaño del array cadena.
 * @return retorna: -1 en caso de que se encuentre un error, 1 si es verdadero y o si es falso.
 */
static int pedirCadena(char cadena[], int longitud) //ajustes de fgets, no se pasa
{
	int retorno = -1; //salio mal.
	char buffer[500]; //__Ver después con memoria dinámica.___
	if(cadena != NULL && longitud > 0)
	{
		__fpurge(stdin);
		if(fgets(buffer, sizeof(buffer), stdin) != NULL) //(espacio de memoria donde guarda el resultado - cantidad  de caracteres que carga (hasta \n - \0) - de donde saca la inf.
		{//fgets devuelve NULL si no salio bien. stdin:terminal. sizeof: macro del precompilador- calcula el tamaño que ocupa en memoria la variable de la funcion(char:1)
			if(buffer[strnlen(buffer, sizeof(buffer))-1] == '\n')// puede no aparecer el \n si se pasa de la longitud
			{
				buffer[strnlen(buffer, sizeof(buffer))-1] = '\0'; //strlen guarda el salto de linea.
			}
			if(strnlen(buffer, sizeof(buffer)) <= longitud)
			{
				strncpy(cadena, buffer, longitud);
				retorno = 0;  //salio todo bien
			}
		}
	}
	return retorno;
}

/*
 * @fn static int esEntero(char[], int)
 * @brief funcion que recibe un array y un entero que es el tamaño de esa cadena
 * recorre el array corroborando que cada indice tenga un número.(y le permite al indice 0 tener un + o -)
 * @param cadena[] array a comparar
 * @param limite valor del tamaño del array recibido.
 * @return retorna: -1 en caso de que se encuentre un error, 1 si es verdadero y o si es falso.
 */
static int esEntero(char cadena[], int limite) //corrobora los indices para corroborar que sea un numero.
{
	int retorno = -1; //ERROR
	int i;
	if(cadena != NULL && limite > 0)
	{
		retorno = 1; // VERDADERO
		for(i=0; (i<limite) && (cadena[i] != '\0'); i++)//no llega al límite ni pasa el \0.
		{
			if((i == 0) && (cadena[i] == '-' || cadena[i] == '+'))//permito ej: -12 || +12 (signo  cadena[0])
			{
				continue; //vuelve a iterar al for(salta lo siguiente. en este caso el if).
			}
			if(cadena[i] > '9' || cadena[i] < '0')
			{
				retorno = 0; //FALSO
				break;
			}
		}
	}
	return retorno;
}
/**
 * @fn static int pedirEntero (int* )
 * @brief funcion que toma un numero como texto para poder validar si es un numero con
 * pedirCadena y corrobora si isNumbre es verdadero.
 * @param pResultado es el puntero que devuelve el entero validado.
 * @return retorno que devuelve -1 si hubo error y 0 si salio todo bien.
 * @
 */
static int pedirEntero (int* pResultado)
{
	int retorno = -1; //ERROR
	char buffer[100];

	if(pResultado != NULL &&
	  pedirCadena(buffer, sizeof(buffer)) == 0 &&
	  esEntero(buffer, sizeof(buffer)))
	{
			retorno = 0; //salio BIEN.
			*pResultado = atoi(buffer); // atoi convierte a buffer en int
	}
	return retorno;
}
/**
 * @fn int utn_pedirEntero(int* , char* , char* , int , max, int , int)
 * @brief funcion que pide un entero, crea reintentos y tiene un minimo y maximo en caso de querer pedir dentro de un rango
 * @pResultado puntero que va a devolver el entero pedido.
 * @mensaje es el mensaje que pide el dato requerido.
 * @mensajeError es el mensaje en caso de que haya un error para indicarle al usuario que algo no esta bien.
 * @min es el minimo en caso de que el usuario tenga que ingresar enteros dentro de un rango.
 * @max es el maximo en caso de que el usuario tenga que ingresar enteros dentro de un rango.
 * @reintentos va a recibir el valor de la cantidad de veces que se va a poder intentar ingresar un dato válido.
 * @condicional se va a recibir 0 en caso de querer ignorar el rango o cualquier otro entero en caso de que no(ej:1).
 * @return retorna -1 si salio algo mal ó 0 si salio todo bien.
 */
int utn_pedirEntero(int* pResultado, char* mensaje, char* mensajeError, int min, int max, int reintentos, int condicional)
{
	int retorno = -1;//salio mal
  	int buffer;

	if(pResultado != NULL && mensaje != NULL && mensajeError != NULL && min <= max && reintentos >=0)
	{
		do
		{
			printf("%s", mensaje);
			if(condicional == 0) //no se toma en cuenta el min ni el max
			{
				if(pedirEntero(&buffer) == 0 )
				{
					*pResultado = buffer;
					retorno = 0; //salio bien
					break;
				}
			}
			else
			{
				if(pedirEntero(&buffer) == 0 &&
				  (buffer >= min) &&
				  (buffer <= max))
				{
					*pResultado = buffer;
					retorno = 0;
					break;
				}
			}
			reintentos --;
			printf("%s", mensajeError);
		}while(reintentos > -1);
	}
	return retorno;
}


/*
 * @fn static int esFlotante(char[], int)
 * @brief funcion que recibe un array y un entero que es el tamaño de esa cadena
 * recorre el array corroborando que cada indice tenga un número decimal.
 * (Le permite al indice 0 tener un mas(+) o menos(-), tambien que tenga un punto en cualquier indice).
 * @param cadena[] array a comparar
 * @param limite valor del tamaño del array recibido.
 * @return retorna: -1 en caso de que se encuentre un error, 1 si es verdadero y o si es falso.
 */
static int esFlotante(char cadena[], int limite)
{
	int retorno = -1; //ERROR
	int i;
	int contadorPuntos = 0;;
	if(cadena != NULL && limite > 0)
	{
		retorno = 1; // VERDADERO
		for(i=0; (i<limite) && (cadena[i] != '\0'); i++)//no llega al límite ni pasa el \0.
		{
			if((i == 0) && (cadena[i] == '-' || cadena[i] == '+'))//permito ej: -12 || +12 (signo  cadena[0])
			{
				continue; //vuelve a iterar al for(salta lo siguiente. en este caso el if).
			}
			if(cadena[i] > '9' || cadena[i] < '0')
			{
				if(cadena[i] == '.' && contadorPuntos == 0)
				{
					contadorPuntos++;
				}
				else
				{
					retorno = 0; //FALSO
					break;
				}
			}
		}
	}
	return retorno;
}
/**
 * @fn static int pedirFlotante (float* )
 * @brief funcion que toma un numero como texto para poder validar si es un numero decimal con
 * pedirCadena y corrobora si esFlotante es verdadero.
 * @param pResultado es el puntero que devuelve el numero decimal validado.
 * @return retorno que devuelve -1 si hubo error y 0 si salio todo bien.
 * @
 */
static int pedirFlotante (float* pResultado)
{
	int retorno = -1; //ERROR
	char buffer[50];

	if(pResultado != NULL &&
	  pedirCadena(buffer, sizeof(buffer)) == 0 &&
	  esFlotante(buffer, sizeof(buffer)))
	{
			retorno = 0; //salio BIEN.
			*pResultado = atof(buffer); // atof convierte a buffer en float
	}
	return retorno;
}
/**
 * @fn int utn_pedirFlotante(float* , char* , char* , float , float , int , int)
 * @brief funcion que pide un número decimal, crea reintentos y tiene un minimo y maximo en caso de querer pedir dentro de un rango
 * @pResultado puntero que va a devolver el decimal pedido.
 * @mensaje es el mensaje que pide el dato requerido.
 * @mensajeError es el mensaje en caso de que haya un error para indicarle al usuario que algo no esta bien.
 * @min es el minimo en caso de que el usuario tenga que ingresar numeros dentro de un rango.
 * @max es el maximo en caso de que el usuario tenga que ingresar numeros dentro de un rango.
 * @reintentos va a recibir el valor de la cantidad de veces que se va a poder reintentar ingresar un dato válido en caso de error.
 * @condicional se va a recibir 0 en caso de querer ignorar el rango o cualquier otro entero en caso de que no(ej:1).
 * @return retorna -1 si salio algo mal ó 0 si salio todo bien.
 */
int utn_pedirFlotante(float* pResultado, char* mensaje, char* mensajeError, float min, float max, int reintentos, int condicional)
{
	int retorno = -1;//salio mal
  	float buffer;

	if(pResultado != NULL && mensaje != NULL && mensajeError != NULL && min <= max && reintentos >=0)
	{
		do
		{
			printf("%s", mensaje);
			if(condicional == 0) //no se toma en cuenta el min ni el max
			{
				if(pedirFlotante(&buffer) == 0)
				{
					*pResultado = buffer;
					retorno = 0; //salio bien
					break;
				}
			}
			else
			{
				if(pedirFlotante(&buffer) == 0 &&
				  (buffer >= min) &&
				  (buffer <= max))
				{
					*pResultado = buffer;
					retorno = 0;
					break;
				}
			}
			reintentos --;
			printf("%s", mensajeError);
		}while(reintentos > -1);
	}
	return retorno;
}


/*
 * @fn static int esAlfabetico(char[], int)
 * @brief funcion que recibe un array y un entero que es el tamaño de esa cadena
 * recorre el array corroborando que cada indice tenga letras
 * @param cadena[] array a comparar
 * @param limite valor del tamaño del array recibido.
 * @return retorna: -1 en caso de que se encuentre un error, 1 si es verdadero y 0 si es falso.
 */
static int esAlfabetico(char cadena[], int limite)
{
	int retorno = -1; //ERROR
	int i;
	if(cadena != NULL && limite > 0)
	{
		retorno = 1; // VERDADERO
		for(i=0; (i<limite) && (cadena[i] != '\0'); i++)//no llega al límite ni pasa el \0.
		{
			if((cadena[i] < 'a' || cadena[i] > 'z') &&
			  (cadena[i] < 'A' || cadena[i] > 'Z'))
			{
				retorno = 0; //FALSO
				break;
			}
		}
	}
	return retorno;
}

/*
 * @fn static int pedirAlfabetico(char[], int)
 * @brief funcion que recibe un array y un entero que es el tamaño de esa cadena
 * y corrobora que no haya errores para poder copiar en cadena lo que guardo en el buffer.
 * @param cadena[] array que devuelve la palabra libre de errores
 * @param longitud valor del tamaño del array recibido.
 * @return retorna: -1 en caso de que se encuentre un error y 0 si salio todo bien.
 */
static int pedirAlfabetico(char cadena[], int longitud) //toma el numero como un texto, valida a que sea correcta las posiciones del array y lo devuelve como int.
{
	int retorno = -1; //ERROR
	char buffer[200];

	if(cadena != NULL &&
	  pedirCadena(buffer, sizeof(buffer)) == 0 &&
	  esAlfabetico(buffer, sizeof(buffer))&&
	  strnlen(buffer, sizeof(buffer)) < longitud)
	{
		strncpy(cadena, buffer, longitud);
		retorno = 0; //salio BIEN.
	}
	return retorno;
}
/**
 * @fn int utn_pedirAlfabetico(char[] , char* , char* , int)
 * @brief funcion que pide una palabra y crea reintentos
 * @cadena array recibido que va a guardar la palabra obtenida en caso que haya salido todo bien.
 * @mensaje es el mensaje que pide el dato requerido.
 * @mensajeError es el mensaje en caso de que haya un error para indicarle al usuario que algo no esta bien.
 * @reintentos va a recibir el valor de la cantidad de veces que se va a poder reintentar ingresar un dato válido en caso de error.
 * @return retorna -1 si salio algo mal ó 0 si salio todo bien.
 */
int utn_pedirAlfabetico(char cadena[], char* mensaje, char* mensajeError, int reintentos)
{
	int retorno = -1;
	char buffer[200];
	if(cadena != NULL && mensaje != NULL &&
	   mensajeError != NULL && reintentos > 0)
	{
		do
		{
			printf("%s", mensaje);
			if(pedirAlfabetico(buffer, sizeof(buffer)) == 0)
			{
				strncpy(cadena, buffer, sizeof(cadena));
				retorno = 0;
				break;
			}
			reintentos --;
			printf("%s", mensajeError);
		}while(reintentos > -1);
	}
	return retorno;
}

/*
 * @fn static int esAlfabeticoEspacio(char[], int)
 * @brief funcion que recibe un array y un entero que es el tamaño de esa cadena
 * recorre el array corroborando que cada indice tenga letras y/o espacios.
 * @param cadena[] array a comparar
 * @param limite valor del tamaño del array recibido.
 * @return retorna: -1 en caso de que se encuentre un error, 1 si es verdadero y 0 si es falso.
 */
static int esAlfabeticoEspacio(char cadena[], int limite)
{
	int retorno = -1; //ERROR
	int i;
	if(cadena != NULL && limite > 0)
	{
		retorno = 1; // VERDADERO
		for(i=0; (i<limite) && (cadena[i] != '\0'); i++)//no llega al límite ni pasa el \0.
		{
			if((cadena[i] != ' ') &&
			  (cadena[i] < 'a' || cadena[i] > 'z') &&
			  (cadena[i] < 'A' || cadena[i] > 'Z'))
			{
				retorno = 0; //FALSO
				break;
			}
		}
	}
	return retorno;
}
/*
 * @fn static int pedirAlfabetico(char[], int)
 * @brief funcion que recibe un array y un entero que es el tamaño de esa cadena
 * y corrobora que no haya errores para poder copiar en cadena lo que guardo en el buffer.
 * @param cadena[] array que devuelve la palabra libre de errores
 * @param longitud valor del tamaño del array recibido.
 * @return retorna: -1 en caso de que se encuentre un error y 0 si salio todo bien.
 */
static int pedirAlfabeticoEspacio(char cadena[], int longitud) //toma el numero como un texto, valida a que sea correcta las posiciones del array y lo devuelve como int.
{
	int retorno = -1; //ERROR
	char buffer[200];

	if(cadena != NULL &&
	  pedirCadena(buffer, sizeof(buffer)) == 0 &&
	  esAlfabeticoEspacio(buffer, sizeof(buffer))&&
	  strnlen(buffer, sizeof(buffer)) < longitud)
	{
		strncpy(cadena, buffer, longitud);
		retorno = 0; //salio BIEN.
	}
	return retorno;
}

/**
 * @fn int utn_pedirAlfabeticoEspacio(char[] , char* , char* , int)
 * @brief funcion que pide texto alfabetico y crea reintentos
 * @cadena array recibido que va a guardar las palabras obtenida en caso que haya salido todo bien.
 * @mensaje es el mensaje que pide el dato requerido.
 * @mensajeError es el mensaje en caso de que haya un error para indicarle al usuario que algo no esta bien.
 * @reintentos va a recibir el valor de la cantidad de veces que se va a poder reintentar ingresar un dato válido en caso de error.
 * @return retorna -1 si salio algo mal ó 0 si salio todo bien.
 */
int utn_pedirAlfabeticoEspacio(char cadena[], char* mensaje, char* mensajeError, int reintentos)
{
	int retorno = -1;
	char buffer[200];
	if(cadena != NULL && mensaje != NULL &&
	   mensajeError != NULL && reintentos > 0)
	{
		do
		{
			printf("%s", mensaje);
			if(pedirAlfabeticoEspacio(buffer, sizeof(buffer)) == 0)
			{
				strncpy(cadena, buffer, sizeof(cadena));
				retorno = 0;
				break;
			}
			reintentos --;
			printf("%s", mensajeError);
		}while(reintentos > -1);
	}
	return retorno;
}

/*
 * @fn static int esAlfanumerico(char[], int)
 * @brief funcion que recibe un array y un entero que es el tamaño de esa cadena
 * recorre el array corroborando que cada indice tenga letras o números.
 * @param cadena[] array a comparar
 * @param limite valor del tamaño del array recibido.
 * @return retorna: -1 en caso de que se encuentre un error, 1 si es verdadero y 0 si es falso.
 */
static int esAlfanumerico(char cadena[], int limite)
{
	int retorno = -1; //ERROR
	int i;
	if(cadena != NULL && limite > 0)
	{
		retorno = 1; // VERDADERO
		for(i=0; (i<limite) && (cadena[i] != '\0'); i++)
		{
			if((cadena[i] < 'a' || cadena[i] > 'z') &&
			   (cadena[i] < 'A' || cadena[i] > 'Z')&&
			   (cadena[i] < '0' || cadena[i] >'9'))
			{
				retorno = 0;
				break;
			}
		}
	}
	return retorno;
}

/*
 * @fn static int pedirAlfanumerico(char[], int)
 * @brief funcion que recibe un array y un entero que es el tamaño de esa cadena
 * y corrobora que no haya errores para poder copiar en cadena lo que guardo en el buffer.
 * @param cadena[] array que devuelve la palabra libre de errores
 * @param longitud valor del tamaño del array recibido.
 * @return retorna: -1 en caso de que se encuentre un error y 0 si salio todo bien.
 */
static int pedirAlfanumerico(char cadena[], int longitud)
{
	int retorno = -1; //ERROR
	char buffer[200];

	if(cadena != NULL &&
	  pedirCadena(buffer, sizeof(buffer)) == 0 &&
	  esAlfanumerico(buffer, sizeof(buffer))&&
	  strnlen(buffer, sizeof(buffer)) < longitud)
	{
		strncpy(cadena, buffer, longitud);
		retorno = 0; //salio BIEN.
	}
	return retorno;
}


/**
 * @fn int utn_pedirAlfanumerico(char[] , char* , char* , int)
 * @brief funcion que pide texto alfanumerico y crea reintentos
 * @cadena array recibido que va a guardar las palabras obtenida en caso que haya salido todo bien.
 * @mensaje es el mensaje que pide el dato requerido.
 * @mensajeError es el mensaje en caso de que haya un error para indicarle al usuario que algo no esta bien.
 * @reintentos va a recibir el valor de la cantidad de veces que se va a poder reintentar ingresar un dato válido en caso de error.
 * @return retorna -1 si salio algo mal ó 0 si salio todo bien.
 */
int utn_pedirAlfanumerico(char cadena[], char* mensaje, char* mensajeError, int reintentos)
{
	int retorno = -1;
	char buffer[500];
	if(cadena != NULL && mensaje != NULL && mensajeError != NULL && reintentos > 0)
	{
		do
		{
			printf("%s", mensaje);
			if(pedirAlfanumerico(buffer, sizeof(buffer)) == 0)
			{
				strncpy(cadena, buffer, sizeof(cadena));
				retorno = 0;
				break;
			}
			reintentos --;
			printf("%s", mensajeError);
		}while(reintentos > -1);
	}

	return retorno;
}


/*
 * @fn static int esAlfanumericoEspacio(char[], int)
 * @brief funcion que recibe un array y un entero que es el tamaño de esa cadena
 * recorre el array corroborando que cada indice tenga letra, espacio o número.
 * @param cadena[] array a comparar
 * @param limite valor del tamaño del array recibido.
 * @return retorna: -1 en caso de que se encuentre un error, 1 si es verdadero y 0 si es falso.
 */
static int esAlfanumericoEspacio(char cadena[], int limite)
{
	int retorno = -1; //ERROR
	int i;
	if(cadena != NULL && limite > 0)
	{
		retorno = 1; // VERDADERO
		for(i=0; (i<limite) && (cadena[i] != '\0'); i++)
		{
			if(cadena[i] != ' ' &&
			  (cadena[i] < 'a' || cadena[i] > 'z') &&
			  (cadena[i] < 'A' || cadena[i] > 'Z')&&
			  (cadena[i] < '0' || cadena[i] >'9'))
			{
				retorno = 0;
				break;
			}
		}
	}
	return retorno;
}

/*
 * @fn static int pedirAlfanumericoSpacio(char[], int)
 * @brief funcion que recibe un array y un entero que es el tamaño de esa cadena
 * y corrobora que no haya errores para poder copiar en cadena lo que guardo en el buffer.
 * @param cadena[] array que devuelve la palabra libre de errores
 * @param longitud valor del tamaño del array recibido.
 * @return retorna: -1 en caso de que se encuentre un error y 0 si salio todo bien.
 */
static int pedirAlfanumericoEspacio(char cadena[], int longitud)
{
	int retorno = -1; //ERROR
	char buffer[200];

	if(cadena != NULL &&
	  pedirCadena(buffer, sizeof(buffer)) == 0 &&
	  esAlfanumericoEspacio(buffer, sizeof(buffer))&&
	  strnlen(buffer, sizeof(buffer)) < longitud)
	{
		strncpy(cadena, buffer, longitud);
		retorno = 0; //salio BIEN.
	}
	return retorno;
}


/**
 * @fn int utn_pedirAlfanumericoEspacio(char[] , char* , char* , int)
 * @brief funcion que pide texto alfanumerico y permite espacios
 * @cadena array recibido que va a guardar las palabras obtenida en caso que haya salido todo bien.
 * @mensaje es el mensaje que pide el dato requerido.
 * @mensajeError es el mensaje en caso de que haya un error para indicarle al usuario que algo no esta bien.
 * @reintentos va a recibir el valor de la cantidad de veces que se va a poder reintentar ingresar un dato válido en caso de error.
 * @return retorna -1 si salio algo mal ó 0 si salio todo bien.
 */
int utn_pedirAlfanumericoEspacio(char cadena[], char* mensaje, char* mensajeError, int reintentos)
{
	int retorno = -1;
	char buffer[500];
	if(cadena != NULL && mensaje != NULL && mensajeError != NULL && reintentos > 0)
	{
		do
		{
			printf("%s", mensaje);
			if(pedirAlfanumericoEspacio(buffer, sizeof(buffer)) == 0)
			{
				strncpy(cadena, buffer, sizeof(cadena));
				retorno = 0;
				break;
			}
			reintentos --;
			printf("%s", mensajeError);
		}while(reintentos > -1);
	}

	return retorno;
}

/*
 * @fn static int esVerificable(char[], int)
 * @brief funcion que recibe un array y un entero que es el tamaño de esa cadena
 * recorre el array corroborando que tenga una s-S-n-N
 * @param cadena[] array a comparar
 * @param limite valor del tamaño del array recibido.
 * @return retorna: -1 en caso de que se encuentre un error, 1 si es no y 0 si es si.
 */
static int esVerificable(char cadena[], int limite)
{
	int retorno = -1; //ERROR
	if(cadena != NULL && limite > 0)
		{
			retorno = -2;
			if(cadena[0] == 'S' || cadena[0] == 's')
			{
				retorno = 0; //si
			}
			else
			{
				if(cadena[0] == 'N' || cadena[0] == 'n')
				{
					retorno = 1; //no
				}
			}
		}
		return retorno;
}

/*
 * @fn static int verificar(char[], int)
 * @brief funcion que recibe un array y un entero que es el tamaño de esa cadena
 * y corrobora que no haya errores para poder copiar en cadena lo que guardo en el buffer.
 * @param cadena[] array que devuelve la palabra libre de errores
 * @param longitud valor del tamaño del array recibido.
 * @return retorna: -1 en caso de que se encuentre un error y 0 si salio todo bien.
 */
static int verificar(char cadena[], int longitud)
{
	int retorno = -1; //ERROR
	char buffer[2];
	if(cadena != NULL &&
	  pedirCadena(buffer, sizeof(buffer)) == 0 &&
	  (esVerificable(buffer, sizeof(buffer)) == 1 ||
	  esVerificable(buffer, sizeof(buffer)) == 0) &&
	  strnlen(buffer, sizeof(buffer))<longitud)
	{
		strncpy(cadena, buffer, longitud);
		retorno = 0; //salio bien
	}
	return retorno;
}



/**
 * @fn int utn_verificar(char[] , char* , char* , int)
 * @brief funcion que se usa esperando una respuesta "si o no" y crea reintentos
 * @cadena array recibido que va a guardar las palabras obtenida en caso que haya salido todo bien.
 * @mensaje es el mensaje que pide el dato requerido.
 * @mensajeError es el mensaje en caso de que haya un error para indicarle al usuario que algo no esta bien.
 * @reintentos va a recibir el valor de la cantidad de veces que se va a poder reintentar ingresar un dato válido en caso de error.
 * @return retorna -1 si salio algo mal ó 0 si la respuesta fue si o 1 si fue no.
 */
int utn_verificar(char* mensaje, char* mensajeError, int reintentos)
{
	int retorno = -1; //ERROR
	char buffer[3];
	char aux;
	if(mensaje != NULL && mensajeError != NULL && reintentos > -1)
	{
		do
		{
			printf("%s", mensaje);
			if(verificar(buffer, sizeof(buffer)) == 0)
			{
				if(esVerificable(buffer, sizeof(buffer)) == 0)
				{
					retorno = 0;//si
					break;
				}
				else
				{
					if(esVerificable(buffer, sizeof(buffer)) == 1)
					{
						retorno = 1; //no
						break;
					}
				}
			}
			reintentos --;
			printf("%s", mensajeError);
		}while(reintentos > -1);

	}
	return retorno;
}
