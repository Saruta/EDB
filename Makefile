include var.mk

CC=clang++
EXEC=edb
CFLAGS+=-std=c++0x
LDFLAGS+=-std=c++0x
SRC= $(wildcard *.cc) $(TARGET_REPO)/commands.cc
OBJ= $(SRC:.cc=.o)

all: $(EXEC) clean

$(EXEC): $(OBJ)
	$(CC) -o $@ $^ $(LDFLAGS)

main.o: edb.hh config.hh 

%.o: %.cc
	$(CC) -o $@ $(CFLAGS) -c $<

.PHONY: clean mrpoper
clean:
	rm -rf *.o
	rm -rf $(TARGET_REPO)/*.o

mrproper: clean
	rm -rf $(EXEC)
	rm -rf tests/test

