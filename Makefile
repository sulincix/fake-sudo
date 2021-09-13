DESTDIR=/
PREFIX=usr
LIBDIR=/lib
BINDIR=/bin

build:
	make -C src build

build-old:
	make -C src-old build

install:
	make -C src install DESTDIR=$(DESTDIR) PREFIX=$(PREFIX) LIBDIR=$(LIBDIR) BINDIR=$(BINDIR)

install-old:
	make -C src-old install DESTDIR=$(DESTDIR) PREFIX=$(PREFIX)

clean:
	make -C src clean

clean-old:
	make -C src-old clean
