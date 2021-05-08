build:
	gcc -O3 -s -g  -o sudo sudo.c

install:
	mkdir -p $(DESTDIR)/usr/bin/ &>/dev/null
	install sudo $(DESTDIR)/usr/bin/sudo

clean:
	rm -f sudo