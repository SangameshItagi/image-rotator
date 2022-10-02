COMPILER = g++
OPTIONS = -g
PROGRAM = rotator.out

all: $(PROGRAM)

run: $(PROGRAM)
	./$(PROGRAM)

$(PROGRAM): rotator.cpp colorPixel.cpp grayPixel.cpp pgm.h ppm.h
	$(COMPILER) $(OPTIONS) rotator.cpp colorPixel.cpp grayPixel.cpp pgm.cpp ppm.cpp -o $(PROGRAM)

clean: $(PROGRAM)
	rm *.out
