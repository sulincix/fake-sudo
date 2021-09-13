# The Fake Sudo
`su -c "command"` with small features

### for build:
./build.sh or make

### for install:
./build.sh install or make install

### control:
* `NOENV=1 sudo (command)` will isolate environment variable
* `FAKEROOT=1 sudo (command)` will use unshare instead of su
* `NOROOT=1 sudo (command)` will run command without root