
server: 
	rm -f server
	gcc server.c -o server
	./server

client:  cclean
	gcc client.c -o client
cclean:
	rm -f client
