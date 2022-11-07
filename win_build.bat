@echo on

cd ../

echo %CD%

set SOURCE_DIR=%CD%\aws-crt-php

call phpsdk_buildtree phpmaster

git clone https://github.com/php/php-src.git && cd php-src

call phpsdk_deps --update --branch master

robocopy %SOURCE_DIR% ..\pecl\awscrt /E

buildconf

configure --enable-cli --with-openssl --enable-awscrt=shared

nmake