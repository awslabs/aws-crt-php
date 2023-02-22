
@echo on

cd ..

%PHP_BINARY% -c php-win.ini vendor/bin/phpunit tests --debug
