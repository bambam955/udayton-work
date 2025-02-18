# Commands to compile for Linux

```bash
gcc catpipewc_linux.c -o catpipewc
./catpipewc <file-names...>
```

# Steps for xv6

1. `cp catpipewc_xv6.c <xv6-loc>/user/catpipewc.c`
2. Open Makefile in user directory...
3. Add `    catpipewc\` to the end of the UPROGS variable
4. From base xv6 directory: `make clean; make; make qemu` as always
