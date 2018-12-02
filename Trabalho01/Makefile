# the compiler
CC = g++
CFLAGS  = -Wall

OBJFILES = screen.o functions.o Trabalho1_FabianaFerreiraFonseca.o
TARGET = Trabalho1_FabianaFerreiraFonseca.exe
SCREENDIR = ./.files

all: $(TARGET)

$(TARGET): $(OBJFILES)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJFILES)

	rm -r $(SCREENDIR) || true
	mkdir $(SCREENDIR)

clean:
	rm -f $(OBJFILES) $(TARGET) *~
