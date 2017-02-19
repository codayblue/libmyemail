CC=g++

all: 
	if [ ! -d "build" ]; then \
		mkdir build; \
	fi
	cd build
	$(CC) -fPIC -c libmyemail.cc -o build/libmyemail.o
	$(CC) -shared -o build/libmyemail.so build/libmyemail.o
