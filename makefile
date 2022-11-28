all: klt ult

BIN := bin
bin:
	mkdir -p $(BIN)

klt: bin
	gcc -o $(BIN)/$@ klt.c -pthread

ult: bin
	gcc -o $(BIN)/$@ ult.c -lpth


.PHONY: clean

clean:
	rm -rf $(BIN)
