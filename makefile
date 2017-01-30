all: pointersorter.c
	gcc -O -Wall -o bin/pointersorter pointersorter.c

debug: pointersorter.c
	gcc -g -Wall -o bin/pointersorter pointersorter.c && gdb bin/pointersorter

tar: readme pointersorter.c testcases.txt 
	cp pointersorter.c testcases.txt readme.pdf Asst0
	tar -czf Asst0.tgz Asst0

readme: readme.tex
	pandoc readme.tex -o readme.pdf
