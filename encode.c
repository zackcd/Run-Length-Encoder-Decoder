//
//  encode.c
//  Cyborg Project
//
//  Created by Zachary Downing on 2/7/20.
//  Copyright © 2020 Zachary Downing. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>

#include "encode.h"
#include "utils.h"

int getCounts(char *data, int len, int *counts) {
    int uniqueVals = 0;
    int where[256];
    
    for (int i = 0; i < 255; i++) {
        where[i] = -1;
    }
    
    for (int i = 0; i < len; i++) {
        if(where[(int) data[i]] == -1) {
            where[(int)data[i]] = uniqueVals;
            uniqueVals++;
        }
        counts[where[(int)data[i]]]++;
    }
    
    return uniqueVals;
}

double getEntropy(int *counts, int len, int uniqueVals) {
    double H = 0;
    
    for (int i = 0; i < uniqueVals; i++) {
        double p = (double)counts[i] / len;
        H -= p * log2(p);
    }
    
    return H;
}

int getCodeLength(int *counts, int len, int uniqueVals) {
    double codeLen = 0;
    
    /*
    In this case with only two unique symbols, a single bit can be used for each symbol, either 0 or 1
    */
    if (uniqueVals == 2) {
        return len;
    }
    
    /*
     Otherwise using Shannon coding to find optimal code length
     */
    for (int i = 0; i < uniqueVals; i++) {
        double p = (double)counts[i] / len;
        //codeLen -= log2(p) * counts[i];
        
        codeLen += ceil(log2(1.0 / p)) * counts[i];
        
    }
    
    return (int)ceil(codeLen);
}

char* runLengthEncode(char *data, int len) {
    char *encoding;
//    int encodedLen = 0;
    
    encoding = malloc(len + 1);
    encoding[0] = '\0';
    
//    printf("%d\n", len);
    
    for (int i = 0; i < len; i++) {
        int count = 1;
        while (i < len - 1 && data[i] == data[i + 1]) {
            count++;
            i++;
        }
        char ch = data[i];
        
        while (count > 0) {
            int subCount;
            if (count > 9) {
                subCount = 9;
                count -= 9;
            }
            else {
                subCount = count;
                count = 0;
            }
            int strLen = sizeof(char)*(int)log10(subCount);
            char *strCount = malloc(strLen);
            sprintf(strCount, "%d", subCount);
//            strCount[strLen + 1]= '\0';
            
            
            size_t encodingLen = strlen(encoding);
    //        char *temp = malloc(encodingLen + 3);
            char *temp = malloc(encodingLen + 2);
            strcpy(temp, encoding);
    //        temp[encodingLen] = CONTROL_CHAR;
            temp[encodingLen] = ch;
            temp[encodingLen + 1] = '\0';
            encoding = temp;
            

//            strcat(encoding, strCount);
            
            if (ch != '\n') {
            
            encodingLen = strlen(encoding);
            temp = malloc(encodingLen + 2);
            strcpy(temp, encoding);
            temp[encodingLen] = *strCount;
            temp[encodingLen + 1] = '\0';
            encoding = temp;
            }
        
//            printf("%c%d\n", ch, subCount);
        }
    }
    return encoding;
}
