//
//  decode.c
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

#include "decode.h"

char* runLengthDecode(char *data, int len) {
    char *decoding = malloc(1);
    decoding[0] = '\0';
    
//    for (int i = 0; i < len; i++) {
//        char current = data[i];
//        int runLen = 0;
//        if (isalpha(current) != 0) {
//            i++;
//            while (isdigit(data[i]) != 0) {
//                runLen = runLen * 10 + (data[i] - '0');
//                i++;
//            }
//            for (int i = 0; i < runLen; i++) {
//                size_t decodingLen = strlen(decoding);
//                char *temp = malloc(decodingLen + 2);
//                strcpy(temp, decoding);
//                temp[decodingLen] = current;
//                temp[decodingLen + 1] = '\0';
//                decoding = temp;
//            }
//        }
//        i--;
//    }
    
//    printf("%d\n", len);
    for (int i = 0; i < len; i++) {
//        printf("%d\n", i);
        char current = data[i];
        if (current == '\n') {
            size_t decodingLen = strlen(decoding);
            char *temp = malloc(decodingLen + 2);
            strcpy(temp, decoding);
            temp[decodingLen] = current;
            temp[decodingLen + 1] = '\0';
            decoding = temp;
        }
        else {
            int runLen = data[i + 1] - '0';
        
    //        printf("i: %d: char: %c; runlen: %d\n", i, current, runLen);
            
            
            if (isdigit(data[i + 1]) == 0) {
                printf("%d: %d\n", i, current);
                return NULL;
            }
            
            for (int j = 0; j < runLen; j++) {
                size_t decodingLen = strlen(decoding);
                char *temp = malloc(decodingLen + 2);
                strcpy(temp, decoding);
                temp[decodingLen] = current;
                temp[decodingLen + 1] = '\0';
                decoding = temp;
            }
            
            i++;
        }
    }
    
    return decoding;
}
