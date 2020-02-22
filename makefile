CC = gcc
CFLAGS  = -g -Wall

default: runlen

runlen:  main.o encode.o decode.o utils.o
	$(CC) $(CFLAGS) -o runlen main.o encode.o decode.o utils.o

main.o: main.c encode.h decode.h utils.h
	$(CC) $(CFLAGS) -c main.c

encode.o: encode.c encode.h utils.h
	$(CC) $(CFLAGS) -c encode.c

decode.o: decode.c decode.h utils.h
	$(CC) $(CFLAGS) -c decode.c

utils.o: utils.c utils.h

clean: 
	$(RM) runlen *.o *~