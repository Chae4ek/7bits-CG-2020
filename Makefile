ifeq ($(OS), Windows_NT)
	build = win
	build_fast = fast_win
else
	build = lin_mac
	build_fast = fast_lm
endif

all: $(build) $(build_fast)

fast: $(build_fast)

lin_mac:
	rm -rf build && rm -rf bin

fast_lm:
	mkdir -p build && cd build && cmake .. && make && mv game ../bin && cd ../bin && ./game

win:
	rd /s /q build & rd /s /q bin &

fast_win:
	mkdir build & cd build && cmake -G "MinGW Makefiles" .. && mingw32-make && move game.exe ../bin && cd ../bin && game.exe