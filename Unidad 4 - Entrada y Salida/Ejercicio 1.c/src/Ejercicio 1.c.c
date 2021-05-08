/*
 ============================================================================
 Name        : c.c
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

void unix_error(char *msg) /* Unix-style error */
{
    fprintf(stderr, "%s: %s\n", msg, strerror(errno));
    exit(0);
}

int main(int argc, char **argv)
{
    DIR *ptr_dir;
    struct dirent *struct_dir;
    struct stat infofile;

    if (argc != 2) {
        printf("Uso incorrecto: %s <ruta>\n", argv[0]);
        exit(1);
    }
    ptr_dir = opendir(argv[1]);

    errno = 0;
    while ((struct_dir = readdir(ptr_dir)) != NULL) {		//Leemos las entradas del directorio
        if(stat(struct_dir->d_name, &infofile) == -1){
        	unix_error("Error de archivo");
        }
        if(S_ISDIR(infofile.st_mode)){
        	printf("Directorio encontrado: %s\n", struct_dir->d_name);
        }
        else{
        	printf("Archivo encontrado: %s\n", struct_dir->d_name);
        }
    }
    if (errno != 0)
        unix_error("Error al leer las entradas del directorio");

    closedir(ptr_dir);
    exit(0);
}

