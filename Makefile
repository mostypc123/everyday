CC := gcc
CFLAGS := -std=c23 -Wall -Wextra -O2
LDFLAGS :=

SOURCES = $(wildcard src/*.c)
OBJECTS = $(SOURCES:src/%.c=obj/%.o)
NAME = everyday
TARGET := $(NAME)

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

DESTDIR := /
PREFIX := /usr
BINDIR := /bin
install: $(TARGET)
	install -m775 $(TARGET) $(DESTDIR)/$(PREFIX)/$(BINDIR)/$(NAME)

.PHONY: all clean rebuild run

