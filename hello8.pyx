from libc.stdio cimport printf

def hello(world):
    cdef bytes raw_world = str(world).encode()
    cdef char *world_c = raw_world
    printf('Hello, %s!\n', world_c)
