a:client.o func.o
	gcc client.o func.o
client.o:client.c server.h
	gcc -c client.c
func.o:func.c server.h
	gcc -c func.c