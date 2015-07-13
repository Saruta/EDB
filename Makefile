CC=clang++
CFLAGS=
LDFLAGS=
EXEC=edb
SRC= $(wildcard *.cc)
OBJ= $(SRC:.cc=.o)

all: $(EXEC)

$(EXEC): $(OBJ)
	$(CC) -o $@ $^ $(LDFLAGS)

main.o: 

%.o: %.cc
	$(CC) -o $@ $(CFLAGS) -c $<

.PHONY: clean mrpoper

clean:
	rm -rf *.o

mrproper: clean
	rm -rf $(EXEC)

