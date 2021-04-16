all: debug

.PHONY:
debug:
	cmake . -B build/debug -G Ninja
	ninja -C build/debug

.PHONY:
release:
	cmake . -B build/release -G Ninja -DCMAKE_BUILD_TYPE=Release
	ninja -C build/release

.PHONY:
clean:
	rm -rf build
