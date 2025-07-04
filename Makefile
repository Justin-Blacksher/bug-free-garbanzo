CC = gcc
DFLAGS = -Wall -02 -I C:/ralib/rabylib-5.0/include
LDFLAGS = -L C:\raylib\raylib\src -lopengl32 -lgdi32 -lwinmm
SRC = src/main.c src/game.c
TARGET = bin/mountainhollow.exe


all: $(TARGET)


$(TARGET): $(SRC)
	$(CC) $(CFLAGS) $(SRC) -o $(TARGET) $(LDFLAGS)

clean:
	del bin\mountainhollow.exe

