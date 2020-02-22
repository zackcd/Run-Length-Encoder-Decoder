//
//  utils.c
//  Cyborg Project
//
//  Created by Zachary Downing on 2/8/20.
//  Copyright © 2020 Zachary Downing. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>

#include "utils.h"

int readFile(const char *fileName, char **buffer) {
    FILE *fp = fopen(fileName, "r");
    
    char *data;
    
    if (fp != NULL) {
        if (fseek(fp, 0L, SEEK_END) == 0) {
            long bufferSize = ftell(fp);
            
            if (bufferSize == -1) {
                return -1;
            }
            
            data = malloc(sizeof(char) * (bufferSize + 1));
            *buffer = malloc(sizeof(char) * (bufferSize + 1));
            
            if (fseek(fp, 0L, SEEK_SET) != 0) {
                return -1;
            }
            
            size_t len = fread(data, sizeof(char), bufferSize, fp);
            
            if (ferror(fp) != 0) {
                return -1;
            }
            else {
                data[len++] = '\0';
            }
            strcpy(*buffer, data);
        }
        else {
            return -1;
        }
        fclose(fp);
        return 0;
    }
    else {
        printf("Null filename\n");
        return -1;
    }
}

int writeFile(const char *fileName, char *data) {
    FILE *fp;
    
    fp = fopen(fileName, "w+");
    
    fprintf(fp, "%s", data);
    
    return 0;
}
