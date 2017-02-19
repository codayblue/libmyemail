CC=g++
OUTDIR=build

build: 
	if [ ! -d "$(OUTDIR)" ]; then \
		mkdir $(OUTDIR); \
	fi
	cd $(OUTDIR)
	$(CC) -fPIC -c libmyemail.cc -o $(OUTDIR)/libmyemail.o
	$(CC) -shared -o build/libmyemail.so $(OUTDIR)/libmyemail.o

clean:
	rm -rf $(OUTDIR)
