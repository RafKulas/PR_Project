CC=gcc
CFLAGS=-lpthread
CDEBUG=-g
CFILES=connection.c game.c priority_queue_list.c server.c
HFILES=connection.h game.h priority_queue_list.h game_structure.h
GCHFILES=connection.h.gch game.h.gch priority_queue_list.h.gch game_structure.h.gch

.PHONY: all

all:
	$(CC) $(CDEBUG) $(CFILES) $(HFILES) $(CFLAGS)

clean:
	rm -rf $(GCHFILES) a.out
    
