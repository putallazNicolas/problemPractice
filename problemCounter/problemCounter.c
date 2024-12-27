#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <string.h>

void changePath(char *path);

const char *thisPath = "\\problemCounter\\problemCounter.exe";

int main(void){
    char directory[MAX_PATH];
    GetModuleFileName(NULL, directory, MAX_PATH); // Finds where is this program installed
    changePath(directory);

    printf("%s\n", directory);
}

void changePath(char *path) {
    // Buscar la posición de 'thisPath' en 'path'
    char *pos = strstr(path, thisPath);
    if (pos != NULL) {
        // Calcular la longitud de la parte de 'path' antes de 'thisPath'
        int prefixLen = pos - path;
        
        // Calcular la longitud de la parte de 'path' después de 'thisPath'
        int suffixLen = strlen(path) - (prefixLen + strlen(thisPath));

        // Mover el contenido posterior a 'thisPath' hacia el principio del arreglo
        memmove(path + prefixLen, path + prefixLen + strlen(thisPath), suffixLen + 1);
    }

    // Agregar '\\problems' al final de la ruta
    const char *problemsPath = "\\problems";
    strcat(path, problemsPath);
}