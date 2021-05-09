/*
 ============================================================================
 Name        : Proyecto.c
 Author      : Juan Pablo Jiménez H
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <sys/types.h>
#include <dirent.h>
#include <errno.h>
#include <string.h>

DIR *ptr_dir;
struct dirent *struct_dir;
struct stat infofile;
DIR *array_ptr[64];
int itera = 0;
char prefijo[512], acomulado[512], origen[512];
int tab = 0;

void report_error(char *msg) /* Unix-style error */
{
    fprintf(stderr, "%s: %s\n", msg, strerror(errno));
    exit(0);
}

void leer_dir(DIR *ptr_d, char prefi[64]){

	while ((struct_dir = readdir(ptr_d)) != NULL) {		//Leemos las entradas del directorio

		strcpy(prefijo,prefi);
		strcpy(acomulado,prefi);

		if( (strcmp(struct_dir->d_name,".") == 0) || (strcmp(struct_dir->d_name,"..") == 0)){

			//printf("Dir: %s\n", struct_dir->d_name);

		}

		else{

			strcat(prefijo,"/");
			strcat(prefijo,struct_dir->d_name);

			if(stat(prefijo, &infofile) == -1){		//Obtenemos la informacion del archivo
				report_error("Error de archivo");
			}

			if(S_ISDIR(infofile.st_mode)){		//Es directorio

				if(tab == 1){
					printf("\tDir: %s\n", struct_dir->d_name);
				}
				else if(tab == 2){
					printf("\t\tDir: %s\n", struct_dir->d_name);
				}
				else{
					printf("Dir: %s\n", struct_dir->d_name);
				}

				strcat(acomulado,"/");
				strcat(acomulado,struct_dir->d_name);

				if( (array_ptr[itera] = opendir(acomulado)) == NULL){
					report_error("Error de directorio");
				}
				tab++;
				leer_dir(array_ptr[itera++], acomulado);
				strcat(acomulado,"/..");
				tab = 0;
			}

			else{							    //Es archivo regular

				printf("\t|__Arc: %s\n", struct_dir->d_name);

			}

		}
	}
}

int main(int argc, char **argv)
{
    if (argc != 2) {
        printf("Uso incorrecto: %s <ruta>\n", argv[0]);
        exit(1);
    }
    ptr_dir = opendir(argv[1]);

    strcpy(origen,argv[1]);

    leer_dir(ptr_dir, argv[1]);

    closedir(ptr_dir);

    exit(0);
}
