hello.o: hello5.c
	cc -c hello5.c -o hello.o

world.o: world.c
	cc -c world.c -o world.o

hello: hello.o world.o
	cc hello.o world.o -o hello


dynamic-world.o: world.c
	cc -c world.c -o world.o

world.so: dynamic-world.o
	cc -shared world.o -o world.so

dynamic-hello: hello.o world.so
	cc hello.o world.so -o dynamic-hello


CFLAGS = `python-config --cflags`
LDFLAGS = `python-config --ldflags`

hello9.c: hello9.pyx
	cython hello9.pyx -o hello9.c

hello9.o: hello9.c
	cc -c hello9.c -o hello9.o ${CFLAGS}

hello10.o: hello10.c
	cc -c hello10.c -o hello10.o ${CFLAGS}

embed-hello: hello9.o hello10.o
	cc hello9.o hello10.o -o embed-hello ${LDFLAGS}


clean:
	rm -rf a.out *.o *.so *.a hello dynamic-hello build hello.egg-info dist \
	hello7.c hello8.c hello9.c hello9.h embed-hello
