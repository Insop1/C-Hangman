CC = gcc
CFLAGS = -g -I./headers
TARGET = output
SRCS = $(wildcard src/*.c)
HEADERS = $(wildcard headers/*.h)

$(TARGET): $(SRCS) $(HEADERS)
	$(CC) $(CFLAGS) -o $(TARGET) $(SRCS)

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(TARGET)
