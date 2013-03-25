all:

client:
	gcc -o client client.c

client-rm:
	rm -rf client