CC = gcc

%.exe: %.c
	$(CC) -o exe/$*.exe $*.c $(CFLAGS) -lm -lglut -lglu32 -lopengl32

clean:
	-@if exist *.exe del *.exe > nul