run: detect-collisions example-data.dat
	cat example-data.dat | ./detect-collisions

detect-collisions: detect-collisions.o collisions_low-level.o
	g++ -o detect-collisions *.o

clean:
	rm -f *.o detect-collisions
