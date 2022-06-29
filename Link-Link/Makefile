CXX = g++
CXXFLAGS =  -Wall -Werror -Wextra -pedantic -std=c++17 -g -fsanitize=address 
LDFLAGS =  -fsanitize=address -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer
LBLIBS = -lstdc++fs
SRC = *.cpp
OBJ = $(SRC:.cc=.o)
EXEC = main

all: $(EXEC)

$(EXEC): $(OBJ)
	$(CXX)  $(LDFLAGS) -o $@ $(OBJ) $(LBLIBS) 

clean:
	rm -rf $(OBJ) $(EXEC).o