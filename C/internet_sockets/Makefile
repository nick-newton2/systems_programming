CC=		gcc
CFLAGS=		-g -Wall -std=gnu99 -Iinclude
LD=		gcc
LDFLAGS=	-Llib
AR=		ar
ARFLAGS=	rcs
TARGETS=	bin/thor

all:		$(TARGETS)

# TODO: Add rules for lib/libthor.a, bin/unit_{url,socket,http,timestamp}
# bin/thor and any objects they require

bin/thor: src/thor.o lib/libtable.a
	@echo Linking bin/thor...
	@$(LD) $(LDFLAGS) -o $@ $^ $(LIBS)

bin/unit_url: src/unit_url.o lib/libtable.a
	$(LD) $(LDFLAGS) -o $@ $^ $(LIBS)

bin/unit_socket: src/unit_socket.o lib/libtable.a
	$(LD) $(LDFLAGS) -o $@ $^ $(LIBS)

bin/unit_http: src/unit_http.o lib/libtable.a
	$(LD) $(LDFLAGS) -o $@ $^ $(LIBS)

bin/unit_timestamp: src/unit_timestamp.o lib/libtable.a
	$(LD) $(LDFLAGS) -o $@ $^ $(LIBS)


lib/libtable.a: src/hammer.o src/http.o src/socket.o src/timestamp.o src/url.o
	@echo Linking lib/libtable.a...
	@$(AR) $(ARFLAGS) $@ $^

src/thor.o: src/thor.c
	@echo Compiling src/thor.o...
	@$(CC) $(CFLAGS) -c -o $@ $^

src/unit_url.o: tests/unit_url.c
	$(CC) $(CFLAGS) -c -o $@ $^

src/unit_socket.o: tests/unit_socket.c
	$(CC) $(CFLAGS) -c -o $@ $^

src/unit_http.o: tests/unit_http.c
	$(CC) $(CFLAGS) -c -o $@ $^

src/unit_timestamp.o: tests/unit_timestamp.c
	$(CC) $(CFLAGS) -c -o $@ $^

src/url.o: src/url.c
	@echo Compiling src/url.o...
	@$(CC) $(CFLAGS) -c -o $@ $^

src/socket.o: src/socket.c
	@echo Compiling src/socket.o...
	@$(CC) $(CFLAGS) -c -o $@ $^

src/http.o: src/http.c
	@echo Compiling src/http.o...
	@$(CC) $(CFLAGS) -c -o $@ $^

src/timestamp.o: src/timestamp.c
	@echo Compiling src/timestamp.o...
	@$(CC) $(CFLAGS) -c -o $@ $^

src/hammer.o: src/hammer.c
	@echo Compiling src/hammer.o...
	@$(CC) $(CFLAGS) -c -o $@ $^
	

test:
	@$(MAKE) -sk test-all

test-all:               test-url test-socket test-http test-timestamp test-thor

test-url:		bin/unit_url
	@bin/test_url.sh

test-socket:		bin/unit_socket
	@bin/test_socket.sh

test-http:		bin/unit_http
	@bin/test_http.sh

test-timestamp:		bin/unit_timestamp
	@bin/test_timestamp.sh

test-thor:		bin/thor
	@bin/test_thor.sh

clean:
	@echo Cleaning...
	@rm -f $(TARGETS) bin/unit_* lib/*.a src/*.o tests/*.o *.log *.input

.PHONY:		all test clean
