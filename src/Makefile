DESTDIR=/
PREFIX=usr
LIBDIR=/lib
BINDIR=/bin

build:
	gcc libsudo.c -shared -o libsudo.so -fPIC -lcrypt -I..
	gcc main.c -L. -I. -o sudo -lsudo
	chmod u+s ./sudo
install:
	mkdir -p $(DESTDIR)/$(PREFIX)/$(BINDIR)/ || true
	mkdir -p $(DESTDIR)/$(PREFIX)/$(LIBDIR)/ || true
	install libsudo.so $(DESTDIR)/$(PREFIX)/$(LIBDIR)/libsudo.so
	cp -pf sudo $(DESTDIR)/$(PREFIX)/$(BINDIR)/sudo
clean:
	rm -f libsudo.so sudo
