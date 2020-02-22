//
//  main.c
//  Cyborg Project
//
//  Created by Zachary Downing on 2/5/20.
//  Copyright © 2020 Zachary Downing. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>

#include "encode.h"
#include "decode.h"
#include "utils.h"


int encodeMode(const char *inputFile, const char *outputFile) {
//    char *inputFile = "test2.txt";
//    char *outputFile = "out2.txt";

    char *buffer;
    int read = readFile(inputFile, &buffer);

    if (read == -1) {
        printf("Failure: error reading file\n");
        return -1;
    }

//    printf("%s\n", buffer);

    int len = (int) strlen(buffer);
    int *counts = (int*)calloc(len,sizeof(int));

    int unique = getCounts(buffer, len, counts);
//    printf("Number unique: %d\n", unique);
    
    double entropy = getEntropy(counts, len, unique);
    printf("Entropy: %f\n", entropy);

    int codeLen = getCodeLength(counts, len, unique);
    printf("Optimal compressed size: %d\n", codeLen);

    char* encoded = runLengthEncode(buffer, len);
//    printf("Encoded: %s\n", encoded);

    int write = writeFile(outputFile, encoded);

    if (write == -1) {
        printf("Failure: error writing file\n");
        return -1;
    }
    return 0;
}

int decodeMode(const char *inputFile, const char *outputFile) {
//    char *inputFile = "out2.txt";
//    char *outputFile = "decoded2.txt";
    
    char *buffer;
    int read = readFile(inputFile, &buffer);
    int len = (int) strlen(buffer);
    
    if (read == -1) {
        printf("Failure: error reading file\n");
        return -1;
    }
    
//    printf("Encoded: %s\n", buffer);
    
    char *decoded = runLengthDecode(buffer, len);
//    printf("Decoded: %s\n", decoded);
    
    if (decoded == NULL) {
        printf("Failure: error occured in runLengthDecode func\n");
        return -1;
    }
    
    int write = writeFile(outputFile, decoded);
    
    if (write == -1) {
        printf("Failure: error writing to file\n");
        return -1;
    }
    
    return 0;
}

int main(int argc, const char * argv[]) {
    
    
    if (argc != 4) {
        printf("Failure: invalid number of arguments\n");
        return -1;
    }
    
    const char *inputFile = argv[1];
    const char *outputFile = argv[2];
    int mode = atoi(argv[3]);
    
    printf("%d", mode);
    
    int ret = -1;
    
    if (mode == ENCODE_MODE) {
        printf("Running in encode mode\n");
        ret = encodeMode(inputFile, outputFile);
    }
    else if (mode == DECODE_MODE) {
        printf("Running in decode mode\n");
        ret = decodeMode(inputFile, outputFile);
    }
    else {
        printf("Invalid mode\n");
        return -1;
    }

    if (ret == 0) {
        printf("Successful run\n");
        return ret;
    }
    else {
        printf("Unsucessful run\n");
        return ret;
    }
}


