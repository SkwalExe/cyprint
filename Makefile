all: build

build:
	mkdir -p dist
	gcc src/main.c -o dist/cyprint

install:
	[ -f dist/cyprint ] || (echo Please build first; exit 1)
	sudo cp dist/cyprint /usr/bin/cyprint

uninstall: 
	sudo rm -f /usr/bin/cyprint
