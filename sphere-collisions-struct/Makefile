run: detect-collisions-struct example-data.dat
	cat example-data.dat | ./detect-collisions-struct

detect-collisions-struct: detect-collisions-struct.o collisions_with_struct.o
	g++ -o detect-collisions-struct *.o

clean:
	rm -f *.o detect-collisions-struct