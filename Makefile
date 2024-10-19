# Compiler
CC = gcc

# Target executable
TARGET = executable

# Default rule to build the program
all: $(TARGET)

# Rule to link the final executable
$(TARGET): main.c
	$(CC) -o $(TARGET) main.c

# Clean rule to remove the executable
clean:
	rm -f $(TARGET)

# Phony targets
.PHONY: all clean
