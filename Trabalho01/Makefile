# the compiler
CC = gcc

# compiler flags:
#  -Wall turns on most, but not all, compiler warnings
CFLAGS  = -Wall

# the build target executable:
OBJFILES = functions.o Trabalho1_FabianaFerreiraFonseca.o
TARGET = Trabalho1_FabianaFerreiraFonseca

all: $(TARGET)

$(TARGET): $(OBJFILES)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJFILES)

clean:
	rm -f $(OBJFILES) $(TARGET) *~
