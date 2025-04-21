pthread-wrapper-test: pthread-wrapper-test.cc libpthread-wrapper.so
	g++ -o $@ $^ -std=c++23 -lpthread-wrapper -I../include -Wl,-rpath=. -L. -Wall -Wextra

pthread-wrapper.o: pthread-wrapper.c
	gcc -o $@ $^ -std=c23 -fPIC -c -Wall -Wextra

libpthread-wrapper.so: pthread-wrapper.o
	gcc -o $@ $^ -shared

clean:
	rm -fr libpthread-wrapper.so pthread-wrapper.o pthread-wrapper-test

.PHONY: clean
