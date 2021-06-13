

all: exec clean

exec: main
		g++ *.o -o main

main:
		g++ -c src/*.cpp

clean:
		rm -rf *.o && clear