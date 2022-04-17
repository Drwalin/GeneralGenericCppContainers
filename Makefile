
OBJECT_FILES = bin/Debug.o
INCLUDES = -I/usr/include -Isrc
LIBS = -L/usr/lib -lboost_iostreams
CXXFLAGS = -m64 -std=c++2a -masm=intel

ifeq ($(BUILD),debug)
	CXXFLAGS += -ggdb3
else
	ifdef DEBUG
		CXXFLAGS += -ggdb3
	else ifdef RELEASE
		CXXFLAGS += -DRELEASE_BUILD -Ofast
	else
		CXXFLAGS += -DRELEASE_BUILD -Ofast
	endif
endif

rbtree: TestRedBlackTree.exe

files_securere: $(OBJECT_FILES)  bin/TestRedBlackTree.o

%.exe: bin/%.o $(OBJECT_FILES)
	g++ $^ -o $@ $(CXXFLAGS) $(LIBS)

bin/%.o: src/%.cpp
	g++ -c $< -o $@ $(CXXFLAGS) $(INCLUDES)
	
bin/%.o: tests/%.cpp
	g++ -c $< -o $@ $(CXXFLAGS) $(INCLUDES)



