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

graph_separation_time.png: graf_separation_time.gp separation.txt
	gnuplot $<

clean: *.txt *.png *.x *.log
	rm *.txt *.png *.x *.log