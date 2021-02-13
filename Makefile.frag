
BUILD_DIR=$(shell pwd)/build
DEPS_DIR=$(BUILD_DIR)/deps
INT_DIR=$(BUILD_DIR)/install
INSTALL_DIR=$(shell pwd)

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

# cmake configure depends on libcrypto above
$(BUILD_DIR)/aws-crt-ffi/CMakeCache.txt: $(INT_DIR)/lib/libcrypto.a
	$(CMAKE_CONFIGURE) -Hcrt/aws-crt-ffi -Bbuild/aws-crt-ffi

# build the FFI library
$(BUILD_DIR)/aws-crt-ffi/libaws-crt-ffi.so: $(BUILD_DIR)/aws-crt-ffi/CMakeCache.txt
	$(CMAKE_BUILD) build/aws-crt-ffi $(CMAKE_TARGET)

# copy the lib into the lib folder
$(INSTALL_DIR)/lib/libaws-crt-ffi.so: $(BUILD_DIR)/aws-crt-ffi/libaws-crt-ffi.so $(INSTALL_DIR)/lib/api.h
	cp -v $(BUILD_DIR)/aws-crt-ffi/libaws-crt-ffi.so $(INSTALL_DIR)/lib/libaws-crt-ffi.so

# install api.h from FFI lib
$(INSTALL_DIR)/lib/api.h: crt/aws-crt-ffi/src/api.h
	cat crt/aws-crt-ffi/src/api.h | grep -v AWS_EXTERN_C | sed -e 's/AWS_CRT_API //' | grep -ve '^#' > $(INSTALL_DIR)/lib/api.h

# Force the crt object target to depend on the FFI library
src/crt.lo: $(INSTALL_DIR)/lib/libaws-crt-ffi.so

ifeq($(TEST_FFI),1)
test-ci: test-ffi
else
test-ci: test
endif

# Test the FFI interface
test-ffi: $(INSTALL_DIR)/lib/libaws-crt-ffi.so
	composer update
	composer run test
