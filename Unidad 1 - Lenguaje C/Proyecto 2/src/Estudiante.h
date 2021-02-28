/*
 * Estudiante.h
 *
 *  Created on: Feb 27, 2021
 *      Author: juanpa
 */

#ifndef ESTUDIANTE_H_
#define ESTUDIANTE_H_

struct s_estud;

struct s_estud* estud();

void new_estud(struct s_estud* estud, char* nombre, int cedula, int semestre);

void des_estud(struct s_estud*);

char* get_snom(struct s_estud*);
int get_sced(struct s_estud*);
int get_ssem(struct s_estud*);

#endif /* ESTUDIANTE_H_ */
