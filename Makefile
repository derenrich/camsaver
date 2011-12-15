CC=gcc
LIBS =  `pkg-config --libs opencv` `pkg-config --libs dbus-glib-1` 
CFLAGS = `pkg-config --cflags opencv` `pkg-config --cflags dbus-glib-1`
all: camsaver

camsaver:
	$(CC) $(LIBS) $(CFLAGS) camera.c camsaver.c -o camsaver
debug:
	$(CC) $(LIBS) $(CFLAGS) -DDEBUG camera.c camsaver.c -o camsaver

.PHONY: clean
clean:
	rm -f camsaver
