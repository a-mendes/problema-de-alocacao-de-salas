#Windows Makefile

all: main.o heuristica.o utils.o
	@g++ ./obj/main.o ./obj/heuristica.o ./obj/utils.o -o pas

main.o: ./src/main.cpp
	@g++ -c ./src/main.cpp -o ./obj/main.o

heuristica.o: ./src/heuristica.cpp
	@g++ -c ./src/heuristica.cpp -o ./obj/heuristica.o

utils.o: ./src/utils.cpp
	@g++ -c ./src/utils.cpp -o ./obj/utils.o

run:
	@./pas.exe

go:
	@cls
	@make all
	@make run

clean:
	@del *.exe /q
	@cd ./obj && del *.o /q && \
	@cls