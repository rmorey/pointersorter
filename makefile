all: pointersorter.c
	mkdir -p bin
	gcc -O -Wall -o bin/pointersorter pointersorter.c

debug: pointersorter.c
	gcc -g -Wall -o bin/pointersorter pointersorter.c && \
	gdb -q bin/pointersorter

tar: style all readme pointersorter.c testcases.txt 
	mkdir -p Asst0
	cp pointersorter.c testcases.txt readme.pdf Asst0
	tar -czf Asst0.tgz Asst0
	rm -r Asst0

readme: readme.md
	pandoc readme.md -o readme.pdf

style: pointersorter.c
	indent -linux -nut -i4 pointersorter.c

