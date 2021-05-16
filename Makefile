build:
	gcc -O3 -s -o sudo sudo.c -I.

install:
	mkdir -p $(DESTDIR)/usr/bin/ &>/dev/null
	install sudo $(DESTDIR)/usr/bin/sudo

clean:
	rm -f sudo
