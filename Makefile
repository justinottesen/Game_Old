ascii: ascii_comp
	./bin/ascii.out

mem: ascii_comp
	valgrind ./bin/ascii.out

sfml: sfml_comp
	./bin/sfml.out

ascii_comp: bin
	g++ src/*.cpp src/renderer/ASCII*.cpp -o bin/ascii.out -Wall -Wextra -g -std=c++11 -I src/include -D RENDERER=ASCIIRenderer

sfml_comp: bin
	g++ src/*.cpp src/renderer/SFML*.cpp -o bin/sfml.out -Wall -Wextra -g -std=c++11 -lsfml-graphics -lsfml-window -lsfml-system -I src/include -D RENDERER=SFMLRenderer

bin:
	mkdir -p bin

clean:
	rm -rf bin