# LOOKING FOR MAINTAINER

## libmyemail

### Installation

1. Install dependencies
  - GNU C++ Compiler or CLANG
  - cmake and make
  - For MySQL: ```libmysqlclient``` or your system equivalent
  - For Maria DB: ```libmariadbclient``` or your system equivalent
  - Install the following lib packages
    - ```libpoconet```
    - ```libpoconetssl```
    - ```libpocofoundation```
    - ```libssl```
2. Configure the cmake to build for your system
  - Set ```INSTALL_DIR``` to the plugin directory for your installation
    - DEFAULT: ```/usr/lib/mysql/plugin```
    - Example: ```cmake -DINSTALL_DIR=/path/to/install ...```
3. Build and install
```
$> mkdir build && cd build
$> cmake <install directory> ../source
$> make
#> make install
$> make clean
#> service mysql restart
$> mysql <login flags> -e "CREATE FUNCTION sendmail RETURNS STRING SONAME 'libmyemail.so';"
```
Note: convert to your systems commands

4. (optional) Send test email
```
mysql> SELECT sendmail(
                        '<from email address>'
                        ,'<comma delimited list or just one email address to send to>'
                        ,'<subject>'
                        ,'<email body>'
                        ,'<smtp server url>'
                        ,<port number>
                        ,'<username>'
                        ,'<password>'
                        ,<secure flag, set to 0 for plain smtp and 1 for TLS>
                      );
```

### Uninstall

```
$> mysql <login flags> -e "DROP FUNCTION sendmail;"
#> rm <install directory>/libmyemail.so
#> service mysql restart
```
Note: convert to your systems commands

### Issues
When you find an issue or something does not work the way you think it is supposed, feel free to make an issue. It will get a label from the repo creator  (or managers when we get more contributors) and someone will begin work on it. If it is an easy fix and is not breaking functionality, we will label for beginners and might wait to fix it until it annoys us enough or some one new to open source comes along and wants to fix it.

When making a new feature or making something work better still put in a issue stating that and it will get a feature or improvement label.

### Contribute
1. Fork this repo
2. Clone your version of the repo
3. pick an issue to fix or make an issue
4. make changes and push them to your repo
  - Mention the issue number in your commits like so
  ```
  git commit -m "git message - ## Ticket Number ##"
  ```
5. make a Pull Request tagging the issue number in the PR
6. congrats you have helped the community!
