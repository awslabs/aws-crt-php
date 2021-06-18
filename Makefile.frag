
INT_DIR=build/install
GENERATE_STUBS=$(shell expr `php --version | head -1 | cut -f 2 -d' '` \>= 7.1)
HAS_FFI=$(shell php -m | grep FFI | wc -l | xargs)

CMAKE = cmake3
ifeq (, $(shell which cmake3))
	CMAKE = cmake
endif

CMAKE_CONFIGURE = $(CMAKE) -DCMAKE_INSTALL_PREFIX=$(INT_DIR) -DBUILD_TESTING=OFF -DCMAKE_BUILD_TYPE=$(CMAKE_BUILD_TYPE)
CMAKE_BUILD = $(CMAKE) --build
CMAKE_BUILD_TYPE ?= RelWithDebInfo
CMAKE_TARGET = --config $(CMAKE_BUILD_TYPE) --target install

all: extension ffi
.PHONY: all extension ffi

# configure for static aws-crt-ffi.a
build/aws-crt-ffi-static/CMakeCache.txt:
	$(CMAKE_CONFIGURE) -Hcrt/aws-crt-ffi -Bbuild/aws-crt-ffi-static -DBUILD_SHARED_LIBS=OFF

# build static libaws-crt-ffi.a
build/aws-crt-ffi-static/libaws-crt-ffi.a: build/aws-crt-ffi-static/CMakeCache.txt
	$(CMAKE_BUILD) build/aws-crt-ffi-static $(CMAKE_TARGET)

# PHP extension target
extension: ext/awscrt.lo

# Force the crt object target to depend on the CRT static library
ext/awscrt.lo: ext/awscrt.c

ext/awscrt.c: build/aws-crt-ffi-static/libaws-crt-ffi.a ext/api.h ext/awscrt_arginfo.h

ext/awscrt_arginfo.h: ext/awscrt.stub.php gen_stub.php
ifeq ($(GENERATE_STUBS),1)
	# generate awscrt_arginfo.h
	php gen_stub.php --minimal-arginfo ext/awscrt.stub.php
endif

# transform/install api.h from FFI lib
src/api.h: crt/aws-crt-ffi/src/api.h
	php gen_api.php crt/aws-crt-ffi/src/api.h > src/api.h

# install api.h to ext/ as well
ext/api.h : src/api.h
	cp -v src/api.h ext/api.h

ext/php_aws_crt.h: ext/awscrt_arginfo.h ext/api.h

# FFI target
ffi: src/api.h src/libaws-crt-ffi.$(SHLIB_SUFFIX_NAME)

# configure for shared aws-crt-ffi.so
build/aws-crt-ffi-shared/CMakeCache.txt:
ifeq ($(HAS_FFI),1)
	$(CMAKE_CONFIGURE) -Hcrt/aws-crt-ffi -Bbuild/aws-crt-ffi-shared -DBUILD_SHARED_LIBS=ON
endif

# build shared libaws-crt-ffi.so
build/aws-crt-ffi-shared/libaws-crt-ffi.$(SHLIB_SUFFIX_NAME): build/aws-crt-ffi-shared/CMakeCache.txt
ifeq ($(HAS_FFI),1)
	$(CMAKE_BUILD) build/aws-crt-ffi-shared $(CMAKE_TARGET)
endif

# copy the lib into the src folder
src/libaws-crt-ffi.$(SHLIB_SUFFIX_NAME): build/aws-crt-ffi-shared/libaws-crt-ffi.$(SHLIB_SUFFIX_NAME) src/api.h
ifeq ($(HAS_FFI),1)
	cp -v build/aws-crt-ffi-shared/libaws-crt-ffi.$(SHLIB_SUFFIX_NAME) src/libaws-crt-ffi.$(SHLIB_SUFFIX_NAME)
endif

vendor/bin/phpunit:
	composer update

test-ffi: vendor/bin/phpunit ffi
ifeq ($(HAS_FFI),1)
	AWS_CRT_PHP_FFI=1 composer run test-ffi
endif

test-extension: vendor/bin/phpunit extension
	AWS_CRT_PHP_EXTENSION=1 composer run test-extension

# Use PHPUnit to run tests
test: test-ffi test-extension
