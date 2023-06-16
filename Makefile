ascii: ascii_comp
	./ascii.out

sfml: sfml_comp
	./sfml.out

ascii_comp:
	g++ *.cpp -o ascii.out -Wall -Wextra -g -std=c++11 -lsfml-graphics -lsfml-window -lsfml-system

sfml_comp:
	g++ *.cpp -o sfml.out -Wall -Wextra -g -std=c++11 -lsfml-graphics -lsfml-window -lsfml-system -D RENDERER=SFMLRenderer