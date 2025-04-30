CC=gcc
CXX=g++
CFLAGS=-Iinclude -Wall -Wextra -g
LDFLAGS=
SRC=src/libmemory.c
OBJ=$(SRC:.c=.o)
TARGET=test/test

all: $(TARGET)

$(TARGET): $(OBJ) test/main.cpp
	$(CXX) $(CFLAGS) -o $@ $^ $(LDFLAGS)

clean:
	rm -f $(OBJ) $(TARGET)
