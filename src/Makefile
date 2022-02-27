DESTDIR=/
PREFIX=usr
LIBDIR=/lib
BINDIR=/bin
PAM=-DENABLE_PAM -lpam -lpam_misc

build:
	gcc libsudo.c -shared -o libsudo.so -fPIC -lcrypt -I.. 
	gcc main.c -L. -I. -o sudo -lsudo
	chmod u+s ./sudo

build-pam:
	gcc libsudo.c -shared -o libsudo.so -fPIC -lcrypt -I.. $(PAM)
	gcc main.c -L. -I. -o sudo -lsudo $(PAM)
	chmod u+s ./sudo	
build-gtk:
	echo -e "#define TOKEN \"$$RANDOM\"" > token.h
	gcc -I. -L. gtk-helper.c -lsudo -o gtk-sudo-helper
	sha1sum gtk-sudo-helper | cut -f 1 -d " " | sed "s/^/#define HASH \"/g;s/$$/\"/g"  >> token.h
	gcc -I. -L. -g gtk-main.c `pkg-config --cflags --libs gtk+-3.0` -lsudo -o gtk-sudo
	chmod u+s ./gtk-sudo-helper
install:
	mkdir -p $(DESTDIR)/$(PREFIX)/$(BINDIR)/ || true
	mkdir -p $(DESTDIR)/$(PREFIX)/$(LIBDIR)/ || true
	install libsudo.so $(DESTDIR)/$(PREFIX)/$(LIBDIR)/libsudo.so
	cp -pf sudo $(DESTDIR)/$(PREFIX)/$(BINDIR)/sudo
	install libsudo.h $(DESTDIR)/$(PREFIX)/include/libsudo.h

install-gtk:
	install gtk-sudo $(DESTDIR)/$(PREFIX)/$(BINDIR)/
	cp -pf gtk-sudo-helper $(DESTDIR)/$(PREFIX)/$(BINDIR)/
	
clean:
	rm -f libsudo.so sudo gtk-sudo-helper gtk-sudo token.h

