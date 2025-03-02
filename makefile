OBJ:= $(patsubst %.c, %.o, $(wildcard *.c))
APC.exe: $(OBJ)
	gcc -o $@ $^

clean:
	rm *.o *.exe
