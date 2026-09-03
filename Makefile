CC := gcc
CFLAGS := -std=c23 -Wall -Wextra -O2
LDFLAGS :=

SOURCES = $(wildcard src/*.c)
OBJECTS = $(SOURCES:src/%.c=obj/%.o)
TARGET = everyday

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

obj/%.o: src/%.c | obj
	$(CC) $(CFLAGS) -c -o $@ $<

obj:
	mkdir -p $@

clean:
	rm -rf obj

rebuild: clean all

run: $(TARGET)
	./$(TARGET)

.PHONY: all clean rebuild run

