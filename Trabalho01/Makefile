# the compiler
CC = g++
CFLAGS  = -Wall

OBJFILES = screen.o functions.o Trabalho1_FabianaFerreiraFonseca.o
TARGET = Trabalho1_FabianaFerreiraFonseca.exe

all: $(TARGET)

$(TARGET): $(OBJFILES)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJFILES)

clean:
	rm -f $(OBJFILES) $(TARGET) *~
