cdef public void hello(char *world):
    cdef bytes raw_world = world
    print('Hello, %s!' % raw_world.decode())
