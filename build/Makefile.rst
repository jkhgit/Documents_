Makefile
==================

Simple code for a simple build test::

	# toolchain
	CC = gcc

	# flags
	CFLAGS = -g
	LDFLAGS =

	SRCS = $(notdir $(wildcard $(PATH)/*.c)) # PATH = PWD normally.
	OBJS = $(patsubst %.c, %.o, $(SRCS))

	# pkgconfig
	PKG=
	PKG_CONFIG = `pkg-config --cflags --libs $(PKG)`

	all: target

	target: $(OBJS)
	$(CC) -o target $(OBJS) $(PKG_CONFIG)

	# GNU function
	%.o: %.c
	@$(CC) $(CFLAGS) -c -o $@ $< $(PKG_CONFIG) # {$@: %.o} {$<: %.c}

	clean:
		rm *o target
