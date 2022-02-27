DESTDIR=/
PREFIX=usr
LIBDIR=/lib
BINDIR=/bin

build:
	make -C src build-pam

build-nopam:
	make -C src build

build-gtk:
	make -C src build-gtk

build-old:
	make -C src-old build

install:
	make -C src install DESTDIR=$(DESTDIR) PREFIX=$(PREFIX) LIBDIR=$(LIBDIR) BINDIR=$(BINDIR)

install-gtk:
	make -C src install-gtk DESTDIR=$(DESTDIR) PREFIX=$(PREFIX) LIBDIR=$(LIBDIR) BINDIR=$(BINDIR)

install-old:
	make -C src-old install DESTDIR=$(DESTDIR) PREFIX=$(PREFIX)

clean:
	make -C src clean

clean-old:
	make -C src-old clean

test:
	LD_LIBRARY_PATH=$(PWD)/src ./src/sudo ls
