##
# Fortune DB
#
# @file
# @version 0.1
CC = gcc
CFLAGS = -g -O0 -Wall -Wextra -std=c11

TARGET = bin/fortunedb

SRC = $(wildcard *.c)
OBJ = $(SRC:.c=.o)

$(TARGET):$(OBJ)
	$(CC) $(OBJ) -o $(TARGET)

%.o:%.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(TARGET)


# end
