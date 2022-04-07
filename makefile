build:
	cd src && gcc -o demon demon.c
	cd src && gcc -o summoner summoner.c spells.c
	mv src/demon ./demon
	mv src/summoner ./summoner

reset:
	rm -f /tmp/daemon.incantation
	rm -f /tmp/daemon.curse