CC=gcc
CFLAGS=-Wall -pedantic
LDFLAGS=
HEADERS=
SOURCES=generator.c 
OBJECTS=$(SOURCES:.c=.o)
OUTPUT=../B3228

.PHONY: clean mrproper

all: $(OUTPUT)

$(OUTPUT): $(OBJECTS)
	$(CC) -o $@ $^ $(LDFLAGS)

%.o: %.clean
	$(CC) $(CFLAGS) -o $@ -c $<

Main.o: Editor.h

clean:
	rm -f $(OBJECTS)

mrproper: clean
	rm -f $(OUTPUT)

exec:
	$(OUTPUT)