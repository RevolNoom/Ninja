GDINCLD=/usr/include/godot/godot-cpp/
CPPINCLD=-I$(GDINCLD)include -I$(GDINCLD)include/core -I$(GDINCLD)include/gen -I$(GDINCLD)godot_headers
CXXFLAGS=--std=c++17
CPPFLAGS=-fPIC $(CPPINCLD) 
LDFLAGS=-shared
LOADLIBES=-L$(GDINCLD)bin
LDLIBS=-lgodot-cpp.linux.debug.64

OBJECTS= fighter.o shuriken.o main.o gdlibrary.o 
HEADERS= fighter.h shuriken.h main.h

ninja.so: $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o ninja.so $(LDFLAGS) $(OBJECTS) $(LOADLIBES) $(LDLIBS)

gdlibrary.o: fighter.h

fighter.o: fighter.h

shuriken.o: shuriken.h

main.o: main.h
