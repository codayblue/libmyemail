CC=g++

all: 
	if [ ! -d "build" ]; then \
		mkdir build; \
	fi
	cd build
	$(CC) -fPIC -c ../libmyemail.cc -o libmyemail.o
	$(CC) -shared -o libmyemail.so libmyemail.o
