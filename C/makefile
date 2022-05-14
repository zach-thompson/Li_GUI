CC = g++

morphological_processing.o: morphological_processing.hpp morphological_processing.cpp
	$(CC) -c $^
morph: test_regmax.cpp morphological_processing.o 
	$(CC) -o $@ $^
centroiding.o: centroiding.hpp centroiding.cpp
	$(CC) -c $^
dilation.o: dilation.cpp dilation.hpp
	$(CC) -c $^
filter.o: filter.cpp filter.hpp
	$(CC) -c $^ -ltiff
com: test_com.cpp centroiding.o morphological_processing.o
	$(CC) -o $@ $^
algorithm.o: algorithm.hpp algorithm.cpp
	$(CC) -c $^
filt: filtering.cpp filter.o
	$(CC) -o $@ $^ -ltiff
run: run_alg.cpp algorithm.o centroiding.o dilation.o filter.o morphological_processing.o
	$(CC) -o $@ $^ -ltiff
all: morphological_processing.o morph centroiding.o com
clean: 
	rm -f *.o
	rm -f morph
	rm -f *.gch