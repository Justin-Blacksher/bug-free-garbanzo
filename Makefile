CC = gcc
CFLAGS = -Wall -O2 -I C:/raylib/raylib-5.0/include
LDFLAGS = -L C:/raylib/raylib-5.0/lib -lraylib -lopengl32 -lgdi32 -lwinmm
SRC = src/main.c src/game.c
TARGET = bin/ultima4_clone.exe

all: $(TARGET)

$(TARGET): $(SRC)
    $(CC) $(CFLAGS) $(SRC) -o $(TARGET) $(LDFLAGS)

clean:
    del bin\ultima4_clone.exe

