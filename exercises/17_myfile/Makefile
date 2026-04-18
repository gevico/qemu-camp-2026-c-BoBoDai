CC = gcc
CFLAGS = -Wall -g -O2 -fPIE

TARGET := 17_myfile
SRCS := 17_myfile.c
OBJS := $(SRCS:.c=.o)

all: $(TARGET) 17_myfile.o 17_myfile

17_myfile.o: 17_myfile.c
	$(CC) $(CFLAGS) -c -o $@ 17_myfile.c

17_myfile: 17_myfile.c
	$(CC) $(CFLAGS) -o $@ 17_myfile.c

clean:
	rm -f $(TARGET) $(OBJS)

.PHONY: all clean