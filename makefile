all: wordler

wordler: wordler.h wordler.cpp game.cpp
	g++ wordler.cpp game.cpp -o wordler
	
eval: wordler.h wordler.cpp eval.cpp
	g++ wordler.cpp eval.cpp -o eval

clean:
	rm wordler
	rm eval