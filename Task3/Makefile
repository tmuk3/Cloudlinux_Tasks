CC = gcc
CFLAGS = -Wall -Wextra -std=c11
TARGET = task3
SRC = main.c

all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) -o $@ $^

run: $(TARGET)
	./$(TARGET) ./test_inputs/prog1.sh ./test_inputs/prog2.sh ./test_inputs/prog3.sh ./test_inputs/expected_output.txt

clean:
	rm -f $(TARGET) output.txt
