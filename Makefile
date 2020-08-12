build:
	gcc -o sudo sudo.c
	
install:
	mkdir -p $(DESTDIR)/usr/bin/ &>/dev/null
	install sudo $(DESTDIR)/usr/bin/sudo
