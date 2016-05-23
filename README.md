This is a simple and lightweight ringbuffer implementation I did for a hiring test. It was done with GCC on Linux/x86_64, and was tested with several other (embedded & similar) compilers like CC65 and VBCC.

To build it on Linux, use:
```
  make
```
Then `./rd_test` launches the simple test code.

To build the Commodore 64 binary of the test code (for fun), use:
```
  make -f Makefile.C64
```
Make sure you have CC65 installed and in the path. Copy the resulting `rb_test.c64` file to a medium your C64 using your favorite method, and LOAD/RUN. :)

If you don't have a C64 or emulator at hand, observe the C64 version in it's full glory here: 

https://twitter.com/chainq/status/734524673451536384
