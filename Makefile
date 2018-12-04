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

clean:
	rm a.out *.o *.so *.a hello dynamic-hello || true
