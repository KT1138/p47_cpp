#CXX = i586-mingw32msvc-g++
#CXXFLAGS = -pg -g -W -Wall -ansi -pedantic   # for debug
CXXFLAGS = -O2
CFLAGS = -O2
OBJS = bulletmlparser-tinyxml.o bulletmlparser.o bulletmltree.o calc.o formula-variables.o bulletmlrunner.o bulletmlrunnerimpl.o bulletml_d.o

all: libbulletml_d.a

libbulletml_d.a: ../bulletml.d $(OBJS)
	$(MAKE) -C tinyxml
	ar cru libbulletml_d.a *.o tinyxml/tiny*.o
#	i586-mingw32msvc-ar cru libbulletml_d.a *.o tinyxml/tiny*.o

../bulletml.d: bulletml_d.cpp
	perl create_d_import.pl bulletml_d.cpp bulletml.d

clean:
	rm -f *.o *.a test_bulletml
	$(MAKE) -C tinyxml clean

calc.cpp: calc.yy
	bison -y   calc.yy && mv y.tab.c calc.cpp

$(OBJS): %.o: %.cpp
	$(CXX) -c $(CXXFLAGS) $(INCLUDES) $<

doxy:
	doxygen

distdir:

