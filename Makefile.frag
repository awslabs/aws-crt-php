
INT_DIR=$(builddir)/build/install
CMAKE_BUILD_DIR=$(builddir)/cmake_build
GENERATE_STUBS=$(shell expr `php --version | head -1 | cut -f 2 -d' '` \>= 7.1)

CMAKE = cmake3
ifeq (, $(shell which cmake3))
	CMAKE = cmake
endif

# default to using system OpenSSL, if disabled aws-lc will be used
USE_OPENSSL ?= ON
ifneq (OFF,$(USE_OPENSSL))
	CMAKE_USE_OPENSSL=-DUSE_OPENSSL=ON
	# if a path was provided, add it to CMAKE_PREFIX_PATH
	ifneq (ON,$(USE_OPENSSL))
    	CMAKE_PREFIX_PATH=-DCMAKE_PREFIX_PATH=$(USE_OPENSSL)
	endif
else
	# Hide symbols from libcrypto.a
	# This avoids problems when an application ends up using both libcrypto.a and libcrypto.so.
	#
	# An example of this happening is the aws-c-io tests.
	# All the C libs are compiled statically, but then a PKCS#11 library is
	# loaded at runtime which happens to use libcrypto.so from OpenSSL.
	# If the symbols from libcrypto.a aren't hidden, then SOME function calls use the libcrypto.a implementation
	# and SOME function calls use the libcrypto.so implementation, and this mismatch leads to weird crashes.
	EXTRA_LDFLAGS="-Wl,--exclude-libs,libcrypto.a"
endif


CMAKE_CONFIGURE = $(CMAKE) \
    -DCMAKE_SOURCE_DIR=$(srcdir) \
    -DCMAKE_BINARY_DIR=$(CMAKE_BUILD_DIR) \
    -DCMAKE_INSTALL_PREFIX=$(INT_DIR) \
    -DBUILD_TESTING=OFF \
    -DCMAKE_BUILD_TYPE=$(CMAKE_BUILD_TYPE) \
    $(CMAKE_USE_OPENSSL) \
    $(CMAKE_PREFIX_PATH)
CMAKE_BUILD = CMAKE_BUILD_PARALLEL_LEVEL='' $(CMAKE) --build
CMAKE_BUILD_TYPE ?= RelWithDebInfo
CMAKE_TARGET = --config $(CMAKE_BUILD_TYPE) --target install

all: extension
.PHONY: all extension

# configure for static aws-crt-ffi.a
$(CMAKE_BUILD_DIR)/aws-crt-ffi-static/CMakeCache.txt:
	$(CMAKE_CONFIGURE) -H$(srcdir)/crt/aws-crt-ffi -B$(CMAKE_BUILD_DIR)/aws-crt-ffi-static -DBUILD_SHARED_LIBS=OFF

# build static libaws-crt-ffi.a
$(CMAKE_BUILD_DIR)/aws-crt-ffi-static/libaws-crt-ffi.a: $(CMAKE_BUILD_DIR)/aws-crt-ffi-static/CMakeCache.txt
	$(CMAKE_BUILD) $(CMAKE_BUILD_DIR)/aws-crt-ffi-static $(CMAKE_TARGET)

# PHP extension target
extension: $(builddir)/ext/awscrt.lo

# Force the crt object target to depend on the CRT static library
$(builddir)/ext/awscrt.lo: $(builddir)/ext/awscrt.c

$(builddir)/ext/awscrt.c: $(CMAKE_BUILD_DIR)/aws-crt-ffi-static/libaws-crt-ffi.a $(builddir)/ext/api.h $(builddir)/ext/awscrt_arginfo.h

$(builddir)/ext/awscrt_arginfo.h: $(srcdir)/ext/awscrt.stub.php $(srcdir)/gen_stub.php
ifeq ($(GENERATE_STUBS),1)
	# generate awscrt_arginfo.h
	mkdir -p $(builddir)/ext && php $(srcdir)/gen_stub.php --minimal-arginfo $(srcdir)/ext/awscrt.stub.php
endif

# transform/install api.h from FFI lib
$(srcdir)/ext/api.h: $(srcdir)/crt/aws-crt-ffi/src/api.h
	php $(srcdir)/gen_api.php $(srcdir)/crt/aws-crt-ffi/src/api.h > $(srcdir)/ext/api.h

# install api.h to ext/ as well
$(builddir)/ext/api.h : $(srcdir)/ext/api.h
	mkdir -p $(builddir)/ext

$(builddir)/ext/php_aws_crt.h: $(srcdir)/ext/awscrt_arginfo.h $(srcdir)/ext/api.h

vendor/bin/phpunit:
	composer update

test-extension: vendor/bin/phpunit extension
	composer run test-extension

# Use PHPUnit to run tests
test: test-extension
