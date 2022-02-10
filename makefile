all: graph_billiard.png

billiard.x: billiard_main.cpp billiard.h billiard.cpp
	g++ -fsanitize=address -fsanitize=undefined -fsanitize=leak $< billiard.h billiard.cpp -o $@

billiard.txt: billiard.x
	./$< 0.0 0.0 0.8 0.8 0.01 50 > $@

graph_billiard.png: graf_billiard.gp billiard.txt
	gnuplot $<

separation_time.x: separation_time.cpp billiard.h billiard.cpp
	g++ -fsanitize=address -fsanitize=undefined -fsanitize=leak $< billiard.h billiard.cpp -o $@

separation: separation_time.x
	./$< 0.01

graphs_separation_time: ajustes.sh graf_separation_time.gp separation_time.x
	bash $<

elipse_billiard.x: elipse_billiard_main.cpp billiard.h billiard.cpp
	g++ -fsanitize=address -fsanitize=undefined -fsanitize=leak $< billiard.h billiard.cpp -o $@

elipse_billiard.txt: elipse_billiard.x
	./$< 0.0 0.0 0.8 0.8 1.01 50 > $@

graph_elipse_billiard.png: graf_elipse_billiard.gp elipse_billiard.txt
	gnuplot $<

elipse_separation_time.x: elipse_separation_time.cpp billiard.h billiard.cpp
	g++ -fsanitize=address -fsanitize=undefined -fsanitize=leak $< billiard.h billiard.cpp -o $@

elipse_separation: elipse_separation_time.x
	./$< 1.01

clean:
	rm *.txt *.png *.x *.log
