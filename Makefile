# the compiler
CC = g++
CFLAGS  = -Wall

OBJFILES = screen.o functions.o Trabalho1_FabianaFerreiraFonseca.o
TARGET = Trabalho1_FabianaFerreiraFonseca.exe
SCREENDIR = ./.files

all: $(TARGET)

$(TARGET): $(OBJFILES)
	$(CC) $(CFLAGS) -std=c++11 -o $(TARGET) $(OBJFILES) -pthread

	rm -r $(SCREENDIR) || true
	mkdir $(SCREENDIR)

clean:
	rm -f $(OBJFILES) $(TARGET) *~
