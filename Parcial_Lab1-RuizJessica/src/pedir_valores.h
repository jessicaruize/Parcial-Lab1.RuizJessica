/*
 * pedir_valores.h
 *
 *  Created on: 15 abr. 2021
 *      Author: jessica
 */

#ifndef PEDIR_VALORES_H_
#define PEDIR_VALORES_H_
#include <stdio.h>
#include <stdlib.h>
#include <stdio_ext.h>
#include <string.h>
#include<ctype.h>


int utn_pedirEntero(int* pResultado, char* mensaje, char* mensajeError, int min, int max, int reintentos, int condicional);
int utn_pedirFlotante(float* pResultado, char* mensaje, char* mensajeError, float min, float max, int reintentos, int condicional);
int utn_pedirAlfabetico(char cadena[], char* mensaje, char* mensajeError, int reintentos);
int utn_pedirAlfabeticoEspacio(char cadena[], char* mensaje, char* mensajeError, int reintentos);
int utn_pedirAlfanumerico(char cadena[], char* mensaje, char* mensajeError, int reintentos);
int utn_pedirAlfanumericoEspacio(char cadena[], char* mensaje, char* mensajeError, int reintentos);
int utn_verificar(char* mensaje, char* mensajeError , int reintentos);

#endif /* PEDIR_VALORES_H_ */

