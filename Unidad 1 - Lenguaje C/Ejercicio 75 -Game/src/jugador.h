/*
 * jugador.h
 *
 *  Created on: Feb 25, 2021
 *      Author: juanpa
 */

#ifndef JUGADOR_H_
#define JUGADOR_H_

//Declaramos un jugador y un arma
struct jugador;
struct gun;

struct jugador* mem_jugador();

void ini_jugador(struct jugador* player, char* nombre);

void elm_jugador(struct jugador*);


//Funciones
void recoger_arma(struct jugador*, struct gun*);
void jugador_dispara(struct jugador*);
void tirar_arma(struct jugador*);

#endif /* JUGADOR_H_ */
