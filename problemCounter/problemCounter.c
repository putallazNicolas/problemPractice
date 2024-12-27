#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <string.h>

void changePath(char *path);
int countFiles(char *path);
void editReadme(int number);

const char *thisPath = "\\problemCounter\\problemCounter.exe";
const char *readmePath = "..\\README.md";

int main(void){
    // Get problems path
    char directory[MAX_PATH];
    GetModuleFileName(NULL, directory, MAX_PATH); // Finds where is this program installed
    changePath(directory); // Changes the current path to problems path

    // Open directory to count files
    int fileCount = countFiles(directory);
    printf("%i\n", fileCount);
    // Edit README file
    editReadme(fileCount);
}

void changePath(char *path) {
    char *pos = strstr(path, thisPath);
    if (pos != NULL) {
        int prefixLen = pos - path;
        
        int suffixLen = strlen(path) - (prefixLen + strlen(thisPath));

        memmove(path + prefixLen, path + prefixLen + strlen(thisPath), suffixLen + 1);
    }

    const char *problemsPath = "\\problems\\*"; // Add * to include every file in the path
    strcat(path, problemsPath);
}

int countFiles(char *path){
    int counter = 0; // file counter

    WIN32_FIND_DATA ffd; // ffd stands for find file data
    HANDLE hFind = FindFirstFile(path, &ffd);

    if (hFind == INVALID_HANDLE_VALUE){ // findFirstFile return that when error
        printf("Couldnt find files");
    }
    else {
        do {
            if (strcmp(ffd.cFileName, ".") != 0 && strcmp(ffd.cFileName, "..") != 0) {
                counter++;
            }
        } while (FindNextFile(hFind, &ffd) != 0);
    }
    FindClose(hFind);
    return counter;
}

void editReadme(int number) {
    FILE *README, *tmp;
    char line[1024];
    int lineNumber = 1;
    int targetLine = 3;  // Línea a editar
    char numberStr[1024];
    
    // Convertir el número a texto y concatenar el resto
    sprintf(numberStr, "%d", number);
    strcat(numberStr, " problems and counting...\n");

    // Abrir el archivo original para leer
    README = fopen(readmePath, "r");
    if (README == NULL) {
        perror("Error al abrir el archivo");
        return;
    }

    // Crear un archivo temporal para escribir los cambios
    tmp = fopen("tmp.md", "w");
    if (tmp == NULL) {
        perror("Error al abrir el archivo temporal");
        fclose(README);
        return;
    }

    // Leer el archivo línea por línea
    while (fgets(line, sizeof(line), README)) {
        if (lineNumber == targetLine) {
            // Si estamos en la línea que queremos modificar, escribir el nuevo texto
            fputs(numberStr, tmp);
        } else {
            // Copiar las líneas no modificadas al archivo temporal
            fputs(line, tmp);
        }
        lineNumber++;
    }

    // Cerrar ambos archivos
    fclose(README);
    fclose(tmp);

    // Reemplazar el archivo original con el archivo temporal
    remove(readmePath);
    rename("tmp.md", readmePath);
}