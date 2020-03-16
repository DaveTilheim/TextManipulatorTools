CC = g++
LD = g++
STD = -std=c++2a
EXE = exe
SRC = $(wildcard *.cpp) $(wildcard Lizzy/*.cpp)
OBJS = $(SRC:.cpp=.o)

all : $(EXE)

$(EXE) : $(OBJS)
	$(LD) -o $(EXE) $(OBJS) $(STD)

%.o : %.cpp %.hpp
	$(CC) -c $< -o $@ $(STD)

main.o : main.cpp
	$(CC) -c $< -o $@ $(STD)

clean:
	@rm -f *.o
	@rm -f $(EXE)
	@rm -f Lizzy/*.o



