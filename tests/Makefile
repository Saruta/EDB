CC=gcc
CFLAGS=-m32
LDFLAGS=-m32
EXEC=test
SRC= $(wildcard *.c)
OBJ= $(SRC:.c=.o)

all: $(EXEC) clean

$(EXEC): $(OBJ)
	$(CC) -o $@ $^ $(LDFLAGS)

break.o:  

%.o: %.c
	$(CC) -o $@ $(CFLAGS) -c $<

.PHONY: clean mrpoper

clean:
	rm -rf *.o

mrproper: clean
	rm -rf $(EXEC)

