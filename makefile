CC=g++
OUTDIR=build
INSTALLDIR=/usr/lib/mysql/plugin

build: 
	if [ ! -d "$(OUTDIR)" ]; then \
		mkdir $(OUTDIR); \
	fi
	$(CC) -std=c++11 -fPIC -c libmyemail.cc -o $(OUTDIR)/libmyemail.o
	$(CC) -std=c++11 -shared -o build/libmyemail.so $(OUTDIR)/libmyemail.o

clean:
	rm -rf $(OUTDIR)

install:
	cp $(OUTDIR)/libmyemail.so $(INSTALLDIR)/libmyemail.so 
