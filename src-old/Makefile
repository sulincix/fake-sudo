PREFIX=usr
build:
	gcc -O3 -s -o sudo sudo.c -I..

install:
	mkdir -p $(DESTDIR)/$(PREFIX)/$(BINDIR)/ &>/dev/null
	install sudo $(DESTDIR)/$(PREFIX)/$(BINDIR)/sudo

clean:
	rm -f sudo
