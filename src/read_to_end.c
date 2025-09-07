//
// Created by paul on 9/7/25.
//
#include <stdio.h>
#include "read_to_end.h"

#include <stdlib.h>
#include <string.h>
#include <unistd.h>
const int BUFFER_SIZE = 1024;

char* read_to_end(const int fd)
{
    char buffer[BUFFER_SIZE];
    ssize_t bytesRead = 0;
    ssize_t totalBytes = 0;
    char *result = NULL;

    while ((bytesRead = read(fd, buffer, BUFFER_SIZE)) > 0)
    {
        char *newResult = realloc(result, totalBytes + bytesRead + 1);
        if (!newResult)
        {
            free(result);
            return NULL; // Memory allocation failed
        }
        result = newResult;
        memcpy(result + totalBytes, buffer, bytesRead);
        totalBytes += bytesRead;
        result[totalBytes] = '\0'; // Null-terminate the string
    }

    return result;
}
