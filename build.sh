[ "$1" == "build" ] && gcc -O3 -s -o sudo sudo.c -I.
[ "$1" == "install" ] && install sudo /usr/bin/sudo
