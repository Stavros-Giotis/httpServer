CC = gcc

TARGET = server

SRC= src/main.c

all:
	$(CC) $(SRC) -o$(TARGET)

clean:
	rm -f $(TARGET)