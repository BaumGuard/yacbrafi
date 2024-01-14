#pragma once
#include<stdlib.h>

char* read_file(const char* filePath) {
    FILE* file = fopen(filePath, "r");

    if (file == NULL) {
        fprintf(stderr, "Error opening file: %s\n", filePath);
        return NULL;
    }

    fseek(file, 0, SEEK_END);
    long fileSize = ftell(file);
    rewind(file);

    char* content = (char*)malloc(fileSize + 1);

    if (content == NULL) {
        fprintf(stderr, "Memory allocation error\n");
        fclose(file);
        return NULL;
    }

    size_t bytesRead = fread(content, 1, fileSize, file);

    if (bytesRead != fileSize) {
        fprintf(stderr, "Error reading file: %s\n", filePath);
        fclose(file);
        free(content);
        return NULL;
    }

    content[fileSize] = '\0'; // Null-terminate the string

    fclose(file);
    return content;
}
