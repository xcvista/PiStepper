
TARGET := libPiStepper.so

C_FILES := $(wildcard *.c)
HEADERS := $(wildcard *.h)

OBJS := ${C_FILES:.c=.c.o}

CC := clang
CFLAGS += -std=gnu99 -I.
LDFLAGS += -lpthread

PREFIX=/usr/local

ifeq ($(debug),yes)
CFLAGS += -O0 -g
else
CFLAGS += -O2
LDFLAGS += -lwiringPi
endif

all: $(TARGET)
.PHONY: all clean install install-library install-headers

$(TARGET): $(OBJS)
	$(CC) $(LDFLAGS) -shared $(OBJS) -o $@

%.c.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	-rm -rf $(TARGET) $(OBJS)

install: install-library install-headers

install-library: $(TARGET)
	install -m 755 $(TARGET) $(PREFIX)/lib/$(TARGET).1.0
	ln -s $(TARGET).1.0 $(PREFIX)/lib/$(TARGET)

install-headers: $(HEADERS)
	install -m 644 $(HEADERS) $(PREFIX)/include/