Edits to MakeFile in <xv6-location>/user:
1. Go down to definition of UPROGS variable
2. Add letterfilter\ at the bottom on its own line
3. Add newlinefilter\ after that on its own line

Linux compilation:
gcc -o letterfilter letterfilter_linux.c
gcc -o newlinefilter newlinefilter_linux.c
./letterfilter
./newlinefilter

xv6 compilation:
mv letterfilter_xv6.c <xv6-location>/user/letterfilter.c
mv newlinefilter_xv6.c <xv6-location>/user/newlinefilter.c
cd <xv6-location>
make clean
make
make qemu-nox
