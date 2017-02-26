## libmyemail

### Installation

1. Install dependencies
  - For MySQL: ```libmysqlclient``` or your distribution equivalent
  - For Maria DB: ```libmariadbclient``` or your distribution equivalent
  - install and configure any smtp application that uses the mail command
    - recommended ```ssmtp```
    - Also works with ```sendmail``` and ```postfix```
2. Configure the makefile to build for your system
  - Set ```INSTALLDIR``` to the plugin directory for your installation
  - Set ```MYUSER``` to your mysql user
  - Set ```MYHOST``` to the mysql installation host
  - Set ```USEMYPASS``` to 1 for password login or 0 for no password
  - Set ```MYSQLUNIT``` to the systemd unit that can start and stop the server
3. Build and install
```
$ make
# make install
$ make clean
```
4. (optional) Send test email
```
mysql> sendmail('test@example.com','subject','email body');
```

### Uninstall

```
# make uninstall
```
