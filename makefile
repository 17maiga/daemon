# Main build process
# Creates the executable in the bin directory
build: src/obj/summoner.o src/obj/demon.o src/obj/spells.o src/obj/utils.o
	gcc -o summoner src/obj/summoner.o src/obj/demon.o src/obj/spells.o src/obj/utils.o
	mkdir -p bin
	mv summoner bin/summoner

# Object files
src/obj/utils.o: src/utils.c
	mkdir -p src/obj
	gcc -c src/utils.c
	mv utils.o src/obj

src/obj/spells.o: src/spells.c
	mkdir -p src/obj
	gcc -c src/spells.c
	mv spells.o src/obj

src/obj/demon.o: src/demon.c
	mkdir -p src/obj
	gcc -c src/demon.c
	mv demon.o src/obj

src/obj/summoner.o: src/summoner.c
	mkdir -p src/obj
	gcc -c src/summoner.c
	mv summoner.o src/obj

# Remove the object files and the executables
clean:
	rm -r src/obj
	rm -r bin

# Removes the communication pipe if needed
reset:
	rm -f /tmp/daemon.spell