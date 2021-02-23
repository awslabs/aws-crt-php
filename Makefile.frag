
BUILD_DIR=$(shell pwd)/build
DEPS_DIR=$(BUILD_DIR)/deps
INT_DIR=$(BUILD_DIR)/install
INSTALL_DIR=$(shell pwd)
AT_LEAST_PHP7=$(shell expr `php --version | head -1 | cut -f 2 -d' '` \>= 7)

CMAKE = cmake3
ifeq (, $(shell which cmake3))
	CMAKE = cmake
endif

# download and build libcrypto.a for the CRT with -fPIC
$(DEPS_DIR)/openssl:
	@echo Fetching libcrypto source
	git clone --depth=1 --single-branch --branch OpenSSL_1_1_1-stable https://github.com/openssl/openssl.git $(DEPS_DIR)/openssl

$(INT_DIR)/lib/libcrypto.a: $(DEPS_DIR)/openssl
	@echo Building libcrypto
	cd $(DEPS_DIR)/openssl && \
		./config -fPIC no-md2 no-rc5 no-rfc3779 no-sctp no-ssl-trace no-zlib no-hw no-mdc2 no-seed no-idea \
			no-camellia no-bf no-dsa no-ssl3 no-capieng \
			-DSSL_FORBID_ENULL -DOPENSSL_NO_DTLS1 -DOPENSSL_NO_HEARTBEATS \
			--prefix=$(INT_DIR) --openssldir=$(INT_DIR) && \
		make -j && \
		make install_sw
	mkdir -p $(INT_DIR)/lib
	ln -s $(INT_DIR)/lib64/libcrypto.a $(INT_DIR)/lib/libcrypto.a || true

CMAKE_CONFIGURE = $(CMAKE) -DCMAKE_INSTALL_PREFIX=$(INT_DIR) -DCMAKE_PREFIX_PATH=$(INT_DIR) -DBUILD_TESTING=OFF
CMAKE_BUILD = $(CMAKE) --build
CMAKE_BUILD_TYPE ?= RelWithDebInfo
CMAKE_TARGET = --config $(CMAKE_BUILD_TYPE) --target install

# configure for shared aws-crt-ffi.so
$(BUILD_DIR)/aws-crt-ffi-shared/CMakeCache.txt: $(INT_DIR)/lib/libcrypto.a
	$(CMAKE_CONFIGURE) -Hcrt/aws-crt-ffi -Bbuild/aws-crt-ffi-shared -DBUILD_SHARED_LIBS=ON

# build shared libaws-crt-ffi.so
$(BUILD_DIR)/aws-crt-ffi-shared/libaws-crt-ffi.so: $(BUILD_DIR)/aws-crt-ffi-shared/CMakeCache.txt
	$(CMAKE_BUILD) build/aws-crt-ffi-shared $(CMAKE_TARGET)

# configure for static aws-crt-ffi.a
$(BUILD_DIR)/aws-crt-ffi-static/CMakeCache.txt: $(INT_DIR)/lib/libcrypto.a
	$(CMAKE_CONFIGURE) -Hcrt/aws-crt-ffi -Bbuild/aws-crt-ffi-static -DBUILD_SHARED_LIBS=OFF

# build static libaws-crt-ffi.a
$(BUILD_DIR)/aws-crt-ffi-static/libaws-crt-ffi.a: $(BUILD_DIR)/aws-crt-ffi-static/CMakeCache.txt
	$(CMAKE_BUILD) build/aws-crt-ffi-static $(CMAKE_TARGET)

# PHP extension target
extension: ext/crt.lo

# Force the crt object target to depend on the CRT static library
ext/crt.lo: $(BUILD_DIR)/aws-crt-ffi-static/libaws-crt-ffi.a ext/api.h ext/awscrt_arginfo.h

ifeq ($(AT_LEAST_PHP7),1)
	GEN_STUB=build/gen_stub.php
	# generate awscrt_arginfo.h
	ext/awscrt_arginfo.h: ext/awscrt.stub.php $(GEN_STUB)
		php $(GEN_STUB) ext/awscrt.stub.php

	# borrow the gen_stub script from PHP's build process
	$(GEN_STUB):
		curl -o $(GEN_STUB) -sSL https://raw.githubusercontent.com/php/php-src/bbb86ba7e2fe8ae365294d1834c6a392570a9dcd/build/gen_stub.php
endif

# transform/install api.h from FFI lib
src/api.h: crt/aws-crt-ffi/src/api.h
	cat crt/aws-crt-ffi/src/api.h | grep -v AWS_EXTERN_C | sed -e 's/AWS_CRT_API //' | grep -ve '^#' > src/api.h

# install api.h to ext/ as well
ext/api.h : src/api.h
	cp -v src/api.h ext/api.h

# FFI target
ffi: src/libaws-crt-ffi.so
	TEST_FFI = 1

# copy the lib into the src folder
src/libaws-crt-ffi.so: $(BUILD_DIR)/aws-crt-ffi-shared/libaws-crt-ffi.so $(INSTALL_DIR)/src/api.h
	cp -v $(BUILD_DIR)/aws-crt-ffi-shared/libaws-crt-ffi.so $(INSTALL_DIR)/src/libaws-crt-ffi.so

ifeq ($(TEST_FFI),1)
test-ci: test-ffi
else
test-ci: test
endif

# Test the FFI interface
test-ffi: src/libaws-crt-ffi.so
	composer update
	composer run test
