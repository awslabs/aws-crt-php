
BUILD_DIR=$(shell pwd)/build
DEPS_DIR=$(BUILD_DIR)/deps
INT_DIR=$(BUILD_DIR)/install
INSTALL_DIR=$(shell pwd)
AT_LEAST_PHP7=$(shell expr `php --version | head -1 | cut -f 2 -d' '` \>= 7)

CMAKE = cmake3
ifeq (, $(shell which cmake3))
	CMAKE = cmake
endif

CMAKE_CONFIGURE = $(CMAKE) -DCMAKE_INSTALL_PREFIX=$(INT_DIR) -DCMAKE_PREFIX_PATH=$(INT_DIR) -DBUILD_TESTING=OFF -DCMAKE_BUILD_TYPE=$(CMAKE_BUILD_TYPE)
CMAKE_BUILD = $(CMAKE) --build
CMAKE_BUILD_TYPE ?= RelWithDebInfo
CMAKE_TARGET = --config $(CMAKE_BUILD_TYPE) --target install

# configure for shared aws-crt-ffi.so
$(BUILD_DIR)/aws-crt-ffi-shared/CMakeCache.txt:
	$(CMAKE_CONFIGURE) -Hcrt/aws-crt-ffi -Bbuild/aws-crt-ffi-shared -DBUILD_SHARED_LIBS=ON

# build shared libaws-crt-ffi.so
$(BUILD_DIR)/aws-crt-ffi-shared/libaws-crt-ffi.so: $(BUILD_DIR)/aws-crt-ffi-shared/CMakeCache.txt
	$(CMAKE_BUILD) build/aws-crt-ffi-shared $(CMAKE_TARGET)

# configure for static aws-crt-ffi.a
$(BUILD_DIR)/aws-crt-ffi-static/CMakeCache.txt:
	$(CMAKE_CONFIGURE) -Hcrt/aws-crt-ffi -Bbuild/aws-crt-ffi-static -DBUILD_SHARED_LIBS=OFF

# build static libaws-crt-ffi.a
$(BUILD_DIR)/aws-crt-ffi-static/libaws-crt-ffi.a: $(BUILD_DIR)/aws-crt-ffi-static/CMakeCache.txt
	$(CMAKE_BUILD) build/aws-crt-ffi-static $(CMAKE_TARGET)

# PHP extension target
awscrt: modules/awscrt.la

# Force the crt object target to depend on the CRT static library
ext/awscrt.lo: ext/awscrt.c

ext/awscrt.c: $(BUILD_DIR)/aws-crt-ffi-static/libaws-crt-ffi.a ext/api.h ext/awscrt_arginfo.h

# borrow the gen_stub script from PHP's build process
GEN_STUB=build/gen_stub.php
$(GEN_STUB):
	curl -o $(GEN_STUB) -sSL https://raw.githubusercontent.com/php/php-src/bbb86ba7e2fe8ae365294d1834c6a392570a9dcd/build/gen_stub.php

ext/awscrt_arginfo.h: ext/awscrt.stub.php $(GEN_STUB)
ifeq ($(AT_LEAST_PHP7),1)
	# generate awscrt_arginfo.h
	php $(GEN_STUB) ext/awscrt.stub.php
endif

# transform/install api.h from FFI lib
src/api.h: crt/aws-crt-ffi/src/api.h
	cat crt/aws-crt-ffi/src/api.h | grep -v AWS_EXTERN_C | sed -e 's/AWS_CRT_API //' | grep -ve '^#' > src/api.h

# install api.h to ext/ as well
ext/api.h : src/api.h
	cp -v src/api.h ext/api.h

ext/php_aws_crt.h: ext/awscrt_arginfo.h ext/api.h

# FFI target
ffi: src/libaws-crt-ffi.so

# copy the lib into the src folder
modules/libaws-crt-ffi.so: $(BUILD_DIR)/aws-crt-ffi-shared/libaws-crt-ffi.so src/api.h
	cp -v $(BUILD_DIR)/aws-crt-ffi-shared/libaws-crt-ffi.so modules/libaws-crt-ffi.so

# Use PHPUnit to run tests
test: ext/api.h ext/awscrt_arginfo.h modules/awscrt.la
	composer update
	composer run test
