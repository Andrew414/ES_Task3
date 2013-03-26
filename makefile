all:
	make client;
	make server;

client:
	$(CROSS_COMPILE)gcc -o client client.c

client-clean:
	rm -rf client

server:
	$(CROSS_COMPILE)gcc -pthread -o server server_thread.c server_filereader.c server.c 

server-clean:
	rm -rf server

clean:
	make client-clean;
	make server-clean;

rebuild:
	make clean;
	make all;
