CC := sdcc
CFLAGS := -mmcs51 --std-c99
INCLUDES := -I.
SOURCES = 01-blink 
SOURCES_LIB = 01-blink-lib 02-uart-lib
LIB_STC = ../lib/serial.rel ../lib/utils.rel


all: $(SOURCES) $(SOURCES_LIB)
.PHONY: $(SOURCES) $(SOURCES_LIB)


$(info $(SOURCES))
$(info $(SOURCES_LIB))

../lib/%.rel: ../lib/%.c
	echo "Compiling $@ -- $<"
	$(CC) $(CFLAGS) $(INCLUDES) -c "$<" -o "$@"

$(SOURCES):
	echo "Compiling $@"
	$(CC) $(CFLAGS) "$@/main.c" -o "$@/main.ihx"

$(SOURCES_LIB): $(LIB_STC)
	echo "Compiling $@"
	$(CC) $(CFLAGS) $(INCLUDES) -c "$@/main.c" -o "$@/main.rel"
	$(CC) $(CFLAGS) $(INCLUDES) "$@/main.rel" $(LIB_STC) -o "$@/main.ihx"