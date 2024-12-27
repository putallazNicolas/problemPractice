#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <string.h>

void changePath(char *path);
int countFiles(char *path);

const char *thisPath = "\\problemCounter\\problemCounter.exe";

int main(void){
    // Get problems path
    char directory[MAX_PATH];
    GetModuleFileName(NULL, directory, MAX_PATH); // Finds where is this program installed
    changePath(directory); // Changes the current path to problems path

    // Open directory to count files
    int fileCount = countFiles(directory);
    printf("%i\n", fileCount);
    // Change README file
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