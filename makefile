#Windows Makefile

all: main.o utils.o
	@gcc ./obj/main.o ./obj/utils.o -o pas

main.o: ./src/main.c
	@gcc -c ./src/main.c -o ./obj/main.o

utils.o: ./src/utils.c
	@gcc -c ./src/utils.c -o ./obj/utils.o

run:
	@./pas.exe

go:
	@make all
	@make run

clean:
	@del *.exe /q
	@cd ./obj && del *.o /q && \
	@cls