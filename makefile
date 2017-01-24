all: pointersorter.c
	gcc -o bin/pointersorter pointersorter.c

tar: pointersorter.c testcases.txt
	cp pointersorter.c testcases.txt Asst0
	tar -czf Asst0.tgz Asst0
