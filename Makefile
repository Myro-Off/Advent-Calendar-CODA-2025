CC = gcc
CFLAGS = -Wall -Wextra
TARGET = elf_solver

all: $(TARGET)

$(TARGET): main.c
	$(CC) $(CFLAGS) -o $(TARGET) main.c

clean:
	rm -f $(TARGET)

run:
	./elf_solver