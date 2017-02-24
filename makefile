CC=g++
OUTDIR=build
INSTALLDIR=/usr/lib/mysql/plugin
MYUSER=root
MYHOST=localhost
USEMYPASS=1
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
ifeq ($(USEMYPASS), 1)
	mysql -u$(MYUSER) -p -h$(MYHOST) -e "CREATE FUNCTION sendmail RETURNS INTEGER SONAME 'libmyemail.so';" 
else 
	mysql -u$(MYUSER) -h$(MYHOST) -e "CREATE FUNCTION sendmail RETURNS INTEGER SONAME 'libmyemail.so';"	
endif

uninstall:
ifeq ($(USEMYPASS), 1)
	mysql -u$(MYUSER) -p -h$(MYHOST) -e "DROP FUNCTION sendmail;" 
else 
	mysql -u$(MYUSER) -h$(MYHOST) -e "DROP FUNCTION sendmail;"	
endif
	systemctl restart $(MYSQLUNIT)
	rm $(INSTALLDIR)/libmyemail.so

