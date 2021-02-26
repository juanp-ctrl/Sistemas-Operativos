/*
 * gun.h
 *
 *  Created on: Feb 25, 2021
 *      Author: juanpa
 */

#ifndef GUN_H_
#define GUN_H_

typedef int estado; //Si el arma esta cargada o no

struct gun; //Declaramos una estructura llamada gun

struct gun* mem_arma(); //Reservamos en memoria la estructura gun

void new_arma(struct gun*, int); //Este vendria siendo el constructor, que recibe la direccion de memoria de la estructura y

void elm_arma(struct gun*); //Liberamos la memoria de la estructura

//Funciones
estado tiene_balas(struct gun*);
void disparar(struct gun*);
void recargar(struct gun*);

#endif /* GUN_H_ */
