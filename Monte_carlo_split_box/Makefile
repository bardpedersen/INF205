run: detect-collisions benchmark-configuration.dat
	./detect-collisions benchmark-configuration.dat

detect-collisions: detect-collisions.o sphere.o box.o small_box.o
	g++ -g3 -O1 -o detect-collisions *.o

%.o: %.cpp
	gcc -g3 -O1 -c -std=c++17 -o $@ $<

clean:
	rm -f *.o detect-collisions
