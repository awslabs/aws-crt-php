@echo on

phpsdk_buildtree php-8.1

git clone https://github.com/php/php-src.git && cd php-src

phpsdk_deps --update --branch 8.1