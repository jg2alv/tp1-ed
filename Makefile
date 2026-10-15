GPP = g++ -Wall -Wextra -fsanitize=address -fsanitize=undefined -I./include
RM = rm -rf

all: ./src/main.cpp ./obj/utils.o
	$(GPP) ./src/main.cpp ./obj/utils.o -o ./bin/tp1.out

./obj/utils.o: ./src/utils.cpp
	$(GPP) -c ./src/utils.cpp -o ./obj/utils.o

clean:
	$(RM) ./obj/*.o ./bin/*