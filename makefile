CC=g++
OUTDIR=build
INSTALLDIR=/usr/lib/mysql/plugin
MYUSER=root
MYHOST=localhost
USEMYPASS=0
MYSQLUNIT=mariadb.service

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
	systemctl restart $(MYSQLUNIT)
	mysql -u$(MYUSER) -p -h$(MYHOST) -e "CREATE FUNCTION sendmail RETURNS INTEGER SONAME 'libmyemail.so';"

uninstall:
	mysql -u$(MYUSER) -p -h$(MYHOST) -e "DROP FUNCTION sendmail;"
	systemctl restart $(MYSQLUNIT)
	rm $(INSTALLDIR)/libmyemail.so

