
server: 
	rm -f server
	gcc server.c -o server
	./server
client: 
	rm -f client
	gcc client.c -o client
