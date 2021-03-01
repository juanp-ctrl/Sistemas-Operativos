/*
 * BD.h
 *
 *  Created on: Feb 27, 2021
 *      Author: juanpa
 */

#ifndef BD_H_
#define BD_H_

struct s_estud;
struct s_datab;

struct s_datab* datab();

void new_db(struct s_datab* db, char* nombre, int regs);

void des_db(struct s_datab*);

void crear_reg(struct s_datab*, char* nombre, int cedula, int semestre);

//Metodos Accesores
char* get_nom(struct s_datab*);
int get_tam(struct s_datab*);
int get_regs(struct s_datab*);
struct s_datab* get_registro(struct s_datab*, int);
void leer_regs(struct s_datab*);

#endif /* BD_H_ */
