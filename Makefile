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
	rm -rf build
