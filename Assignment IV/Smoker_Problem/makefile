hdrs = ipc.h
opts = -g -c
s_src = smoker.c ipc.c setup.c
s_obj = smoker.o ipc.o setup.o
p_src = provider.c ipc.c setup.c
p_obj = provider.o ipc.o setup.o

all:    provider smoker

smoker:  $(s_obj)
	gcc $(s_obj) -o smoker
smoker.o:  $(rc) $(hdrs)
	gcc $(opts) $(s_src)
provider: $(p_obj)
	gcc $(p_obj) -o provider
provider.o:  $(p_src) $(hdrs)
	gcc $(opts) $(p_src)

clean:
	rm smoker provider ipc setup *.o
