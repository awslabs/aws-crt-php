
BUILD_DIR=build
INT_DIR=$(BUILD_DIR)/install
GENERATE_STUBS=$(shell expr `php --version | head -1 | cut -f 2 -d' '` \>= 7.1)

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
awscrt: ext/awscrt.lo

# Force the crt object target to depend on the CRT static library
ext/awscrt.lo: ext/awscrt.c

ext/awscrt.c: $(BUILD_DIR)/aws-crt-ffi-static/libaws-crt-ffi.a ext/api.h ext/awscrt_arginfo.h

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
ffi: src/libaws-crt-ffi.so

# copy the lib into the src folder
modules/libaws-crt-ffi.so: $(BUILD_DIR)/aws-crt-ffi-shared/libaws-crt-ffi.so src/api.h
	cp -v $(BUILD_DIR)/aws-crt-ffi-shared/libaws-crt-ffi.so modules/libaws-crt-ffi.so

# Use PHPUnit to run tests
test: ext/api.h ext/awscrt_arginfo.h ext/awscrt.lo
	composer update
	composer run test
