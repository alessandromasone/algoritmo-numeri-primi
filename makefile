CC = gcc
CFLAGS = -Wall -Wextra -std=c11

SRCS := $(wildcard *.c)
OBJS := $(SRCS:.c=.o)
TARGET = my_program

.PHONY: all clean start start-with-args

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

# Target to run the program without arguments
start: $(TARGET)
	./$(TARGET)

# Pattern rule to match start with an argument
start-%: $(TARGET)
	./$(TARGET) $*

clean:
	rm -f $(OBJS) $(TARGET)
