all:

linux:
	rm -rf build && mkdir build && cd build && cmake .. && make && mv game ../bin && cd ../bin/ && ./game

win:
	rd /s /q build & mkdir build && cd build && cmake ..