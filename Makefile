hashcrack: src/main.c
	gcc -Wall src/main.c -o hashcrack -lcrypto -lssl
clean:
	rm hashcrack
