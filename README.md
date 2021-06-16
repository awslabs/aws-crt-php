# AWS Common Runtime PHP bindings

## Requirements
* PHP 5.5+ on UNIX platforms, 7.2+ on Windows
* CMake 3.x
* GCC 4.4+, clang 3.8+ on UNIX, Visual Studio 2017 build tools on Windows
* Tests require [Composer](https://getcomposer.org)

## Building on UNIX
```sh
$ git clone --recursive https://github.com/awslabs/aws-crt-php.git
$ cd aws-crt-php
$ phpize
$ ./configure
$ make && make test
```

## Building on Windows
* First, ensure that you are able to build PHP on windows via the PHP SDK (this example assumes installation of the SDK to C:\php-sdk and that you've checked out the PHP source to php-src within the build directory). The following are hopeful
    * https://github.com/microsoft/php-sdk-binary-tools
    * https://medium.com/@erinus/how-to-build-php-on-windows-a7ad0a87862a
    * https://medium.com/@erinus/how-to-build-php-extension-on-windows-d1667290f809

```bat
""" From VS2017 Command Prompt
> C:\php-sdk\phpsdk-vc15-x64.bat

C:\php-sdk\
$ phpsdk_buildtree php-<version>

C:\php-sdk\php-<version>\vc15\x64\
$ git clone https://github.com/php/php-src.git && cd php-src

""" This only has to be done once, the first time you set this all up
C:\php-sdk\php-<version>\vc15\x64\php-src
$ phpsdk_deps --update --branch <php-major.minor-version>

C:\php-sdk\php-<version>\vc15\x64\php-src
$ git clone --recursive https://github.com/awslabs/aws-crt-php.git ..\pecl\awscrt

C:\php-sdk\php-<version>\vc15\x64\php-src
$ buildconf

C:\php-sdk\php-<version>\vc15\x64\php-src
$ configure --disable-all --enable-cli --enable-awscrt=shared

C:\php-sdk\php-<version>\vc15\x64\php-src
$ nmake
```

## Security

See [CONTRIBUTING](CONTRIBUTING.md#security-issue-notifications) for more information.

## License

This project is licensed under the Apache-2.0 License.
