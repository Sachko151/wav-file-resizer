wav_make: main.c src/main_functions.c src/wav_operations.c
	gcc -o output main.c src/main_functions.c src/wav_operations.c -I.
clean:
	rm output