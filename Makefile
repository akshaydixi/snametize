snametize: snametize.o
	g++ -std=c++11 -o snametize snametize.o -lboost_program_options

snametize.o : snametize.cpp
	g++ -std=c++11 -c snametize.cpp -lboost_program_options

.PHONY : clean
clean :
	rm -f snametize.o snametize
