@echo on

git clone https://github.com/Microsoft/php-sdk-binary-tools.git php-sdk
cd ./php-sdk

./phpsdk-vs16-x64.bat

phpsdk_buildtree php-8.1

git clone https://github.com/php/php-src.git && cd php-src

phpsdk_deps --update --branch 8.1