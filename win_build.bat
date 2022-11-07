@echo on

echo %CD%

call phpsdk_buildtree phpmaster

git clone https://github.com/php/php-src.git && cd php-src

call phpsdk_deps --update --branch master

echo %CD%

cd ../../ && ls