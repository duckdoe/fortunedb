##
# Fortune DB
##

CC = gcc
CPPFLAGS = -Iinclude
CFLAGS = -g -O0 -Wall -Wextra -std=c11

TARGET = bin/fortunedb
SRC = $(wildcard src/*.c)
OBJ = $(SRC:src/%.c=bin/%.o)

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(OBJ) | bin
	$(CC) $(CFLAGS) $(OBJ) -o $@

bin/%.o: src/%.c | bin
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@

bin:
	mkdir -p $@

clean:
	rm -f $(OBJ) $(TARGET)
