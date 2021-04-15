all: debug

.PHONY:
debug:
	cmake . -B build -G Ninja
	ninja -C build

.PHONY:
release:
	cmake . -B build -G Ninja -DCMAKE_BUILD_TYPE=Release
	ninja -C build

.PHONY:
clean:
	rm -rf bin
	rm -rf build

.PHONY:
run: all
	./bin/neumann

test: debug
	./bin/test_neumann
