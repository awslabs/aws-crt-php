@echo on

call phpsdk_buildtree php-7.4

git clone https://github.com/php/php-src.git && cd php-src

phpsdk_deps --update --branch 7.4