[ "$1" == "build" ] && gcc -o sudo sudo.c
[ "$1" == "install" ] && install sudo /usr/bin/sudo
