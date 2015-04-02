snametize: snametize.o
	g++ -std=c++11 -o snametize snametize.o 

snametize.o : snametize.cpp
	g++ -std=c++11 -c snametize.cpp

.PHONY : clean
clean :
	rm -f snametize.o snametize
