build:
	cd src2 && gcc -o demon demon.c
	cd src2 && gcc -o summoner summoner.c
	mv src2/demon bin/demon
	mv src2/summoner bin/summoner

reset:
	rm -f /tmp/daemon.incantation.txt
	rm -f /tmp/daemon.curse.txt