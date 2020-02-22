//
//  utils.h
//  Cyborg Project
//
//  Created by Zachary Downing on 2/8/20.
//  Copyright © 2020 Zachary Downing. All rights reserved.
//

#ifndef utils_h
#define utils_h

#define CONTROL_CHAR '*'
#define ENCODE_MODE 1
#define DECODE_MODE 2

#include <stdio.h>

int readFile(const char *fileName, char **buffer);

int writeFile(const char *fileName, char *data);

#endif /* utils_h */
