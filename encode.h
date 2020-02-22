//
//  encode.h
//  Cyborg Project
//
//  Created by Zachary Downing on 2/7/20.
//  Copyright © 2020 Zachary Downing. All rights reserved.
//

#ifndef encode_h
#define encode_h

#include <stdio.h>

int getCounts(char *data, int len, int *counts);

double getEntropy(int *counts, int len, int uniqueVals);

int getCodeLength(int *counts, int len, int uniqueVals);

char* runLengthEncode(char *data, int len);

#endif /* encode_h */
