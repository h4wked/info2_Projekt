CFLAGS=-W -Wall -Werror -o3

all: clean ueb01

ueb01:
	$(CC) -o $@ $@.c

clean:
	$(RM) ueb01
