CC = g++
LD = g++
STD = -std=c++2a
EXE = exe
LIZZY = Lizzy/LizzyPackage.cpp Lizzy/LizzyStd.cpp Lizzy/LizzyInfo.cpp Lizzy/Lizzy.cpp
SRC = $(wildcard *.cpp) $(LIZZY)
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



