

all: main clean

main:
		g++ -c src/*.cpp

clean:
		rm -rf *.o && clear