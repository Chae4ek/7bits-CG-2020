all:

linux:
	rm -rf build && rm -rf bin && mkdir build && cd build && cmake .. && make && mv game ../bin && cd ../bin && ./game

win:
	rd /s /q build & rd /s /q bin & mkdir build && cd build && cmake -G "MinGW Makefiles" .. && mingw32-make && move game.exe ../bin && cd ../bin && game.exe

mac: linux