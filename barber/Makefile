hdrs = ipc.h
c_src = control.c ipc.c
c_obj = control.o ipc.o
cst_src = customer.c ipc.c
cst_obj = customer.o ipc.o
b_src = barber.c ipc.c
b_obj = barber.o ipc.o
opts = -g -c

all: control customer barber

control: $(c_obj)
	gcc $(c_obj) -o control

control.o: $(c_src) $(hdrs)
	gcc $(opts) $(c_src)

customer: $(cst_obj)
	gcc $(cst_obj) -o customer

customer.o: $(cst_src) $(hdrs)
	gcc $(opts) $(cst_src)

barber: $(b_obj)
	gcc $(b_obj) -o barber

barber.o: $(b_src) $(hdrs)
	gcc $(opts) $(b_src)

clean:
	rm control customer barber *.o
