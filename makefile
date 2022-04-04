build:
	cd src && gcc -o demon demon.c
	cd src && gcc -o summoner summoner.c spells.c
	mv src/demon bin/demon
	mv src/summoner bin/summoner

reset:
	rm -f /tmp/daemon.incantation.txt
	rm -f /tmp/daemon.curse.txt