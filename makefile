GXX=g++
exectest=exectest
tests=run
libs=-lgtest
sources=./circular-buffer.cpp \
		./circular-buffer.hpp \

.PHONY: clean exec-test

all:
	$(GXX) $(libs) $(sources) ./tests.cpp -o $(tests)

exec-test:
	$(GXX) $(sources) ./execution-time-test.cpp -o $(exectest)
	
clean:
	rm -rf $(exectest) $(tests)
