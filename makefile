all: wordler

worlder:worlder.cpp
	g++ wordler.cpp -o wordler -lm

clean:
	rm wordler