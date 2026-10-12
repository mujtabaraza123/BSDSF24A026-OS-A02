CC = gcc
CFLAGS = -Wall -Wextra -g
TARGET = bin/ls
SRC = src/ls-v1.0.0.c

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) $(SRC) -o $(TARGET)

clean:
	rm -f $(TARGET)
