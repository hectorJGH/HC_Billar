all: graph_billiard.png

billiard.x: billiard_main.cpp billiard.h billiard.cpp
	g++ -fsanitize=address -fsanitize=undefined -fsanitize=leak $< billiard.h billiard.cpp -o $@

billiard.txt: billiard.x
	./a.out 0.0 0.0 0.8 0.8 0.01 50 > $@

graph_billiard.png: graf_billiard.gp billiard.txt
	gnuplot $<
