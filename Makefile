c         = gcc
src       = src/*.c
sharedarg = -g -std=c99 -shared -fpic -Wall -Wextra -Werror -pedantic
staticarg = -g -std=c99 -Wall -Wextra -Werror -pedantic
outshared = bin/libytui.so
outstatic = bin/libytui.o

shared:
	$(c) $(src) $(sharedarg) -o $(outshared)

static:
	$(c) $(src) -o $(outstatic)

install: $(outshared)
	cp $(outshared) /usr/lib/
	mkdir -p /usr/include/ytui
	cp src/*.h /usr/include/ytui/