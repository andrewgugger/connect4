INCLUDE := -I ~/include
LDFLAGS := -L ~/lib -lsense -lm
# If you are compiling this to run on CISC210,
# uncomment the below line
#LDFLAGS := $(LDFLAGS) -lncurses

all: final inputtest outputtest
final: main.o input.o output.o
	cc -o final main.o input.o output.o $(LDFLAGS)
run: final
	./final

inputtest: inputtest.o input.o output.o
	cc -o inputtest inputtest.o input.o output.o $(LDFLAGS)
outputtest: outputtest.o output.o input.o
	cc -o outputtest outputtest.o output.o input.o $(LDFLAGS)



clean:
	rm -f *.o final inputtest outputtest
main.o: main.c project.h
	cc -c main.c -I ~/include
input.o: input.c project.h
	cc -c input.c -I ~/include
output.o: output.c project.h
	cc -c output.c -I ~/include
	
inputtest.o: inputtest.c project.h
	cc -c inputtest.c -I ~/include
outputtest.o: outputtest.c project.h
	cc -c outputtest.c -I ~/include
