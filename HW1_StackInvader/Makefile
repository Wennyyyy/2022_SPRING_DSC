OBJS=13453.cpp function.cpp function.h

all: $(OBJS)
	g++ $^ -o 13453.exe

debug: $(OBJS)
	g++ -D_WYNNE_DEBUG_ $^ -o 13453.exe
clean:
	rm -rf *.o *exe