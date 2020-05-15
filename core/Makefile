CXXFLAGS = -std=c++11 -g -Wall -Wextra -Werror
all: language.o files.o wordMatch.o Wordmap.o Wordgraph.o Worddata.o
	${CXX} $(CXXFLAGS) -o wordMatch $^

wordMatch.o: wordMatch.cpp language.h files.h Wordmap.h Wordgraph.h Worddata.h
	${CXX} $(CXXFLAGS) -c -o $@ $<


test: language.o files.o test.o Wordmap.o Wordgraph.o Worddata.o
	${CXX} $(CXXFLAGS) -o $@ $^

test.o: test.cpp language.h files.h Wordmap.h Wordgraph.h Worddata.h
	${CXX} $(CXXFLAGS) -c -o $@ $<

Worddata.o: Worddata.cpp Worddata.h
	${CXX} $(CXXFLAGS) -c -o $@ $<

language.o: language.cpp language.h
	${CXX} $(CXXFLAGS) -c -o $@ $<

files.o: files.cpp files.h
	${CXX} $(CXXFLAGS) -c -o $@ $<

Wordmap.o: Wordmap.cpp Wordmap.h
	${CXX} $(CXXFLAGS) -c -o $@ $<

Wordgraph.o: Wordgraph.cpp Wordgraph.h
	${CXX} $(CXXFLAGS) -c -o $@ $<
clean:
	rm -f *.o test


