all: build 

build: PIXEL.cpp IMAGE.cpp main.cpp
	g++ -Wall -o main $^

.PHONY: clean
clean:
	rm main *.swp *.swo
