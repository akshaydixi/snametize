all : snametize.o
	g++ -std=c++11 -o bin/snametize snametize.o -lboost_program_options
	rm -f snametize.o

snametize.o : src/snametize.cc
	g++ -std=c++11 -c src/snametize.cc -lboost_program_options

.PHONY : clean
clean :
	rm -f snametize.o bin/snametize
