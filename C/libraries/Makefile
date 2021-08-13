CC=		gcc
CFLAGS=		-g -Wall -std=gnu99
LD=		gcc
LDFLAGS=	-L.
AR=		ar
ARFLAGS=	rcs

TARGETS=	libstr.a str-dynamic \
		libstr.so str-static

all:		$(TARGETS)

clean:
	rm -f $(TARGETS) *.o

# TODO: Add rules for libstr.a libstr.so
%.o:		%.c
	$(CC) $(CFLAGS) -fPIC -c -o $@ $^

libstr.so:	library.o
	$(LD) -L. -shared -o $@ $^

libstr.a:	library.o
	$(AR) $(ARFLAGS) $@ $^

# TODO: Add rules for str-dynamic str-static
str-dynamic:	main.o libstr.so
	$(LD) $(LDFLAGS) -o $@ $^

str-static:	main.o libstr.a
	$(LD) $(LDFLAGS) -static -o $@ $^
