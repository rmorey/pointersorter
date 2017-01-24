all: pointersorter.c
	gcc -g -Wall -o bin/pointersorter pointersorter.c

tar: pointersorter.c testcases.txt
	make
	make readme
	cp pointersorter.c testcases.txt readme.pdf Asst0
	tar -czf Asst0.tgz Asst0

readme: readme.tex
	pandoc readme.tex -o readme.pdf


