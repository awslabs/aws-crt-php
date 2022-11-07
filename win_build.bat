@echo on

@REM Passing the source dirctory of aws-crt-php, if not passing the source directory, it will be pulled from github
if not (%1)==() set SOURCE_DIR=%1

call phpsdk_buildtree phpmaster

git clone https://github.com/php/php-src.git && cd php-src

call phpsdk_deps --update --branch master

if (%SOURCE_DIR%)==() (git clone --recursive https://github.com/awslabs/aws-crt-php.git ..\pecl\awscrt) else (robocopy %SOURCE_DIR% ..\pecl\awscrt /E)

call buildconf

call configure --enable-cli --with-openssl --enable-awscrt=shared

call nmake

@REM call nmake test-awscrt
