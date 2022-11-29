run: detect-collisions example-data.dat
	./detect-collisions example-data.dat

detect-collisions: detect-collisions.o sphere.o box.o
	g++ -g3 -O1 -o detect-collisions *.o

%.o: %.cpp
	g++ -g3 -O1 -c -std=c++17 -o $@ $<

clean:
	rm -f *.o detect-collisions
