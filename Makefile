CC 	= gcc
INCLUDE  = -I ../include -I /usr/local/include
CFLAGS  = $(INCLUDE) -Wall -c -g3
LDFLAGS = -o


OBJ = eBTS.o eL1.o eMessages.o eSockets.o

.PHONY: all

all: eBTS

eBTS: $(OBJ)
	$(CC) $(INCLUDE) -g -O0 $(OBJ) -o eBTS/eBTS $(LIBOSMOCORE)

eBTS.o: eBTS/main.c
	$(CC) $(CFLAGS) -o eBTS.o eBTS/main.c

eL1.o: eBTS/eL1.c
	$(CC) $(CFLAGS) -o eL1.o eBTS/eL1.c

eMessages.o: eBTS/eMessages.c 
	$(CC) $(CFLAGS) -o eMessages.o eBTS/eMessages.c

eSockets.o: eBTS/eSockets.c 
	$(CC) $(CFLAGS) -o eSockets.o eBTS/eSockets.c

.PHONY: clean

clean:
	rm -f eBTS/*.o
	rm -f eBTS/eBTS
