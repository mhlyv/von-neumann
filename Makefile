all:
	cmake . -B build -G Ninja
	ninja -C build

.PHONY:
clean:
	rm -rf bin
	rm -rf build

.PHONY:
run: all
	./bin/neumann

test: all
	./bin/test_neumann
